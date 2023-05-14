#include <stdio.h>

void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}


void selectionSort(int array[], int size){
    for (int i = 0; i < size-1; i++){
        int posMenor = i;
        for (int j = i; j < size; j++){
            if (array[j]< array[posMenor]){
                posMenor = j;
            }
        }
        if (i!=posMenor) swap(&array[posMenor], &array[i]);
    }
}

int main(){
    int vetor[10];
    for (int i =0; i< 10; i++){
        scanf("%d", &vetor[i]);
    }
    selectionSort(vetor, 10);
    for (int j=0; j < 10; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}