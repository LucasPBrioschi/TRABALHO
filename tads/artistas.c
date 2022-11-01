#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "artistas.h"

Artista *Artista_aloca(int qtd_alocados){
    Artista *a = (Artista *)calloc(qtd_alocados, sizeof(Artista));
    for(int i = 0; i < qtd_alocados; i++){
        a[i].nome = (char *)malloc(500 * sizeof(char));
        a[i].id = (char *)malloc(500 * sizeof(char));
        //genero
        a[i].genero = (char **)malloc(5 * sizeof(char *));
        for(int j = 0; j < 5; j++){
            a[i].genero[j] = (char *)malloc(50 * sizeof(char));
        }
        a[i].generos_alocados = 5;
        a[i].n_generos_lidos = 0;
    }
    return a;
}

Artista *Artista_realoca(Artista *a, int *qtd_alocados){
    Artista *a2 = (Artista *)realloc(a, (*qtd_alocados * 2) * sizeof(Artista));
    for(int i = *qtd_alocados; i < (*qtd_alocados * 2); i++){
        a2[i].nome = (char *)malloc(500 * sizeof(char));
        a2[i].id = (char *)malloc(500 * sizeof(char));
        //genero
        a2[i].genero = (char **)malloc(5 * sizeof(char *));
        for(int j = 0; j < 5; j++){
            a2[i].genero[j] = (char *)malloc(50 * sizeof(char));
        }
        a2[i].generos_alocados = 5;
        a2[i].n_generos_lidos = 0;
    }
    *qtd_alocados *= 2;   

    return a2;
}

void Artista_le(Artista *a, FILE *entrada, int indice_artista){
    char verificador = '0'; // verifica se so possui um genero ou mais
    int num_generos_lidos = 0;
    fscanf(entrada,"%[^;];%lf;%[^|;]%c", a[indice_artista].id, &a[indice_artista].seguidores,
            a[indice_artista].genero[num_generos_lidos], &verificador);

    num_generos_lidos++;

    while(verificador == '|'){
        fscanf(entrada,"%[^|;]%c", a[indice_artista].genero[num_generos_lidos], &verificador);
        num_generos_lidos++;
        if(num_generos_lidos >= a[indice_artista].generos_alocados-1){
            a[indice_artista].genero = Artista_genero_realoca(a[indice_artista].genero, 
                                        &a[indice_artista].generos_alocados);
        }
    }
    fscanf(entrada, "%[^;];%d\n", a[indice_artista].nome, &a[indice_artista].popularidade);

    a[indice_artista].n_generos_lidos = num_generos_lidos;
    a[indice_artista].posicao_vetor = indice_artista;
}

char **Artista_genero_realoca(char **genero, int *qtd_alocados){
    char **g2 = (char **)realloc(genero, (*qtd_alocados * 2) * sizeof(char *));
    for(int i = *qtd_alocados; i < *qtd_alocados * 2; i++){
        g2[i] = (char *)malloc(50 * sizeof(char));
    } 
    (*qtd_alocados) = 2 * (*qtd_alocados);
    return g2;
}

void Artista_imprime(Artista a, FILE *saida){
    fprintf(saida,"ID: %s\nSeguidores: %.1f\n", a.id, a.seguidores);
    fprintf(saida,"Generos: ");
    for(int i = 0; i < a.n_generos_lidos; i++){
        
        if(i == a.n_generos_lidos -1){
            fprintf(saida,"%s\n", a.genero[i]);    
        }else{
            fprintf(saida,"%s|", a.genero[i]);
        }
    }
    fprintf(saida,"Nome: %s\nPopularidade: %d\n", a.nome, a.popularidade);
    fprintf(saida,"\n");

}

void Artista_libera(Artista *a, int qtd_artistas_alocados){
    for(int i = 0; i < qtd_artistas_alocados; i++){
        free(a[i].nome);
        free(a[i].id);
        for(int j = 0; j < a[i].generos_alocados; j++){
            free(a[i].genero[j]);
        } 
        free(a[i].genero); 
    }
    
    free(a);
}