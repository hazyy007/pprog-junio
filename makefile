# ==============================================================================
# Makefile para el proyecto del Juego (Fusión)
# ==============================================================================

# Variables de compilación
CC = gcc
CFLAGS = -Wall -pedantic -g
LDFLAGS = -L. -lscreen

# Nombre del ejecutable
EXE = castle_game

# Archivos objeto requeridos
OBJS = command.o \
       space.o \
       game_reader.o \
       graphic_engine.o \
       object.o \
       character.o \
       set.o \
       link.o \
       inventory.o \
       player.o \
       game_actions.o \
       game.o \
       game_loop.o

# Regla principal (se ejecuta por defecto al hacer 'make')
all: $(EXE)

# Enlazado final del ejecutable
$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

# Regla genérica para compilar los .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Limpiar archivos compilados (útil antes de una recompilación limpia)
clean:
	rm -f *.o $(EXE)

# Comando para ejecutar el juego directamente
run: $(EXE)
	./$(EXE) castle.dat

# Comando para ejecutar el juego con Valgrind (para buscar fugas de memoria)
valgrind: $(EXE)
	valgrind --leak-check=full --track-origins=yes ./$(EXE) castle.dat

# Evita conflictos con archivos que se llamen igual que las reglas
.PHONY: all clean run valgrind