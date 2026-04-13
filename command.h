/**
 * @brief Define el gestor de comandos del juego
 *
 * @file command.h
 * @author Unai y Alejandro (Fusión)
 * @version 2.0
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 10

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, TAKE, DROP , ATTACK , CHAT, MOVE, INSPECT } CommandCode;

typedef struct _Command Command;

Command* command_create();
void command_destroy(Command* cmd);
Status command_set_code(Command* cmd, CommandCode code);
CommandCode command_get_code(Command* cmd);
Status command_set_arg(Command* cmd, char* arg);
char* command_get_arg(Command* cmd);
Command* command_get_user_input();

#endif