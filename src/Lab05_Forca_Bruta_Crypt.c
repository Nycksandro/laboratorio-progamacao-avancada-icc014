//Aluno: Nycksandro Lima dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h> //Descomentar pra segunda questão


//Questão 01
/*
int tamanhoMaximo = 2; // Variavel pra guardar o tamanho maximo
char caracteres[] = "abcdefghijklmnopqrstuvwyxz"; // Caracteres que serão utilizados na senha

void gerarTodasSenhas(char *senha, int pos, int tam){ // Função que recebe o vetor pra guardar as senhas, a posição e o tamanho desejado da senha
    if(pos < tam){
        for(int i = 0; i < strlen(caracteres); i++){
            senha[pos] = caracteres[i];
            gerarTodasSenhas(senha, pos+1, tam); // Chamada recursiva
        }
    }
    senha[pos] = 0; //Finalizando a string
    printf("%s\n", senha); // Printando a senha
}

void main() {
   char senha[tamanhoMaximo]; // Criando um vetor vazio de char pra guardar a senha
   gerarTodasSenhas(senha, 0, tamanhoMaximo); // Aplicando a função
}

*/

//Questão 02

/*

//01 : Resposta = 0451
int tamanhoMaximo = 4; // Variavel pra guardar o tamanho maximo
char caracteres[] = "0123456789"; // Caracteres que serão utilizados na senha
char *senhaCriptografada = "$6$LrSF5BAseToYYHJ0$SYY1avj8FRoRGpn.1kPXuZ6Xn5WTl2kL3"
"hxc3yMWdDUyz4c/Ac3Av3WO8Q9LciP8o4c9WaeLcgxIXWaHpJMFb.";

*/

/*
//02: Resposta = cpp
int tamanhoMaximo = 3; // Variavel pra guardar o tamanho maximo
char caracteres[] = "abcdefghijklmnopqrstuvwxyz"; // Caracteres que serão utilizados na senha
char *senhaCriptografada = "$6$rMAk28dVkWjpYoA3$SkWbPYqEB8O/10ryvvjm1qN9BOrkeBOXp"
"JScVSGDL5L88OIs0UCBuP.pnd9TQ6SBx60dLKwR9WAzfnLtvjGvj.";

*/
//03: Resposta = 31337
int tamanhoMaximo = 5; // Variavel pra guardar o tamanho maximo
char caracteres[] = "0123456789"; // Caracteres que serão utilizados na senha
char *senhaCriptografada = "$6$l2xE4w9twgjtnZBz$9YK9krslZFraLffy5VNiahAfT.xZNvB54"
"j91DMCMIoVFvj335ZKxb11qgVMn.KzU2GqVPPyS2FTBqPSciYq761";



int verificaSenha(char* senhaTeste, char* senhaCriptografada) {
    char *senhaTesteCriptografada = crypt(senhaTeste, senhaCriptografada);
    return strcmp(senhaTesteCriptografada, senhaCriptografada);
}

void gerarTodasSenhasV2(char *senha, int pos, int tam){ // Função que recebe o vetor pra guardar as senhas, a posição e o tamanho desejado da senha, só que verifica se a senha é igual a criptografada
    if(pos < tam){
        for(int i = 0; i < strlen(caracteres); i++){
            senha[pos] = caracteres[i];
            if(verificaSenha(senha, senhaCriptografada) == 0){ // Verifica se a senha atual é igual a senha criptografada (em hash), se for eu printo que achei a senha
                printf("%s --> sim! Senha encontrada\n", senha); // Printando a senha
                exit(1); // gambiarra pra parar a execução do programa assim que achar a senha
            }
            else{
                printf("%s --> nao\n", senha); // Printando quando não é a senha correta
            }
            gerarTodasSenhasV2(senha, pos+1, tam); // Chamada recursiva
        }
        senha[pos] = 0; //Finalizando a string
    }
}

int main(){
    char senha[tamanhoMaximo];
    gerarTodasSenhasV2(senha, 0, tamanhoMaximo);
}