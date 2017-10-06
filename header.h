#include "gerador.h"

typedef struct {
    char tipoImovel;
    char endereco[50];
    short int numQuartos;
    double precoAluguel;
    int dataDisponivel;
} Imovel;