#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

struct _Link {
    Id id;
    char name[WORD_SIZE];
    Id origin;
    Id destination;
    Directions direction;
    BOOL is_open;
};

Link* link_create(Id id) {
    Link* new_link = NULL;

    if (id == NO_ID) return NULL;

    new_link = (Link*)malloc(sizeof(Link));
    if (!new_link) return NULL;

    new_link->id = id;
    new_link->name[0] = '\0';
    new_link->origin = NO_ID;
    new_link->destination = NO_ID;
    new_link->direction = U; /* Un valor por defecto */
    new_link->is_open = TRUE;

    return new_link;
}

void link_destroy(Link* link) {
    if (!link) return;
    free(link);
}

Id link_get_id(Link* link) {
    if (!link) return NO_ID;
    return link->id;
}

Status link_set_name(Link* link, char* name) {
    if (!link || !name) return ERROR;
    strcpy(link->name, name);
    return OK;
}

const char* link_get_name(Link* link) {
    if (!link) return NULL;
    return link->name;
}

Status link_set_origin(Link* link, Id id) {
    if (!link || id == NO_ID) return ERROR;
    link->origin = id;
    return OK;
}

Id link_get_origin(Link* link) {
    if (!link) return NO_ID;
    return link->origin;
}

Status link_set_destination(Link* link, Id id) {
    if (!link || id == NO_ID) return ERROR;
    link->destination = id;
    return OK;
}

Id link_get_destination(Link* link) {
    if (!link) return NO_ID;
    return link->destination;
}

Status link_set_direction(Link* link, Directions dir) {
    if (!link) return ERROR;
    link->direction = dir;
    return OK;
}

Directions link_get_direction(Link* link) {
    if (!link) return U; /* En caso de error devolvemos algo genérico */
    return link->direction;
}

Status link_set_open(Link* link, BOOL open) {
    if (!link) return ERROR;
    link->is_open = open;
    return OK;
}

BOOL link_get_open(Link* link) {
    if (!link) return FALSE;
    return link->is_open;
}