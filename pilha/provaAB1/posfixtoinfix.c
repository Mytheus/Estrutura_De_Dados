#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100


typedef struct
{
    int top;
    int items[MAX_SIZE];
} Stack;

int isEmpty(Stack *ps)
{
    if (ps->top == -1)
        return 1;
    else
        return 0;
};

char pop(Stack *ps)
{
    if (isEmpty(ps))
    {
        printf("underflow");
        return 0;
    }
    else
    {
        return ps->items[ps->top--]; // retorna e atualiza elemento na posição top
    }
}

void push(Stack *ps, char n)
{
    if (ps->top == MAX_SIZE - 1)
    {
        printf("stack-overflow");
        return;
    }
    else
    {
        ps->items[++(ps->top)] = n;
        return;
    }
}

int preference(char operador){
    if (operador=='+'||operador=='-'){
        return 1;
    }
    else if (operador=='*'||operador=='/')
    {
        return 2;
    }
    else{
        return 3;
    }
}

void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

void inftopos(char *infixa, char *posfixa){
    Stack* pilha = malloc(sizeof(Stack));
    remove_spaces(infixa);
    pilha->top = -1;
    int j = 0;
    for (int i = 0; i<strlen(infixa); i++){
        if(isdigit(infixa[i]) || islower(infixa[i]) || isupper(infixa[i]))
        {
            printf("%c\n", infixa[i]);
            posfixa[j] = infixa[i];
            j +=1;
        }
        else 
        {
            while (preference(infixa[i]) < preference(pilha->items[pilha->top]) && !isEmpty(pilha))
            {
                posfixa[j++] = pop(pilha);
            }
            push(pilha, infixa[i]);
        }
    }
    while(!isEmpty(pilha))
    {
        posfixa[j++] = pop(pilha);
    }
}

int main(){
    char infixa[MAX_SIZE];
    char posfixa[MAX_SIZE];
    scanf("%[^\n]s", infixa);
    inftopos(infixa, posfixa);
    printf("%s\n", posfixa);
    return 0;
}