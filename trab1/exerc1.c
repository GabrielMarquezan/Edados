
/*
Faça um programa que trate uma matriz diagonal de inteiros. O programa deve armazenar os valores da diagonal
principal (que são os não nulos) em um vetor v, e os demais valores (que são nulos) não devem ser lidos nem
armazenados em lugar algum. O programa deve contemplar as operações de:
- criação da matriz;
- preenchimento da matriz;
- impressão da matriz;
- consulta de um determinado elemento da matriz (para consultar um elemento, informe a linha e a coluna onde ele se
encontra);
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct diagonal
{
    int ordem; //ordem da matriz
    int* v; //o tamanho do vetor é igual a ordem da matriz. Os elementos da diagonal principal são armazenados neste vetor
};
typedef struct diagonal Diagonal;

typedef struct matriz
{
    int** matriz;
    Diagonal* diagonal_info;
} Matriz;

int decide_ordem_matriz();
int* aloca_vetor(int tamanho);
void preenche_vetor_diagonal(Diagonal* diagonal_info);
void aloca_matriz(Matriz* matriz);
void preenche_matriz(Matriz* matriz);
void imprime_matriz(Matriz* matriz);
bool consultar_elemento(Matriz* matriz);
bool deseja_continuar();
void desaloca_matriz_e_vetor(Matriz* matriz);

int main()
{
    int ordem = decide_ordem_matriz();
    Diagonal diagonal_info = {ordem, aloca_vetor(ordem)};
    Diagonal* ponteiro_diagonal = &diagonal_info;
    Matriz matriz = {NULL, ponteiro_diagonal};
    Matriz* ponteiro_matriz = &matriz;
    bool continuar = true;

    aloca_matriz(ponteiro_matriz);
    preenche_vetor_diagonal(ponteiro_diagonal);

    while(continuar)
    {
        preenche_matriz(ponteiro_matriz);
        imprime_matriz(ponteiro_matriz);
        consultar_elemento(ponteiro_matriz);
        continuar = deseja_continuar();
    }

    desaloca_matriz_e_vetor(ponteiro_matriz);
}

int decide_ordem_matriz()
{
    int ordem = -1;
    while(ordem < 1)
    {
        printf("Qual será a ordem da matriz quadrada?\n");
        scanf("%d", &ordem);
    }
    return ordem;
}

int* aloca_vetor(int tamanho)
{
    int* vetor = malloc(tamanho * sizeof(int));
    return vetor;
}

void preenche_vetor_diagonal(Diagonal* diagonal_info)
{
    for(int i = 0; i < diagonal_info->ordem; i++)
    {
        printf("Insira o número da posição %d,%d: ", i+1, i+1);
        scanf("%d", &diagonal_info->v[i]);
    }
}

void aloca_matriz(Matriz* matriz)
{
    int ordem_da_matriz = matriz->diagonal_info->ordem;
    matriz->matriz = malloc(ordem_da_matriz * sizeof(int*));
    for(int i = 0; i < ordem_da_matriz; i++) matriz->matriz[i] = malloc(ordem_da_matriz * sizeof(int));
}

void preenche_matriz(Matriz* matriz)
{
    int ordem_da_matriz = matriz->diagonal_info->ordem;
    for(int i = 0; i < ordem_da_matriz; i++) matriz->matriz[i][i] = matriz->diagonal_info->v[i];
}

void imprime_matriz(Matriz* matriz)
{
    int ordem_da_matriz = matriz->diagonal_info->ordem;
    
    printf("\n       ");

    //Imprime o índice das colunas
    for(int i = 0; i < ordem_da_matriz; i++)
    {
        if(i < 9) printf("|  00%d  ", i + 1);
        else if(i < 99) printf("|  0%d  ", i + 1);
        else printf("|  %d  ", i + 1);
    }

    printf("|\n");

    for(int i = 0; i < ordem_da_matriz; i++)
    {
        for(int k = 0; k < 8 * ordem_da_matriz + 8; k++) printf("-"); //Divide as linhas
        
        //Imprime o índice das linhas
        if(i < 9) printf("\n  00%d  ", i + 1); 
        else if(i < 99) printf("\n  0%d  ", i + 1);
        else printf("\n  %d  ", i + 1);

        for(int j = 0; j < ordem_da_matriz; j++) 
        {
            if(i == j) 
            {
                if(matriz->matriz[i][j] < 10) printf("|  00%d  ", matriz->matriz[i][j]);
                else if(matriz->matriz[i][j] < 100) printf("|  0%d  ", matriz->matriz[i][j]);
                else printf("|  %d  ", matriz->matriz[i][j]);
            }
            else printf("|  000  ");
        }
        printf("|\n");
    }

    printf("\n");
}

bool consultar_elemento(Matriz* matriz)
{
    int elemento = 0;
    printf("Insira o elemento você deseja pesquisar: ");
    scanf("%d", &elemento);

    if(elemento == 0)
    {
        printf("Elemento encontrado na posição 1, 2\n\n");
        return true;
    }

    int ordem_da_matriz = matriz->diagonal_info->ordem;
    for(int i = 0; i < ordem_da_matriz; i++)
    {
        if(matriz->matriz[i][i] == elemento)
        {
            printf("Elemento encontrado na posição %d, %d\n\n", i+1, i+1);
            return true;
        }
    }

    printf("Elemento não encontrado!\n\n");
    return false;
}

bool deseja_continuar()
{
    int resposta = -1;
    
    while(true)
    {
        printf("Você deseja continuar?\nSim - digite 1\nNão - digite 0\n");
        printf("Resposta: ");
        scanf("%d", &resposta);

        if(resposta == 1) return true;
        else if(resposta == 0) return false;
    }  
}

void desaloca_matriz_e_vetor(Matriz* matriz)
{
    for(int i = 0; i < matriz->diagonal_info->ordem; i++) free(matriz->matriz[i]);
    free(matriz->matriz);
    free(matriz->diagonal_info->v);
}