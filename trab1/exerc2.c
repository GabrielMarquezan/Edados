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

void append_left(Lista** lista, int elemento, int linha, int coluna)
{
    Lista* novo_no = (Lista*) malloc(sizeof(Lista));
    novo_no->linha = linha;
    novo_no->coluna = coluna;
    novo_no->info = elemento;
    novo_no->prox = *lista;
    *lista = novo_no;
}

bool verifica_se_posicao_preenchida(Lista* lista, int linha, int coluna)
{
    if(lista == NULL) return false;
    Lista* no_atual = lista;
    
    while(true)
    {
        Lista* proximo_no = no_atual->prox;

        if(no_atual->linha == linha && no_atual->coluna == coluna) return true;
        if(proximo_no == NULL) break;

        no_atual = proximo_no;
    }

    return false;
}

void preenche_lista(Lista** lista, int tamanho_maximo)
{
    int elemento = -1, linha = -1, coluna = -1, resposta = -1;
    bool posicao_preenchida = false;

    for(int i = 0; i < tamanho_maximo; i++)
    {
        while(true)
        {
            printf("Você deseja adicionar um elemento à lista de elementos não-nulos?\n");
            printf("Sim - 1\n");
            printf("Não - 0\n");
            printf("Resposta: ");
            scanf("%d", &resposta);

            if(resposta != 1 && resposta != 0) continue;
            else if(resposta == 0) break;

            printf("Insira o elemento a adicionar: ");
            scanf("%d", &elemento);
            printf("Insira a linha do elemento: ");
            scanf("%d", &linha);
            printf("Insira a coluna do elemento: ");
            scanf("%d", &coluna);

            posicao_preenchida = verifica_se_posicao_preenchida(*lista, linha, coluna);

            if(!posicao_preenchida) append_left(lista, elemento, linha, coluna);
            else printf("Essa posição já está preenchida!\n");
        }

        if(resposta == 0) break;
    }
}

int busca_elemento_da_lista_pela_posicao(Lista* lista, int linha, int coluna)
{
    Lista* no_atual = lista;
    if(no_atual == NULL) return 111;
    
    while(true)
    {
        Lista* proximo_no = no_atual->prox;

        if(no_atual->linha == linha && no_atual->coluna == coluna) return no_atual->info;
        if(proximo_no == NULL) break;

        no_atual = proximo_no;
    }

    return 0;
}

void imprime_matriz(Esparsa* matriz)
{
    int elemento = 0;

    printf("\n       ");

    //Imprime o índice das colunas
    for(int i = 0; i < matriz->colunas; i++)
    {
        if(i < 9) printf("|  00%d  ", i + 1);
        else if(i < 99) printf("|  0%d  ", i + 1);
        else printf("|  %d  ", i + 1);
    }

    printf("|\n");

    for(int i = 1; i <= matriz->linhas; i++)
    {
        for(int k = 0; k < 8 * matriz->colunas + 8; k++) printf("-"); //Divide as linhas

        //Imprime o índice das linhas
        if(i < 9) printf("\n  00%d  ", i); 
        else if(i < 99) printf("\n  0%d  ", i);
        else printf("\n  %d  ", i + 1);

        
        for(int j = 1; j <= matriz->colunas; j++) 
        {
            elemento = busca_elemento_da_lista_pela_posicao(matriz->prim, i, j);

            if(elemento < 10) printf("|  00%d  ", elemento);
            else if(elemento < 100) printf("|  0%d  ", elemento);
            else printf("|  %d  ", elemento);
        }
        printf("|\n");
    }

    printf("\n");
}

Lista* aloca_lista()
{
    Lista* lista = NULL;
    return lista;
}

void desaloca_lista(Lista* lista)
{
    int contador = 0;
    Lista* no_atual = lista;
    Lista* proximo_no;
    
    while(no_atual != NULL)
    {
        proximo_no = no_atual->prox;
        free(no_atual);
        no_atual = proximo_no;
    }
}

int main()
{
    Esparsa matriz = {2, 3, aloca_lista()};
    Esparsa* ponteiro_pra_matriz = &matriz;
    preenche_lista(&matriz.prim, matriz.linhas * matriz.colunas);
    imprime_matriz(ponteiro_pra_matriz);
    desaloca_lista(matriz.prim);
}