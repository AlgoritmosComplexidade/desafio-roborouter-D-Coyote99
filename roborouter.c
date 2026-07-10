#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ALGORITMOS EM GRAFOS - Desafio RoboRouter (RescueBotics)
// Utilize este código base para iniciar o seu desafio.
// Descomente e implemente as funções de acordo com o nível escolhido.

#define MAX_VERTICES 10
#define INFINITO 9999 // Utilizado no Nível Mestre para o algoritmo de Dijkstra

// ====================================================================
// NÍVEL NOVATO: Representação do Grafo (Matriz de Adjacências)
// ====================================================================

// Matriz global para simplificar o uso didático
int grafo[MAX_VERTICES][MAX_VERTICES];
int num_vertices = 0;

// Função para zerar a matriz (nenhuma conexão inicial)
void inicializarGrafo(int n) {
    num_vertices = n;
    // Dica: Crie dois laços 'for' aninhados (i e j) para percorrer a matriz
    // e preencha todos os espaços com 0 (para não ponderado) ou INFINITO (se for focar no Mestre).
    for (int i = 0; i < MAX_VERTICES; i++){
        for (int j = 0; j < MAX_VERTICES; j++){
        	if (i == j){
        		grafo[i][j] = 0;
			} else {
				grafo[i][j] = INFINITO;
			}
		}
	}
}

// Função para criar conexão entre cruzamentos do labirinto
void adicionarAresta(int origem, int destino, int peso) {
    // Dica: Para grafos não direcionados, se A se conecta a B, B se conecta a A.
    grafo[origem][destino] = peso;
    grafo[destino][origem] = peso;
}

// Função para exibir a Matriz
void imprimirGrafo() {
    printf("--- Representacao do Labirinto (Matriz) ---\n");
    // Dica: Crie laços 'for' aninhados para dar um printf na matriz.
    for (int i = 0; i < num_vertices; i++){
        for (int j = 0; j < num_vertices; j++)
            printf("%d ", grafo[i][j]);
        printf("\n");  
    }
}


// ====================================================================
// NÍVEL AVENTUREIRO: Travessia (Busca)
// ====================================================================

// Dica: Para a DFS ou BFS, você precisará de um vetor para marcar quem já foi visitado
bool visitados[MAX_VERTICES];

void inicializarVisitados() {
    for(int i = 0; i < MAX_VERTICES; i++) {
        visitados[i] = false;
    }
}

// Implemente a Busca em Profundidade (DFS) de forma recursiva

void buscaProfundidade(int vertice_atual, int destino) {
    // 1. Marque o vertice_atual como visitado (true).
    visitados[vertice_atual] = true;
    // 2. Imprima o vertice_atual.
    printf("%d ", vertice_atual);
    // 3. Verifique se vertice_atual == destino. Se sim, achou!
    if (vertice_atual == destino){
        printf("\n Destino %d alcancado!\n", destino);
        return;
    }
    // 4. Faça um 'for' percorrendo os vizinhos. Se houver aresta e não estiver visitado, chame a buscaProfundidade recursivamente.
    for (int vizinho = 0; vizinho < num_vertices; vizinho++){
        if (grafo[vertice_atual][vizinho] > 0 && !visitados[vizinho]){
            buscaProfundidade(vizinho, destino);
            if (visitados[destino]){
                return;
            }
        }
    }

}



// ====================================================================
// NÍVEL MESTRE: O Caminho Mínimo (Dijkstra)
// ====================================================================


void dijkstra(int origem, int destino) {
    int distancias[MAX_VERTICES];
    int antecessores[MAX_VERTICES];
    bool processados[MAX_VERTICES];

    // 1. Inicialização: Defina todas as distâncias como INFINITO e processados como false.
    for (int i = 0; i < num_vertices; i++){
    	distancias[i] = INFINITO;
    	antecessores[i] = -1;
    	processados[i] = false;
	}
    // 2. A distância da origem para ela mesma é 0 (distancias[origem] = 0).
    distancias[origem] = 0;

    // 3. Loop principal para encontrar o vértice com menor distância não processado.
    for (int i = 0; i < num_vertices - 1; i++){
    	int menor_distancia = INFINITO;
    	int u = -1;
    	
    	for (int v = 0; v < num_vertices; v++){
    		if (!processados[v] && distancias[v] < menor_distancia){
    			menor_distancia = distancias[v];
    			u = v;
			}
		}
		if (u == -1) break;
		
		processados[u] = true;
	
    
    	// 4. Relaxamento: Atualize as distâncias dos vizinhos do vértice escolhido.
    	//    Se (distancia_atual + peso_aresta < distancia_conhecida_do_vizinho), atualize!
    	//    Não se esqueça de salvar o antecessor.
    	for (int v = 0; v < num_vertices; v++){
    		if (grafo[u][v] != INFINITO && grafo[u][v] > 0 && !processados[v]){
    			if (distancias[u] + grafo[u][v] < distancias[v]){
    				distancias[v] = distancias[u] + grafo[u][v];
    				antecessores[v] = u;
				}
			}
		}
	}
    // 5. No final, use o vetor de antecessores, partindo do destino, para imprimir o caminho reverso até a origem.
    //    Mostre também a distancias[destino] como o custo total.
    if (distancias[destino] == INFINITO){
    	printf("Não existe caminho entre %d e %d.\n", origem, destino);
    	return;
	}
	
	printf("Distancia total: %d\n", distancias[destino]);
	
	int caminho[MAX_VERTICES];
	int tam_caminho = 0;
	int atual = destino;
	
	while (atual != -1){
		caminho[tam_caminho++] = atual;
		atual = antecessores[atual];
	}
	
	printf("Caminho percorrido: ");
	for (int i = tam_caminho - 1; i >= 0; i--){
		printf("%d", caminho[i]);
		if (i > 0) printf(" -> ");
	}
	printf("\n");
}


// ====================================================================
// FUNÇÃO PRINCIPAL
// ====================================================================

int main() {
    printf("=== RESCUE BOTICS: ROBOROUTER ===\n\n");

    // ---------------------------------------------------------
    // ÁREA DO NÍVEL NOVATO
    // ---------------------------------------------------------
    
    // Exemplo: Inicializar um grafo com 6 vértices (0 a 5)
    inicializarGrafo(6);

    // Dica: Modele o labirinto do PDF. Exemplo: Vértice 0 ligado ao 1
    adicionarAresta(0, 1, 2);
    adicionarAresta(0, 4, 5);
    adicionarAresta(1, 2, 2);
    adicionarAresta(1, 3, 4);
    adicionarAresta(1, 4, 1);
    adicionarAresta(2, 3, 3);
    adicionarAresta(2, 4, 3);
    adicionarAresta(3, 5, 1);
    adicionarAresta(4, 5, 5);
    
    imprimirGrafo();
    

    // ---------------------------------------------------------
    // ÁREA DO NÍVEL AVENTUREIRO
    // ---------------------------------------------------------
    
    printf("\n--- Buscando Rota (DFS) ---\n");
    inicializarVisitados();
    buscaProfundidade(0, 5); // Exemplo: Buscar do 0 ao 5
    

    // ---------------------------------------------------------
    // ÁREA DO NÍVEL MESTRE
    // ---------------------------------------------------------
    
    printf("\n--- Calculando Rota Mais Rapida (Dijkstra) ---\n");
    // Lembre-se de alterar as inserções do Nível Novato para incluir o Peso (distância real).
    dijkstra(0, 5); // Exemplo: Menor caminho do 0 ao 5
    

    return 0;
}
