/**
 * @brief Archivo de prueba para el módulo object
 * @file object_test.c
 * @author Alejandro Domínguez
 * @version 1.0
 * @date 15-03-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

/** @brief Número total de pruebas unitarias del módulo Object. */
#define MAX_TESTS 32

/**
 * @brief Función principal de pruebas para el módulo Object.
 * @author Alejandro Domínguez
 *
 * Dos modos de ejecución:
 *   1.-Si se ejecuta sin argumentos se ejecutan todas las pruebas
 *   2.-Si se ejecuta con un argumento (entero) se ejecuta la prueba con ese identificador
 */
int main(int argc, char** argv) {

    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all tests for module Object:\\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\\t", test);
	if (test < 1 || test > MAX_TESTS) {
	  printf("Error: unknown test %d\\t", test);
	  return 1;
	}
    }


    if (all || test == 1) test1_object_create();
    if (all || test == 2) test2_object_create();
    if (all || test == 3) test1_object_destroy();
    if (all || test == 4) test2_object_destroy();
    if (all || test == 5) test1_object_get_id();
    if (all || test == 6) test2_object_get_id();
    if (all || test == 7) test1_object_set_name();
    if (all || test == 8) test2_object_set_name();
    if (all || test == 9) test1_object_get_name();
    if (all || test == 10) test2_object_get_name();
    if (all || test == 11) test1_object_print();
    if (all || test == 12) test2_object_print();
    if (all || test == 13) test1_object_set_desc();
    if (all || test == 14) test2_object_set_desc();
    if (all || test == 15) test1_object_get_desc();
    if (all || test == 16) test2_object_get_desc();
    if (all || test == 17) test1_object_set_health();
    if (all || test == 18) test2_object_set_health();
    if (all || test == 19) test1_object_get_health();
    if (all || test == 20) test2_object_get_health();
    if (all || test == 21) test1_object_set_movable();
    if (all || test == 22) test2_object_set_movable();
    if (all || test == 23) test1_object_get_movable();
    if (all || test == 24) test2_object_get_movable();
    if (all || test == 25) test1_object_set_dependency();
    if (all || test == 26) test2_object_set_dependency();
    if (all || test == 27) test1_object_get_dependency();
    if (all || test == 28) test2_object_get_dependency();
    if (all || test == 29) test1_object_set_open();
    if (all || test == 30) test2_object_set_open();
    if (all || test == 31) test1_object_get_open();
    if (all || test == 32) test2_object_get_open();


    PRINT_PASSED_PERCENTAGE;

    return 0;
}

void test1_object_create() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(o != NULL);
    object_destroy(o);
}

void test2_object_create() {
    Object *o;
    o = object_create(NO_ID);
    PRINT_TEST_RESULT(o == NULL);
}

void test1_object_destroy() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test2_object_destroy() {
    PRINT_TEST_RESULT(object_destroy(NULL) == ERROR);
}

void test1_object_get_id() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_get_id(o) == 1);
    object_destroy(o);
}

void test2_object_get_id() {
    PRINT_TEST_RESULT(object_get_id(NULL) == NO_ID);
}

void test1_object_set_name() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "test") == OK);
    object_destroy(o);
}

void test2_object_set_name() {
    PRINT_TEST_RESULT(object_set_name(NULL, "test") == ERROR);
}

void test1_object_get_name() {
    Object *o;
    o = object_create(1);
    object_set_name(o, "test");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "test") == 0);
    object_destroy(o);
}

void test2_object_get_name() {
    PRINT_TEST_RESULT(object_get_name(NULL) == NULL);
}

void test1_object_print() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_print(o) == OK);
    object_destroy(o);
}

void test2_object_print() {
    PRINT_TEST_RESULT(object_print(NULL) == ERROR);
}

void test1_object_set_desc() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_desc(o, "test description") == OK);
    object_destroy(o);
}

void test2_object_set_desc() {
    PRINT_TEST_RESULT(object_set_desc(NULL, "test description") == ERROR);
}

void test1_object_get_desc() {
    Object *o;
    o = object_create(1);
    object_set_desc(o, "test description");
    PRINT_TEST_RESULT(strcmp(object_get_desc(o), "test description") == 0);
    object_destroy(o);
}

void test2_object_get_desc() {
    PRINT_TEST_RESULT(object_get_desc(NULL) == NULL);
}

void test1_object_set_health() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_health(o, -3) == OK);
    object_destroy(o);
}

void test2_object_set_health() {
    PRINT_TEST_RESULT(object_set_health(NULL, 3) == ERROR);
}

void test1_object_get_health() {
    Object *o;
    o = object_create(1);
    object_set_health(o, 5);
    PRINT_TEST_RESULT(object_get_health(o) == 5);
    object_destroy(o);
}

void test2_object_get_health() {
    PRINT_TEST_RESULT(object_get_health(NULL) == -1);
}

void test1_object_set_movable() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
    object_destroy(o);
}

void test2_object_set_movable() {
    PRINT_TEST_RESULT(object_set_movable(NULL, TRUE) == ERROR);
}

void test1_object_get_movable() {
    Object *o;
    o = object_create(1);
    object_set_movable(o, TRUE);
    PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
    object_destroy(o);
}

void test2_object_get_movable() {
    PRINT_TEST_RESULT(object_get_movable(NULL) == FALSE);
}

void test1_object_set_dependency() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_dependency(o, 10) == OK);
    object_destroy(o);
}

void test2_object_set_dependency() {
    PRINT_TEST_RESULT(object_set_dependency(NULL, 10) == ERROR);
}

void test1_object_get_dependency() {
    Object *o;
    o = object_create(1);
    object_set_dependency(o, 10);
    PRINT_TEST_RESULT(object_get_dependency(o) == 10);
    object_destroy(o);
}

void test2_object_get_dependency() {
    PRINT_TEST_RESULT(object_get_dependency(NULL) == NO_ID);
}

void test1_object_set_open() {
    Object *o;
    o = object_create(1);
    PRINT_TEST_RESULT(object_set_open(o, 20) == OK);
    object_destroy(o);
}

void test2_object_set_open() {
    PRINT_TEST_RESULT(object_set_open(NULL, 20) == ERROR);
}

void test1_object_get_open() {
    Object *o;
    o = object_create(1);
    object_set_open(o, 20);
    PRINT_TEST_RESULT(object_get_open(o) == 20);
    object_destroy(o);
}

void test2_object_get_open() {
    PRINT_TEST_RESULT(object_get_open(NULL) == NO_ID);
}
