//Aluno: Nycksandro Lima dos Santos
//Lab 03

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct lista_vizinhos_t{
    int id;
    struct lista_vizinhos_t* prox_vizinho;
}lista_vizinhos_t;

typedef struct no_t{
    int id;
    double pos_x;
    double pos_y;
    lista_vizinhos_t *lista_vizinhos;
}no_t;

typedef no_t* grafo_t;


bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
    lista_vizinhos_t* novo_vizinho = (lista_vizinhos_t*) malloc(sizeof(lista_vizinhos_t)); // aloca memoria para um novo vizinho
    if(novo_vizinho == NULL) return false; // Falta memória?
    novo_vizinho->id = vizinho; // Adiciona o id no novo vizinho
    novo_vizinho->prox_vizinho = *lista; // O proximo desse vizinho será o novo adicionado
    *lista = novo_vizinho; // Agora o primeiro elemento é oque eu adicionei
    return true; // Deu certo
}

void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    lista_vizinhos_t* item_atual = lista;
    while(item_atual != NULL){
        printf("%d ", item_atual->id); // printa
        item_atual = item_atual->prox_vizinho; // atualiza o ponteiro
    }

}

grafo_t grafo_criar(int tam){
    grafo_t grafo = malloc(tam*sizeof(no_t)); // aloca memoria
    return grafo;
}
void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(i != j){ 
                double distancia_euclidiana = sqrt(pow(grafo[i].pos_x - grafo[j].pos_x, 2) + pow(grafo[i].pos_y - grafo[j].pos_y, 2));
                if(distancia_euclidiana < raio_comunicacao){ // distância entre i e j seja menor que o raio de comunicação
                    lista_vizinhos_adicionar(grafo[i].id, &grafo[j].lista_vizinhos); // adiciona i na lista de vizinhos de j
                }
            }
        }
    }
}

void grafo_imprimir(int tam, grafo_t grafo){
    for(int i = 0; i < tam; i++){
        printf("NO %d: ", i);
        lista_vizinhos_imprimir(grafo[i].lista_vizinhos);
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    int  num_nos;
    double raio_comunicacao;

    int id;
    double posicao_x;
    double posicao_y;

    int i = 0;

    grafo_t grafo;


    FILE *arq;
    arq = fopen(argv[1], "r");

    fscanf(arq, "%d\t%lf\n", &num_nos, &raio_comunicacao);

    grafo = grafo_criar(num_nos); //criando o grafo

    while(fscanf(arq, "%d\t%lf\t%lf\n", &id, &posicao_x, &posicao_y) != EOF){ // lendo o arquivo e pegando os valores para colocar no grafico
        grafo[i].id = id;
        grafo[i].pos_x = posicao_x;
        grafo[i].pos_y = posicao_y;

        grafo[i].lista_vizinhos = NULL;
        i++;
    }
    fclose(arq);

    grafo_atualizar_vizinhos(num_nos, raio_comunicacao, grafo); // atualizando os vizinhos

    grafo_imprimir(num_nos, grafo); // imprimindo o grafo

}