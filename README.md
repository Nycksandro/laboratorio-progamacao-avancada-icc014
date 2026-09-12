# Trabalhos Práticos - Laboratório de Programação Avançada

Repositório destinado ao armazenamento e documentação dos 10 trabalhos práticos (laboratórios) desenvolvidos na disciplina de **Laboratório de Programação Avançada**. Os projetos focam na implementação em linguagem C de estruturas de dados dinâmicas, manipulação direta de arquivos binários, análise de cabeçalhos e protocolos de redes, computação gráfica com OpenGL e algoritmos de força bruta/segurança.

---

## Tecnologias e Ferramentas Utilizadas

- **Linguagem C (GCC):** Implementação de baixo e médio nível de algoritmos e estruturas de dados dinâmicas.
- **Estruturas de Dados Dinâmicas:** Listas encadeadas simples, tabelas hash com encadeamento e grafos de conectividade.
- **Análise e Inspecção de Arquivos Binários:** Manipulação de ponteiros de arquivo, leitura de *headers*, *structs packed* (`__attribute__((packed))`) e controle de *endianness* (`ntohl`, `ntohs`).
- **Bibliotecas do Sistema e Criptografia:** `<crypt.h>` para quebra de hashes de senha e `<arpa/inet.h>` para decodificação de pacotes de rede.
- **OpenGL & FreeGLUT:** Computação gráfica interativa, alocação de primitivas geométricas e algoritmos de geometria computacional.

---

## Lista de Trabalhos Desenvolvidos

### Trabalho 01: Simulador de Eventos Discretos com Lista Encadeada
- **Descrição:** Implementação de uma estrutura de dados do tipo Lista Encadeada Simples em C para o gerenciamento e ordenação de eventos discretos baseados em marcação temporal (*timestamps*).
- **Destaques:** 
  - Alocação dinâmica de memória para structs de eventos (`evento_t`) e nós da lista (`lista_eventos_t`).
  - Suporte a inserção no início, inserção no fim e inserção ordenada por tempo.
  - Leitura de eventos a partir de arquivo texto e ordenação em tempo de inserção $O(N)$.
- **Entregáveis:** [Código-fonte em C](src/Lab01_Lista_Eventos.c).

---

### Trabalho 02: Tabela Hash de Pessoas com Encadeamento Exterior
- **Descrição:** Construção de uma Tabela Hash em C utilizando listas encadeadas para tratamento de colisões por encadeamento (*separate chaining*).
- **Destaques:**
  - Armazenamento dinâmico de registros com nome, CPF e idade.
  - Função hash modular personalizada baseada no CPF do registro (`CPF % tamanho_tabela`).
  - Leitura de registros formatados via arquivo de entrada e distribuição dinâmica nas posições da hash.
- **Entregáveis:** [Código-fonte em C](src/Lab02_Tabela_Hash.c).

---

### Trabalho 03: Grafo de Adjacência e Raio de Comunicação Sem Fio
- **Descrição:** Modelagem e implementação de um Grafo para simular uma rede de nós móbies e sua conectividade baseada em alcance por raio de comunicação.
- **Destaques:**
  - Representação do grafo via vetor de nós contendo listas de adjacência dinâmicas para os vizinhos.
  - Cálculo de distância euclidiana 2D para determinar dinamicamente se dois nós estão no alcance de transmissão.
  - Leitura de coordenadas cartesianas e atualização das conexões do grafo.
- **Entregáveis:** [Código-fonte em C](src/Lab03_Grafo_Vizinhos.c).

---

### Trabalho 04: Simulação de Inundação de Pacotes em Rede de Sensores (Flooding)
- **Descrição:** Integração entre a Lista de Eventos Ordenada (Lab 01) e o Grafo de Conectividade (Lab 03) para simular o protocolo de repasse por inundação (*flooding*) em uma rede de sensores.
- **Destaques:**
  - Motor de simulação discreta orientado a eventos de recebimento e propagação de pacotes.
  - Controle de estado dos nós para evitar retransmissões infinitas (verificação de `pacote_enviado`).
  - Cálculo de atrasos de propagação com base nos IDs dos nós vizinhos.
- **Entregáveis:** [Código-fonte em C](src/Lab04_Simulacao_Flooding.c).

---

### Trabalho 05: Quebra de Senhas por Força Bruta (Cracker de Hashes POSIX)
- **Descrição:** Algoritmo de geração recursiva de combinações de caracteres e ataque de força bruta contra hashes criptográficos gerados pela função `crypt()` do POSIX.
- **Destaques:**
  - Geração recursiva de senhas para alfabetos numéricos e alfabéticos com limitação de comprimento.
  - Comparação iterativa de hashes SHA-512 (`$6$`) em tempo real até a captura da senha original.
- **Entregáveis:** [Código-fonte em C](src/Lab05_Forca_Bruta_Crypt.c).

---

### Trabalho 06: Parser de Arquivos Compactados ZIP
- **Descrição:** Leitor e analisador de estruturas de arquivos binários `.zip` via manipulação direta de ponteiros em C.
- **Destaques:**
  - Mapeamento direto de estruturas binárias através de `struct __attribute__((packed))`.
  - Validação de assinaturas mágicas (*Magic Numbers*: `0x04034b50`) dos cabeçalhos locais dos arquivos.
  - Extração de metadados como nome do arquivo, tamanho compactado e descompactado, e navegação via `fseek`.
- **Entregáveis:** [Código-fonte em C](src/Lab06_Parser_ZIP.c).

---

### Trabalho 07: Inspeção e Extrator de Chunks em Imagens PNG
- **Descrição:** Analisador binário para decodificação de imagens no formato PNG (Portable Network Graphics).
- **Destaques:**
  - Leitura e pulo da assinatura inicial de 8 bytes da imagem PNG.
  - Conversão de *Big-Endian* para a ordem de bytes da máquina (*Little-Endian*) usando `ntohl`.
  - Leitura do chunk principal `IHDR` para extração de dimensões (largura/altura) e iterador de navegação até o chunk de término `IEND`.
- **Entregáveis:** [Código-fonte em C](src/Lab07_Parser_PNG.c).

---

### Trabalho 08: Parser de Stream de Vídeo MPEG (MPEG-1/MPEG-2)
- **Descrição:** Analisador de arquivos de vídeo e áudio codificados em MPEG para identificação de *Start Codes* e estruturas do *stream*.
- **Destaques:**
  - Busca sequencial do prefixo de código `0x000001` no fluxo de bytes.
  - Identificação de quadros e estruturas: *Pack*, *System*, *Sequence Header*, *Group of Pictures* e *Pictures* (frames tipo I, P e B).
  - Cálculo de resolução da imagem (largura/altura) e taxa de quadros por segundo (*fps*) através de operações *bitwise* (deslocamento e máscaras).
- **Entregáveis:** [Código-fonte em C](src/Lab08_Parser_MPEG.c).

---

### Trabalho 09: Decodificador de Pacotes de Rede (Ethernet / IP / TCP / HTTP)
- **Descrição:** Analisador de captura binária de rede para decodificação das camadas da pilha de protocolos TCP/IP.
- **Destaques:**
  - Leitura encadeada das estruturas das camadas de Enlace (Ethernet), Rede (IPv4) e Transporte (TCP).
  - Extração de endereços MAC de origem/destino, IPs formatados e portas TCP.
  - Tratamento de tamanhos variáveis de cabeçalho (`hdr_len`) e isolamento da carga útil de dados (*payload* HTTP).
- **Entregáveis:** [Código-fonte em C](src/Lab09_Parser_Pcap_TCP.c).

---

### Trabalho 10: Renderização e Teste de Interseção de Segmentos com OpenGL/FreeGLUT
- **Descrição:** Aplicação gráfica interativa desenvolvida com OpenGL/GLUT para geração de segmentos de reta aleatórios não-intersectantes usando geometria computacional.
- **Destaques:**
  - Implementação do algoritmo de orientação de pontos 2D (**CCW** - *Counter-Clockwise*) para determinar a interseção entre segmentos.
  - Loop de geração determinística de retas sem colisão visual dentro da janela gráfica.
  - Configuração de projeção ortogonal 2D e renderização via OpenGL (`GL_LINES`).
- **Entregáveis:** [Código-fonte em C](src/Lab10_OpenGL_Segmentos.c).