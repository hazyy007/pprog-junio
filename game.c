#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"
#include "game_actions.h"

struct _Game {
    Player *player;
    Space *spaces[MAX_SPACES];
    Object *objects[MAX_OBJECTS];
    Character *characters[MAX_CHARACTERS];
    Link *links[MAX_LINKS];
    
    Command *last_cmd;
    int turn;
    
    char chat_message[WORD_SIZE];
    char object_desc[WORD_SIZE];
};

Game* game_create() {
    Game *game = NULL;
    int i;

    game = (Game*)malloc(sizeof(Game));
    if (!game) return NULL;

    game->player = NULL;
    for (i = 0; i < MAX_SPACES; i++) game->spaces[i] = NULL;
    for (i = 0; i < MAX_OBJECTS; i++) game->objects[i] = NULL;
    for (i = 0; i < MAX_CHARACTERS; i++) game->characters[i] = NULL;
    for (i = 0; i < MAX_LINKS; i++) game->links[i] = NULL;

    game->last_cmd = command_create();
    game->turn = 0;
    
    game->chat_message[0] = '\0';
    game->object_desc[0] = '\0';

    return game;
}

Status game_create_from_file(Game* game, char* filename) {
    if (!game || !filename) return ERROR;

    if (game_reader_load_spaces(game, filename) == ERROR) return ERROR;
    if (game_reader_load_links(game, filename) == ERROR) return ERROR;
    if (game_reader_load_objects(game, filename) == ERROR) return ERROR;
    if (game_reader_load_characters(game, filename) == ERROR) return ERROR;
    if (game_reader_load_players(game, filename) == ERROR) return ERROR;

    return OK;
}

void game_destroy(Game* game) {
    int i;
    if (!game) return;

    if (game->player) player_destroy(game->player);
    for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) space_destroy(game->spaces[i]);
    for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) object_destroy(game->objects[i]);
    for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) character_destroy(game->characters[i]);
    for (i = 0; i < MAX_LINKS && game->links[i] != NULL; i++) link_destroy(game->links[i]);

    command_destroy(game->last_cmd);
    free(game);
}

BOOL game_is_over(Game* game) {
    if (!game) return TRUE;
    /* Si el jugador muere, el juego termina */
    if (game->player && player_get_health(game->player) <= 0) return TRUE;
    return FALSE;
}

Status game_update(Game* game, Command* cmd) {
    Status status = ERROR;
    if (!game || !cmd) return ERROR;

    command_set_code(game->last_cmd, command_get_code(cmd));
    command_set_arg(game->last_cmd, command_get_arg(cmd));

    status = game_actions_update(game, cmd);
    
    if (status == OK && command_get_code(cmd) != UNKNOWN && command_get_code(cmd) != EXIT) {
        game->turn++;
    }

    return status;
}


Command* game_get_last_command(Game* game) { return game->last_cmd; }
int game_get_turn(Game* game) { return game->turn; }
Status game_add_space(Game* game, Space* space) { 
    int i;
    for(i=0; i<MAX_SPACES; i++) {
        if(!game->spaces[i]) { game->spaces[i] = space; return OK; }
    }
    return ERROR; 
}
Space* game_get_space(Game* game, Id id) {
    int i;
    if (id == NO_ID) return NULL;
    for (i = 0; i < MAX_SPACES && game->spaces[i]; i++) {
        if (id == space_get_id(game->spaces[i])) return game->spaces[i];
    }
    return NULL;
}
Status game_set_player(Game* game, Player* player) { game->player = player; return OK; }
Player* game_get_player(Game* game) { return game->player; }
Id game_get_player_location(Game* game) { return player_get_location(game->player); }

/* --- GETTERS / SETTERS ENTIDADES --- */
Status game_add_object(Game* game, Object* object) {
    int i;
    for(i=0; i<MAX_OBJECTS; i++) {
        if(!game->objects[i]) { game->objects[i] = object; return OK; }
    }
    return ERROR;
}
Object* game_get_object(Game* game, Id id) {
    int i;
    if (id == NO_ID) return NULL;
    for(i=0; i<MAX_OBJECTS && game->objects[i]; i++) {
        if (id == object_get_id(game->objects[i])) return game->objects[i];
    }
    return NULL;
}
Status game_set_object_location(Game* game, Id location, Id object_id) {
    Space *s = game_get_space(game, location);
    if (!s) return ERROR;
    return space_add_object(s, object_id);
}
Id game_get_object_location(Game* game, Id object_id) {
    int i;
    /* Comprobar espacios */
    for(i=0; i<MAX_SPACES && game->spaces[i]; i++) {
        if(space_has_object(game->spaces[i], object_id)) return space_get_id(game->spaces[i]);
    }
    /* Comprobar mochila jugador */
    if (inventory_has_id(player_get_backpack(game->player), object_id)) return player_get_id(game->player);
    return NO_ID;
}

Status game_add_character(Game* game, Character* character) {
    int i;
    for(i=0; i<MAX_CHARACTERS; i++) {
        if(!game->characters[i]) { game->characters[i] = character; return OK; }
    }
    return ERROR;
}
Character* game_get_character(Game* game, Id id) {
    int i;
    if (id == NO_ID) return NULL;
    for(i=0; i<MAX_CHARACTERS && game->characters[i]; i++) {
        if (id == character_get_id(game->characters[i])) return game->characters[i];
    }
    return NULL;
}
Status game_set_character_location(Game* game, Id location, Id character_id) {
    Space *s = game_get_space(game, location);
    if (!s) return ERROR;
    return space_set_character(s, character_id);
}
Id game_get_character_location(Game* game, Id character_id) {
    int i;
    for(i=0; i<MAX_SPACES && game->spaces[i]; i++) {
        if(space_get_character(game->spaces[i]) == character_id) return space_get_id(game->spaces[i]);
    }
    return NO_ID;
}

Status game_add_link(Game* game, Link* link) {
    int i;
    for(i=0; i<MAX_LINKS; i++) {
        if(!game->links[i]) { game->links[i] = link; return OK; }
    }
    return ERROR;
}
Link* game_get_link(Game* game, Id id) {
    int i;
    if (id == NO_ID) return NULL;
    for(i=0; i<MAX_LINKS && game->links[i]; i++) {
        if (id == link_get_id(game->links[i])) return game->links[i];
    }
    return NULL;
}
Id game_get_connection(Game* game, Id space_id, Directions dir) {
    int i;
    Link *link;
    for(i=0; i<MAX_LINKS && game->links[i]; i++) {
        link = game->links[i];
        if(link_get_origin(link) == space_id && link_get_direction(link) == dir && link_get_open(link)) {
            return link_get_destination(link);
        }
    }
    return NO_ID;
}

Status game_set_chat_message(Game* game, char* message) {
    if (!game || !message) return ERROR;
    strcpy(game->chat_message, message);
    return OK;
}
const char* game_get_chat_message(Game* game) { return game->chat_message; }

Status game_set_object_desc(Game* game, char* desc) {
    if (!game || !desc) return ERROR;
    strcpy(game->object_desc, desc);
    return OK;
}
const char* game_get_object_desc(Game* game) { return game->object_desc; }