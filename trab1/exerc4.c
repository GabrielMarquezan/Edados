#include <stdio.h>
#include <stdlib.h>

int*** aloca_matriz (int m, int n, int z){
    int*** matriz = (int***) malloc(sizeof(int**)*m);
    for(int i=0; i<m; i++){
        matriz[i] = (int**) malloc(sizeof(int*)*n);
        for(int j=0; j<n; j++){
            matriz[i][j] = (int*) malloc(sizeof(int)*z);
        }
    }
    return matriz;
}

void desaloca(int*** matriz, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            free(matriz[i][j]);
        }
        free(matriz[i]);
    }
    free(matriz);
}

void preenche_matriz (int m, int n, int z, int ***mat){
    printf("\nA matriz será preenchida por linhas e depois por profundidade;\n");
    printf("Caso deseje completar o preenchimento com 0's, digite -12345;\n");
    printf("\n\tDigite os elementos da matriz um a um:");
    int temp = 0;
    for(int k =0; k<z; k++){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(temp != -12345) scanf(" %d", &temp);
                if(temp != -12345) mat[i][j][k] = temp;
                else mat[i][j][k] = 0;
            }
        }
    }
}

void imprime_matriz (int m, int n, int z, int ***mat){
    for(int k =0; k<z; k++){
        printf("Na profundidade %d:\n", k);
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                printf("| %d ", mat[i][j][k]);
            }
            printf("|\n");
        }
    }
}

int main(){
    int m, n, z;
    printf("Digite as dimensões da matriz (m x n x z):");
    scanf(" %d %d %d", &m, &n, &z);
    int*** matriz = aloca_matriz(m, n, z);
    preenche_matriz(m, n, z, matriz);
    imprime_matriz(m, n, z, matriz);
    desaloca(matriz, m, n);
}