/**
 * @brief Implementa utilidades comunes para las pruebas unitarias.
 * @file test.c
 * @author Profesores PPROG
 * @version 1.0
 * @copyright GNU Public License
 */

#include "test.h"
#include <stdio.h>

/** @brief Número total de pruebas registradas por las utilidades simples. */
static int total_tests = 0;
/** @brief Número total de pruebas superadas por las utilidades simples. */
static int passed_tests = 0;
/** @brief Contador global usado por la macro PRINT_TEST_RESULT. */
int __test_counter = 0;
/** @brief Contador global de pruebas superadas por PRINT_TEST_RESULT. */
int __test_passed  = 0;
/** @brief Resultado de la última comprobación ejecutada. */
int __pass = 0;

/**
 * @brief Imprime el resultado de una prueba simple.
 * @author Profesores PPROG
 * @param result Valor distinto de cero si la prueba ha sido superada.
 */
void test_print_result(int result) {
    if (result) {
        printf("\tPASSED\n");
        passed_tests++;
    } else {
        printf("\tFAILED\n");
    }
    total_tests++;
}

/**
 * @brief Imprime el resumen acumulado de pruebas simples.
 * @author Profesores PPROG
 */
void test_print_summary() {
    printf("\n%d/%d tests passed (%.2f%%)\n", passed_tests, total_tests, (float)passed_tests / total_tests * 100);
}
