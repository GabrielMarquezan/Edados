#include <stdio.h>
#include <stdlib.h>

typedef struct Fora_diag_principal errados;

typedef struct Fora_diag_principal{
    int lin;
    int col;
    int valor;
    errados* next;
}errados;

void libera(errados* matriz){
    errados* p = matriz;
    while(p != NULL){
        matriz = matriz->next;
        free(p);
        p = matriz;
    }
}

errados* cria_matriz(){
    return NULL;
}

errados* insere_na_lista(errados* prim, int val, int lin, int col) {
    errados* novo = (errados*) malloc(sizeof(errados));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    novo->lin = lin;
    novo->col = col;
    novo->valor = val;
    novo->next = prim;
    return novo;
}

void le_matriz(errados** prim, int dimensao){
    int temp;
    printf("Digite todos os elementos da matriz(um a um): ");
    for(int i=0; i<dimensao; i++){
        for(int j=0; j<dimensao; j++){
            scanf(" %d", &temp);
            if(i == j){
                if(temp != 1)*prim = insere_na_lista(*prim, temp, i, j);
            }
            else if(temp != 0) *prim = insere_na_lista(*prim, temp, i, j);
        }
    }
}

errados* busca_valor(errados* prim, int lin, int col){
    while(prim != NULL){
        if(prim->col == col && prim->lin == lin) return prim;
        prim = prim->next;
    }
    return NULL;
}

void imprime_matriz(errados* prim, int dimensao){
    if(prim == NULL){
        for(int i=0; i<dimensao; i++){
            for(int j=0; j<dimensao; j++){
                if(i == j) printf("| 1 ");
                else printf("| 0 ");
            }
            printf("\n");
        }
    }else{
        for(int i=0; i<dimensao; i++){
            for(int j=0; j<dimensao; j++){         
                errados* aux = busca_valor(prim, i, j);       
                if(aux != NULL) printf("| %d ", aux->valor);
                else if(i == j) printf("| 1 ");
                else printf("| 0 ");
            }
            printf("\n");
        }
    }

}

void mostra_errados(errados* matriz){
    if(matriz != NULL){
        printf("Os seguintes elementos violam a regra de matriz identidade:\n");
        while(matriz != NULL){
            printf("Elemento %d na linha %d e coluna %d;\n", matriz->valor, matriz->lin, matriz->col);
            matriz = matriz->next;
        }
    }
    else printf("A matriz é uma matriz identidade!\n");
}

int main(){
    int dimensao;
    printf("Digite a dimensão da matriz quadrada: ");
    scanf(" %d", &dimensao);
    errados* matriz = cria_matriz();
    le_matriz(&matriz, dimensao);
    imprime_matriz(matriz, dimensao);
    mostra_errados(matriz);
    libera(matriz);
}