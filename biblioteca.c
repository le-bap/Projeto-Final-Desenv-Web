#include <stdio.h>
#include <string.h>
#include "biblioteca.h"

///////////// funções principais /////////////
void printMenu(){ // usada para printar o menu toda vez que acontece alguma ação no programa
    printf("\nGerenciador de Tarefas\n");
    printf("Escolha a funcao:\n 1. Adicionar nova tarefa\n 2. Deletar tarefa\n 3. Listar tarefas\n 4. Editar tarefa\n 5. Filtrar tarefas por prioridade\n 6. Filtrar tarefas por estado\n 7. Filtrar tarefas por categoria\n 8. Filtrar tarefas por prioridade e categoria\n 9. Exportar tarefas por prioridade\n10. Exportar tarefas por categoria\n11. Exportar tarefas por prioridade e categoria\n 0. Sair\n");
}


int criarTarefa(ListaDeTarefas *lt) {

    if (lt->qtd < 100) { // se a lista tiver menos que 100 tarefas, é possivel configurar uma
        printf("Digite a descricao: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].descricao);
        clearBuffer();

        printf("Digite a prioridade (0 a 10): ");
        scanf(" %d", &lt->tarefas[lt->qtd].prioridade);
        clearBuffer();

        printf("Digite a categoria: ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].categoria);
        clearBuffer();

        printf("Digite o status da tarefa (completo / em andamento / nao iniciado): ");
        scanf(" %[^\n]", lt->tarefas[lt->qtd].status);
        clearBuffer();

        printf("Tarefa adicionada com sucesso!\n");
    }
    else{
        printf("Sua lista de tarefas esta cheia!");
    }
    lt->qtd++;// estrutura que pula pra proxima linha do arquivo para que o usuario nao salve as novas tarefas em cima das outras
    return 0;
}

int DeletarTarefa(ListaDeTarefas *lt){
    int tarefaEscolhida;
    printf("Qual tarefa voce deseja deletar? (0 a 99) "); // informa a tarefa a ser deletada
    scanf("%d", &tarefaEscolhida);
    clearBuffer();

    for (int i = tarefaEscolhida; i < 100; i++){
        lt->tarefas[i] = lt->tarefas[i + 1];
    }

    lt->qtd--;// ao deletar uma tarefa, as posições das restante devem "descer" para uma posição abaixo da que estava
    return 0;
}


int ListarTarefa(ListaDeTarefas lt){
    for (int i = 0; i < lt.qtd; i++){ //apenas aparece as tarefas já estabelecidas
        printf("Tarefa %d\n", i);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
        printf("Status: %s\n", lt.tarefas[i].status);
        printf("\n");
    }
    return 0;
}

int EditarTarefa(ListaDeTarefas *lt){

    int tarefaEscolhida;
    printf("\nDigite o numero da tarefa que deseja editar (0 a 99): ");
    scanf("%d", &tarefaEscolhida);
    clearBuffer();

    if (tarefaEscolhida > lt->qtd){
        printf("\nDigite um numero valido.");
    }
    else{
        int campoAlteracao;
        printf("\nDigite o campo que deseja alterar:\n1. Categoria\n2. Descricao\n3. Prioridade\n4. Status\n>>> ");
        scanf("%d", &campoAlteracao);
        clearBuffer();

        if (campoAlteracao == 1){
            printf("Digite a nova categoria: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].categoria);
            clearBuffer();
        }
        else if (campoAlteracao == 2){
            printf("Digite a nova descricao: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].descricao);
            clearBuffer();
        }
        else if (campoAlteracao == 3){
            printf("Digite o novo numero de prioridade: ");
            scanf("%d",  &lt->tarefas[tarefaEscolhida].prioridade);
            clearBuffer();
        }
        else if (campoAlteracao == 4){
            printf("Digite o novo status: ");
            scanf("%[^\n]",  lt->tarefas[tarefaEscolhida].status);
            clearBuffer();
        }
    }
}


///////////// funções base /////////////
void clearBuffer(){ //evita erros com a função scanf
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


///////////// funções relacionadas ao arquivo /////////////
int salvarLista(ListaDeTarefas *lt, char nome[]){ // "escreve" em uma arquivo a lista de tarefas em binário para salvá-la
    FILE *f = fopen(nome, "wb");
    if(f == NULL){
        return 1;
    }else {
        fwrite(lt, sizeof(ListaDeTarefas), 1, f);
        fclose(f);
    }
    return 0;
}
int carregarLista(ListaDeTarefas *lt, char nome[]){ // "lê" as informações em binário para que sejam usadas no programa toda vez que for iniciado
    FILE *f = fopen(nome, "rb");
    if (f == NULL){
        return 1;
    }
    else{
        fread(lt, sizeof(ListaDeTarefas),1, f);
        fclose(f);
    }
    return 0;
}
