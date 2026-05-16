# LESSONS

## 2026-05-16
- La carpeta indicada inicialmente por el entorno, `/home/ikerpapu/informatica/edat-2`, no existia al empezar este trabajo. La carpeta con los enunciados de PPROG extraordinaria era `/home/ikerpapu/informatica/pprog-2`, asi que el repo se clono en `/home/ikerpapu/informatica/pprog-2/pprog-junio`.
- Para este repo hay que respetar el aspecto de codigo de estudiante y no hacer refactors grandes: el objetivo es arreglar bugs concretos con cambios pequeños.
- Fallo: `./run_tests.sh 0` da `Permission denied` porque el script no tiene permiso de ejecucion. Prevencion: ejecutar con `bash run_tests.sh 0` o, si Iker lo aprueba, marcarlo executable con `chmod +x run_tests.sh`.
- Fallo: `bash run_tests.sh 0` no compila los tests porque `include/test.h` inicializa `__test_counter`, `__test_passed` y `__pass` como `extern`, y `src/test.c` los vuelve a definir. Prevencion: si se arreglan tests, dejar solo declaraciones `extern` en la cabecera y las definiciones en `src/test.c`.
- Fallo: al leer jugadores, un `|` final podia convertir el salto de linea en id `0` y meter un objeto fantasma en la mochila. Prevencion: despues de `strtol`, comprobar `endptr != toks` antes de aceptar el id.
- Quirk: para que el recorrido multijugador funcione, `colab` debe ser bidireccional y `open` debe aceptar objetos que lleve el colaborador.
- Entorno: `make doxygen` falla con `doxygen: No such file or directory` porque Doxygen no esta instalado en esta maquina.
