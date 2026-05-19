# SCRATCHPAD

## Active
- Repo clonado: `/home/ikerpapu/informatica/pprog-2/pprog-junio`.
- Rama actual: `main`.
- Tarea actual: parches aplicados y verificados para `save/load`, tests y recorrido.
- Enunciado prioritario externo: `/home/ikerpapu/informatica/pprog-2/PPROG-25_26-Extraordinaria.pdf`.

## Pending
- Doxygen no esta instalado en esta maquina, asi que `make doxygen` falla por entorno aunque el target existe.

## Findings
- `make clean && make && make tests` compila sin warnings.
- `./run_tests.sh 0` pasa todos los tests unitarios disponibles.
- `save/load/save` mantiene 78 entidades y no duplica el estado.
- `take Cable` + `save/load/save` conserva el objeto en mochila y fuera del mapa.
- `colab Hacker` + `save/load/save` conserva colaboradores en ambos jugadores.
- `recorrido_neocorp.cmd` se ejecuta completo sin lineas `ERROR`.
- Valgrind sobre `colab + save/load` termina con 0 errores y 0 leaks.

## History
- 2026-05-16: Inicializada memoria local `codex/` tras clonar `hazyy007/pprog-junio`.
- 2026-05-16: Leido enunciado de extraordinaria; F10(j) y F11 piden guardar/cargar partidas. Diagnostico: ambos comandos existen pero no cumplen bien.
- 2026-05-16: Corregidos `save/load`, tests, `colab/open` de equipo y recorrido de Neocorp; queda pendiente solo generar Doxygen cuando la herramienta este instalada.
