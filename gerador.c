#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "header.h"

void gerarSemente() {
    srand(time(NULL));
}

int gerarInteiro(int minimo, int maximo) {
    int numeroAleatorio;

    if (minimo > maximo) {
        return 0;
    }

    numeroAleatorio = rand() % (maximo - minimo + 1) + minimo;

    return numeroAleatorio;
}

double gerarDouble(int minimo, int maximo) {
    double numeroAleatorio;

    if (minimo < 0) {
        minimo = 0;
    }

    if (maximo < 1) {
        maximo = 1;
    }

    numeroAleatorio = rand() % ((maximo - minimo + 1) + minimo); //- (pow(rand(), 1));

    if (numeroAleatorio >= 1) {
        numeroAleatorio -= (rand() % 1000) / 1000.0;
    }

    return numeroAleatorio;
}

int gerarData() {

    int dtAleatoria;
    int vAno;
    int vMes;
    int vDia;

    vAno = rand() % (18) + 2000;
    vMes = rand() % (12) + 1;
    vDia = rand() % (28) + 1;

    dtAleatoria = (vAno*10000) + (vMes*100) + (vDia);

    return dtAleatoria ;
}

void convEnderecos() {
    FILE *arqEnderecos;
    int qtEnderecos = 15;
    char pEnd [qtEnderecos][50];
    int i;

    if ((arqEnderecos = fopen("arquivos/endereços.txt", "r")) == NULL) {
        printf("\n\nErro ao abrir o arquivo de enderecos!\n\n");
        getchar();
        return NULL;
    } else {
        for ( i = 0; i < qtEnderecos; i++ ) {
            fgets(pEnd[i], sizeof(pEnd), arqEnderecos);
        }
    }

    fclose(arqEnderecos);

    if ((arqEnderecos = fopen("arquivos/endereços.bin", "wb")) == NULL) {
        printf("\n\nErro ao abrir arquivo de enderecos!\n\n");
        getchar();
        return NULL;
    } else {
        for ( i = 0; i < qtEnderecos; i++ ) {
            fwrite(&pEnd[i], sizeof(char) * 50, 1, arqEnderecos);
        }
    }

    fclose(arqEnderecos);
}

const char *gerarEndereco() {
    char *enderecoAleatorio = malloc(sizeof(char) * 50);

    strcpy(enderecoAleatorio, pEnd2[gerarInteiro(0, 15)]);

    return enderecoAleatorio;
}

void carregarEnderecos () {
    FILE *arqEnderecos;
    int i;

    if ((arqEnderecos = fopen("arquivos/endereços.bin", "rb")) == NULL) {
        printf("\n\nErro ao abrir o arquivo de enderecos!\n\n");
        getchar();
        return NULL;
    } else {
        for ( i = 0; i < 15; i++ ) {
            fread(&pEnd2[i], sizeof(char) * 50, 1, arqEnderecos);
        }
    }
}

Imovel* gerarImovel() {
    Imovel *im = malloc(sizeof(Imovel));
    char *endereco = gerarEndereco();

    im->tipoImovel = gerarInteiro(0, 1) + '0';
    strcpy(im->endereco, endereco);
    im->numQuartos = gerarInteiro(1, 5);
    im->precoAluguel = gerarDouble(400, 10000);
    im->dataDisponivel = gerarData();

    free(endereco);

    return im;
}
