#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

void shellSort(int *V, int n){
    int h, aux;

    h = 1;
    while(h< n/3){
        h = 3*h+1;
    }
    while (h>0){
        printf("H: %d\n", h);
        for (int i = h; i < n; i++){
            aux = V[i];
            int j = i;

            while (j>=h && aux<V[j-h]){
                V[j] = V[j-h];
                j = j-h;
            }
            V[j] = aux;
            printLista(V, n);
        }
        h = (h-1)/3;
    }


}

int main(){
    int vetor[7];
    for (int i =0; i< 7; i++){
        scanf("%d", &vetor[i]);
    }
    shellSort(vetor, 7);
    for (int j=0; j < 7; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}