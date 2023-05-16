#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2
//BUSCA EM PROFUNDIDADE: Melhor representação nesse caso é a lista de adjacências

//Adjacência: lista encadeada que indica as ligações entre vértices(arestas), contem referencia ao vertice de destino e ao peso da ligação, além da referência ao próximo item (lista)
typedef struct adjacencia {
    int vertice;
    int peso;
    struct adjacencia *prox;
} adjacencia;
//Vertice: vertice de fato, contém a lista de adjacências e qualquer outra informação 
typedef struct vertice{
    int inf;
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
        g->adj[i].inf = i+1;
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

/* A busca por profundidade vai funcionar da seguinte maneira:
    1 - Escolho um vértice para iniciar a busca
    2 - "Pinto de amarelo" (estou buscando)
    3 - Visito sua primeira aresta se não foi ainda buscada (se for branca)
    4 - Repito o processo
    5 - Se encontro um vértice sem arestas ou apenas com arestas que já foram visitadas, retorno para o anterior
        e continuo a busca pelas outras adjacências do vértice anterior
    Então, sempre vou entrando pelas arestas até encontrar uma que não tenha mais para onde ir.
    Ou seja, eu paro se ela nao tiver mais arestas pra buscar
    É chamado de por profundidade pois eu sempre busco entrando pela primeira aresta mais a fundo antes de voltar e procurar pelas outras.
    Logo, quando é encontrada uma aresta que não tem mais caminhos a seguir (não tem arestas ou é ligada apenas a arestas que já foram exploradas)
    a busca retorna para o vértice anterior para continuar a busca pelas outras arestas.
    O algoritmo a seguir apenas passeia utilizando-se do método de busca por profundidade, mas as linhas que podem ser alteradas para buscar algo estão comentadas.
    Veja primeiro a função profundidade e após a função visitaP
*/
// visitaP(grafo, vértice, lista de cores)
void visitaP(grafo* gr, int i, int *cor /*, int inf*/) { //Usa cores pra representar grafos que já foram analisados ou não, na prática: BRANCO: 0, AMARELO: 1, VERMELHO: 2
    //if (gr->adj[i].inf == inf) return 1; //Caso encontre a busca pelo item
    cor[i] = AMARELO; // Pinta de amarelo pois está sendo analisado
    adjacencia *v = gr->adj[i].head; // Pega a lista de adjacências(arestas/ligações) do vértice que ta analisando
    while (v){ //Enquanto tiver adjacências
        if (cor[v->vertice]==BRANCO){ // Se não tiver sido analisado posteriormente
            //if (visitaP(gr, v->vertice, cor , inf)) return 1; //Caso encontre a busca pelo item
            visitaP(gr, v->vertice, cor); // Chamada recursiva para a adjacência, ou seja, busca no vértice mais a fundo
        }
        v = v->prox; // Quando terminar a busca pelo caminho que a adjacência i tomou, busca pela adjacência i+1 (próxima adjacência)
    }
    cor[i] = VERMELHO; //Quando já buscou por todas as adjacências de um vértice, pinta-o de vermelho
    //return 0; // Caso nao encontre a busca pelo item
}
// profundidade(grafo)
void profundidade(grafo* gr/*, int inf*/){ //Função principal
    int cor[gr->vertices]; // Crio lista de cores (para cada vértice uma cor)
    for (int i = 0; i < gr->vertices; i++){
        cor[i] = BRANCO; // Pinto todos de branco
    }
    for (int i = 0; i < gr->vertices; i++){
        if (cor[i] == BRANCO) // Se não foi analisado ainda
        {
            //if(visitaP(gr, i, cor, inf)) return 1; // Caso a busca verifique a existencia
            visitaP(gr, i, cor); //chama para inicar a busca para cada vértice, ocorre pois podem haver vértices inacessíveis
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
    int busca;
    for (int i = 0; i < grafo->vertices;i++){
        printf("%d\n", grafo->adj[i].inf);
    }
    while (1)
    {
       printf("Digite o termo para bucar: ");
       scanf(" %d", &busca);
       profundidade(grafo);
    }
    

    return 0;
}