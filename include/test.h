/**
 * @brief Define utilidades comunes para las pruebas unitarias.
 * @file test.h
 * @author Profesores PPROG
 * @version 1.0
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
/** @brief Código ANSI para mostrar texto rojo en las pruebas. */
#define KRED  "\x1B[31m"
/** @brief Código ANSI para mostrar texto verde en las pruebas. */
#define KGRN  "\x1B[32m"
/** @brief Código ANSI para mostrar texto amarillo en las pruebas. */
#define KYEL  "\x1B[33m"
/** @brief Código ANSI para mostrar texto cian en las pruebas. */
#define KCYN  "\x1B[36m"
/** @brief Código ANSI para restaurar el color por defecto. */
#define RESET "\033[0m"
#else
/** @brief Cadena vacía usada cuando las pruebas se ejecutan sin color. */
#define KRED
/** @brief Cadena vacía usada cuando las pruebas se ejecutan sin color. */
#define KGRN
/** @brief Cadena vacía usada cuando las pruebas se ejecutan sin color. */
#define KYEL
/** @brief Cadena vacía usada cuando las pruebas se ejecutan sin color. */
#define KCYN
/** @brief Cadena vacía usada cuando las pruebas se ejecutan sin color. */
#define RESET
#endif

/** @brief Ejecuta una aserción de prueba y muestra su resultado. */
#define PRINT_TEST_RESULT(x) do{					\
    __test_counter++;							\
    __pass = (x);							\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;	\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n",	\
	   __FILE__, __LINE__ , __FUNCTION__,				\
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

/** @brief Imprime el porcentaje de pruebas superadas. */
#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))

/** @brief Contador global de pruebas ejecutadas. */
extern int __test_counter;
/** @brief Contador global de pruebas superadas. */
extern int __test_passed;
/** @brief Resultado de la última prueba ejecutada. */
extern int __pass;

#endif
