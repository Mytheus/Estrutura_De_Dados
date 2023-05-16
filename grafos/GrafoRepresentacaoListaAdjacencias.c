#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0



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
    return 0;
}