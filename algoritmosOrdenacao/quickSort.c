#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}


int particiona(int array[], int inicio, int fim){
    //dir e esq dois indices da extrema direita e esquerda da lista
    int dir = fim;
    int esq = inicio;
    //escolhe o pivo como o primeiro
    int pivo = array[(inicio+fim)/2];
    //enquanto o indice da dir nao ta atras do da esq
    while (dir > esq){
        //move pra direita ate achar numero maior que o pivo ou o fim do array
        while (array[esq] <= pivo && esq<fim){
            esq++;
        }
        //move pra esquerda ate achar numero menor que o pivo ou o comeco do array
        while (array[dir]>pivo && dir>=inicio){
            dir--;
        }
        //se apos achar esses numeros, o indice esq ainda estiver antes do indice dir, troca os numeros nas posicoes dir e esq
        if (esq<dir)swap(&array[dir], &array[esq]);
    }
    //Troca o pivo do inicio pra dir
    swap(&array[dir], &array[(inicio+fim)/2]);
    //nova pos do pivo
    pivo = dir;
    return pivo;
}


void quickSort(int array[], int inicio, int fim){
    int pivo;
    if (fim>inicio){
        //Encontra pivo
        pivo = particiona(array, inicio, fim);
        quickSort(array, inicio, pivo-1);
        quickSort(array, pivo+1, fim);
    }
}

int main(){
    int vetor[8];
    for (int i =0; i< 8; i++){
        scanf("%d", &vetor[i]);
    }
    quickSort(vetor, 0, 7);
    for (int j=0; j < 8; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}