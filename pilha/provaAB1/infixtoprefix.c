#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100


void inverteString(char str[]){
     
    int length = strlen(str); // tamanho da string
    int i;

    for (i = 0; i < length / 2; i++) { // varre metade da string
        char temp = str[i]; // salva o caractere da posição atual em uma variável temporária
        str[i] = str[length - i - 1]; // troca o caractere da posição atual com o caractere no final da string
        str[length - i - 1] = temp; // salva o caractere do final da string em outra variável temporária
    }
}

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

void inftopre(char *infixa, char *prefixa){
    Stack* pilha = malloc(sizeof(Stack));
    inverteString(infixa);
    pilha->top = -1;
    int j = 0;
    for (int i = 0; i<strlen(infixa); i++){
        if(isdigit(infixa[i]) || islower(infixa[i]) || isupper(infixa[i]))
        {
            printf("%c\n", infixa[i]);
            prefixa[j] = infixa[i];
            j +=1;
        }
        else if(infixa[i]==' '){
        }
        else 
        {
            while (preference(infixa[i]) < preference(pilha->items[pilha->top]) && !isEmpty(pilha))
            {
                prefixa[j++] = pop(pilha);
            }
            push(pilha, infixa[i]);
        }
    }
    while(!isEmpty(pilha))
    {
        prefixa[j++] = pop(pilha);
    }
    inverteString(prefixa);
}

int main(){
    char infixa[MAX_SIZE];
    char prefixa[MAX_SIZE];
    scanf("%[^\n]s", infixa);
    inftopre(infixa, prefixa);
    printf("%s\n", prefixa);
    return 0;
}