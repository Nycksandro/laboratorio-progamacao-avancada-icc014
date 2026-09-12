// Aluno: Nycksandro Lima dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

typedef struct {
    uint8_t daddr[6]; // Endereco MAC de destino
    uint8_t saddr[6]; // Endereco MAC de origem (source)
    uint16_t protocol; // Protocolo da próxima camada (IP!)
} __attribute__((packed)) ethernet_hdr_t;
    
typedef struct {
    uint8_t hdr_len:4, // Tamanho do Cabeçalho,
    version:4; // Versão do IP
    uint8_t tos; // Tipo de serviço
    uint16_t tot_len; // Tamanho total do IP
    uint16_t id; // Id do pacote
    uint16_t frag_off; // Fragmentado?
    uint8_t ttl; // Tempo de vida
    uint8_t protocol; // Protocolo próxima camada (TCP!)
    uint16_t check; // Checksum
    uint8_t saddr[4]; // Endereço IP de origem
    uint8_t daddr[4]; // Endereço IP de destino
} __attribute__((packed)) ip_hdr_t;

typedef struct {
    uint16_t sport; // Porta TCP de origem
    uint16_t dport; // Porta TCP de destino
    uint32_t seq; // Sequência
    uint32_t ack_seq; // Acknowledgement
    uint8_t reservado:4, // Não usado
    hdr_len:4; // Tamanho do cabecalho
    uint8_t flags; // Flags do TCP
    uint16_t window; // Tamanho da janela
    uint16_t check; // Checksum
    uint16_t urg_ptr; // Urgente
} __attribute__((packed)) tcp_hdr_t;


int main(int argc, char *argv[]){
    FILE* arq;
    arq = fopen(argv[1], "rb"); // Lendo o arquivo

    if(arq == NULL || argc != 2){ // Vendo se tá no formato errado
        printf("Nao deu pra abrir o arquivo ou formato incorreto\n");
        exit(1);
    }
    else{ // Deu certo
        ethernet_hdr_t *ethernet = malloc(sizeof(ethernet_hdr_t));
        ip_hdr_t *ip = malloc(sizeof(ip_hdr_t));
        tcp_hdr_t *tcp = malloc(sizeof(tcp_hdr_t)); 
        
        //ETHERNET
        fread(ethernet, sizeof(ethernet_hdr_t), 1, arq); // Lendo o cabeçalho de ethernet

        printf("Lendo Ethernet ..\n  --> MAC de Origem: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", ethernet->saddr[0],ethernet->saddr[1],ethernet->saddr[2],ethernet->saddr[3],ethernet->saddr[4], ethernet->saddr[5]);
        printf(" --> MAC de Destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",ethernet->daddr[0],ethernet->daddr[1],ethernet->daddr[2],ethernet->daddr[3],ethernet->daddr[4], ethernet->daddr[5]);
        
        //IP
        fread(ip, sizeof(ip_hdr_t), 1, arq); // Lendo o cabeçalho de IP
        printf("Lendo IP ..\n  --> Versão do IP: %d\n", ip->version);
        printf("  --> Tamanho do cabeçalho: %d bytes\n", ip->hdr_len*4);
        printf("  --> Tamanho do pacote: %d bytes\n", ntohs(ip->tot_len));

        printf("  --> Endereço IP de Origem: %u.%u.%u.%u\n", ip->saddr[0], ip->saddr[1], ip->saddr[2], ip->saddr[3]);
        printf("  --> Endereço IP de Destino: %u.%.u.%.u.%u\n", ip->daddr[0], ip->daddr[1], ip->daddr[2], ip->daddr[3]);
                
        if(ip->hdr_len*4 - sizeof(ip_hdr_t) > 0){ // Só vou pular se tiver extra 
            fseek(arq, (ip->hdr_len*4 - sizeof(ip_hdr_t)), SEEK_CUR); // Pulando o que foi pedido
        }
        
        //TCP
        fread(tcp, sizeof(tcp_hdr_t), 1, arq); // Lendo o cabeçalho do TCP
        
        printf("Lendo TCP ..\n  --> Porta de Origem: %d\n", ntohs(tcp->sport));
        printf("  --> Porta de Destino: %d\n", ntohs(tcp->dport));
        printf("  --> Tamanho do cabeçalho: %d bytes\n", tcp->hdr_len*4); 
        
        if(tcp->hdr_len*4 - sizeof(tcp_hdr_t) > 0){ // Também só vou pular se tiver espaço extra
            fseek(arq, (tcp->hdr_len*4 - sizeof(tcp_hdr_t)), SEEK_CUR); // Pulando denovo como foi pedido
        }
        //HTTP
        int tam_dados = ntohs(ip->tot_len) - (ip->hdr_len*4) - (tcp->hdr_len*4);
        int caractere;
        printf("Lendo Dados (HTTP) ..\n  --> Tamanho dos dados: %d bytes\n  --> Dados:\n", tam_dados);
        //Agora lendo o resto do arquivo
        while ((caractere = fgetc(arq)) != EOF) { // Imprimindo o resto
            putchar(caractere);  
        }

        //desalocando os ponteiros q usei
        free(ethernet); 
        free(ip);
        free(tcp);
        fclose(arq); // Fechando arquivo

    }   
}