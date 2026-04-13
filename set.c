#include <stdio.h>
#include <stdlib.h>
#include "set.h"

struct _Set {
    Id ids[MAX_SET];
    int n_ids;
};

Set* set_create() {
    Set* new_set = NULL;
    int i;

    new_set = (Set*)malloc(sizeof(Set));
    if (!new_set) return NULL;

    for (i = 0; i < MAX_SET; i++) {
        new_set->ids[i] = NO_ID;
    }
    new_set->n_ids = 0;

    return new_set;
}

void set_destroy(Set* set) {
    if (!set) return;
    free(set);
}

Status set_add(Set* set, Id id) {
    if (!set || id == NO_ID || set->n_ids >= MAX_SET) return ERROR;
    
    /* Evitar duplicados */
    if (set_has_id(set, id) == TRUE) return ERROR;

    set->ids[set->n_ids] = id;
    set->n_ids++;

    return OK;
}

Status set_del(Set* set, Id id) {
    int i, j;

    if (!set || id == NO_ID || set->n_ids == 0) return ERROR;

    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) {
            /* Desplazar los elementos para rellenar el hueco */
            for (j = i; j < set->n_ids - 1; j++) {
                set->ids[j] = set->ids[j + 1];
            }
            set->ids[set->n_ids - 1] = NO_ID;
            set->n_ids--;
            return OK;
        }
    }

    return ERROR;
}

BOOL set_has_id(Set* set, Id id) {
    int i;
    if (!set || id == NO_ID) return FALSE;

    for (i = 0; i < set->n_ids; i++) {
        if (set->ids[i] == id) return TRUE;
    }

    return FALSE;
}

int set_get_n_ids(Set* set) {
    if (!set) return -1;
    return set->n_ids;
}

Id set_get_id_at(Set* set, int position) {
    if (!set || position < 0 || position >= set->n_ids) return NO_ID;
    return set->ids[position];
}