#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
    int inf;
    int prioridade;
    struct Fila* next;
} Fila;

Fila* getNode(){
    return malloc(sizeof(Fila));
}

void insertValue(Fila** fila, int inf, int prioridade){
    Fila** aux = &((*fila)->next);
    int i = 1;
    while(i){
        printf("%d %d\n", (*fila)->inf, (*aux)->inf);
        if((*fila)){
            fila=&((*fila)->next);
        }
        else{
            i--;
        }
        if ((*aux)){
            aux=&((*aux)->next);
            if((*aux)->prioridade<prioridade){
                i--;
            }
        }
    }
    Fila* newnode = getNode();
    newnode->inf = inf;
    newnode->prioridade = prioridade;
    newnode->next=(*aux);
    (*fila)->next = newnode;
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
        printf("%d: %d ", fila->inf, fila->prioridade);
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
    insertValue(&fila, 1,3);
    insertValue(&fila, 2,3);
    insertValue(&fila, 2,3);
    insertValue(&fila, 1,2);
    insertValue(&fila, 2,2);
    display(fila);
    return 0;
}
