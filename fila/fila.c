#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
    int inf;
    struct Fila* next;
} Fila;

Fila* getNode(){
    return malloc(sizeof(Fila));
}

void insertValue(Fila** fila, int inf){
    while((*fila)){
        fila=&((*fila)->next);
    }
    (*fila) = getNode();
    (*fila)->inf = inf;
    (*fila)->next = NULL;
}

void deleteValue(Fila** fila){
    Fila* aux = (*fila);
    (*fila) = (*fila)->next;
    free(aux);
}

void display(Fila* fila){
    if (!fila){
        printf("\n");
        return;
    }
    else{
        printf("%d ", fila->inf);
        display(fila->next);
    }
}

int size(Fila* fila){
    int qntd = 0;
    while(fila){
        qntd++;
        fila= fila->next;
    }
    return qntd;
}

int isEmpty(Fila* fila){
    return !fila;
}

int main(){
    Fila* fila = NULL;
    insertValue(&fila, 10);
    insertValue(&fila, 9);
    deleteValue(&fila);
    deleteValue(&fila);
    display(fila);
    printf("%d", fila==NULL);
    return 0;
}
