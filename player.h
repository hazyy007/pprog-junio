/**
 * @brief Define la interfaz del jugador
 *
 * @file player.h
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"

typedef struct _Player Player;

Player* player_create(Id id);
void player_destroy(Player* player);
Id player_get_id(Player* player);

Status player_set_name(Player* player, char* name);
const char* player_get_name(Player* player);

Status player_set_gdesc(Player* player, char* gdesc);
const char* player_get_gdesc(Player* player);

Status player_set_location(Player* player, Id location);
Id player_get_location(Player* player);

Status player_set_health(Player* player, int health);
int player_get_health(Player* player);

Inventory* player_get_backpack(Player* player);
Status player_add_object(Player* player, Id id);
Status player_remove_object(Player* player, Id id);
Id player_get_object(Player* player, int pos); /* Para recorrer la mochila en la UI */

#endif