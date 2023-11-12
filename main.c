#include <stdio.h>
#include "biblioteca.h"

Tarefa tarefasLidas[100];
int numLidas = 0;
int i = 0;


int main() {



    Tarefa pessoaTarefa[100];
    int opcao;
    int n = numLidas; //essa variavél é para manter o controle de numeros de tarefas sa struct




    do {
        menu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if(numLidas <100){
                    escreverTarefa(&pessoaTarefa[numLidas]);
                    numLidas++;
                    salvarArquivo(pessoaTarefa,numLidas);
                }else {
                    printf("cheio");
                }
                // salvar e ler  os dados da struct ante de encerrar o programa


                break;

            case 2:
                //chamar a funcao para carregar as tarefas antes de listar
                if(carregarArquivo(pessoaTarefa,&numLidas))

                // lista as tarefas apenas se foram carregadas com sucesso
                listarStruct(pessoaTarefa,numLidas); // salva as tarefas após adicionar uma nova
                break;

            case 3:
                //chamar a funcao excluir
                printf("Digite o numero da tarefa que deseja excluir: \n");
                int cDeletar;
                scanf("%d",&cDeletar);
                excluir(pessoaTarefa,&numLidas,cDeletar);
                salvarArquivo(pessoaTarefa,numLidas);
                break;

            case 0:

                printf("Programa encerrado!\n");

                break;
          case 4:
            printf("Digite o numero da que deseja editar: \n");
            int editar;
            scanf("%d",&editar);
            editarTarefa(pessoaTarefa,numLidas,editar - 1);
            salvarArquivo(pessoaTarefa, numLidas);
           break;
          
            default:
                printf("erro! \n");
        }

    } while (opcao != 0);

    return 0;

}