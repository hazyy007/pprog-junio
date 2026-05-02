/**
 * @brief Define la interfaz del módulo de reglas del juego
 * @file game_rules.h
 * @author Alejandro Dominguez
 * @version 1.0
 * @copyright GNU Public License
 */

 #ifndef GAME_RULES_H
 #define GAME_RULES_H

 #include "game.h"
 #include "types.h"

 /**
  * @brief Estructura opca de las reglas del juego
  */
 typedef struct _GameRules GameRules;

 /**
 * @brief Crea e inicializa el módulo de reglas
 * @return Puntero a GameRules o NULL en caso de error
 */
GameRules* game_rules_create();

/**
 * @brief Libera la memoria del módulo de reglas
 * @param rules Puntero al módulo de reglas
 * @return OK o ERROR
 */
Status game_rules_destroy(GameRules* rules);

/**
 * @brief Ejecuta las reglas aleatorias sobre el estado del juego
 * @param rules Puntero al módulo de reglas
 * @param game Puntero al juego actual
 * @return OK si se actualiza correctamente, ERROR en caso contrario
 */
Status game_rules_update(GameRules* rules, Game* game);


 #endif