/**
 * @brief implemneta el motor gráfico textual
 *
 * @file graphic_engine.h
 * @author Alejandro Domínguez
 * @version 3.0
 * @copyright GNU Public License
 */

 #include "graphic_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "character.h"
#include "player.h"
#include "object.h"

#define WIDTH_MAP 60
#define WIDTH_DES 55
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3
#define MAX_OBJECTS 100
#define ROOM_WIDTH 15

struct _Graphic_engine {
    Area *map, *descript, *banner, *help, *feedback;
};

void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act);
Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);

Graphic_engine *graphic_engine_create() {
    static Graphic_engine *ge = NULL;
    if (ge) return ge;

    screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
    ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
    if (ge == NULL) return NULL;

    ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
    ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
    ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
    ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
    ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

    return ge;
}

void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, BOOL is_act) {
    Space *west, *east;
    Character *character;
    Player *player;
    char str[255], west_str[85], middle_str[85], east_str[85], obj_list[ROOM_WIDTH + 1];
    const char *character_gdesc;
    char (*space_gdesc)[GDESC_COLS];
    int i;
    Status obj_list_status;
    BOOL west_disc = FALSE, east_disc = FALSE, middle_disc = FALSE;
    BOOL light_w = TRUE, light_c = TRUE, light_e = TRUE;

    if (!area || !middle) return;

    player = game_get_player(game);
    west = game_get_space(game, game_get_connection(game, space_get_id(middle), W));
    east = game_get_space(game, game_get_connection(game, space_get_id(middle), E));
    
    middle_disc = space_get_discovered(middle);

    /* Logica de iluminacion (Objeto 22 = Candelabro) */
    /* Asumimos que la función space_get_light y player_has_object existen basandonos en la fusion */
    if (space_get_light(middle) == FALSE && !inventory_has_id(player_get_backpack(player), 22)) light_c = FALSE;
    if (west && space_get_light(west) == FALSE && !inventory_has_id(player_get_backpack(player), 22)) light_w = FALSE;
    if (east && space_get_light(east) == FALSE && !inventory_has_id(player_get_backpack(player), 22)) light_e = FALSE;

    /* Borde superior */
    sprintf(west_str,  west ? "+---------------+  " : "                   ");
    sprintf(east_str,  east ? "  +---------------+" : "                   ");
    sprintf(str, "%s+---------------+%s", west_str, east_str);
    screen_area_puts(area, str);

    /* Fila IDs y Personajes */
    if (!west) sprintf(west_str, "                   ");
    else if (!(west_disc = space_get_discovered(west)) || !light_w) sprintf(west_str, "|            %3d|  ", (int)space_get_id(west));
    else {
        character = game_get_character(game, space_get_character(west));
        sprintf(west_str, "|     %s %3d|  ", character ? character_get_gdesc(character) : "      ", (int)space_get_id(west));
    }

    character = game_get_character(game, space_get_character(middle));
    if (middle_disc && light_c) {
        sprintf(middle_str, "| %s %s %3d|", is_act == TRUE ? player_get_gdesc(player) : "   ", character ? character_get_gdesc(character) : "      ", (int)space_get_id(middle));
    } else {
        sprintf(middle_str, "|            %3d|", (int)space_get_id(middle));
    }

    if (!east) sprintf(east_str, "                   ");
    else if (!(east_disc = space_get_discovered(east)) || !light_e) sprintf(east_str, "  |            %3d|", (int)space_get_id(east));
    else {
        character = game_get_character(game, space_get_character(east));
        sprintf(east_str, "  |     %s %3d|", character ? character_get_gdesc(character) : "      ", (int)space_get_id(east));
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* Renderizado interior GDESC y oscuridad */
    for (i = 0; i < GDESC_ROWS; i++) {
        if (!west) sprintf(west_str, "                   ");
        else if (!west_disc) sprintf(west_str, "|               |  ");
        else if (!light_w) sprintf(west_str, "|  ???????????  |  ");
        else {
            space_gdesc = space_get_gdesc(west);
            sprintf(west_str, "|%s      |  ", space_gdesc ? space_gdesc[i] : "               ");
        }

        if (!middle_disc) sprintf(middle_str, "|               |");
        else if (!light_c) sprintf(middle_str, "|  ???????????  |");
        else {
            space_gdesc = space_get_gdesc(middle);
            sprintf(middle_str, "|%s      |", space_gdesc ? space_gdesc[i] : "               ");
        }

        if (!east) sprintf(east_str, "                   ");
        else if (!east_disc) sprintf(east_str, "  |               |");
        else if (!light_e) sprintf(east_str, "  |  ???????????  |");
        else {
            space_gdesc = space_get_gdesc(east);
            sprintf(east_str, "  |%s      |", space_gdesc ? space_gdesc[i] : "               ");
        }

        sprintf(str, "%s%s%s", west_str, middle_str, east_str);
        screen_area_puts(area, str);
    }

    /* Renderizado de objetos */
    if (!west) sprintf(west_str, "                   ");
    else if (!west_disc || !light_w) sprintf(west_str, "|               |  ");
    else {
        obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
        sprintf(west_str, "|%s|  ", obj_list_status == ERROR ? "               " : obj_list);
    }

    if (!middle_disc || !light_c) sprintf(middle_str, " %s|               |%s ", west ? "<" : " ", east ? ">" : " ");
    else {
        obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);
        sprintf(middle_str, " %s|%s|%s ", west ? "<" : " ", obj_list_status == ERROR ? "               " : obj_list, east ? ">" : " ");
    }

    if (!east) sprintf(east_str, "                   ");
    else if (!east_disc || !light_e) sprintf(east_str, "  |               |");
    else {
        obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
        sprintf(east_str, "  |%s|", obj_list_status == ERROR ? "               " : obj_list);
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);

    /* Borde inferior */
    sprintf(west_str,  west ? "+---------------+  " : "                   ");
    sprintf(east_str,  east ? "  +---------------+" : "                   ");
    sprintf(str, "%s+---------------+%s", west_str, east_str);
    screen_area_puts(area, str);
}

Status graphic_engine_get_objects_str(Game *game, Space *space, char *str) {
    Id *n; int i, cont; char car[ROOM_WIDTH + 1] = "";
    if (!game || !space || !str) return ERROR;

    n = space_get_objects(space);
    cont = space_get_number_of_objects(space);
    if (!n || cont == -1) return ERROR;

    for (i = 0; i < cont; i++) {
        if (strlen(car) + strlen(object_get_name(game_get_object(game, n[i]))) < ROOM_WIDTH) {
            strcat(car, object_get_name(game_get_object(game, n[i])));
        }
        if (i < cont - 1) strcat(car, ", ");
    }

    while (strlen(car) < 15) strcat(car, " ");
    strcpy(str, car);
    return OK;
}

void graphic_engine_destroy(Graphic_engine *ge) {
    if (!ge) return;
    screen_area_destroy(ge->map);
    screen_area_destroy(ge->descript);
    screen_area_destroy(ge->banner);
    screen_area_destroy(ge->help);
    screen_area_destroy(ge->feedback);
    screen_destroy();
    free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game, Status last_cmd_status, BOOL paint_cmd) {
    Id id_act = NO_ID, id_back = NO_ID, id_top = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
    Space *act = NULL;
    char str[255];
    CommandCode last_cmd = UNKNOWN;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    int i;
    Player *player = NULL;
    Character *character = NULL;
    Object *obj = NULL;

    if (!game) return;

    /* 1. MAPA */
    screen_area_clear(ge->map);
    if ((id_act = game_get_player_location(game)) != NO_ID) {
        act = game_get_space(game, id_act);
        id_back = game_get_connection(game, space_get_id(act), N);
        id_next = game_get_connection(game, space_get_id(act), S);

        if (id_back != NO_ID) {
            id_top = game_get_connection(game, id_back, N);
            if (id_top != NO_ID) {
                graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_top), FALSE);
                screen_area_puts(ge->map, " ");
            }
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE);
            screen_area_puts(ge->map, "                             ^"); 
        }

        graphic_engine_paint_spaces_row(ge->map, game, act, TRUE);

        if (id_next != NO_ID) {
            screen_area_puts(ge->map, "                             v");
            graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
        }
    }

    /* 2. DESCRIPCIONES (Fusionado) */
    screen_area_clear(ge->descript);

    screen_area_puts(ge->descript, " Objects:");
    for (i = 0; i < MAX_OBJECTS; i++) {
        obj = game_get_object(game, i);
        if (obj && (obj_loc = game_get_object_location(game, i)) != NO_ID) {
            sprintf(str, "  %-12s: %3d (Mov: %s)", object_get_name(obj), (int)obj_loc, object_get_movable(obj) ? "Yes" : "No");
            screen_area_puts(ge->descript, str);
        }
    }

    screen_area_puts(ge->descript, " Characters:");
    for (i = 0; i < MAX_CHARACTERS; i++) {
        character = game_get_character(game, i);
        if (character && game_get_character_location(game, i) != NO_ID) {
            char type = character_get_friendly(character) ? 'F' : 'E';
            sprintf(str, "  [%c] %-10s: %d (HP:%d)", type, character_get_name(character), (int)game_get_character_location(game, i), character_get_health(character));
            screen_area_puts(ge->descript, str);
        }
    }

    player = game_get_player(game);
    sprintf(str, "\n Player: %d (HP: %d)", (int)player_get_location(player), player_get_health(player));
    screen_area_puts(ge->descript, str);
    
    screen_area_puts(ge->descript, " Player has: ");
    int max_backpack_obj = inventory_get_max_objs(player_get_backpack(player));
    int obj_found = 0;
    for (i = 0; i < max_backpack_obj; i++) {
        Id p_obj = player_get_object(player, i);
        if (p_obj != NO_ID) {
            obj = game_get_object(game, p_obj);
            /* Durabilidad añadida para espada/escudo */
            if (p_obj == 21 || p_obj == 24) {
                sprintf(str, "  - %s (%d dur)", object_get_name(obj), object_get_durability(obj) + 1);
            } else {
                sprintf(str, "  - %s", object_get_name(obj));
            }
            screen_area_puts(ge->descript, str);
            obj_found++;
        }
    }
    if (obj_found == 0) screen_area_puts(ge->descript, "  no objects");

    screen_area_puts(ge->descript, " ");
    screen_area_puts(ge->descript, game_get_chat_message(game));
    game_set_chat_message(game, ""); 

    /* 3. BANNER Y FEEDBACK */
    sprintf(str, "  Turn Player :%d ", game_get_turn(game) + 1);
    screen_area_puts(ge->banner, str);

    screen_area_clear(ge->help);
    screen_area_puts(ge->help, " Commands: exit/e, take/t, drop/d, attack/a, chat/c, move/m, inspect/i");

    if (paint_cmd == TRUE) {
        last_cmd = command_get_code(game_get_last_command(game));
        sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], last_cmd_status == OK ? "OK" : "ERROR");
        screen_area_puts(ge->feedback, str);
    }

    screen_paint(game_get_turn(game));
    printf("prompt:> ");
}