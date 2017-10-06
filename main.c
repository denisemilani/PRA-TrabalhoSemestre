#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "menu.h"
#include "gerador.h"
#include "utils.h"

int main()
{
    gerarSemente();
    setWindowTitle("Trabalho PRA v. 1");
    convEnderecos();
    carregarEnderecos();

    char loop = 0;

    while (loop < 1) {
        int opcao = menu();

        switch(opcao) {
            case 1: gerarArquivoQtd(); break;
            case 2: gerarArquivoTam(); break;
            case 3: gerar1GB(); break;
            case 4: lerArquivoQtd(); break;
            case 5: lerArquivoTam(); break;
            case 20: printf("%d", gerarInteiro(5, 25)); getchar(); break;
            case 23: printf("%d", gerarData()); getchar(); break;
            case 24: {
                char *t = gerarEndereco();
                printf("%s\n", t);
                free(t);
                getchar();
            } break;
            case 25: printf("%lf", gerarDouble(0, 2000)); getchar(); break;
            case 26: {
                Imovel *imovel = gerarImovel();

                if (imovel->tipoImovel == '1') {
                    printf("Tipo de imovel: %s\n", "Apto");
                } else {
                    printf("Tipo de imovel: %s\n", "Casa");
                }
                printf("Endereco: %s", imovel->endereco);
                printf("Numero de quartos: %d\n", imovel->numQuartos);
                printf("Preco aluguel: R$ %2.lf\n", imovel->precoAluguel);
                printf("Data de disponibilidade: %d\n", imovel->dataDisponivel);
                printf("\n----------------------------------------------\n\n");
                getchar();
            } break;
            case 27: break;
            case 28: break;
            case 29: break;

            default: return 0;
        }
    }

    return 1;
}
