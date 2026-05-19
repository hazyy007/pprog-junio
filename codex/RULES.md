# RULES

## Estilo de cambios
- Mantener el estilo de proyecto de estudiante: C sencillo, funciones cortas cuando se pueda, sin abstracciones nuevas si no hacen falta.
- Tocar la base de codigo lo minimo posible. Para bugs concretos, preferir parches locales en las funciones afectadas.
- No reescribir modulos enteros ni "limpiar" formato de archivos que no se estan arreglando.
- Usar los tipos y convenciones existentes: `Status`, `OK`, `ERROR`, `Id`, `NO_ID`, `BOOL`, `TRUE`, `FALSE`.
- Mantener compatibilidad con el `makefile`: `gcc -g -Wall -pedantic -ansi`.
- Evitar C moderno: no `//`, no declaraciones mezcladas con codigo si se puede evitar, no librerias nuevas innecesarias.

## Estilo de codigo local
- Comentarios en castellano, simples y funcionales, parecidos a los actuales.
- Validar punteros al principio de las funciones y devolver `ERROR`, `NULL` o `NO_ID` segun toque.
- El parser del fichero de juego usa lineas `#p:`, `#s:`, `#o:`, `#l:`, `#c:` separadas por `|`.
- Si se modifica guardado/carga, el formato escrito debe seguir siendo legible por las funciones `game_managment_load_*`. En jugadores, tras `max_objs` se guarda el colaborador y despues los objetos de mochila.
- No cambiar requisitos o comportamiento no relacionado con `save/load` sin avisar primero.
