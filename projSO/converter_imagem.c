#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void converter_imagem(const char *imagem){
    char nome_saida[1000];
    FILE *arquivo_saida;

    sprintf(nome_saida, "%s.png", strtok(strdup(imagem), ".")); // Obtém o nome do arquivo de saída com extensão .png

    if ((arquivo_saida = fopen(nome_saida, "r"))) { // Verifica se o arquivo de saída já existe
        fclose(arquivo_saida);
        printf("Arquivo existente. Exclua antes de converter.\n");
        return;
    }

    if (system("convert --version") != 0) { // Verifica se o comando 'convert' está disponível
        printf("O comando 'convert' não está disponível. Certifique-se de ter o ImageMagick instalado.\n");
        return;
    }
char comando[2000];
    sprintf(comando, "convert \"%s\" \"%s\"", imagem, nome_saida); // Cria o comando de conversão

    if(system(comando) == 0) {
        printf("Conversão concluída: %s\n", nome_saida); // Exibe mensagem de sucesso
    } else {
        printf("Erro ao converter imagem.\n"); // Exibe mensagem de erro
    }
}

int main(int argc, char *argv[]){
    if(argc != 2 ) {
        printf("O número de argumentos está incorreto. Deve inserir 1 argumento: o nome da imagem.\n");
        return 1;
    } else {
        converter_imagem(argv[1]);
        return 0;
    }
}