/**
 * @brief Interfaz para la gestión de las acciones del juego
 *
 * @file game_actions.h
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "game.h"
#include "command.h"

Status game_actions_update(Game* game, Command* cmd);

#endif