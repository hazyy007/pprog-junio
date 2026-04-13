/**
 * @brief Gestiona la mochila de objetos
 *
 * @file inventory.h
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

Inventory* inventory_create();
void inventory_destroy(Inventory* inv);

Status inventory_add_id(Inventory* inv, Id id);
Status inventory_remove_id(Inventory* inv, Id id);
BOOL inventory_has_id(Inventory* inv, Id id);
Id inventory_get_id_at(Inventory* inv, int position);

Status inventory_set_max_objs(Inventory* inv, int max_objs);
int inventory_get_max_objs(Inventory* inv);
int inventory_get_num_objs(Inventory* inv);

#endif