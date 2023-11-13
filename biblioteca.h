//
// Created by unifbemerenciano on 18/09/2023.
//

#ifndef PROJETO01_BIBLIOTECA_H
#define PROJETO01_BIBLIOTECA_H




// foi criada a struct o ativo � para dizer se a estruct esta ali ou n�o, foi acrecentada para a fun��o de excluir
typedef struct tarefa {

    int prioridade;
    char descricao[301];
    char categoria[101];
    char estado[20];
}Tarefa;


void menu();
void  escreverTarefa( Tarefa *tarefa);
void listarStruct( const Tarefa *tarefas, int numTarefas);
void excluir(Tarefa *tarefa,int *n,  int c);
void salvarArquivo(const Tarefa *tarefas,int numTarefas);
int carregarArquivo(Tarefa *tarefas,int *numTarefas);
void editarTarefa(Tarefa *tarefa,int numTarefas, int indice);
void prioridade(const Tarefa *tarefa,int numTarefa, int prioridade);
void estado(const Tarefa * tarefa, int numTarefa,const char *estado);
void categoria(const Tarefa *tarefa, int numTarefa,const char *categoria);

extern Tarefa tarefaLidas[100];
extern int numLidas;





#endif //PROJETO01_BIBLIOTECA_H