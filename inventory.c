#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"

struct _Inventory {
    Set *objs;
    int max_objs;
};

Inventory* inventory_create() {
    Inventory *inv = (Inventory*)malloc(sizeof(Inventory));
    if (!inv) return NULL;

    inv->objs = set_create();
    if (!inv->objs) {
        free(inv);
        return NULL;
    }
    inv->max_objs = 0; /* Se configura al cargar el jugador */
    return inv;
}

void inventory_destroy(Inventory* inv) {
    if (!inv) return;
    set_destroy(inv->objs);
    free(inv);
}

Status inventory_add_id(Inventory* inv, Id id) {
    if (!inv || id == NO_ID) return ERROR;
    if (set_get_n_ids(inv->objs) >= inv->max_objs) return ERROR;
    return set_add(inv->objs, id);
}

Status inventory_remove_id(Inventory* inv, Id id) {
    if (!inv || id == NO_ID) return ERROR;
    return set_del(inv->objs, id);
}

BOOL inventory_has_id(Inventory* inv, Id id) {
    if (!inv || id == NO_ID) return FALSE;
    return set_has_id(inv->objs, id);
}

Id inventory_get_id_at(Inventory* inv, int position) {
    if (!inv || position < 0 || position >= set_get_n_ids(inv->objs)) return NO_ID;
    return set_get_id_at(inv->objs, position);
}

Status inventory_set_max_objs(Inventory* inv, int max_objs) {
    if (!inv || max_objs < 0) return ERROR;
    inv->max_objs = max_objs;
    return OK;
}

int inventory_get_max_objs(Inventory* inv) {
    if (!inv) return -1;
    return inv->max_objs;
}

int inventory_get_num_objs(Inventory* inv) {
    if (!inv) return -1;
    return set_get_n_ids(inv->objs);
}