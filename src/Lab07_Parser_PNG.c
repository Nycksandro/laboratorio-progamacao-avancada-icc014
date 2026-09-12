// Aluno: Nycksandro Lima dos Santos
// Lab 07 - LPA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct tipoChunk{
    int tamanho;
    char tipo[4]; // Tem que ter 5 pq o ultimo é o '\0'
}tipoChunk;

typedef struct png_chunk_hdr{
    int largura;
    int altura;
    char bitDepth;
    char colourType;
    char compressionMethod;
    char filterMethod;
    char interfaceMethod;
} __attribute__ ((packed));
 
int main(int argc, char *argv[]){
    FILE *png_file;

    tipoChunk *png_chunk;
    struct png_chunk_hdr *png_hdr;

    //Alocando memória
    png_chunk = (tipoChunk*)malloc(sizeof(tipoChunk));

    png_hdr = (struct png_chunk_hdr*)malloc(sizeof(struct png_chunk_hdr));


    png_file = fopen(argv[1], "r"); // Lendo o arquivo

    if(png_file){ // Verificando se abriu certo
        int cont = 1; // Contador de chunks        
        fseek(png_file, 8, SEEK_CUR); // Pulando a assinatura
        while(!feof(png_file)){ // Lendo enquanto não for o fim do arquivo
            fread(png_chunk, sizeof(struct tipoChunk), 1, png_file); // Lendo o chunk
            printf("Lendo o chunk %d:\n", cont);
            printf("    --> Tamanho: %d\n", ntohl(png_chunk->tamanho));
            printf("    --> Tipo:    %.4s\n", png_chunk->tipo);
           
            if(strcmp(png_chunk->tipo, "IHDR") == 0){ // Se for IDHR o tipo eu leio o a quantidade de bytes do tipo png_chunk_hdr
                fread(png_hdr, sizeof(struct png_chunk_hdr), 1, png_file);
                printf("    --> Largura: %d\n", ntohl(png_hdr->largura));
                printf("    --> Altura: %d\n", ntohl(png_hdr->altura));
                fseek(png_file, 4, SEEK_CUR); // Pulando 4 bytes pra pular o CRC
            }
            else if(strcmp(png_chunk->tipo, "IEND") == 0){ // Se for igual a "IEND" 
                break;
            }
            else{
                fseek(png_file, ntohl(png_chunk->tamanho) + 4, SEEK_CUR);
            }
            cont++;
        }
        free(png_chunk);
        free(png_hdr);
        fclose(png_file); // Fechano arquivo
    }
}