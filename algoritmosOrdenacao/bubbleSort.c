#include <stdio.h>

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

int main(){
    int vetor[10];
    for (int i =0; i< 10; i++){
        scanf("%d", &vetor[i]);
    }
    bubbleSort(vetor, 10);
    for (int j=0; j < 10; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}