// Aluno: Nycksandro Lima dos Santos

#include <stdio.h>
#include <GL/glut.h>
#include <time.h> 
#include <stdlib.h>
#include <stdbool.h>

//Variaveis globais pra facilitar nas funções
int altura;
int largura;
int quant_segm;

typedef struct ponto_t{
    int x; // cordenada x
    int y; // cordenada y
}ponto_t;

typedef struct segmento_t{ //Adpatei codigo do Lab01 de listas pra cá
    ponto_t final;
    ponto_t inicial;
}segmento_t;

typedef struct lista_segmentos_t{
    segmento_t *segmento;
    struct lista_segmentos_t* prox_segmento;
}lista_segmentos_t;

int ccw(ponto_t A, ponto_t B, ponto_t C){
    return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x);
    
}

int intersect(ponto_t A, ponto_t B, ponto_t C, ponto_t D){
    return ccw(A,C,D) != ccw(B,C,D) && ccw(A,B,C) != ccw(A,B,D);
    
}

segmento_t* cria_segmento(ponto_t *inicio, ponto_t *fim){ //Função pra criar
    segmento_t* novo_segmento = (segmento_t*)malloc(sizeof(segmento_t));
    if(novo_segmento == NULL){
        return NULL;
    }
    novo_segmento->inicial.x = inicio->x;
    novo_segmento->inicial.y = inicio->y;
    novo_segmento->final.x = fim->x;
    novo_segmento->final.y = fim->y;

    return novo_segmento;
}

bool lista_segmentos_adicionar_inicio(segmento_t *segmento, lista_segmentos_t **lista){ //Função pega da Dica do PDF
    lista_segmentos_t *item_novo = (lista_segmentos_t*) malloc(sizeof(lista_segmentos_t)); // Aloca o novo item
    if (item_novo == NULL) return false; // Falta memória?
    item_novo->segmento = segmento; // Seta o novo item
    item_novo->prox_segmento = *lista; // O próximo do novo item será a lista
    *lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
    return true;
}

void lista_segmentos_listar(lista_segmentos_t *lista){ // Função que recebe o primeiro elemento e printa toda a lista, mostrando as informações dos segmentos
    lista_segmentos_t* item_atual = lista;
    while(item_atual->prox_segmento != NULL){
        printf("%d\t%d\t%d\t%d\n", item_atual->segmento->inicial.x, item_atual->segmento->inicial.y, item_atual->segmento->final.x, item_atual->segmento->final.y);
        item_atual = item_atual->prox_segmento;
    }
}

bool busca_lista_intersecao(lista_segmentos_t *lista, ponto_t A, ponto_t B){ // Função pra verificar se dois segmentos tem interseção
    lista_segmentos_t* item_atual = lista;
    int intersecao;
    for(item_atual; item_atual->prox_segmento != NULL; item_atual = item_atual->prox_segmento){
        intersecao = intersect(item_atual->segmento->inicial, item_atual->segmento->final, A, B); // Verifica se ta intersectada
        if(intersecao == true){
            return true;
        }
    }
    return false;
}

void setar_pontos(ponto_t *ponto, int x, int y){ // Função pra setar pontos
    ponto->x = x;
    ponto->y = y;
}

int gerar_aleatorio(int minimo, int maximo){ // Função pra gerar número aleatorio em um intervalo
    int numero_aleatorio = (rand() % (maximo - minimo + 1)) + minimo; // Usei a formula pra achar numero aleatorio em intervalo
    return numero_aleatorio;

}

void display(void) { // Função do siplay
    int x1,x2,y1,y2,valor_maximo;
    segmento_t *segm;
    lista_segmentos_t *lista_segm = (lista_segmentos_t*) malloc(sizeof(lista_segmentos_t)); // criando a lista
    ponto_t ponto_inicio;
    ponto_t  ponto_fim;
    bool intersecao = true;

    if(altura > largura){ // Pegando o valor maximo entre eles pra poder gerar certinho
        valor_maximo = altura;
    }
    else{
        valor_maximo = largura;
    }

    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0.0, 0.0, 0.0); // Seta a cor do seg. (Red, Green, Blue, entre 0.0 e 1.0)
    glBegin(GL_LINES); // Indica que um segmento será iniciado

    //Gerando numeros aleatorios pra x1 e y1, x2 e y2
    for(int i = 0; i < quant_segm; i++){
        intersecao = true;
        while(intersecao != false){
            x1 = gerar_aleatorio(0,valor_maximo);
            while(x1 > largura){ // Vou gerando x1 até ele ficar dentro da janela 
                x1 = gerar_aleatorio(0,valor_maximo);
            }

            y1 = gerar_aleatorio(0,valor_maximo);
            while(y1 > altura){ // Vou gerando y1 até ele ficar dentro da janela
                y1 = gerar_aleatorio(0,valor_maximo);
            }

            x2 = gerar_aleatorio(0, valor_maximo);
            while(x2 > largura){ // Vou gerando x2 até ele ficar dentro da janela 
                x2 = gerar_aleatorio(0,valor_maximo);
            }
            y2 = gerar_aleatorio(0, valor_maximo);
            while(y2 > altura){ // Vou gerando y2 até ele ficar dentro da janela
                y2 = gerar_aleatorio(0,valor_maximo);
            }
            //Agora que todas as 4 cordenadas estão certas, eu crio os pontos, depois o segmento e adiciono na lista
            setar_pontos(&ponto_inicio,x1,y1);
            setar_pontos(&ponto_fim, x2, y2);
            intersecao = busca_lista_intersecao(lista_segm, ponto_inicio, ponto_fim);

        }
        segm = cria_segmento(&ponto_inicio, &ponto_fim); //cria o segmento
        lista_segmentos_adicionar_inicio(segm, &lista_segm); //taca na lista

        glVertex2f(x1, y1); // Seta a posição inicial do segmento (inteiros)
        glVertex2f(x2, y2); // Seta a posição final do segmento (inteiros)
    }
    glEnd(); // Finaliza a criação do segmento
    //lista_segmentos_listar(lista_segm);

    //Liberando o espaço
    free(lista_segm);

    glFlush();
}

int main(int argc, char* argv[]){
    largura = atoi(argv[1]); // Lendo a largura
    altura = atoi(argv[2]); // Lendo a altura
    quant_segm = atoi(argv[3]); // Lendo a quantidade de segmentos
    srand(time(NULL)); // Setando a seed dos numeros aleatorios

    //Trecho do codigo pra abrir a janela
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
    // Cria uma janela de tamanho “largura” x “altura”
    glutInitWindowSize(largura, altura);
    glutCreateWindow ("Segmentos Aleatorios");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, largura, 0.0, altura, -1.0, 1.0);
    // Seta a cor do fundo da janela
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // Seta a função “display” como sendo a função que irá pintar a janela (infinitamente)
    glutDisplayFunc(display);
    glutMainLoop();

}