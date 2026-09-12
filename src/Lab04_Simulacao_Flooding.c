//Aluno: Nycksandro Lima dos Santos
//Lab 04

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct evento_t{
    double tempo;
    int alvo;
    int tipo;
}evento_t;

typedef struct lista_eventos_t{
    evento_t* evento;
    struct lista_eventos_t* prox_evento;
}lista_eventos_t;

evento_t* cria_evento(double tempo, int alvo, int tipo){ // Função que recebe os parametros da struct "evento_t", cria e retorna um evento_t*
    evento_t* novo_evento = (evento_t*)malloc(sizeof(evento_t));
    if(novo_evento == NULL){
        return NULL;
    }
    novo_evento->tempo = tempo;
    novo_evento->alvo = alvo;
    novo_evento->tipo = tipo;
    return novo_evento;
}

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){ //Função pega da Dica do PDF
    lista_eventos_t *item_novo = (lista_eventos_t*) malloc(sizeof(lista_eventos_t)); // Aloca o novo item
    if (item_novo == NULL) return false; // Falta memória?
    item_novo->evento = evento; // Seta o novo item
    item_novo->prox_evento = *lista; // O próximo do novo item será a lista
    *lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
    return true;
}

void lista_eventos_listar(lista_eventos_t *lista){ // Função que recebe o primeiro elemento e printa toda a lista, mostrando as informações dos eventos
    lista_eventos_t* item_atual = lista;
    while(item_atual != NULL){
        printf("%3.6f\t%d\t%d\n", item_atual->evento->tempo, item_atual->evento->alvo, item_atual->evento->tipo);
        item_atual = item_atual->prox_evento;
    }
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){ // Função para inserir no final da lista
    lista_eventos_t* item_novo = (lista_eventos_t*)malloc(sizeof(lista_eventos_t)); // Tenta alocar mémoria
    lista_eventos_t* item_atual;

    if(item_novo == NULL){ // se der errado a alocação de memoria
        return false;
    }

    item_novo->evento = evento; // coloca o evento
    item_novo->prox_evento = NULL; // o proximo é nulo
    
    if(*lista == NULL){ // Se a lista tiver vazia, o evento vira o primeiro elemento
        *lista = item_novo;
        return true;
    }

    else{ // Se não, percorre até o final da lista e insere
        item_atual = *lista; // Primeiro elemento
        while(item_atual->prox_evento != NULL){ // Percorre até chegar no final da lista
            item_atual = item_atual->prox_evento; // atualiza o ponteiro e percorre
        }
        //chegou no final
        item_atual->prox_evento = item_novo; // Insere no final
        return true;
    }   
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t* item_novo = (lista_eventos_t*)malloc(sizeof(lista_eventos_t)); // Tenta alocar mémoria
    lista_eventos_t* item_atual = *lista;
    
    if(item_novo == NULL){ // se der errado a alocação de memoria
        return false;
    }

    item_novo->evento = evento; // coloca o evento
    item_novo->prox_evento = NULL; // o proximo é nulo

    if(*lista == NULL){ // Se a lista for vazia, coloca o primeiro elemento (já está ordenado)
        *lista = item_novo;
    }
    else if(evento->tempo < item_atual->evento->tempo){ // Se o tempo do novo evento for menor que o tempo do primeiro, adiciona no inicio
        item_novo->prox_evento = *lista; // depois do novo vem o antigo primeiro
        *lista = item_novo; // agora o primeiro é o novo
    }
    else{ 
        while(item_atual->prox_evento != NULL && item_atual->prox_evento->evento->tempo < evento->tempo){
            item_atual = item_atual->prox_evento; // atualiza o ponteiro
        }
        //achou
        if(item_atual->prox_evento != NULL){ 
            item_novo->prox_evento = item_atual->prox_evento; // Seta o proximo elemento depois do inserido
        }
        item_atual->prox_evento = item_novo;
    }
}

typedef struct lista_vizinhos_t{
    int id;
    struct lista_vizinhos_t* prox_vizinho;
}lista_vizinhos_t;

typedef struct no_t{
    int id;
    double pos_x;
    double pos_y;
    lista_vizinhos_t *lista_vizinhos;
    bool pacote_enviado;
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

void simulacao_iniciar(lista_eventos_t **lista, grafo_t grafo){
    while(lista != NULL){
        evento_t* prim_evento = (*lista)->evento; // pega o primeiro elemento (primeiro passo)
        (*lista) = (*lista)->prox_evento; // remove o primeiro e agora o novo atual é o antigo segundo (segundo passo)
        printf("[%3.6f] No %d recebeu pacote.\n", prim_evento->tempo, prim_evento->alvo); // printando
        int indice = prim_evento->alvo; 
        // Agora executar o evento

        if(grafo[indice].pacote_enviado == false){ // ainda não mandou
            lista_vizinhos_t* aux = grafo[indice].lista_vizinhos; // criando um aux 
            while(aux != NULL){ // percorre todos os nós
                printf("\t--> Repassando pacote para o no %d ...\n", aux->id);
                
                evento_t* novo_evento = cria_evento((prim_evento->tempo + (0.1 + (aux->id * 0.01))), aux->id,1); // criando um evento

                lista_eventos_adicionar_ordenado(novo_evento, lista); // Adicionando de forma ordenada

                aux = aux->prox_vizinho; // atualizando para o proimo
            }
            grafo[indice].pacote_enviado = true; // setando como true no final
        }
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
    lista_eventos_t* lista = NULL; // criando a lista com NULL
    evento_t* evento_inicial;

    FILE *arq;
    arq = fopen(argv[1], "r");

    fscanf(arq, "%d\t%lf\n", &num_nos, &raio_comunicacao);

    grafo = grafo_criar(num_nos); //criando o grafo

    while(fscanf(arq, "%d\t%lf\t%lf\n", &id, &posicao_x, &posicao_y) != EOF){ // lendo o arquivo e pegando os valores para colocar no grafico
        grafo[i].id = id;
        grafo[i].pos_x = posicao_x;
        grafo[i].pos_y = posicao_y;
        grafo[i].pacote_enviado = false;
        grafo[i].lista_vizinhos = NULL;
        i++;
    }
    fclose(arq);

    grafo_atualizar_vizinhos(num_nos, raio_comunicacao, grafo); // atualizando os vizinhos    

    evento_inicial = cria_evento(1.0,0,1); // criando evento inicial
    lista_eventos_adicionar_ordenado(evento_inicial, &lista); // adicionando na lista de forma ordenada 
    simulacao_iniciar(&lista, grafo); // inciando a simulação

}