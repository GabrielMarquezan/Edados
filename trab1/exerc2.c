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

Lista* aloca_lista()
{
    Lista* lista = NULL;
    return lista;
}

void pega_dimensoes_da_matriz(Esparsa* matriz)
{
    int linhas = -1, colunas = -1;
    while(true)
    {
        printf("\nQuantas linhas terá a matriz esparsa?\n");
        printf("Resposta: ");
        scanf("%d", &linhas);

        if(linhas >= 1) break;

        printf("Uma matriz deve ter, ao menos, uma linha!");
    }

    while(true)
    {
        printf("\nQuantas colunas terá a matriz esparsa?\n");
        printf("Resposta: ");
        scanf("%d", &colunas);

        if(colunas >= 1) break;

        printf("Uma matriz deve ter, ao menos, uma coluna!");
    }

    matriz->linhas = linhas;
    matriz->colunas = colunas;
}

void append_left(Lista** lista, int elemento, int linha, int coluna)
{
    Lista* novo_no = (Lista*) malloc(sizeof(Lista));
    novo_no->linha = linha;
    novo_no->coluna = coluna;
    novo_no->info = elemento;
    novo_no->prox = *lista;
    *lista = novo_no;
}

int verifica_se_posicao_preenchida(Lista* lista, int linha, int coluna)
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

bool deseja_fazer_algo(char texto[])
{
    int resposta = -1;
    while(resposta != 1 && resposta != 0)
    {
        printf("\nVocê deseja %s?\n", texto);
        printf("Sim - 1\n");
        printf("Não - 0\n");
        printf("Resposta: ");
        scanf("%d", &resposta);
    }
    return resposta == 1 ? true : false;
}

int pega_elemento()
{
    int elemento = -1;
    printf("Insira o elemento a adicionar: ");
    scanf("%d", &elemento);
    return elemento;
} 

int pega_linha(int linha_maxima)
{
    int linha = -1;
    while(true)
    {
        printf("Insira a linha: ");
        scanf("%d", &linha);
        if(linha > linha_maxima || linha < 1) printf("\n\nLINHA INVÁLIDA!\n\n");
        else return linha;
    }
}

int pega_coluna(int coluna_maxima)
{
    int coluna = -1;
    while(true)
    {
        printf("Insira a coluna: ");
        scanf("%d", &coluna);
        if(coluna > coluna_maxima || coluna < 1) printf("\n\nCOLUNA INVÁLIDA!\n\n");
        else return coluna;
    }
}

void preenche_lista(Esparsa* matriz, int tamanho_maximo)
{
    int elemento = -1, linha = -1, coluna = -1;
    bool resposta = false, posicao_preenchida = false;

    for(int i = 0; i < tamanho_maximo; i++)
    {
        while(true)
        {
            resposta = deseja_fazer_algo("adicionar um elemento à lista de elementos não-nulos");
            if(!resposta) break;

            elemento = pega_elemento();
            linha = pega_linha(matriz->linhas);
            coluna = pega_coluna(matriz->colunas);

            posicao_preenchida = verifica_se_posicao_preenchida(matriz->prim, linha, coluna);

            if(!posicao_preenchida) append_left(&matriz->prim, elemento, linha, coluna);
            else printf("Essa posição já está preenchida!\n");
        }

        if(resposta == 0) break;
    }
}

int busca_elemento_da_lista_pela_posicao(Lista* lista, int linha, int coluna)
{
    Lista* no_atual = lista;
    if(no_atual == NULL) return 0;
    
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

            if(elemento >= 0)
            {
                if(elemento < 10) printf("|  00%d  ", elemento);
                else if(elemento < 100) printf("|  0%d  ", elemento);
                else printf("|  %d  ", elemento);
            }
            else
            {
                if(elemento > -10) printf("| -00%d  ", (-1) * elemento);
                else if(elemento > -100) printf("| -0%d  ", (-1) * elemento);
                else printf("| -%d  ", (-1) * elemento);
            }
        }
        printf("|\n");
    }

    printf("\n");
}

void busca_elemento(Esparsa* matriz)
{
    int elemento = -1, linha = -1, coluna = -1;
    bool resposta = false;
    while(true)
    {
        resposta = deseja_fazer_algo("buscar um elemento da matriz");
        if(!resposta) break;

        linha = pega_linha(matriz->linhas);
        coluna = pega_coluna(matriz->colunas);

        elemento = busca_elemento_da_lista_pela_posicao(matriz->prim, linha, coluna);
        printf("\nO elemento na linha %d e coluna %d é %d\n\n", linha, coluna, elemento);
    }
}

int somatorio_de_linha(Esparsa* matriz, int linha)
{
    int total = 0;
    for(int i = 1; i <= matriz->colunas; i++) total += busca_elemento_da_lista_pela_posicao(matriz->prim, linha, i);
    return total;
}

void somar_linha(Esparsa* matriz)
{
    bool resposta = false;
    int linha = -1, total = 0;

    while(true)
    {
        resposta = deseja_fazer_algo("somar os valores de uma linha");
        if(!resposta) break;

        linha = pega_linha(matriz->linhas);
        total = somatorio_de_linha(matriz, linha);

        printf("\n\nO somatório dos valores da linha %d é %d\n\n", linha, total);
    }
}

int tamanho_da_lista(Lista* lista)
{
    if(lista == NULL) return 0;
    int contador = 1;
    Lista* no_atual = lista;
    
    while(true)
    {
        Lista* proximo_no = no_atual->prox;
        if(proximo_no == NULL) break;
        no_atual = proximo_no;
        contador++;
    }
    return contador;
}

void imprime_percentual_de_nao_nulos(Esparsa* matriz)
{
    float tamanho = (float) tamanho_da_lista(matriz->prim);
    float total = (float) (matriz->linhas * matriz->colunas);
    printf("\n\nO percentual de elementos não-nulos na matriz é: %.2f%%\n\n",  tamanho / total * 100);
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
    Esparsa matriz = {0, 0, aloca_lista()};
    Esparsa* ponteiro_pra_matriz = &matriz;
    pega_dimensoes_da_matriz(ponteiro_pra_matriz);
    preenche_lista(ponteiro_pra_matriz, matriz.linhas * matriz.colunas);
    imprime_matriz(ponteiro_pra_matriz);
    imprime_percentual_de_nao_nulos(ponteiro_pra_matriz);
    busca_elemento(ponteiro_pra_matriz);
    somar_linha(ponteiro_pra_matriz);
    desaloca_lista(matriz.prim);
}