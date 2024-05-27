#include <stdio.h>
#include <string.h>

// Forward declarations of functions from other files
void iniciar_converter(int argc, char *argv[]);
void iniciar_historico();
void iniciar_task(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command> [options]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "convert") == 0) {
        iniciar_converter(argc - 1, &argv[1]);  // Adjust argc and argv for the submodule
    } else if (strcmp(argv[1], "history") == 0) {
        iniciar_historico();
    } else if (strcmp(argv[1], "task") == 0) {
        iniciar_task(argc - 1, &argv[1]);  // Adjust argc and argv for the submodule
    } else {
        printf("Invalid command '%s'. Valid commands are 'convert', 'history', 'task'.\n", argv[1]);
        return 1;
    }

    return 0;
}
