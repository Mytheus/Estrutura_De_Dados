#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Sistema de elevadores: Predio de 300 andares com 3 corredores para elevadores. Cada corredor tem 5 elevadores de posição incial arbitrária, nesta implementação foi decidido mantêlos numa distância de 20 andares intercalando corredores (como uma escadinha).

//Definindo constantes
#define nAndares 300
#define nCorredores 3
#define nElevadores 15

//Definindo alguns tipos auxiliares
typedef enum status {ativo, standby} status; //Status do elevador, se ativo ou em espera
typedef enum statusProcesso {fonte, destino} statusProcesso; //Status do processo, se vai até o local de chamada (fonte) ou até o local destino (destino)

//Structs utilizadas:
typedef struct Elevador{  //Elevador: Guarda informação do andar, corredor e o status do elevador
    int andar;
    int corredor;
    status statusElev;
} Elevador;

typedef struct Processo{ //Processo: Guarda elevador do processo, andar de destino, andar de fonte, e status do processo (Fonte ou Destino)
    int elevador;
    int andarDestino;
    int andarFonte;
    statusProcesso FouD;
} Processo;

//Declaro todos os 15 elevadores globalmente, eles serão identificados pela sua posição no vetor, que será seu ID
Elevador elevadores[nElevadores];

//Estrutura auxiliar de fila para gerenciar processos e métodos da fila necessários para essa aplicação:
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


//Inicializador do elevador, começa em standby
void initializeElevador(Elevador* elevador, int andar, int corredor){
    elevador->andar = andar;
    elevador->corredor = corredor;
    elevador->statusElev = standby;
}

//Inicializador do prédio, nessa aplicação o prédio é uma matriz de inteiros, onde -1 indica vazio e os números de 0 a 14 são os IDs dos elevadores.
//Dessa forma, é possível economizar espaço.
void initializePredio(int matriz[nCorredores][nAndares]){
    int pos[nElevadores] = {10, 30, 50, 70, 90, 110 ,130, 150, 170, 190, 210, 230, 250, 270, 290}; //Posições iniciais dos elevadores
    int index = 0, elevador = 0, corredor = 0;

    for (int i = 0; i < nAndares; i++){
        for (int u = 0; u < nCorredores; u++){
            if (i == pos[index]-1 && u == corredor%3){ //Coloca nos andares predefinidos intercalando corredores.
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

//Inicializador de processo, o processo definirá qual caminho o elevador deve seguir.
void initializeProcesso(Processo* processo, int elevador,int andarFonte, int andarDestino, statusProcesso FouD){
    processo->andarDestino = andarDestino;
    processo->andarFonte = andarFonte;
    processo->elevador = elevador;
    processo->FouD = FouD;
}

//Funções para movimento do elevador: Subida, descida, para a direita e para a esquerda.
//Têm em cada um deles também as verificações de limites e colisão com outros elevadores, retornando 0 sempre que não for possível realizar o movimento.
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



//Verifica se o caminho de um andar a outro, por um corredor, está livre.
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

//Ativa elevador, ou seja, troca seu status
void ativarElevador(int elevador){
    elevadores[elevador].statusElev = ativo;
}

//Desativa elevador.
void desativarElevador(int elevador){
    elevadores[elevador].statusElev = standby;
}

//Lê o processo e realiza uma ação dependendo do processo.
int runProcesso(int matriz[nCorredores][nAndares], Processo* processo){
    if (elevadores[processo->elevador].andar == processo->andarDestino){
        return 1; //Caso o processo chegue ao fim, retorna 1.
    }
    else if (elevadores[processo->elevador].andar < processo->andarDestino){ //Caso seja subida
        if (matriz[elevadores[processo->elevador].corredor][elevadores[processo->elevador].andar+1] != -1){ //Verificação de colisão
            if (!deslocarElevadorDireita(matriz, processo->elevador)) if (!deslocarElevadorEsquerda(matriz, processo->elevador)) //Tenta desviar para a direita ou para a esquerda para evitar colisão.
            return 0; //Se não conseguir, não sobe.
        }
        else subirElevador(matriz, processo->elevador); //Caso não houver colisão iminente, sobe
        return 0;
    }
    else {//Caso seja descida
        if (matriz[elevadores[processo->elevador].corredor][elevadores[processo->elevador].andar-1] != -1){ //Verificação de colisão
            if (!deslocarElevadorDireita(matriz, processo->elevador)) if (!deslocarElevadorEsquerda(matriz, processo->elevador)) //Tenta desviar para a direita ou para a esquerda para evitar colisão.
            return 0; //Se não conseguir, não desce
        }
        else descerElevador(matriz, processo->elevador); //Caso não houver colisão iminente, desce
        return 0;
    }

}

//Encontra o elevador mais próximo de determinado andar
int findNearestElevator(int andar){
    int nearest = 0;
    int menorDist = 300;
    for (int i = 0; i < nElevadores; i++){
        if (abs(elevadores[i].andar-andar)<menorDist && elevadores[i].statusElev == standby){
            menorDist = abs(elevadores[i].andar-andar);
            nearest = i;
        }
    }
    return nearest;
}

//Retorna a distância entre dois elevadores
int distEntreElevadores(int elevador1, int elevador2){
    return abs(elevadores[elevador1].andar - elevadores[elevador2].andar);
}

//Retorna a distância entre dois andares
int distEntreAndares(int andar1, int andar2){
    return abs(andar1 - andar2);
}

//Gerencia as chamadas do sistema
void chamadas(int matriz[nCorredores][nAndares]){
    puts("SISTEMA DE ELEVADORES");
    char c;
    Fila* processos = NULL;
    int ativos = 0; //Processos ativos atualmente
    while (1){
        int finalizados = 0; //Processos finalizados (Impede que a finalização de um processo diminua o tamanho do for)
        for (int i = 0; i < ativos; i++){ //Repete a leitura de processos apenas pela quantidade de processos ativos, e não até a fila esvaziar.
            Processo* processo = deleteProcesso(&processos); //Leio e retiro o primeiro processo da fila
            if(!runProcesso(matriz, processo)){ //Executa processo. Se não foi finalizado:
                if (distEntreAndares(elevadores[findNearestElevator(processo->andarDestino)].andar, processo->andarDestino)<distEntreAndares(elevadores[processo->elevador].andar, processo->andarDestino) && processo->FouD==fonte){ //Verifica a possibilidade de encontrar um elevador mais próximo que o do processo ao andar de fonte da chamada. Permite que chame elevadores recém desativados mais próximos.
                    desativarElevador(processo->elevador);
                    processo->elevador = findNearestElevator(processo->andarDestino);
                }
                insertProcesso(&processos, processo); //Reinsiro o processo no final da fila

            }
            else{ //Caso tenha finalizado
                if (processo->FouD == fonte){ //Se finalizou a estapa de deslocamento até a chamada, troco o status e inicia a ida até o destino 
                    processo->FouD = destino;
                    processo->andarDestino = processo->andarFonte;
                    insertProcesso(&processos, processo);
                }
                else{ //Se finalizou a chamada completa (até a fonte e até o destino) desativa o elevador e aumenta o número de finalizados.
                    desativarElevador(processo->elevador);
                    free(processo);
                    finalizados++;
                }
            }
        }
        ativos = ativos - finalizados; //Atualiza o número de ativos fora do for.
        
        //Interface de entrada
        printf("Chamada? (S ou s para SIM) ");
        scanf(" %c", &c);
        
        if (c=='s' || c=='S'){ //Caso tenha uma nova chamada:
            ativos++; //Ativa mais um processo
            int andarSource, andarDestino;
            printf("Informe andar de origem e andar de destino: "); //Recebe andares de fonte e destino
            scanf(" %d %d", &andarSource, &andarDestino);

            while (andarSource < 1 || andarSource > 300 || andarDestino > 300 || andarDestino < 1){ //Verifica limites
                printf("Entrada inválida\nInforme andar de origem e andar de destino (prédio de 300 andares): ");
                scanf(" %d %d", &andarSource, &andarDestino);
            }

            int elevador = findNearestElevator(andarSource-1); //Encontra elevador mais próximo
            ativarElevador(elevador); //Ativa-o
            Processo* processo = malloc(sizeof(processo)); //Aloca espaço para o processo
            initializeProcesso(processo, elevador, andarDestino-1, andarSource-1, fonte); //Inicializa o processo
            insertProcesso(&processos, processo); //Insere o processo na fila de execução
        }
        //Display da situação atual dos elevadores
        for (int i = 0; i < nElevadores; i++){
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
    // for (int i = 0; i < nElevadores; i++){
    //     printf("Elevador %d: Andar: %d Corredor: %d\n", i+1 ,elevadores[i].andar+1, elevadores[i].corredor+1);
    // }
    return 0;
}