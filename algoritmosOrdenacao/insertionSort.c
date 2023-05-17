#include <stdio.h>

void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}

void printLista(int *lista, int tam){
    for (int j=0; j < tam; j++){
        printf("%d ", lista[j]);
    }
    puts("");
}

void insertionSort(int array[], int size){
    int aux, insertSpot, j, i;
    for (i = 1; i < size; i++){
        aux = array[i];
        for(j=i; (j>0) && (aux<array[j-1]); j--){
            array[j] = array[j-1];
        }
        array[j] = aux;
        printLista(array, size);
    }
}

int main(){
    int vetor[7];
    for (int i =0; i < 7; i++){
        scanf("%d", &vetor[i]);
    }
    insertionSort(vetor, 7);
    for (int j=0; j < 7; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}