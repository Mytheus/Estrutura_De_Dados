#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TAM 5

typedef struct balde{
    int qtd;
    int valores[TAM];
} balde;


void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}

void bubbleSort(int array[], int size){
    int posUltimoSwap;
    do{
        posUltimoSwap=0;
        for(int i = 0; i<size-1;i++){
            if (array[i]>array[i+1]){
                swap(&array[i], &array[i+1]);
                posUltimoSwap = i;
            }
        }
        size--;
    }while (posUltimoSwap!=0);
}

void bucketSort(int *vetor, int n){
    int maior, menor, pos;
    balde *bd;
    maior = menor = vetor[0];
    for (int i = 1; i < n; i++){
        if (vetor[i] > maior) maior = vetor[i];
        if (vetor[i] < menor) menor = vetor[i];
    }
    int nBaldes = (maior-menor)/TAM+1;
    printf("nBaldes: %d\n", nBaldes);
    bd = malloc(sizeof(balde) * nBaldes);
    for (int i =0; i < nBaldes; i++){
        bd[i].qtd = 0;
    }

    for (int i = 0; i < n; i++){
        pos = (vetor[i] - menor)/TAM;
        printf("Pos: %d\n", pos);
        bd[pos].valores[bd[pos].qtd] = vetor[i];
        bd[pos].qtd++;
    }

    pos = 0;
    for (int i = 0; i <  nBaldes; i++){
        bubbleSort(bd[i].valores, bd[i].qtd);
        for (int j = 0; j < bd[i].qtd; j++){
            vetor[pos] = bd[i].valores[j];
            pos++;
        }
    }
    free(bd);
}

int main(){
    int vetor[7];
    for (int i =0; i< 7; i++){
        scanf("%d", &vetor[i]);
    }
    bucketSort(vetor, 7);
    for (int j=0; j < 7; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}