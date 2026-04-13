/**
 * @brief Contiene el bucle principal del juego
 *
 * @file game_loop.c
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"
#include "game.h"
#include "command.h"

int game_loop_clean_up(FILE *f, int exit_code);

int main(int argc, char *argv[]) {
    Game *game = NULL;
    Graphic_engine *gengine = NULL;
    Command *cmd = NULL;
    Status st = OK;
    extern char *cmd_to_str[N_CMD][N_CMDT];
    FILE *log_file = NULL;

    if (argc < 2) {
        fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>]\n", argv[0]);
        return 1;
    }

    if (argc == 4 && strcmp(argv[2], "-l") == 0) {
        log_file = fopen(argv[3], "w");
        if (!log_file) {
            fprintf(stderr, "Error opening log file.\n");
            return 1;
        }
    }

    game = game_create();
    if (!game) return game_loop_clean_up(log_file, 1);

    if (game_create_from_file(game, argv[1]) == ERROR) {
        fprintf(stderr, "Error loading game data.\n");
        game_destroy(game);
        return game_loop_clean_up(log_file, 1);
    }

    gengine = graphic_engine_create();
    if (!gengine) {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return game_loop_clean_up(log_file, 1);
    }

    /* Bucle principal */
    while ((command_get_code(game_get_last_command(game)) != EXIT) && !game_is_over(game)) {
        graphic_engine_paint_game(gengine, game, st, TRUE);
        
        cmd = command_get_user_input();
        st = game_update(game, cmd);

        if (log_file) {
            fprintf(log_file, "%s (%s): %s\n", 
                    cmd_to_str[command_get_code(cmd) - NO_CMD][CMDL], 
                    cmd_to_str[command_get_code(cmd) - NO_CMD][CMDS], 
                    st == OK ? "OK" : "ERROR");
        }
        
        command_destroy(cmd);
    }

    /* Pinta el estado final */
    graphic_engine_paint_game(gengine, game, st, TRUE);
    
    if (game_is_over(game)) {
        printf("\n\n >>> GAME OVER <<<\n\n");
    }

    game_destroy(game);
    graphic_engine_destroy(gengine);
    
    return game_loop_clean_up(log_file, 0);
}

int game_loop_clean_up(FILE *f, int exit_code) {
    if (f) fclose(f);
    return exit_code;
}