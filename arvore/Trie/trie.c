#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define N_ALFABETO 26

typedef struct no {
    int fim;
    struct no *filhos[N_ALFABETO];
} no;

no* criaNo(){
    
    no* aux = NULL;

    aux = malloc(sizeof(no));


    if (aux){//ve se deu problema no maloka
        aux->fim = false;
        for (int i = 0; i < N_ALFABETO; i++){
            aux->filhos[i] = NULL;
        }
    }

    return aux;
}

int mapearIndice(char c){
    return (c-'a');
}

no* inicializa(){
    return criaNo();
}

void insere(no* raiz, char* word){
    int index;
    no* aux = raiz;
    for (int i = 0; i < strlen(word); i++){
        index = mapearIndice(word[i]);
        if(!aux->filhos[index])
            aux->filhos[index] = criaNo();
        aux = aux->filhos[index];
    }
    aux->fim = true;
}

int busca(no* raiz, char* word){
    int index;
    no* aux = raiz;
    for (int i = 0; i < strlen(word); i++){
        index = mapearIndice(word[i]);
        if(aux->filhos[index])
            aux = aux->filhos[index];
        else return false;
    }
    return aux->fim;
}

int main(){
    no* trie = inicializa();
    char *word, *searchedWord;
    word = malloc(sizeof(char)*10);
    searchedWord = malloc(sizeof(char)*10);
    scanf(" %[^\n]", word);
    insere(trie, word);
    scanf(" %[^\n]", searchedWord);
    printf("%d\n", busca(trie, searchedWord));

    return 0;
}