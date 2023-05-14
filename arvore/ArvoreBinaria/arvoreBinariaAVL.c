#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;


int max (int a, int b){
    return (a>b?a:b);
}
typedef struct no {
    int inf;
    struct no* esq;
    struct no* dir;
    int h;
} no;

no* criaNo(int inf){
    no* aux = malloc(sizeof(no));
    aux->dir = NULL;
    aux->esq = NULL;
    aux->inf = inf;
    aux->h = 0;
    return aux;
}

no* inicializa(){
    return NULL;
}

int altura (no* raiz){
    if (!raiz){
        return -1;
    }
    return raiz->h;
}

no* direita(no* raiz){
    no* aux;
    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;

    raiz->h = max(altura(raiz->dir), altura(raiz->esq)) +1;
    aux->h = max(altura(aux->esq), raiz->h) +1;

    return aux;
}

no* esquerda(no* raiz){
    no* aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;

    raiz->h = max(altura(raiz->dir), altura(raiz->esq)) +1;
    aux->h = max(altura(aux->esq), raiz->h) +1;

    return aux;
}

no* esquerdaDireita(no* raiz){
    raiz->esq = esquerda(raiz->esq);
    return(direita(raiz));
}

no* direitaEsquerda(no* raiz){
    raiz->dir = direita(raiz->dir);
    return(esquerda(raiz));
}

int insere(no* raiz, int inf){
    if (!raiz) return criaNo(inf);
    if (inf < raiz->inf){
        raiz->esq = insere(raiz->esq, inf);
        if (altura(raiz->esq) - altura(raiz->dir == 2))
            if (inf < raiz->esq->inf)
                raiz = direita(raiz);
            else
                raiz = esquerdaDireita(raiz);
    }
    else if (inf > raiz->inf){
            raiz->dir = insere(raiz->dir, inf);
            if (altura(raiz->dir)-altura(raiz->esq)==2)
                if (inf > raiz->dir->inf)
                    raiz = esquerda(raiz);
                else
                    raiz = direitaEsquerda(raiz);
    }
    raiz->h = max(altura(raiz->esq), altura(raiz->dir))+1;
    return raiz;
}

int main(){
    no* root = inicializa();
    // printf("%d\n", max(9,5));
    return 0; 
}

