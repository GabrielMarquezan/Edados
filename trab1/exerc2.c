/*
Faça um programa que trate uma matriz esparsa de inteiros. O programa deve armazenar os valores não nulos da
matriz esparsa em uma lista simplesmente encadeada (ver struct Lista), e os demais valores (que são nulos) não devem
ser lidos nem armazenados em lugar algum. O programa deve contemplar as operações de:
- criação da matriz;
- preenchimento da matriz (ler apenas os valores não nulos);
- impressão da matriz;
- consulta de um determinado elemento da matriz (para consultar um elemento, informe a linha e a coluna onde ele se
encontra);
- impressão de somatório de uma linha i (informada pelo usuário);
- percentual de elementos não nulos na matriz lida.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct lista
{
    int linha; // linha onde se encontra o elemento não nulo
    int coluna; // coluna onde se encontra o elemento não nulo
    int info; // valor do elemento não nulo
    struct lista* prox; // apontador para o proximo elemento não nulo da matriz
};
typedef struct lista Lista;

struct esparsa
{
    int linhas; //numero de linhas da matriz
    int colunas; //numero de colunas da matriz
    struct lista* prim; //apontador para o primeiro noh não nulo da matriz
};
typedef struct esparsa Esparsa;

int main()
{

}

Lista* append_left(Lista* lista, int elemento, int linha, int coluna)
{
    Lista* novo_no = malloc(sizeof(Lista));
    novo_no->linha = linha;
    novo_no->coluna = coluna;
    novo_no->info = elemento;
    novo_no->prox = lista;
    return novo_no;
}

void preenche_lista(Lista* lista)
{
    int elemento = -1, linha = -1, coluna = -1, resposta = -1;

    while(true)
    {
        printf("Você deseja adicionar um elemento à lista de elementos não-nulos?\n");
        printf("Sim - 1\n");
        printf("Não - 0\n");
        printf("Resposta: ");
        scanf("%d", &resposta);

        if(resposta == 0) break;
        else if(resposta != 1) continue;

        printf("Insira o elemento a adicionar: ");
        scanf("%d", &elemento);
        printf("Insira a linha do elemento: ");
        scanf("%d", &linha);
        printf("Insira a coluna do elemento: ");
        printf("%d", &coluna);

        lista = append_left(lista, elemento, linha, coluna);
    }
}

void aloca_matriz(int** matriz, Esparsa* matriz_info)
{
    matriz = malloc(matriz_info->linhas * sizeof(int*));
    for(int i = 0; i < matriz_info->linhas; i++) matriz[i] = malloc(matriz_info->colunas * sizeof(int));
}

Lista busca_no_da_lista(Lista* lista, int posicao)
{
    Lista* no_atual = lista;
    Lista* proximo_no = NULL;
    int elemento_buscado = 0;
    
    for(int i = 0; i < posicao; i++)
    {
        elemento_buscado = no_atual->info;
        proximo_no = no_atual->prox;
        no_atual = proximo_no;
    }

    return no_atual;
}

int tamanho_da_lista(Lista* lista)
{
    if(lista == NULL) return 0;
    Lista* no_atual = lista;
    Lista* proximo_no = no_atual->prox;
    int contador = 1;
    
    while(proximo_no != NULL)
    {
        contador++;
        no_atual = proximo_no;
        proximo_no = no_atual->prox;
    }

    return contador;
}

void preenche_matriz(int** matriz, Esparsa* matriz_info)
{
    int tamanho = tamanho_da_lista(matriz_info->prim);
    Lista no_da_lista;

    for(int i = 0; i < tamanho; i++)
    {
        no_da_lista = busca_no_da_lista(lista, i + 1);
        matriz[no_da_lista.linha][no_da_lista.coluna] = no_da_lista.info
    }
}

