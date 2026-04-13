#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

struct _Player {
    Id id;
    char name[WORD_SIZE];
    char gdesc[WORD_SIZE];
    Id location;
    int health;
    Inventory *backpack;
};

Player* player_create(Id id) {
    Player *new_player = NULL;

    if (id == NO_ID) return NULL;

    new_player = (Player *)malloc(sizeof(Player));
    if (!new_player) return NULL;

    new_player->id = id;
    new_player->name[0] = '\0';
    new_player->gdesc[0] = '\0';
    new_player->location = NO_ID;
    new_player->health = 10;
    
    new_player->backpack = inventory_create();
    if (!new_player->backpack) {
        free(new_player);
        return NULL;
    }

    return new_player;
}

void player_destroy(Player* player) {
    if (!player) return;
    inventory_destroy(player->backpack);
    free(player);
}

Id player_get_id(Player* player) {
    if (!player) return NO_ID;
    return player->id;
}

Status player_set_name(Player* player, char* name) {
    if (!player || !name) return ERROR;
    strcpy(player->name, name);
    return OK;
}

const char* player_get_name(Player* player) {
    if (!player) return NULL;
    return player->name;
}

Status player_set_gdesc(Player* player, char* gdesc) {
    if (!player || !gdesc) return ERROR;
    strcpy(player->gdesc, gdesc);
    return OK;
}

const char* player_get_gdesc(Player* player) {
    if (!player) return NULL;
    return player->gdesc;
}

Status player_set_location(Player* player, Id location) {
    if (!player) return ERROR;
    player->location = location;
    return OK;
}

Id player_get_location(Player* player) {
    if (!player) return NO_ID;
    return player->location;
}

Status player_set_health(Player* player, int health) {
    if (!player || health < 0) return ERROR;
    player->health = health;
    return OK;
}

int player_get_health(Player* player) {
    if (!player) return -1;
    return player->health;
}

Inventory* player_get_backpack(Player* player) {
    if (!player) return NULL;
    return player->backpack;
}

Status player_add_object(Player* player, Id id) {
    if (!player || id == NO_ID) return ERROR;
    return inventory_add_id(player->backpack, id);
}

Status player_remove_object(Player* player, Id id) {
    if (!player || id == NO_ID) return ERROR;
    return inventory_remove_id(player->backpack, id);
}

Id player_get_object(Player* player, int pos) {
    if (!player) return NO_ID;
    return inventory_get_id_at(player->backpack, pos);
}