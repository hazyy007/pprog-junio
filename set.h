/**
 * @brief Define la estructura de conjunto (Set) para gestionar IDs
 *
 * @file set.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_SET 100

typedef struct _Set Set;

Set* set_create();
void set_destroy(Set* set);

Status set_add(Set* set, Id id);
Status set_del(Set* set, Id id);
BOOL set_has_id(Set* set, Id id);

int set_get_n_ids(Set* set);
Id set_get_id_at(Set* set, int position);

#endif