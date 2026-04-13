#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

struct _Character {
    Id id;
    char name[WORD_SIZE];
    char gdesc[8]; /* Representación gráfica corta */
    int health;
    BOOL friendly;
    char message[WORD_SIZE];
};

Character* character_create(Id id) {
    Character* new_character = NULL;

    if (id == NO_ID) return NULL;

    new_character = (Character *)malloc(sizeof(Character));
    if (!new_character) return NULL;

    new_character->id = id;
    new_character->name[0] = '\0';
    new_character->gdesc[0] = '\0';
    new_character->health = 10; /* Vida por defecto */
    new_character->friendly = FALSE;
    new_character->message[0] = '\0';

    return new_character;
}

void character_destroy(Character* character) {
    if (!character) return;
    free(character);
}

Id character_get_id(Character* character) {
    if (!character) return NO_ID;
    return character->id;
}

Status character_set_name(Character* character, char* name) {
    if (!character || !name) return ERROR;
    strcpy(character->name, name);
    return OK;
}

const char* character_get_name(Character* character) {
    if (!character) return NULL;
    return character->name;
}

Status character_set_gdesc(Character* character, char* gdesc) {
    if (!character || !gdesc) return ERROR;
    strncpy(character->gdesc, gdesc, 7);
    character->gdesc[7] = '\0';
    return OK;
}

const char* character_get_gdesc(Character* character) {
    if (!character) return NULL;
    return character->gdesc;
}

Status character_set_health(Character* character, int health) {
    if (!character || health < 0) return ERROR;
    character->health = health;
    return OK;
}

int character_get_health(Character* character) {
    if (!character) return -1;
    return character->health;
}

Status character_set_friendly(Character* character, BOOL friendly) {
    if (!character) return ERROR;
    character->friendly = friendly;
    return OK;
}

BOOL character_get_friendly(Character* character) {
    if (!character) return FALSE;
    return character->friendly;
}

Status character_set_message(Character* character, char* message) {
    if (!character || !message) return ERROR;
    strcpy(character->message, message);
    return OK;
}

const char* character_get_message(Character* character) {
    if (!character) return NULL;
    return character->message;
}