#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//Máximo de N
#define N_MAX 52

//Pilha estática
typedef struct Pilha{
    int topo;
    int vetor[N_MAX];
}Pilha;

Pilha* initPilha(int nItems){
    Pilha* pilha = malloc(sizeof(Pilha));
    pilha->topo = -1;
}

void push(Pilha* pilha, int inf){
    pilha->topo+=1;
    pilha->vetor[pilha->topo] = inf;
}

int pop(Pilha* pilha){
    int retorno = pilha->vetor[pilha->topo];
    pilha->topo-=1;
    return retorno;
}

int peek(Pilha* pilha){
    return pilha->vetor[pilha->topo];
}

void display(Pilha* pilha){
    for (int i =0; i <= pilha->topo; i++){
        printf("%d ", pilha->vetor[i]);
    }
    printf("\n");
}

int length(Pilha* pilha){
    return pilha->topo+1;
}

int isEmpty(Pilha* pilha){
    return pilha->topo==-1;
}

void shufflePilha(Pilha* baralho){
    //Cria duas pilhas auxiliares
    Pilha* aux1 = initPilha(N_MAX);
    Pilha* aux2 = initPilha(N_MAX);
    int nCartas = length(baralho);
    //Dsitribui entre as pilhas aleatoreamente
    while (length(baralho)>0){
        int escolha = rand()%10;
        if (escolha<5){
            push(aux1, pop(baralho));
        }
        else{
            push(aux2, pop(baralho));
        }
    }
    //Retorna à pilha original aleatoreamente
    while (length(baralho)<nCartas){
        int escolha = rand()%10;
        if (escolha<5){
            if (!isEmpty(aux1))push(baralho, pop(aux1));
            else{
                push(baralho, pop(aux2));
            }
        }
        else{
            if (!isEmpty(aux2))push(baralho, pop(aux2));
            else{
                push(baralho, pop(aux1));
            }
        }
    }
}

void preenchePilha(Pilha* pilha, int n){
    for (int i =1; i <= n; i++){
        push(pilha, i);
    }
}


int etapa(Pilha* pilhaA, Pilha* pilhaB){
    //Embaralha
    shufflePilha(pilhaA);
    shufflePilha(pilhaB);
    if (peek(pilhaA)>peek(pilhaB)){
        pop(pilhaB);
        shufflePilha(pilhaA);
        shufflePilha(pilhaB);
        return 1;
    }
    else if (peek(pilhaA)<peek(pilhaB)){
        pop(pilhaA);
        shufflePilha(pilhaA);
        shufflePilha(pilhaB);
        return 2;
    }
    else{
        pop(pilhaA);
        pop(pilhaB);
        return 0;
    }

}
void jogo(){
    int n;
    printf("Digite o número de cartas para os dois jogadores(máximo de %d cartas): ", N_MAX);
    scanf("%d", &n);
    while (n>N_MAX || n<1){
        if (n>N_MAX)printf("Número informado é maior que %d, informe um número menor: ", N_MAX); 
        if (n<1)printf("Número informado é menor que 1, informe um número maior: "); 
        scanf("%d", &n);
    }
    Pilha* pilhaA = initPilha(n); //Cria as pilhas
    Pilha* pilhaB = initPilha(n);
    preenchePilha(pilhaA, n); //Preenche as pilhas 
    preenchePilha(pilhaB, n);
    srand(time(NULL)); //Seta a seed da funcao rand()
    while (!isEmpty(pilhaA) && !isEmpty(pilhaB)){//Enquanto nenhum dos dois perde, o jogo repete e printa os resultados
        printf("%d ", etapa(pilhaA, pilhaB));
    }
    printf("\n");
    //verificação de vitória
    if (isEmpty(pilhaA) && isEmpty(pilhaB)){
        printf("Empate!\n");
    }
    else if (isEmpty(pilhaB)){
        printf("Jogador A ganhou o jogo!\n");
    }
    else if (isEmpty(pilhaA)){
        printf("Jogador B ganhou o jogo!\n");
    }
}

int main(){
    jogo();
    return 0;
}