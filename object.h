/**
 * @brief Define la interfaz de los objetos del juego
 *
 * @file object.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

Object* object_create(Id id);
void object_destroy(Object* object);
Id object_get_id(Object* object);
Status object_set_name(Object* object, char* name);
const char* object_get_name(Object* object);
Status object_set_desc(Object* object, char* desc);
const char* object_get_desc(Object* object);

/* Nuevas mecánicas: Movilidad y Durabilidad */
Status object_set_movable(Object* object, BOOL movable);
BOOL object_get_movable(Object* object);
Status object_set_durability(Object* object, int durability);
int object_get_durability(Object* object);

#endif