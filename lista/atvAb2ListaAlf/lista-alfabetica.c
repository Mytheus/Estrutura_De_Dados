#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define W_MAX 30
#define TAM_LISTA 78

int ordemAlfabetica(char word1[], char word2[]){
    int tam_for = strlen(word1);
    if (strlen(word2)> strlen(word1)){
        tam_for = strlen(word2);
    }
    for (int i = 0; i < tam_for; i++){
        if (word1[i]>word2[i]){
            return 1;
        }
        else if (word2[i]>word1[i])
        {
            return 0;
        } 
    }
}

void stringToUpper(char word[]){
    for (int i = 0; i <  strlen(word); i++){
        word[i] = toupper(word[i]);
    }
}


int compareString(char word1[], char word2[]){
    stringToUpper(word1);
    stringToUpper(word2);
    return strcmp(word1, word2)==0;
}

void emptyWord(char word[]){
    word[0] = '\0';
}

void fillGaps(char names[][W_MAX]){
    for (int i = 0; i < TAM_LISTA; i++){
        emptyWord(names[i]);
    }
}

int isGap(char word[]){
    return word[0]=='\0';
}


int gapInSection(char names[][W_MAX], int inic, int final){
    for (int i =inic; i < final; i++){
        if (isGap(names[i])){
            return i;
        }
    }
    return -1;
}




void sortSection(char names[][W_MAX], int inic, int final){
    for (int j = inic; j <= final; j++){
        for (int i  = inic; i <= final; i++ ){
            if (!ordemAlfabetica(names[j], names[i]) && !isGap(names[i]) && !isGap(names[j])){
                char aux[W_MAX];
                strcpy(aux, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], aux);
            }
        }
    }
}

void insertName(char names[][W_MAX], char name[]){
    stringToUpper(name);
    int sinal = 1;
    int posInicial = (name[0]-'A') * (TAM_LISTA/26);
    int posFinal = posInicial+(TAM_LISTA/26);

    if (('Z'-name[0])<(('Z'-'A')/2)){
        posInicial = (TAM_LISTA-1)-(('Z'-name[0]) * (TAM_LISTA/26));
        posFinal = posInicial - (TAM_LISTA/26);
        sinal = -1;
        for (int i = posInicial; i > posFinal; i+=sinal){
            if (isGap(names[i])){
                if (i-1 > posFinal && isGap(names[i-1]) && i!= posInicial && name[0]!='O'){
                    strcpy(names[i-1], name);
                    sortSection(names, posFinal, posInicial);
                    return;
                }
                else{
                    strcpy(names[i], name);
                    sortSection(names, posFinal, posInicial);
                    return;
                }
            }
        }
        
    }
    else{
        for (int i = posInicial; i < posFinal; i+=sinal){
            if (isGap(names[i])){
                if (i+1 < posFinal && isGap(names[i+1]) && i!= posInicial && name[0]!='N'){
                    strcpy(names[i+1], name);
                    sortSection(names, posInicial, posFinal);
                    return;
                }
                else{
                    strcpy(names[i], name);
                    sortSection(names, posInicial, posFinal);
                    return;
                }
            }
        }
    }
}

int deleteNameWName(char names[][W_MAX], char name[]){
    stringToUpper(name);
    int posInicial = (name[0]-'A') * (TAM_LISTA/26);
    int posFinal = posInicial+(TAM_LISTA/26);
    for (int i = posInicial; i < posFinal; i++){
        if (compareString(name, names[i])){
            emptyWord(names[i]);
            return 1;
        };
    }
    return 0;
}

int deleteNameWPos(char names[][W_MAX], int pos){
    if(isGap(names[pos])) return 0;
    emptyWord(names[pos]);
    return 1;
}


void display(char names[][W_MAX]){
    char final = ',';
    for (int i =0; i < TAM_LISTA; i++){
        if (i==TAM_LISTA-1){
            final = ' ';
        }
        if(isGap(names[i])){
            printf("%d - [____]%c\n", i, final);
        }
        else{
            printf("%d - %s%c\n", i, names[i], final);
        }
    }
    printf("\n");
}

void displayWoutGaps(char names[][W_MAX]){
    char final = ',';
    int cont = 0;
    for (int i =0; i < TAM_LISTA; i++){
        if (i==TAM_LISTA-1){
            final = ' ';
        }
        if(!isGap(names[i])){
            printf("%d - %s%c\n", i, names[i], final);
        }
    }
    printf("\n");
}

int main(){
    char word1[10];
    char listaAlfabetica[TAM_LISTA][W_MAX];
    fillGaps(listaAlfabetica);
    int loop=1;
    int selecao;
    int index;
    char aux[W_MAX];
    while(loop){
        printf("Questão 1 - SEMANA 2\n");
        printf("Digite seu comando e aperte enter:\n1 - Inserir nome\n2 - Deletar nome pelo nome\n3 - Deletar nome pelo índice\n4 - Mostrar lista com gaps\n5 - Mostrar lista sem gaps\n6 - Verificar detalhe da questão\n");
        scanf(" %d", &selecao);
        switch (selecao)
        {
        case 1:
            printf("Digite o nome que deseja adicionar: ");
            scanf(" %[^\n]", aux);
            puts(" ");
            insertName(listaAlfabetica, aux);
            printf("Nome inserido com sucesso!\n");
            break;
        case 2:
            printf("Digite o nome que deseja deletar: ");
            scanf(" %[^\n]", aux);
            puts(" ");
            if (deleteNameWName(listaAlfabetica, aux))printf("Nome deletado com sucesso!\n");
            else printf("Nome não existente na lista!\n");
            break;
        case 3:
            printf("Digite o índice do nome que deseja deletar: ");
            scanf(" %d", &index);
            puts(" ");
            if (deleteNameWPos(listaAlfabetica, index))printf("Nome deletado com sucesso!\n");
            else printf("Nome não existente na lista!\n");
            break;
        case 4:
            display(listaAlfabetica);
            break;
        case 5:
            displayWoutGaps(listaAlfabetica);
            break;
        case 6:
            printf("Questão do tipo:\n5: os gaps devem ocorrer preferencialmente no meio da sequência separados\n");
            puts("");
            break;
        default:
            printf("Operação não reconhecida.\n");
            puts("");
            break;
        }
    }
    

    // char word1[10], word2[10];
    // scanf("%[^\n]", word1);
    // scanf(" %[^\n]", word2);
    // printf("%d\n", ordemAlfabetica(word1, word2));
    return 0;
}