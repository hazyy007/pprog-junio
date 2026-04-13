/**
 * @brief Implementación del módulo de carga de juegos
 * @file game_reader.c
 * @author Unai
 * @version 1.0
 * @date 16-03-2026
 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"
#include "game.h"
#include "space.h"
#include "character.h"
#include "object.h"
#include "player.h"
#include "link.h"

Status game_reader_load_spaces(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID;
    Space *space = NULL;
    Status status = OK;
    char gdesc[GDESC_ROWS][GDESC_COLS];
    int light = 1;
    int i;

    if (!filename) return ERROR;
    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#s:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|\n\r");
            light = toks ? atoi(toks) : 1;

            space = space_create(id);
            if (space) {
                space_set_name(space, name);
                space_set_light(space, light ? TRUE : FALSE);

                /* Parseo de gráficos multilínea al estilo !# */
                if (fgets(line, WORD_SIZE, file) && strncmp("!#", line, 2) == 0) {
                    for (i = 0; i < GDESC_ROWS; i++) {
                        if (fgets(line, WORD_SIZE, file)) {
                            line[strcspn(line, "\r\n")] = '\0';
                            strcpy(gdesc[i], line);
                        } else {
                            strcpy(gdesc[i], "         ");
                        }
                    }
                    space_set_gdesc(space, gdesc);
                }
                game_add_space(game, space);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

Status game_reader_load_objects(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char desc[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    Object *object = NULL;
    Status status = OK;
    int movable = 1;

    if (!filename) return ERROR;
    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#o:", line, 3) == 0) {
            toks = strtok(line + 3, "|");
            id = atol(toks);
            toks = strtok(NULL, "|");
            strcpy(name, toks);
            toks = strtok(NULL, "|");
            location_id = atol(toks);
            toks = strtok(NULL, "|");
            if (toks) strcpy(desc, toks);
            toks = strtok(NULL, "|\n\r");
            movable = toks ? atoi(toks) : 1;

            object = object_create(id);
            if (object) {
                object_set_name(object, name);
                object_set_desc(object, desc);
                object_set_movable(object, movable ? TRUE : FALSE);

                game_add_object(game, object);
                game_set_object_location(game, location_id, id);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

Status game_reader_load_characters(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char gdesc[7] = "";
    char message[101] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    int health = 0, friendly = 0;
    Character *character = NULL;
    Status status = OK;

    if (!filename) return ERROR;
    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#c:", line, 3) == 0) {
            toks = strtok(line + 3, "|"); id = atol(toks);
            toks = strtok(NULL, "|"); strcpy(name, toks);
            toks = strtok(NULL, "|"); strcpy(gdesc, toks);
            toks = strtok(NULL, "|"); location_id = atol(toks);
            toks = strtok(NULL, "|"); health = atoi(toks);
            toks = strtok(NULL, "|"); friendly = atoi(toks);
            toks = strtok(NULL, "|"); strcpy(message, toks);

            character = character_create(id);
            if (character) {
                character_set_name(character, name);
                character_set_gdesc(character, gdesc);
                character_set_health(character, health);
                character_set_friendly(character, friendly);
                character_set_message(character, message);
                
                game_add_character(game, character);
                game_set_character_location(game, location_id, id);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

Status game_reader_load_players(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char gdesc[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, location_id = NO_ID;
    int health = 0, max_objs = 0;
    Player *player = NULL;
    Space* starting_space = NULL;
    Status status = OK;

    if (!filename) return ERROR;
    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#p:", line, 3) == 0) {
            toks = strtok(line + 3, "|"); id = atol(toks);
            toks = strtok(NULL, "|"); strcpy(name, toks);
            toks = strtok(NULL, "|"); strcpy(gdesc, toks);
            toks = strtok(NULL, "|"); location_id = atol(toks);
            toks = strtok(NULL, "|"); health = atoi(toks);
            toks = strtok(NULL, "|"); max_objs = atoi(toks);

            player = player_create(id);
            if (player) {
                player_set_name(player, name);
                player_set_gdesc(player, gdesc);
                player_set_location(player, location_id);
                player_set_health(player, health);
                inventory_set_max_objs(player_get_backpack(player), max_objs);
                
                game_set_player(game, player);
                starting_space = game_get_space(game, location_id);
                if (starting_space) space_set_discovered(starting_space, TRUE);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}

Status game_reader_load_links(Game *game, char *filename) {
    FILE *file = NULL;
    char line[WORD_SIZE] = "";
    char name[WORD_SIZE] = "";
    char *toks = NULL;
    Id id = NO_ID, origin = NO_ID, destination = NO_ID;
    int dir_int = 0, open_int = 0;
    Link *link = NULL;
    Status status = OK;

    if (!filename) return ERROR;
    file = fopen(filename, "r");
    if (!file) return ERROR;

    while (fgets(line, WORD_SIZE, file)) {
        if (strncmp("#l:", line, 3) == 0) {
            toks = strtok(line + 3, "|"); id = atol(toks);
            toks = strtok(NULL, "|"); strcpy(name, toks);
            toks = strtok(NULL, "|"); origin = atol(toks);
            toks = strtok(NULL, "|"); destination = atol(toks);
            toks = strtok(NULL, "|"); dir_int = atoi(toks);
            toks = strtok(NULL, "|"); open_int = atoi(toks);

            link = link_create(id);
            if (link) {
                link_set_name(link, name);
                link_set_origin(link, origin);
                link_set_destination(link, destination);
                link_set_direction(link, (Directions)dir_int);
                link_set_open(link, open_int ? TRUE : FALSE);
                game_add_link(game, link);
            }
        }
    }

    if (ferror(file)) status = ERROR;
    fclose(file);
    return status;
}