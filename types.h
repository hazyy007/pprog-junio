/**
 * @brief Define los tipos de datos comunes y estructuras básicas
 *
 * @file types.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1
#define GDESC_ROWS 9
#define GDESC_COLS 10 /* 9 caracteres + '\0' */

typedef long Id;

typedef enum {
  FALSE = 0,
  TRUE = 1
} BOOL;

typedef enum {
  ERROR = 0,
  OK = 1
} Status;

typedef enum {
  N,
  S,
  E,
  W,
  U,
  D
} Directions;

#endif