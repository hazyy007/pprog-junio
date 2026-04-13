#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_actions.h"

static void game_action_move(Game* game, Directions dir);
static void game_action_take(Game* game, Command* cmd);
static void game_action_drop(Game* game, Command* cmd);
static void game_action_attack(Game* game);
static void game_action_chat(Game* game);
static void game_action_inspect(Game* game, Command* cmd);

Status game_actions_update(Game* game, Command* cmd) {
    CommandCode ncmd;
    if (!game || !cmd) return ERROR;

    ncmd = command_get_code(cmd);

    switch (cmd)
  {
    case UNKNOWN:
        game_actions_unknown(game);
        break;

    case EXIT:
        game_actions_exit(game);
        break;

    case TAKE:
        game_actions_take(game);
        break;

    case DROP:
        game_actions_drop(game);
        break;

    case ATTACK:
        game_actions_attack(game);
        break;

    case INSPECT:
        game_actions_inspect(game, cmd);
        break;

    case MOVE:
        game_action_move(game, command_get_arg(cmd)[0]);
        break;

    case CHAT:
        game_actions_chat(game);
        break;

    default:
        break;
  }

  return OK;
}

static void game_action_move(Game* game, Directions dir) {
    Id p_loc = game_get_player_location(game);
    Id dest = game_get_connection(game, p_loc, dir);
    Space *dest_space;

    if (dest != NO_ID) {
        player_set_location(game_get_player(game), dest);
        dest_space = game_get_space(game, dest);
        if (dest_space) space_set_discovered(dest_space, TRUE);
    }
}

static void game_action_take(Game* game, Command* cmd) {
    Id p_loc = game_get_player_location(game);
    Space *s = game_get_space(game, p_loc);
    char *arg = command_get_arg(cmd);
    Id *objs;
    int n_objs, i;
    Object *target_obj = NULL;

    if (!s || !arg) return;

    objs = space_get_objects(s);
    n_objs = space_get_number_of_objects(s);

    /* Buscar el objeto en la sala por nombre */
    for (i = 0; i < n_objs; i++) {
        Object *o = game_get_object(game, objs[i]);
        if (o && strcasecmp(object_get_name(o), arg) == 0) {
            target_obj = o;
            break;
        }
    }

    if (!target_obj) {
        game_set_chat_message(game, "Object not found here.");
        return;
    }

    if (object_get_movable(target_obj) == FALSE) {
        game_set_chat_message(game, "You cannot move this object.");
        return;
    }

    /* Intentar meterlo en la mochila */
    if (player_add_object(game_get_player(game), object_get_id(target_obj)) == OK) {
        space_remove_object(s, object_get_id(target_obj));
        game_set_chat_message(game, "You took the object.");
    } else {
        game_set_chat_message(game, "Your backpack is full!");
    }
}

static void game_action_drop(Game* game, Command* cmd) {
    Id p_loc = game_get_player_location(game);
    Space *s = game_get_space(game, p_loc);
    char *arg = command_get_arg(cmd);
    Player *player = game_get_player(game);
    Inventory *inv = player_get_backpack(player);
    int i, n_objs;
    Object *target_obj = NULL;

    if (!s || !arg) return;

    n_objs = inventory_get_num_objs(inv);
    
    for (i = 0; i < n_objs; i++) {
        Id obj_id = inventory_get_id_at(inv, i);
        Object *o = game_get_object(game, obj_id);
        if (o && strcasecmp(object_get_name(o), arg) == 0) {
            target_obj = o;
            break;
        }
    }

    if (target_obj) {
        player_remove_object(player, object_get_id(target_obj));
        space_add_object(s, object_get_id(target_obj));
        game_set_chat_message(game, "You dropped the object.");
    } else {
        game_set_chat_message(game, "You don't have that object.");
    }
}

static void game_action_attack(Game* game) {
    Id p_loc = game_get_player_location(game);
    Space *s = game_get_space(game, p_loc);
    Id c_id;
    Character *c;
    Player *p = game_get_player(game);

    if (!s) return;

    c_id = space_get_character(s);
    if (c_id == NO_ID) {
        game_set_chat_message(game, "There is no one here to attack.");
        return;
    }

    c = game_get_character(game, c_id);
    if (!c) return;

    /* Combate simple: jugador golpea 1, recibe 1 (o modificado por armas) */
    character_set_health(c, character_get_health(c) - 1);
    
    if (character_get_health(c) <= 0) {
        game_set_chat_message(game, "You defeated the enemy!");
        space_set_character(s, NO_ID); /* Muere y desaparece de la sala */
    } else {
        /* Contraataque */
        player_set_health(p, player_get_health(p) - 1);
        game_set_chat_message(game, "You attacked! The enemy hit you back.");
    }
}

static void game_action_chat(Game* game) {
    Id p_loc = game_get_player_location(game);
    Space *s = game_get_space(game, p_loc);
    Id c_id;
    Character *c;
    char buffer[WORD_SIZE];

    if (!s) return;

    c_id = space_get_character(s);
    if (c_id == NO_ID) {
        game_set_chat_message(game, "Silence. No one is here.");
        return;
    }

    c = game_get_character(game, c_id);
    if (c) {
        sprintf(buffer, "%s says: \"%s\"", character_get_name(c), character_get_message(c));
        game_set_chat_message(game, buffer);
    }
}

static void game_action_inspect(Game* game, Command* cmd) {
    char *arg = command_get_arg(cmd);
    Player *p = game_get_player(game);
    Space *s = game_get_space(game, player_get_location(p));
    /* Lógica simplificada: buscar si el argumento coincide con "space" o "s" 
       o con un objeto en la sala / mochila e imprimir su descripción */
    if (!arg) return;
    
    if (strcasecmp(arg, "s") == 0 || strcasecmp(arg, "space") == 0) {
        /* Imprimir descripción iluminada o oscura si fuera un texto */
        game_set_object_desc(game, "You inspect the space carefully.");
    } else {
        /* Aquí iría el for loop para buscar el objeto por nombre y setear su object_desc */
        game_set_object_desc(game, "You inspect the item.");
    }
}