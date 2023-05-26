#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define BRANCO 0
#define VERMELHO 1
//Adjacência: lista encadeada que indica as ligações entre vértices(arestas), contem referencia ao vertice de destino e ao peso da ligação, além da referência ao próximo item (lista)
typedef struct adjacencia {
    int vertice;
    int peso;
    struct adjacencia *prox;
} adjacencia;
//Vertice: vertice de fato, contém a lista de adjacências e qualquer outra informação 
typedef struct vertice{
    //Pode ter outros dados aqui
    adjacencia *head;
} vertice;
//Grafo: lista de vértices, guarda a informação das quantidades de vertices, de arestas e a lista de vértices.
typedef struct grafo{
    int vertices;
    int arestas;
    vertice *adj;
} grafo;

/*FILA*/
typedef struct Fila {
    int inf;
    struct Fila* next;
} Fila;

Fila* getNode(){
    return malloc(sizeof(Fila));
}

Fila* initFila(){
    return NULL;
}

void insertValue(Fila** fila, int inf){
    while((*fila)){
        fila=&((*fila)->next);
    }
    (*fila) = getNode();
    (*fila)->inf = inf;
    (*fila)->next = NULL;
}

int deleteValue(Fila** fila){
    Fila* aux = (*fila);
    int retorno = (*fila)->inf;
    (*fila) = (*fila)->next;
    free(aux);
    return retorno;
}

void displayFila(Fila* fila){
    if (!fila){
        printf("\n");
        return;
    }
    else{
        printf("%d ", fila->inf);
        displayFila(fila->next);
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






grafo* criaGrafo(int v){
    grafo* g = malloc(sizeof(grafo)); //Aloca espaço para o grafo
    g->vertices = v; //Define quantos vértices terá
    g->arestas = 0; //Como é um grafo recém criado, não tem adjacências
    g->adj = malloc(sizeof(vertice)*v); //Aloca espaço pra lista de vértices
    for (int i = 0; i < v; i++){
        g->adj[i].head = NULL; //Inicializa a lista de adjacências de cada vértice como NULL
    }
    return g; //Retorna o grafo
}

adjacencia* criaAdj(int v, int peso) {
    adjacencia *aux = malloc(sizeof(adjacencia)); //Aloca espaço pra adjacência
    aux->vertice = v; //define o vertice de destino
    aux->peso = peso; //define o peso
    aux->prox = NULL; //define a referencia pro proximo (NULL)
    return aux; //Retorna a adjacência (ligação/aresta)
}

int criaAresta(grafo *gr, int vf, int vd, int p){ // grafo, vertice fonte, vertice destino, peso
    if (!gr) return false; //Verificacoes
    if ((vf<0)||(vf>=gr->vertices)) return false;
    if ((vd<0)||(vd>=gr->vertices)) return false;
    adjacencia* novaAdj = criaAdj(vd, p); //Cria a adjacencia
    novaAdj->prox = gr->adj[vf].head; //Adiciona a lista de adjacencia do vertice fonte no prox (ou seja, insere antes do primeiro item da lista) (IMPORTANTE: Inserir no inicio ou no fim é arbitrário, tanto faz a ordem)
    gr->adj[vf].head = novaAdj; // Coloca no inicio
    gr->arestas++; //Mais uma aresta
    return true;
}

void display(grafo *gr){
    printf("Vértices: %d.\nArestas: %d.\n", gr->vertices, gr->arestas);
    for (int i = 0; i < gr->vertices; i++){
        printf("v%d: ", i +1);
        adjacencia* aux = gr->adj[i].head;
        while (aux){
            printf("v%d(%d) ", aux->vertice+1, aux->peso);
            aux = aux->prox; 
        }
        printf("\n");
    }
}

/*
A busca em largura se caracteriza em procurar por todas adjacências de um vértice antes de passar para outro vértice através da aresta,
ou seja, eu percorro todas as arestas ligadas ao vértice, só então posso ir ao próximo vértice, e procurar pelas arestas novamente.
Então, o passo a passo é:
1 - Busco na aresta atual (inicial)
2 - Defino ela como buscada
3 - Insiro ela numa *fila* 
4 - Enquanto a fila não estiver vazia, eu vou:
    4.1 - Armazenar e Deletar o primeiro da fila (primeiro que entra primeiro que sai)
    4.2 - Percorrer os vértices adjacentes ao vértice armazenado, se não explorados
    4.3 - Marcá-los como explorados
    4.4 - Inserí-los na fila
    4.5 - Repetir o processo

Inserindo-os numa fila, você garante que não explorará os vértices adjacentes aos 
vértices adjantes do vértice atual, uma vez que eles seguirão a ordem da fila.
*/
//visitaL(Grafo, vértice inicial, lista de cores))
void visitaL(grafo* gr, int i, int *cor){
    int aux;
    Fila* fila = initFila(); // Cria fila
    insertValue(&fila, i); // Insere o inicial
    cor[i] = VERMELHO; // Define o inicial como explorado
    while (!isEmpty(fila)){ // Enquanto a fila não estiver vazia
        aux = deleteValue(&fila); // Armazena e deleta o primeiro da lista
        printf("V%d ->", aux+1);
        adjacencia* filhos = gr->adj[aux].head; // Lista de filhos (adjacências)
        while(filhos){ // Percorre os filhos
            if (cor[filhos->vertice]==BRANCO){ // Se não foi explorado
                cor[filhos->vertice]=VERMELHO; // Marca como explorado
                insertValue(&fila, filhos->vertice); // Insere na fila
            }
            filhos = filhos->prox; // Prox adjacência
        }
    }
    puts("");
}

void largura(grafo* grafo){
    int cor[grafo->vertices]; // Lista de verificação
    for (int i = 0; i < grafo->vertices; i++){
        cor[i] = BRANCO;
    } // Inicializa
    for (int i = 0; i < grafo->vertices; i++){ // Garante que visitou todos os grafos, mesmo os inacessíveis
        if (cor[i]==BRANCO){
            visitaL(grafo, i, cor); 
            printf("\n");
        }
    }   
}


int main(){
    int n, destino, peso;
    printf("Quantas vértices no grafo?: ");
    scanf(" %d", &n);
    grafo* grafo = criaGrafo(n);
    for (int i =0; i < n; i++){
        while(destino>=0){
            printf("Vértice: v%d\n", i+1);
            printf("Deseja criar adjacência à qual vértice?(-1 para finalizar)");
            scanf(" %d", &destino);
            if (destino>=0){
                printf("Qual peso da aresta? ");
                scanf(" %d", &peso);
                if (criaAresta(grafo, i, destino-1, peso)) printf("Adjacência adicionada com sucesso!\n");
            }
        }
        destino = 0;
    }
    display(grafo);
    int cor[10] = {0,0,0,0,0,0,0,0,0,0};
    visitaL(grafo, 0, cor);
    return 0;
}