/**
 * @brief Contiene el bucle principal de ejecución del juego
 *
 * @file game_loop.c
 * @author 
 * @version 1.0
 * @date 15-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"
#include "game_actions.h"
#include "game_rules.h"
#include <time.h>

void game_loop_update_turn(Game *game, Command *command);

void game_loop_update_turn(Game *game, Command *command)
{
  char turn_message[WORD_SIZE] = "";

  /* Comprobaciones de seguridad basicas */
  if (!game || !command)
  {
    return;
  }

  if (game_get_last_command_status(game) == ERROR)
  {
    return;
  }

  if (command_get_code(command) == MOVE)
  {
    game_next_turn(game);
    sprintf(turn_message, "Te has movido. Turno del Jugador %d.", game_get_turn(game) + 1);
    game_set_chat_message(game, turn_message);
  }
}

int main(int argc, char *argv[])
{
  Game *game = NULL;
  Command *command = NULL;
  Graphic_engine *gengine;
  FILE *log_file = NULL;
  char *log_filename = NULL;
  GameRules *rules = NULL;
  int determinista = 0;
  int i;
  /* Comprueba los argumentos de entrada */
  if (argc < 2)
  {
    fprintf(stderr, "Uso: %s <game_data_file> [-l <log_file>] [-d]\n", argv[0]);
    return 1;
  }

  /*Gestionar argumentos de entrada -l y -d*/
  for (i = 2; i < argc; i++)
  {
    if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
        log_filename = argv[++i];
        log_file = fopen(log_filename, "w");
        if (log_file == NULL) {
            fprintf(stderr, "Error opening log file.\n");
            return 1;
        }
    } else if (strcmp(argv[i], "-d") == 0) {
        determinista = 1; /* Desactiva la aleatoriedad */
    }
  }

  if (determinista) {
      srand(1); /* Semilla fija para resultados predecibles */
  } else {
      srand(time(NULL)); /* Semilla basada en el tiempo para aleatoriedad real */
  }
  printf("Funciona\n");
printf("se abre");
  /* Inicializacion del juego desde archivo */
  if (game_create_from_file(&game, argv[1]) == ERROR)
  {
    fprintf(stderr, "Error while initializing game.\n");
    if (log_file)
    {
      fclose(log_file);
    }
    return 1;
  }
printf("se crea");
  /* Inicializacion del motor grafico */
  if ((gengine = graphic_engine_create()) == NULL)
  {
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(game);
    if (log_file)
    {
      fclose(log_file);
    }
    return 1;
  }
  rules = game_rules_create();
  command = game_get_last_command(game);

  /* Bucle principal del juego */
  while ((command_get_code(command) != EXIT) && !game_get_finished(game))
  {
    /* Actualiza la interfaz grafica pre-comando */
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), FALSE);

    /* Obtiene la entrada del usuario */
    command_get_user_input(command);

    /* Procesa el comando y actualiza el estado */
    game_set_last_command_status(game, game_actions_update(game, command));

    /* Registro en log si aplica */
    if (log_file)
    {
      char *last_input = command_get_last_input(command);
      if (last_input)
      {
        last_input[strcspn(last_input, "\n")] = 0;
        fprintf(log_file, "%s: %s\n", last_input, game_get_last_command_status(game) == OK ? "OK" : "ERROR");
      }
    }

    if (command_get_code(command) == EXIT || game_get_finished(game)) break;

    
    /* Actualiza la interfaz grafica post-comando */
    graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), TRUE);
    sleep(1);
    if (!determinista)
    {
      game_rules_update(rules, game);
    }

    /* Procesa el cambio de turno solo tras acciones validas de exploracion */
    game_loop_update_turn(game, command);
  }

  /* Imprime el estado final antes de salir */
  graphic_engine_paint_game(gengine, game, game_get_last_command_status(game), TRUE);

  /* Liberacion de recursos generales */
  game_destroy(game);
  graphic_engine_destroy(gengine);

  if (log_file)
  {
    fclose(log_file);
  }
  game_rules_destroy(rules);
  return 0;
}
