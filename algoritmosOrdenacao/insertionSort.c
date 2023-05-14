#include <stdio.h>

void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}


void insertionSort(int array[], int size){
    int aux, insertSpot;
    for (int i = 1; i < size; i++){
        aux = array[i];
        for(int j=i; (j>0) && (aux<array[j-1]); j--){
            array[j] = array[j-1];
            insertSpot = j-1;
        }
        array[insertSpot] = aux;
    }
}

int main(){
    int vetor[10];
    for (int i =0; i< 10; i++){
        scanf("%d", &vetor[i]);
    }
    insertionSort(vetor, 10);
    for (int j=0; j < 10; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}