/**
 * @brief Define la interfaz principal del juego
 *
 * @file game.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"
#include "character.h"
#include "link.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100
#define MAX_LINKS 100

typedef struct _Game Game;

Game* game_create();
Status game_create_from_file(Game* game, char* filename);
void game_destroy(Game* game);

BOOL game_is_over(Game* game);
void game_print_data(Game* game);
Status game_update(Game* game, Command* cmd);

/* Comandos y Turnos */
Command* game_get_last_command(Game* game);
Status game_set_last_command(Game* game, Command* command);
int game_get_turn(Game* game);

/* Espacios */
Status game_add_space(Game* game, Space* space);
Space* game_get_space(Game* game, Id id);
Id game_get_player_location(Game* game);
Id game_get_connection(Game* game, Id space_id, Directions dir);

/* Jugador */
Status game_set_player(Game* game, Player* player);
Player* game_get_player(Game* game);

/* Objetos */
Status game_add_object(Game* game, Object* object);
Object* game_get_object(Game* game, Id id);
Status game_set_object_location(Game* game, Id location, Id object_id);
Id game_get_object_location(Game* game, Id object_id);

/* Personajes */
Status game_add_character(Game* game, Character* character);
Character* game_get_character(Game* game, Id id);
Status game_set_character_location(Game* game, Id location, Id character_id);
Id game_get_character_location(Game* game, Id character_id);

/* Enlaces (Links) */
Status game_add_link(Game* game, Link* link);
Link* game_get_link(Game* game, Id id);

/* Mensajes e Inspección */
Status game_set_chat_message(Game* game, char* message);
const char* game_get_chat_message(Game* game);
Status game_set_object_desc(Game* game, char* desc);
const char* game_get_object_desc(Game* game);

#endif