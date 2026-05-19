# PROJECT_MAP

## Raiz
- `makefile`: compila `neocorp` y los tests con `-ansi -pedantic`.
- `neocorp.dat`: partida/mapa principal en formato de texto.
- `game1.cmd` y `recorrido_neocorp.cmd`: scripts de comandos para probar recorridos.
- `run_tests.sh`: compila y ejecuta tests, opcionalmente con valgrind.

## include/
- Cabeceras de los TADs principales: `game`, `command`, `space`, `object`, `player`, `character`, `link`, `inventory`, `set`.
- `game_actions.h`: entrada publica para ejecutar comandos.
- `game_managment.h`: carga/guardado de entidades desde fichero.
- `game_reader.h`: lector antiguo/alternativo parecido a `game_managment`.

## src/
- `game_loop.c`: `main`, bucle de juego, lectura de comandos, log y turnos.
- `command.c`: traduce entrada de usuario a `CommandCode` y argumentos.
- `game_actions.c`: implementa comandos como `move`, `take`, `open`, `save`, `load`, etc.
- `game.c`: estructura principal `Game`, getters/setters y colecciones internas.
- `game_managment.c`: carga `#s/#p/#o/#l/#c` y contiene `game_managment_save_game`.
- `graphic_engine.c`: pintado por pantalla.
- `*_test.c`: tests unitarios de TADs.
