

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

typedef struct _Space Space;

Space* space_create(Id id);
void space_destroy(Space* space);
Id space_get_id(Space* space);
Status space_set_name(Space* space, char* name);
const char* space_get_name(Space* space);

/* Iluminación e inspección */
Status space_set_light(Space* space, BOOL light);
BOOL space_get_light(Space* space);
Status space_set_discovered(Space* space, BOOL discovered);
BOOL space_get_discovered(Space* space);

/* Representación gráfica */
Status space_set_gdesc(Space* space, char gdesc[GDESC_ROWS][GDESC_COLS]);
char (*space_get_gdesc(Space* space))[GDESC_COLS];

/* Gestión de objetos */
Status space_add_object(Space* space, Id id);
Status space_remove_object(Space* space, Id id);
Id* space_get_objects(Space* space);
int space_get_number_of_objects(Space* space);
BOOL space_has_object(Space* space, Id id);

/* Personajes */
Status space_set_character(Space* space, Id id);
Id space_get_character(Space* space);

#endif