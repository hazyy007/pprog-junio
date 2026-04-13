/**
 * @brief Define la estructura de enlaces (caminos/puertas)
 *
 * @file link.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef struct _Link Link;

Link* link_create(Id id);
void link_destroy(Link* link);
Id link_get_id(Link* link);

Status link_set_name(Link* link, char* name);
const char* link_get_name(Link* link);

Status link_set_origin(Link* link, Id id);
Id link_get_origin(Link* link);

Status link_set_destination(Link* link, Id id);
Id link_get_destination(Link* link);

Status link_set_direction(Link* link, Directions dir);
Directions link_get_direction(Link* link);

Status link_set_open(Link* link, BOOL open);
BOOL link_get_open(Link* link);

#endif