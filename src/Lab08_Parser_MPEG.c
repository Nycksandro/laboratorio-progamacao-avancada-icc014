// Aluno: Nycksandro Lima dos Santos
// Lab 08

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){
    FILE* mpg_file;
    mpg_file = fopen(argv[1], "rb"); // Lendo o arquivo

    unsigned char *code_prefix = "\x00\x00\x01"; // code prefix
    if(mpg_file == NULL || argc != 2){ // Vendo se tá no formato errado
        printf("Nao deu pra abrir o arquivo ou formato incorreto\n");
        exit(1);
    }
    else{ // Deu certo
        unsigned char bytes[3];
        unsigned char stream;
        
        while(fread(bytes, 1, 3, mpg_file) == 3){ // leio 3 bytes
            if(memcmp(bytes, code_prefix, 3) != 0){ // Comparando 3 bytes com o code_prefix e se não for igual eu pulo 2 bytes
                fseek(mpg_file, -2, SEEK_CUR); // retornando o fseek com 2 bytes
                    //printf("2\n");
            }
            else{ // se for igual, eu leio 1 byte e verifico qual é a sua stream
                fread(&stream, 1, 1, mpg_file); // leio 1 byte
                if(stream == 0xBA){ // Pack
                    printf("--> Codigo %.2x _-- Pack\n", stream);
                }
                else if(stream  == 0xBB){ // System
                    printf("--> Codigo %.2x _-- System\n", stream);
                }
                else if(stream == 0xB3){ // Sequence
                    //Pego do pdf
                    unsigned char byte1 = fgetc(mpg_file);
                    unsigned char byte2 = fgetc(mpg_file);
                    unsigned char byte3 = fgetc(mpg_file);
                    unsigned char byte4 = fgetc(mpg_file);
                    unsigned int largura = byte1 * 16 + (byte2 >> 4);
                    unsigned int altura = ( byte2 & 0x0F) * 256 + byte3;
                    unsigned int frame_rate = byte4 & 0x0f;
                    float fr;
                    if(frame_rate == 1){
                        fr = 23.976; 
                    }
                    else if(frame_rate == 2){
                        fr = 24.000;
                    }
                    else if(frame_rate == 3){
                        fr = 25.000;
                    }
                    else if(frame_rate == 4){
                        fr = 29.970;
                    }
                    else if(frame_rate == 5){
                        fr = 30.000;
                    }
                    else if(frame_rate == 6){
                        fr = 50.000;

                    }
                    else if(frame_rate == 7){
                        fr = 59.940;
                    }
                    else if(frame_rate == 8){
                        fr = 60.000;
                    }

                    printf("--> Codigo: %.2x -- Sequence Header -- Width = %d, Height = %d -- Frame rate = %.3ffps\n", stream, largura, altura, fr); // printando igual pedido na especificação
                }
                else if(stream == 0xB8){ // Group of Pictures
                    printf("--> Codigo %.2x -- Group of Pictures\n", stream);
                }
                else if(stream == 0x00){ // Picture
                    unsigned char byte1 = fgetc(mpg_file);
                    unsigned char byte2 = (fgetc(mpg_file) << 2); // dando dois shifts a esquerda
                    char tipo;
                    byte2 = (byte2 >> 5); // dando 5 shifts a direita
                    if(byte2 == 1){
                        tipo = 'I';
                    }
                    else if(byte2 == 2){
                        tipo = 'P';
                    }
                    else if(byte2 == 3){
                        tipo = 'B';
                    }
                    printf("--> Codigo %.2x -- Picture -- Tipo = %c\n", stream, tipo);
                }
                else if(stream >= 0x01 && stream <= 0xAF){ // Slice
                    printf("--> Codigo: %.2x -- Slice\n", stream);
                }
                else if(stream >= 0xC0 && stream <= 0xDF){ // Packet Video 
                    printf("--> Codigo %.2x _-- Packet Video\n", stream);
                }
                else if(stream >= 0xE0 && stream <= 0xEF){ // Packet Audio
                    printf("--> Codigo %.2x _-- Packet Audio\n", stream);
                }
                else{ // Desconhecido
                    printf("--> Codigo: %.2x -- Tipo de stream não implementado\n", stream);

                }
            }
        }
    }
}