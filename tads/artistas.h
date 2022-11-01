#ifndef ARTISTAS_T_
#define ARTISTAS_T_
#include <stdio.h>

typedef struct 
{
    char *id;
    double seguidores;
    char **genero;
    int n_generos_lidos;
    int generos_alocados;
    char *nome;
    int popularidade;
    int posicao_vetor;

}Artista;

Artista *Artista_aloca(int qtd_alocados);
/**
 * qtd_alocados = artistatas a serem alocados
 * essa funcao aloca 5 generos para cada artista pode mudar dps
*/
Artista *Artista_realoca(Artista *a, int *qtd_alocados);

char **Artista_genero_realoca(char **genero, int *qtd_alocados); // realoca genero

void Artista_le(Artista *a, FILE *entrada, int indice_artista); // le de um arquivo 
void Artista_imprime(Artista a, FILE *saida); // imprime um unico artista
void Artista_libera(Artista *a, int qtd_artistas_alocados);

#endif