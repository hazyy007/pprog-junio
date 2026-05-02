/**
 * @brief Implementa las reglas del juego
 * @file game_rules.c
 * @author Alejandro Dominguez
 * @version 1.0
 * @date 02-05-2026
 * @copyright GNU Public License
 */

 #include "game_rules.h"
 #include <stdlib.h>
 #include <time.h>

 struct _GameRules
 {
    int execution_counter; /* Contador de ejecuciones para controlar la frecuencia de las reglas*/
 };

 GameRules* game_rules_create()
 {
    GameRules* rules = (GameRules*)malloc(sizeof(GameRules));
    if (!rules) return NULL;
    rules->execution_counter = 0;
    return rules;
 }

 Status game_rules_destroy(GameRules* rules)
 {
    if (!rules) return ERROR;
    free(rules);
    return OK;
 }

 Status game_rules_update(GameRules* rules, Game* game)
 {
    int random_event;
    Player *player = NULL;
    Object *object = NULL;
    Link *link = NULL;
    Space *space = NULL;
    Character *character = NULL;
    if (!rules || !game) return ERROR;

    /* Incrementa el contador de ejecuciones */
    rules->execution_counter++;

    /*Solo aplicamos las reglas un 30% de las veces*/
    random_event = rand() % 100;
    if (random_event >= 30) return OK;

    /*Regla 1: Daño (0-4)*/
    if (random_event < 5)
    {
        player = game_get_player(game);
        if (player && player_get_health(player) > 1)
        {
            player_set_health(player, player_get_health(player) - 1);
            game_set_chat_message(game, "Un gas toxico te ha afectado, pierdes 1 punto de salud.");
        }
    }
    /*Regla 2: Curacion (5-9)*/
    if (random_event >= 5 && random_event < 10)
    {
        player = game_get_player(game);
        if (player && player_get_health(player) < 10)
        {
            player_set_health(player, player_get_health(player) + 1);
            game_set_chat_message(game, "Encuentras una fuente de agua pura, ganas 1 punto de salud.");
        }
    }

    /*Regla 3: Cambio de lugar de objectos (10-14)*/
    if (random_event >= 10 && random_event < 15)
    {
        if (game_get_number_of_objects(game) > 0 && game_get_number_of_space(game) > 0)
        {
            object = game_get_object_from_index(game, rand()%game_get_number_of_objects(game));
            space = game_get_space_from_index(game, rand()%game_get_number_of_space(game));
            if (object && space && object_get_movable(object) == TRUE)
            {
                game_set_object_location(game, space_get_id(space), object_get_id(object));
                game_set_chat_message(game, "Un terremoto ha movido un objeto a otro lugar.");
            }
        }   
    }

    /*Regla 4: Se cierran puertas (15-19)*/
    if (random_event >= 15 && random_event < 20)
    {
        if (game_get_number_of_links(game) > 0)
        {
            link = game_get_link_from_index(game, rand()%game_get_number_of_links(game));
            if (link)
            {
                link_set_open(link, !link_get_open(link));
                game_set_chat_message(game, "Un derrumbe ha bloqueado un camino.");
            }
        }
    }

    /*Regla 5: Mensaje ambiente*/
    if (random_event >= 20 && random_event < 25)
    {
        game_set_chat_message(game, "El ambiente se siente más tenso.");
    }

    /*Regla 6: Character se mueve*/
    if (random_event >= 25 && random_event < 30)
    {
        if (game_get_number_of_characters(game) > 0)
        {
            character = game_get_character_from_index(game, rand()%game_get_number_of_characters(game));
            if (!character || character_get_friendly(character)) return OK; /* Solo los personajes enemigos se mueven */
            space = game_get_space_from_index(game, rand()%game_get_number_of_space(game));
            if (space)
            {
                game_set_character_location(game, space_get_id(space), character_get_id(character));
                game_set_chat_message(game, "Un personaje ha cambiado de lugar.");
            }
        }
    }
    return OK;
 }
 