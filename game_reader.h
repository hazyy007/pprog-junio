/**
 * @brief Define la interfaz de lectura de datos del juego
 *
 * @file game_reader.h
 * @author Alejandro Dominguez
 * @version 2.0
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

Status game_reader_load_spaces(Game *game, char *filename);
Status game_reader_load_objects(Game *game, char *filename);
Status game_reader_load_characters(Game *game, char *filename);
Status game_reader_load_players(Game *game, char *filename);
Status game_reader_load_links(Game *game, char *filename);

#endif