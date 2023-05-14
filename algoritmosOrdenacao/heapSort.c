#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}


void heapSort(int array[], int size);

int main(){
    int vetor[10];
    for (int i =0; i< 10; i++){
        scanf("%d", &vetor[i]);
    }
    heapSort(vetor, 10);
    for (int j=0; j < 10; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}