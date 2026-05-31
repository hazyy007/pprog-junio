/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/** @brief Tamaño máximo usado para cadenas genéricas del proyecto. */
#define WORD_SIZE 1000
/** @brief Identificador inválido o no inicializado. */
#define NO_ID -1

/** @brief Tipo común para identificadores de entidades del juego. */
typedef long Id;

/** @brief Resultado estándar de una operación. */
typedef enum { ERROR, OK } Status;

/** @brief Direcciones disponibles para navegar entre espacios. */
typedef enum { NO_DIRECTION = -1, N, S, E, W, U, D } Directions;

/** @brief Tipo booleano usado por los módulos del proyecto. */
typedef enum { FALSE, TRUE } BOOL;

#endif
