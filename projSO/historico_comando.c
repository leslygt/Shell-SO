#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COMMAND_LENGTH 1024
#define MAX_HISTORY_SIZE 1000


// 
void executar_comando(char *comando){
    printf("O comando %s\n esta a ser executado", comando);
    system(comando);
}


int readCommandHistory(char history[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH]) {
    FILE *history_file; // Declara um ponteiro de arquivo para o arquivo de histórico

    int numCommands = 0; // Variável para rastrear o número de comandos no histórico
    history_file = fopen("/home/kali/.zsh_history", "r");

    if (history_file == NULL){
        printf("Nao foi possivel abrir o historico");
        exit(1);
    }

  


    //!!CORRECAO!! -> adicionar numCommands < MAX_HISTORY_SIZE antes do fgets no while, assim:
    while (numCommands < MAX_HISTORY_SIZE && fgets(history[numCommands], sizeof(history[0]), history_file) != NULL) { // Lê cada linha do arquivo de histórico e a armazena na matriz
         printf("%d: %s", numCommands + 1, history[numCommands]); // Imprime cada comando do histórico com um número sequencial
        numCommands++; // Incrementa o contador de comandos
    }

    fclose(history_file);
    return numCommands;

}

// Funcao para selecionar e editar comando
void selectAndEditCommand(char history[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH], int numCommands) {
    // Pedir ao utilizador para selecionar um comando para reexecutar ou editar
    int selection; // Variável para armazenar a seleção do usuário
    printf("Enter the number of the command to execute or edit: "); // Solicita ao usuário que selecione um comando para executar ou editar
    scanf("%d", &selection); // Lê a seleção do usuário

    getchar();//Limpa o caractere de nova linha

    if (selection < 1 || selection > numCommands){
        printf("Invalid selection!");
        exit(1);
    }

    //Get selected command char
    char selectedCommand[MAX_COMMAND_LENGTH]; //Declara uma matriz para armazenar o comando selecionado

    strcpy(selectedCommand, history[selection -1]); //Copia o comando selecionado para a variavel selectedCommand 

    

    char editChoice;
    printf("Do you want to edit this command? (y/n): ");
    scanf(" %c", &editChoice);

    getchar();

    if(editChoice == 'Y' || editChoice == 'y'){ 

        printf("Corrently editing this command %s", selectedCommand);
        printf("Enter the edited command: "); // Solicita ao usuário que insira o comando editado

        fgets(selectedCommand, sizeof(selectedCommand), stdin);
        selectedCommand[strcspn(selectedCommand, "\n")] = '\0';
    }

    executar_comando(selectedCommand);

    
}

int main (){
    char history[MAX_HISTORY_SIZE][MAX_COMMAND_LENGTH]; //Declara uma matriz para armazenar o historico de comandos 

    
    int numCommands = readCommandHistory(history); // Read command history into array and get number of commands
    selectAndEditCommand(history, numCommands); // Select and possibly edit a command

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso

}