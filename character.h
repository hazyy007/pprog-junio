/**
 * @brief Define los personajes no jugables (NPCs) y enemigos
 *
 * @file character.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

Character* character_create(Id id);
void character_destroy(Character* character);
Id character_get_id(Character* character);

Status character_set_name(Character* character, char* name);
const char* character_get_name(Character* character);

Status character_set_gdesc(Character* character, char* gdesc);
const char* character_get_gdesc(Character* character);

Status character_set_health(Character* character, int health);
int character_get_health(Character* character);

Status character_set_friendly(Character* character, BOOL friendly);
BOOL character_get_friendly(Character* character);

Status character_set_message(Character* character, char* message);
const char* character_get_message(Character* character);

#endif