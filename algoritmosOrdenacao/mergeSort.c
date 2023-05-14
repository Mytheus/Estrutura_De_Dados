#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void swap(int* var1, int* var2){
    int aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}

void merge(int array[], int inicio, int meio, int fim){
    //trabalha com DOIS ARRAYS (array1:[inicio-meio], array2: [meio+1-fim])
    //Variáveis pra saber se chegamos ao fim dos dois arrays
    int fim1=0, fim2=0;
    //Tamanho do array principal
    int tamanho = fim-inicio+1;
    //indices pra percorrer os dois arrays que
    //serão juntados no array principal
    int indiceArray1 = inicio; 
    int indiceArray2 = meio+1;
    //Array principal auxiliar
    int* temp = malloc(sizeof(int)*tamanho);
    for (int i =0; i< tamanho; i++){
        //Se nenhum deles tiver chegado ao fim
        if (!fim1 && !fim2){
            if (array[indiceArray1]<array[indiceArray2]){
                //Coloca no array principal e incrementa o indice
                temp[i] = array[indiceArray1++];
            }
            else{
                temp[i] = array[indiceArray2++];
            }
            //Verifica se algum dos dois chegou ao fim
            if(indiceArray1>meio)fim1=!fim1;
            if(indiceArray2>fim)fim2=!fim2;
        }
        else{
            if(!fim1){
                //Se foi o primeiro que nao chegou ao fim, coloca apenas do primeiro
                temp[i] = array[indiceArray1++];
            }
            else{
                //Se foi o segundo que nao chegou ao fim, coloca apenas do segundo
                temp[i] = array[indiceArray2++];
            }
        }
    }
    //pega do array auxiliar e coloca de volta no array principal (de inicio ao fim) 
    for (int j=0, k=inicio;j<tamanho;j++, k++){
        array[k] = temp[j];
    }
    free(temp);
}

void mergeSort(int array[], int inicio, int fim){
    int meio;
    if (inicio<fim){
        meio = (inicio+fim)/2;
        mergeSort(array, inicio, meio);
        mergeSort(array, meio+1, fim);
        merge(array, inicio, meio, fim);
    }
}

int main(){
    int vetor[10];
    for (int i =0; i< 10; i++){
        scanf("%d", &vetor[i]);
    }
    mergeSort(vetor, 0, 9);
    for (int j=0; j < 10; j++){
        printf("%d ", vetor[j]);
    }
    puts("");
    return 0;
}