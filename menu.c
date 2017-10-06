#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include "utils.h"

int menu() {
    int opcao;
    int opDisponiveis[] = {1, 2, 3, 4, 5, 9, 20, 23, 24, 25, 26, 27, 28, 29};

    //setWindowSize("80, 30");

    do {
        clearScreen();
        printf(" ----------------------------MENU----------------------------\n\n");
        printf(" [1] - Gerar arquivo por quantidade de registros\n");
        printf(" [2] - Gerar arquivo por tamanho\n");
        printf(" [3] - Gerar 1GB de registros aleatorios com contador de tempo\n");
        printf(" [4] - Ler arquivo por quantidade de registros\n");
        printf(" [5] - [WIP] Ler arquivo por tamanho\n");
        printf(" [9] - Sair\n\n ");
        scanf("%d", &opcao);
        getchar();
    } while (verificarOpcao(opcao, &opDisponiveis, sizeof(opDisponiveis)) == 0);

    clearScreen();
    return opcao;
}

int verificarOpcao(int opcao, int *opDisponiveis, int tamOpDisponiveis) {
    int qtOpcoes = tamOpDisponiveis / sizeof(int);
    int i;

    for ( i = 0; i < qtOpcoes; i++ ) {
        if (opcao == opDisponiveis[i]) {
            return 1;
        }
    }

    return 0;
}

void gerarArquivoQtd() {
    int numReg;
    int i;
    char nomeArquivo[50];
    char enderecoArquivo[80];
    FILE *arq;

    printf("De um nome ao arquivo binario: ");
    scanf("%s", &nomeArquivo);
    getchar();

    strcpy(enderecoArquivo, "");
    strcat(enderecoArquivo, "arquivos/");
    strcat(enderecoArquivo, nomeArquivo);

    printf("%s\n", enderecoArquivo);

    do {
        printf("\nGerar quantos registros (max de 22369621)? ");
        scanf("%d", &numReg);
        getchar();
        if (numReg > 22369621) {
            printf("\n\nNumero de registros acima do permitido!\n\n");
        }
        printf("----------------------------\n\n");
    } while (numReg > 22369621);


    if ((arq = fopen(enderecoArquivo, "wb+")) == NULL) {
        printf("Erro ao criar o arquivo!");
        getchar();
    } else {

        for ( i = 0; i < numReg; i++ ) {
            Imovel *imovel = gerarImovel();

            fwrite(imovel, sizeof(Imovel), 1, arq);
            free(imovel);
        }

        fclose(arq);

        printf("Arquivo gerado com sucesso!");
        getchar();
    }
}

void gerarArquivoTam() {
    int tamReg;
    int i;
    char nomeArquivo[50];
    char enderecoArquivo[80];
    FILE *arq;

    printf("Dê um nome ao arquivo binario: ");
    scanf("%s", &nomeArquivo);
    getchar();

    strcpy(enderecoArquivo, "");
    strcat(enderecoArquivo, "arquivos/");
    strcat(enderecoArquivo, nomeArquivo);

    printf("%s\n", enderecoArquivo);

    do {
        printf("\nQual o tamanho do arquivo (max de 1610612736 bytes)? ");
        scanf("%d", &tamReg);
        getchar();
        if (tamReg > 1610612736) {
            printf("\n\nTamanho do arquivo maior do que o permitido!\n\n");
        }
        printf("----------------------------\n\n");
    } while(tamReg > 1610612736);

    if ((arq = fopen(enderecoArquivo, "wb+")) == NULL) {
        printf("Erro ao criar o arquivo!");
        getchar();
    } else {


        printf("Serao inseridos %d registros em %d bytes.\n\n", tamReg/sizeof(Imovel), (tamReg/sizeof(Imovel))*sizeof(Imovel));
        getchar();

        for ( i = 0; i < (tamReg/sizeof(Imovel)); i++ ) {
            Imovel *imovel = gerarImovel();

            fwrite(imovel, sizeof(Imovel), 1, arq);
            free(imovel);
        }

        fclose(arq);

        printf("Arquivo gerado com sucesso!");
        getchar();
    }
}

void gerar1GB() {
    FILE *arq;
    int tempoInicial = time(NULL);
    int tempoFinal;

    if ((arq = fopen("arquivos/1GB.bin", "wb+")) == NULL) {
        printf("Erro ao criar o arquivo!");
        getchar();
    } else {
        int i;

        double progresso = 0;

        for ( i = 0; i < 14913081; i++ ) {
            Imovel *imovel = gerarImovel();

            fwrite(imovel, sizeof(Imovel), 1, arq);
            free(imovel);

            if ((i / 14913081.0 * 100) - progresso >= 0.01) {
                progresso = (i / 14913081.0) * 100;
                gotoxy(3,1);
                printf("Progresso: %3.2lf%%", progresso);
                gotoxy(3,2);
                printf("Tempo: %ds", time(NULL) - tempoInicial);
            }
        }

        fclose(arq);

        tempoFinal = time(NULL);

        printf("\n\n  Arquivo gerado com sucesso!\n");
        printf("  Tempo utilizado: %ds", tempoFinal - tempoInicial);
        getchar();
    }
}

void lerArquivoQtd() {
    int numReg;
    int i;
    char nomeArquivo[50];
    char enderecoArquivo[80];
    FILE *arq;

    printf("Insira o nome do arquivo binario: ");
    scanf("%s", &nomeArquivo);
    getchar();

    strcpy(enderecoArquivo, "");
    strcat(enderecoArquivo, "arquivos/");
    strcat(enderecoArquivo, nomeArquivo);

    printf("%s\n", enderecoArquivo);

    do {
        printf("\nLer quantos registros (max de 5000)? ");
        scanf("%d", &numReg);
        getchar();
        if (numReg > 5000) {
            printf("\n\nNumero de registros acima do permitido!\n\n");
        }
        printf("----------------------------\n\n");
    } while (numReg > 5000);


    if ((arq = fopen(enderecoArquivo, "rb")) == NULL) {
        printf("Erro ao abrir o arquivo!");
        getchar();
    } else {
        Imovel *imovel = malloc(sizeof(Imovel) * numReg);

        for ( i = 0; i < numReg; i++ ) {
            fread(&imovel[i], sizeof(Imovel), 1, arq);
        }

        fclose(arq);

        for ( i = 0; i < numReg; i++ ) {
            if (imovel[i].tipoImovel == 1) {
                printf("Tipo de imovel: %s\n", "Apto");
            } else {
                printf("Tipo de imovel: %s\n", "Casa");
            }
            printf("Endereco: %s", imovel[i].endereco);
            printf("Numero de quartos: %d\n", imovel[i].numQuartos);
            printf("Preco aluguel: R$ %2.lf\n", imovel[i].precoAluguel);
            printf("Data de disponibilidade: %d\n", imovel[i].dataDisponivel);
            printf("\n----------------------------------------------\n\n");
        }


        free(imovel);

        printf("Arquivo lido com sucesso!");
        getchar();
    }
}

void lerArquivoTam() {
    printf("WIP");
    getchar();
}
