//Aluno: Nycksandro Lima dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/* 1°Questão

int main(int argc, char *argv[]){
    double tempoB;
    int alvoB;
    int tipoB;

    evento_t* eventoitem_atual;
    lista_eventos_t* lista = NULL;
    
    FILE *arq;
    arq = fopen(argv[1], "r+");

    while(fscanf(arq, "%lf\t%d\t%d\n", &tempoB, &alvoB, &tipoB) != EOF){
        eventoitem_atual = cria_evento(tempoB,alvoB,tipoB); // Crio um evento
        lista_eventos_adicionar_inicio(eventoitem_atual, &lista);
    }
    fclose(arq);

    lista_eventos_listar(lista);
}

*/

/* 2°Questão 
int main(int argc, char *argv[]){
    double tempoB;
    int alvoB;
    int tipoB;

    evento_t* eventoitem_atual;
    lista_eventos_t* lista = NULL;
    
    FILE *arq;
    arq = fopen(argv[1], "r+");

    while(fscanf(arq, "%lf\t%d\t%d\n", &tempoB, &alvoB, &tipoB) != EOF){
        eventoitem_atual = cria_evento(tempoB,alvoB,tipoB); // Crio um evento
        lista_eventos_adicionar_fim(eventoitem_atual, &lista);
    }
    fclose(arq);

    lista_eventos_listar(lista);
}

*/

// 3°Questão

int main(int argc, char *argv[]){
    double tempoB;
    int alvoB;
    int tipoB;

    evento_t* eventoitem_atual;
    lista_eventos_t* lista = NULL;
    
    FILE *arq;
    arq = fopen(argv[1], "r+");

    while(fscanf(arq, "%lf\t%d\t%d\n", &tempoB, &alvoB, &tipoB) != EOF){
        eventoitem_atual = cria_evento(tempoB,alvoB,tipoB); // Crio um evento
        lista_eventos_adicionar_ordenado(eventoitem_atual, &lista);
    }
    fclose(arq);

    lista_eventos_listar(lista);
}