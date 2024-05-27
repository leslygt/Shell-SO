#ifndef HISTORICO_COMANDO_H
#define HISTORICO_COMANDO_H

#define MAX_HISTORY_SIZE 100
#define MAX_COMMAND_LENGTH 1024

int readCommandHistory(char history[][MAX_COMMAND_LENGTH]);
void selectAndEditCommand(char history[][MAX_COMMAND_LENGTH], int numCommands);

#endif
