//Aluno: Nycksandro Lima dos Santos
//Lab02-LPA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int tam_hash;

typedef struct pessoa_t{ // Tipo Pessoa
    char nome[51];
    long long int cpf;
    int idade;
}pessoa_t;

typedef struct lista_pessoas_t{ // Tipo Lista de Pessoas
    pessoa_t* pessoa;
    struct lista_pessoas_t* prox_pessoa; // ponteiro pra prox pessoa
}lista_pessoas_t;

/*
typedef struct tabela_hash_t{ // Tipo Hash 
    lista_pessoas_t** tabela_hash_t;
}tabela_hash_t;
*/

typedef lista_pessoas_t** tabela_hash_t;


pessoa_t* cria_pessoa(char nome[51], long long int cpf, int idade){ // Função que recebe as informações de uma pessoa e cria um pessoa_t*
    pessoa_t* pessoa = (pessoa_t*)malloc(sizeof(pessoa_t));

    strcpy(pessoa->nome, nome);
    pessoa->cpf = cpf;
    pessoa->idade = idade;

    return pessoa;
}

bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){ //Adiciona no inicio
    lista_pessoas_t *item_novo = (lista_pessoas_t*) malloc(sizeof(lista_pessoas_t)); // Aloca o novo item
    
    if (item_novo == NULL) return false; // Falta memória?
    
    item_novo->pessoa = pessoa; // Seta o novo item
    item_novo->prox_pessoa = *lista; // O próximo do novo item será a lista (primeiro elemento)
    *lista = item_novo; // Aqui, estamos mudando o ponteiro da lista pra dizer quem é o primeiro elemento
    
    return true;
}

void lista_pessoas_listar(lista_pessoas_t *lista){ //Printa Lista
    lista_pessoas_t* atual = lista; //pega o primeiro elemento
    
    while(lista != NULL){ // printa tudo até acabar
        printf("- %s\t%lld\t%d\n", lista->pessoa->nome, lista->pessoa->cpf, lista->pessoa->idade);

        lista = lista->prox_pessoa; 
    }
    //acabou
}

tabela_hash_t tabela_hash_pessoas_criar(){ //cria uma tabela hash de "tam_hash" elementos
    tabela_hash_t tabela_hash = malloc(tam_hash*sizeof(tabela_hash_t)); // aloca memoria para um vetor de listas de "tam_hash" elementos
    
    for(int i = 0; i < tam_hash; i++){ //percorrendo o vetor e tam_hash = variavel global
       tabela_hash[i] = NULL; //aponta pra null
    } 

    return tabela_hash;
}

int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
    return (pessoa->cpf % tam_hash); //tam_hash = variavel global = arg[1]
}

bool tabela_hash_pessoas_adicionar(pessoa_t* pessoa, tabela_hash_t tabela_hash){
    int resultado;
    int indice = tabela_hash_pessoas_funcao(pessoa); //calcula o indice a ser colocado
    
    resultado = lista_pessoas_adicionar(pessoa, &tabela_hash[indice]); // adiciona na lista correspondente  

    if(resultado == 0){ // erro;
        printf("Erro em adicionar pessoa na tabela hash!\n");
        return false;
    }
    return true; // Deu certo
}

void tabela_hash_pessoas_listar(tabela_hash_t tabela_hash){ // printar tabela
    for(int i = 0; i < tam_hash; i++){
        printf("POSICAO %d DA TABELA HASH:\n", i);
        lista_pessoas_listar(tabela_hash[i]); // acessa a lista da posição "i"
    }
}


int main(int argc, char *argv[]){

    char nome_p[51];
    long long int cpf_p;
    int idade_p;
    pessoa_t *pessoa;
    FILE *arq;

    sscanf(argv[1], "%d", &tam_hash); //lendo o tamanho da tabela hash

    tabela_hash_t tabela_h = tabela_hash_pessoas_criar(); // cria a tabela com o tamanho especificado em arg[1]
    
    arq = fopen(argv[2], "r+"); // tenta ler o arquivo

    if(arq == NULL){ // Se não der pra abrir o arquivo
        printf("Deu erro ao tentar abrir o arquivo\n"); 
        return 1;
    }
    // Deu certo, então vamo ler
    while(fscanf(arq, "%50[^\t]\t%lld\t%d\n", nome_p, &cpf_p, &idade_p) != EOF){ //lê 50 caracteres ou até encontrar um tab, um long long int, e um int
        pessoa = cria_pessoa(nome_p, cpf_p, idade_p); // crio a pessoa com as informações lidas
        
        tabela_hash_pessoas_adicionar(pessoa,tabela_h);
    }

    fclose(arq); // Fechar arquivo

    tabela_hash_pessoas_listar(tabela_h); // Mostrando a tabela

}