#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

struct _Object {
    Id id;
    char name[WORD_SIZE];
    char desc[WORD_SIZE];
    BOOL movable;
    int durability;
};

Object* object_create(Id id) {
    Object *new_object = NULL;

    if (id == NO_ID) return NULL;

    new_object = (Object *)malloc(sizeof(Object));
    if (new_object == NULL) return NULL;

    new_object->id = id;
    new_object->name[0] = '\0';
    new_object->desc[0] = '\0';
    new_object->movable = TRUE; /* Por defecto se pueden coger */
    new_object->durability = 5; /* Durabilidad base por defecto */

    return new_object;
}

void object_destroy(Object* object) {
    if (!object) return;
    free(object);
}

Id object_get_id(Object* object) {
    if (!object) return NO_ID;
    return object->id;
}

Status object_set_name(Object* object, char* name) {
    if (!object || !name) return ERROR;
    if (!strcpy(object->name, name)) return ERROR;
    return OK;
}

const char* object_get_name(Object* object) {
    if (!object) return NULL;
    return object->name;
}

Status object_set_desc(Object* object, char* desc) {
    if (!object || !desc) return ERROR;
    if (!strcpy(object->desc, desc)) return ERROR;
    return OK;
}

const char* object_get_desc(Object* object) {
    if (!object) return NULL;
    return object->desc;
}

Status object_set_movable(Object* object, BOOL movable) {
    if (!object) return ERROR;
    object->movable = movable;
    return OK;
}

BOOL object_get_movable(Object* object) {
    if (!object) return FALSE;
    return object->movable;
}

Status object_set_durability(Object* object, int durability) {
    if (!object || durability < 0) return ERROR;
    object->durability = durability;
    return OK;
}

int object_get_durability(Object* object) {
    if (!object) return -1;
    return object->durability;
}