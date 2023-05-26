#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nAndares 300
#define nCorredores 3

typedef enum status {ativo, standby} status;
typedef enum statusProcesso {fonte, destino} statusProcesso;
typedef struct Elevador{
    int andar;
    int corredor;
    status statusElev;
} Elevador;

typedef struct Processo{
    int elevador;
    int andarDestino;
    int andarFonte;
    statusProcesso FouD;
} Processo;

Elevador elevadores[15];

typedef struct Fila {
    Processo* processo;
    struct Fila* next;
} Fila;

Fila* getNode(){
    return malloc(sizeof(Fila));
}

void insertProcesso(Fila** fila, Processo* processo){
    while((*fila)){
        fila=&((*fila)->next);
    }
    (*fila) = getNode();
    (*fila)->processo = processo;
    (*fila)->next = NULL;
}

Processo* deleteProcesso(Fila** fila){
    Fila* aux = (*fila);
    Processo* retorno = aux->processo;
    (*fila) = (*fila)->next;
    free(aux);
    return retorno;
}

void initializeElevador(Elevador* elevador, int andar, int corredor){
    elevador->andar = andar;
    elevador->corredor = corredor;
    elevador->statusElev = standby;
}

void initializePredio(int matriz[nCorredores][nAndares]){
    int pos[15] = {10, 30, 50, 70, 90, 110 ,130, 150, 170, 190, 210, 230, 250, 270, 290};
    int index = 0, elevador = 0, corredor = 0;


    for (int i = 0; i < nAndares; i++){
        for (int u = 0; u < nCorredores; u++){
            if (i == pos[index]-1 && u == corredor%3){
                matriz[u][i] = elevador;
                initializeElevador(&elevadores[elevador], i, u);
                elevador++;
                index++;
                corredor++;
            }
            else matriz[u][i] = -1;
        }
    }
}

void initializeProcesso(Processo* processo, int elevador,int andarFonte, int andarDestino, statusProcesso FouD){
    processo->andarDestino = andarDestino;
    processo->andarFonte = andarFonte;
    processo->elevador = elevador;
    processo->FouD = FouD;
}

int subirElevador(int matriz[nCorredores][nAndares], int elevador){
    if (elevadores[elevador].andar==nAndares-1) return 0;
    if (matriz[elevadores[elevador].corredor][elevadores[elevador].andar+1] != -1) return 0;

    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = -1;
    elevadores[elevador].andar+=1;
    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = elevador;

    return 1;
}

int descerElevador(int matriz[nCorredores][nAndares], int elevador){
    if (elevadores[elevador].andar==0) return 0;
    if (matriz[elevadores[elevador].corredor][elevadores[elevador].andar-1]!=-1) return 0;

    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = -1;
    elevadores[elevador].andar-=1;
    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = elevador;
    
    return 1;
}

int deslocarElevadorDireita(int matriz[nCorredores][nAndares], int elevador){
    if (elevadores[elevador].corredor==nCorredores-1) return 0;
    if (matriz[elevadores[elevador].corredor+1][elevadores[elevador].andar]!=-1) return 0;

    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = -1;
    elevadores[elevador].corredor+=1;
    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = elevador;
    return 1;
}

int deslocarElevadorEsquerda(int matriz[nCorredores][nAndares], int elevador){
    if (elevadores[elevador].corredor==0) return 0;
    if (matriz[elevadores[elevador].corredor-1][elevadores[elevador].andar]!=-1) return 0;

    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = -1;
    elevadores[elevador].corredor-=1;
    matriz[elevadores[elevador].corredor][elevadores[elevador].andar] = elevador;
    return 1;
}


int caminhoLivre(int matriz[nCorredores][nAndares], int andarFonte, int andarDestino, int corredor){
    if (andarFonte == andarDestino){
        return -1;
    }
    else{
        if (andarFonte < andarDestino){
            for (int i = andarFonte +1; i <= andarDestino; i++){
                // printf("Andar: %d Corredor: %d \n", i, corredor);
                if (matriz[corredor][i] != -1) return matriz[corredor][i];
            }
        }
        else{
            for (int i = andarFonte +1; i >= andarDestino; i--){
                if (matriz[corredor][i] != -1) return matriz[corredor][i];
            }
        }
    }
    return -1;
}

void ativarElevador(int elevador){
    elevadores[elevador].statusElev = ativo;
}

void desativarElevador(int elevador){
    elevadores[elevador].statusElev = standby;
}


int runProcesso(int matriz[nCorredores][nAndares], Processo* processo){
    if (elevadores[processo->elevador].andar == processo->andarDestino){
        return 1;
    }
    else if (elevadores[processo->elevador].andar < processo->andarDestino){
        subirElevador(matriz, processo->elevador);
        return 0;
    }
    else {
        descerElevador(matriz, processo->elevador);
        return 0;
    }

}

int findNearestElevator(int andar){
    int nearest = 0;
    int menorDist = abs(elevadores[0].andar-andar);
    for (int i = 1; i < 15; i++){
        if (abs(elevadores[i].andar-andar)<menorDist && elevadores[i].statusElev == standby){
            menorDist = abs(elevadores[i].andar-andar);
            nearest = i;
        }
    }
    return nearest;
}


void chamadas(int matriz[nCorredores][nAndares]){
    //acha Elevador Mais Próximo
    //Desloca até source
    //Desloca até destino
    puts("Sistema de elevadores");
    char c;
    Fila* processos = NULL;
    int ativos = 0;
    while (1){
        int finalizados = 0;
        for (int i = 0; i < ativos; i++){
            Processo* processo = deleteProcesso(&processos);
            if(!runProcesso(matriz, processo)) insertProcesso(&processos, processo);
            else{
                if (processo->FouD == fonte){
                    processo->FouD = destino;
                    processo->andarDestino = processo->andarFonte;
                    insertProcesso(&processos, processo);
                }
                else{
                    desativarElevador(processo->elevador);
                    finalizados++;
                }
            }
        }
        ativos = ativos - finalizados;
        printf("Chamada? (S ou s para SIM) ");
        scanf(" %c", &c);
        if (c=='s' || c=='S'){
            ativos++;
            int andarSource, andarDestino;
            printf("Informe andar de origem e andar de destino: ");
            scanf(" %d %d", &andarSource, &andarDestino);
            while (andarSource < 1 || andarSource > 300 || andarDestino > 300 || andarDestino < 1){
                printf("Entrada inválida\nInforme andar de origem e andar de destino (prédio de 300 andares): ");
                scanf(" %d %d", &andarSource, &andarDestino);
            }
            int elevador = findNearestElevator(andarSource-1);
            ativarElevador(elevador);
            Processo* processo = malloc(sizeof(processo));
            initializeProcesso(processo, elevador, andarDestino-1, andarSource-1, fonte);
            puts("Chega aqui");
            insertProcesso(&processos, processo);
        }

        for (int i = 0; i < 15; i++){
            printf("Elevador %d: Andar: %d Corredor: %d\n", i+1 ,elevadores[i].andar+1, elevadores[i].corredor+1);
        }
        puts("");
    }
}



void displayPredio(int matriz[nCorredores][nAndares]){
    for (int i = nAndares-1; i >= 0; i--){
        printf("%d:\t", i+1);
        for (int u = 0; u < nCorredores; u++){
            printf("|\t%d\t|", matriz[u][i]);
        }
        puts("");
        puts("\t-------------------------------------------------");
    }
}

int main(){
    int predio[nCorredores][nAndares];
    initializePredio(predio);
    chamadas(predio);
    // deslocamento(predio, 0, 69);
    // displayPredio(predio);
    // for (int i = 0; i < 15; i++){
    //     printf("Elevador %d: Andar: %d Corredor: %d\n", i+1 ,elevadores[i].andar+1, elevadores[i].corredor+1);
    // }
    return 0;
}