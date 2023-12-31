//
// Created by unifbemerenciano on 18/09/2023.
//
#include "biblioteca.h"

#include <stdio.h>
#include <string.h>

Tarefa tarefaLidas[100];

void menu() {
  printf("        \n");
  printf("Selecione uma opcao: \n");
  printf("1- Adicionar \n");
  printf("2- Listar \n");
  printf("3- Excluir \n");
  printf("4- Editar tarefa\n");
  printf("5- filtrar por prioridade\n");
  printf("6- filtrar por estado\n");
  printf("7- filtrar por categoria\n");
  printf("8- filtrar por prioridade e categoria \n");
  
  printf("0- Sair\n");
  printf("Digite:\n ");
}

/* na função escrever tarefa é usado um fgets para ler strings e scanf para ler a prioridade, é removido caracteres de nova linha das strings para evitar problemas de formatação para que possa ser armazenado na estrutura */

void escreverTarefa(Tarefa *tarefa) {

  printf("Digite a prioridade da tarefa(valor de 0 a 10):\n");
  scanf("%d", &tarefa->prioridade);

  printf("Descreva a  tarefa:\n");
  getchar();

  // lê a linha de texto fornecida pelo usuário e armazena no campo da estrutura

  fgets(tarefa->descricao, sizeof(tarefa->descricao), stdin);
  tarefa->descricao[strcspn(tarefa->descricao, "\n")] = '\0';

  printf("Digite a categoria:\n");
  fgets(tarefa->categoria, sizeof(tarefa->categoria), stdin);

  // remove o caractere da nova linha para a string ser salva corretamente

  tarefa->categoria[strcspn(tarefa->categoria, "\n")] = '\0';

  printf("estado da tarefa:(completo, em andamento,nao iniciado)\n");
  fgets(tarefa->estado, sizeof(tarefa->estado), stdin);
  tarefa->estado[strcspn(tarefa->estado, "\n")] = '\0';
}







/*na função listar ha uma iteração no array de tarefas para que possa ser imprimido as tarefas cadastradas*/

// função listar
void listarStruct(const Tarefa *tarefas, int numTarefas) {

  int indice;
  int contador = 0;

  for (indice = 0; indice < numTarefas; indice++) {
    if (tarefas[indice].prioridade >= 0) {
      contador++;

      printf(" tarefas: %d \n", indice + 1);
      printf("Prioridade: %d\n", tarefas[indice].prioridade);
      printf("Descricao: %s\n", tarefas[indice].descricao);
      printf("Categoria: %s\n", tarefas[indice].categoria);
      printf("Estado: %s\n", tarefas[indice].estado);
      printf("-------------------\n");
    }

  }
  }



/*na função excluir é removido uma tarefa do array com base no indice  da tarefa fornecido pelo usuario usada pela variavel c, a variavel n serve para deslocar as tarefas a direita no indice para preencher o espaço deixado pela tarefa excluida e atualiza o numero total de tarefas*/
void excluir(Tarefa *tarefa, int *n, int c) {
  if (c >= 1 && c <= *n) {
    for (int i = c - 1; i < *n - 1; i++) {
      tarefa[i] = tarefa[i + 1];
    }
  
    (*n)--;
    printf("tarefa excluida com sucesso\n");
  } else {
    printf("indice inválido para a exclusao\n");
  }
}







/* função salvar abre o arquivo binario tarefas.bin para a escrita e usa o fwrite para escrever os dados da tarefa no arquivo e fecha após a escrita*/

void salvarArquivo(const Tarefa *tarefas, int numTarefas) {
  FILE *arquivo = fopen("tarefas.bin", "wb");

  if (arquivo != NULL) {
    fwrite(tarefas, sizeof(Tarefa), numTarefas, arquivo);
    fclose(arquivo);
    printf("Tarefa salvas com sucesso!\n");
  } else {
    printf("Erro ao abrir o arquivo para salvar as tarefas.\n!");
  }
}



/*a função carregar abre o arquivo binario para a leitura, calcula o tamanho do arquivo, determina o numero de tarefas e usa o fread, para ler dados do arquivo array de tarefas, retorna -1 se occoreu erro ao subir o arquivo*/
int carregarArquivo(Tarefa *tarefas, int *numTarefas) {
  FILE *arquivo = fopen("tarefas.bin", "rb");

  if (arquivo != NULL) {
    fseek(arquivo, 0, SEEK_END);
    long tamArquivo = ftell(arquivo);
    rewind(arquivo);

    *numTarefas = tamArquivo / sizeof(Tarefa);

    if (*numTarefas > 0) {
      fread(tarefas, sizeof(Tarefa), *numTarefas, arquivo);
      fclose(arquivo);
      printf("Tarefas carregadas com sucesso!\n");
      return 1; // aqui indica que as tarefas foram carregadas
    } else {
      fclose(arquivo);
      printf("Arquivo de tarefas vazio\n");
      return 0; // aqui indica que o arquivo de tarefas está vázio
    }

  } else {
    printf("Erro ao abrir o arquivo para carregar as tarefas.\n");
    return -1; // aqui indica erro ao abrir o arquivo
  }
}

  /* a função editar usa o fgets para ler a  string de estado e remove caracteres de nova linha para evitar problema de formatação*/

void editarTarefa(Tarefa *tarefa,int numTarefas, int indice){
  if (indice >= 0 && indice  < numTarefas){
    printf("Edite o novo estado da tarefa: completo, em andamento,nao iniciado: \n");
    getchar(); //limpa o buffer do teclado
    fgets(tarefa[indice].estado,sizeof(tarefa[indice].estado),stdin);
    tarefa[indice].estado[strcspn(tarefa[indice].estado,"\n")] = '\0';
    printf("Estado da tarefa alterado com sucesso!\n");
  } else {
    printf("Indice inválido\n");
    
  }
    
}


/*  a função prioridade como todas as outras recebe paramentros, há um loop para iterar sobre todas as tarefas do array, verifica se a prioridade da tarefa na posicao atual é igual a prioridade desejada, se a condição for verdadeira ele imprime as informaçoes, e incrementa a variavel achadas sempre que uma tarefa é encontrada*/

void prioridade(const Tarefa *tarefa,int numTarefa, int prioridade){
  int achadas = 0;
  printf("Tarefas com prioridade %d: \n",prioridade);

  for(int i = 0; i < numTarefa; i++){
    if(tarefa[i].prioridade == prioridade){
      printf("Prioridade: %d\n", tarefa[i].prioridade);
      printf("Descricao: %s\n", tarefa[i].descricao);
      printf("Categoria: %s\n", tarefa[i].categoria);
      printf("Estado: %s\n", tarefa[i].estado);
      printf("---------------------------\n");
      achadas++;
      
    }
  }

  if(achadas == 0){
    printf("Nenhuma tarefa encontrada com prioridade %d.\n",prioridade);
  }
}


/*função estado , há um loop para iterar sobre o array, verifica se o estado da tarefa na posicao atual é igual ao estado desejado usando a função strcmp para comparar strings, se a condição for verdadeira exibe as informaçoes ao usuario*/
void estado(const Tarefa * tarefa, int numTarefa,const char *estado){
  int  achadas = 0;
  printf("Tarefa com estado %s: \n",estado);

  for(int i = 0; i < numTarefa; i++){
   
    if(strcmp(tarefa[i].estado,estado) == 0){
      printf("Prioridade: %d\n", tarefa[i].prioridade);
      printf("Descricao: %s\n", tarefa[i].descricao);
      printf("Categoria: %s\n", tarefa[i].categoria);
      printf("Estado: %s\n", tarefa[i].estado);
      printf("---------------------------\n");
      achadas++;

      
    }
  }

  if (achadas == 0){
    printf("Nenhuma tarefa encontrada com o estado %s.\n",estado);
  }

  
}

/*há um for para iterar sobre todas as tarefas no array, verifica se a categoria da tarefa na posicao atual é igual a categoria desejada usando o strcmp para comparar strings, se a condição for verdadeira imprime as informacoes, também é incrementada a variavel encontrada sempre que uma tarefa é encontrada */

void categoria(const Tarefa *tarefa, int numTarefa,const char *categoria){
  Tarefa tarefaF[100]; 
  int encontrada = 0;

  // filtrando pela categoria desejada
  for(int i = 0; i < numTarefa; i++){
    if(strcmp(tarefa[i].categoria,categoria) == 0){
      tarefaF[encontrada++] = tarefa[i];
    }
  }
// ordenando as tarefas filtradas pela prioridade de forma de crescente
  for(int i = 0; i < encontrada - 1; i++){
    for(int j = 0; j < encontrada - i -1; j++){
      if(tarefaF[j].prioridade > tarefaF[j + 1].prioridade){
        //troca as tarefas de posicao
        Tarefa temp = tarefaF[j];
        tarefaF[j] = tarefaF[j + 1];
      tarefaF[j + 1] = temp;
        }
    }
  }

  // imprime as tarefas filtradas e ordenadas
  printf("Tarefas na categoria %s ordenadas por prioridades em ordem crescente:\n",categoria);
  for (int i = 0; i < encontrada; i++){
    printf("Prioridade: %d\n",tarefaF[i].prioridade);
    printf("Descricao: %s\n",tarefaF[i].descricao);
    printf("Categoria: %s\n",tarefaF[i].categoria);
    printf("Estado: %s\n",tarefaF[i].estado);
    printf("----------------------\n");
    
  }

  if(encontrada == 0){
    printf("Nenhuma tarefa encontrada na categoria %s\n",categoria);
  }

  
}


/* essa função tem como objetivo encontrar e imprimir as tarefas que correspondam a prioridade e categoria especificada, há um looping que itera sobre as tarefas e comprara a prioridade e categoria, se amobos valores corresponderem é imprimido os dados */

void categoriaEprioridade(const Tarefa *tarefa,int numTarefa, int prioridade, const char *categoria){
  int achadas = 0;
  printf("Tarefas com prioridades %d e categoria %s: \n", prioridade,categoria);
  for(int j = 0; j < numTarefa; j ++){
    if(tarefa[j].prioridade == prioridade && strcmp(tarefa[j].categoria,categoria) == 0){
      printf("Prioridade: %d\n",tarefa[j].prioridade);
      printf("Descricao: %s\n",tarefa[j].descricao);
      printf("Categoria: %s\n",tarefa[j].categoria);
      printf("Estado: %s\n",tarefa[j].estado);
      printf("-------------------------\n");
      achadas++;
      
    }
  }

  if(achadas == 0){
    printf("Nenhuma tarefa encontrada com prioridade %d e categoria %s \n",prioridade,categoria);
  }
  
}




