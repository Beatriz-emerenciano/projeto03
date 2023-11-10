//
// Created by unifbemerenciano on 18/09/2023.
//
#include "biblioteca.h"

#include <stdio.h>
#include <string.h>

Tarefa tarefaLidas[100];





void menu(){
    printf("        \n");
    printf("Selecione uma opcao: \n");
    printf("1- Adicionar \n");
    printf("2- Listar \n");
    printf("3- Excluir \n");
    printf("0- Sair\n");
    printf("Digite:\n ");

}


/* essa função pega os dados do usuario e armazena em uma estrutura*/

void  escreverTarefa( Tarefa *tarefa) {


    printf("Digite a prioridade da tarefa(valor de 0 a 10):\n");
    scanf("%d", &tarefa->prioridade);

    printf("Descreva a  tarefa:\n");
    getchar();

    //lê a linha de texto fornecida pelo usuárop e armazena no campo da estrutura



    fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin);
    tarefa->descricao[strcspn(tarefa->descricao, "\n")] = '\0';

    printf("Digite a categoria:\n");
    fgets(tarefa->categoria, sizeof(tarefa->categoria), stdin);

    //remove o caractere da nova linha para a string ser salva corretamente

    tarefa->categoria[strcspn(tarefa->categoria, "\n")] = '\0';
}


/* nessa função é aceita a struct tarefa e o arquivobin
 * há uma verificação se do arquivo e em seguida escreve a estrutura
 * do arquivo*/





//função listar
void listarStruct(const Tarefa *tarefas, int numTarefas){

    int indice;
    int contador = 0;

    for( indice = 0; indice < numTarefas; indice++){
        if(tarefas[indice].prioridade >= 0){
            contador++;

            printf(" tarefas: %d \n", indice + 1);
            printf("Prioridade: %d\n",tarefas[indice].prioridade);
            printf("Descricao: %s\n",tarefas[indice].descricao);
            printf("Categoria: %s\n",tarefas[indice].categoria);
            printf("-------------------\n");
        }
    }
   if(contador == 0) {
       printf("Nenhuma tarefa disponivel!\n");
   }else {
       printf("Listagem realizada!");
   }

}


//funçao excluir
//função excluir
void excluir(Tarefa *tarefa, int *n, int c){
    if(c >= 1  &&  c <= *n) {
        for (int i = c -1; i < *n - 1; i++) {
            tarefa[i] = tarefa[i + 1];
        }

        (*n)--;
        printf("tarefa excluida com sucesso\n");
    }else{
        printf("indice inválido para a exclusao\n");


    }

}

/* função salvar e leitura em arquivo biário*/

void salvarArquivo(const Tarefa *tarefas,int numTarefas){
    FILE *arquivo = fopen("tarefas.bin","wb");

    if(arquivo != NULL) {
        fwrite(tarefas, sizeof(Tarefa), numTarefas, arquivo);
        fclose(arquivo);
        printf("Tarefa salvas com sucesso!\n");
    } else{
        printf("Erro ao abrir o arquivo para salvar as tarefas.\n!");
    }
}

int carregarArquivo(Tarefa *tarefas,int *numTarefas){
    FILE *arquivo = fopen("tarefas.bin","rb");

    if(arquivo != NULL){
        fseek(arquivo, 0, SEEK_END);
        long tamArquivo = ftell(arquivo);
        rewind(arquivo);

        *numTarefas = tamArquivo/sizeof(Tarefa);

        if(*numTarefas > 0){
            fread(tarefas,sizeof(Tarefa),*numTarefas,arquivo);
            fclose(arquivo);
            printf("Tarefas carregadas com sucesso!\n");
            return 1; // aqui indica que as tarefas foram carregadas
            } else{
            fclose(arquivo);
            printf("Arquivo de tarefas vazio\n");
            return 0; // aqui indica que o arquivo de tarefas está vázio

        }

    }else {
        printf("Erro ao abrir o arquivo para carregar as tarefas.\n");
        return -1; // aqui indica erro ao abrir o arquivo
    }
}






