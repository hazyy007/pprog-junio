/**
 * @brief Define la interfaz del motor gráfico textual
 *
 * @file graphic_engine.h
 * @author Alejandro Domínguez
 * @version 3.0
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

Graphic_engine* graphic_engine_create();
void graphic_engine_destroy(Graphic_engine* ge);
void graphic_engine_paint_game(Graphic_engine* ge, Game* game, Status last_cmd_status, BOOL paint_cmd);

#endif