#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

/* FUNÇÕES PARA LIDAR COM PROCESSOS */
Process* cria_processo() //Função que retorna um ponteiro pra processo
{
    Process *newer;
    if((newer = (Process *) malloc(sizeof(Process)))==NULL)
    {
        puts("Sem espaco livre");
        exit(1);
    }
    return newer;
}

ProcessIO* cria_processoIO() //Função que retorna um ponteiro pra processoIO
{
    ProcessIO *newer;
    if((newer = (ProcessIO *) malloc(sizeof(ProcessIO)))==NULL)
    {
        puts("Sem espaco livre");
        exit(1);
    }
    return newer;
}

// TODO: adicionar função (builder) que instancia o struct do processo
/**
 *
 * @param pid
 * @param ppid
 * @param priority
 * @param status
 * @param duration
 * @param total_exec
 * @param activation_time
 * @param end_time
 * @param num_ios
 * @param processIOs
 * @param io_return
 * @return instância de um struct Process com os parâmetros passados
 */
Process* instantiate_process(int pid, int ppid, int priority, int status, int duration, int total_exec, int activation_time, int end_time, int num_ios, ProcessIO *processIOs, int io_return) {
    Process* process = cria_processo();

    process->pid = pid;
    process->ppid = ppid;
    process->priority = priority;
    process->status = status;
    process->duration = duration;
    process->total_exec = total_exec;
    process->activation_time = activation_time;
    process->end_time = end_time;
    process->num_ios = num_ios;
/*
    for(int i=0; i<10; i++)
        process->processIOs[i] = &processIOs[i];
*/
    process->io_return = io_return;

    return process;
}

// TODO: adicionar função (builder) que instancia o struct do IO
/**
 *
 * @param type
 * @param activation_time
 * @param duration
 * @param priority
 * @return instância de um struct ProcessIO com os valores passados
 */
ProcessIO* instatiante_processIO(int type, int activation_time, int duration, int priority) {
    ProcessIO* processIO = cria_processoIO();

    processIO->type = type;
    processIO->activation_time = activation_time;
    processIO->duration = duration;
    processIO->priority = priority;

    return processIO;
}


/* FUNÇÕES PARA LIDAR COM FILAS */
/**
 *
 * @param head primeiro elemento da lista de processos
 * @return primeiro processo da fila
 */
Process* pop(fila** head) {
    fila* temp = *head;
    Process* process = temp->processo;
    *head = (fila *)temp->prox;

    return process;
}

/**
 * Insere um elemento no final da fila
 * @param head primeiro elemento da fila
 * @param process processo que será adicionado à fila
 */
void push(fila* head, Process* process) {
    fila* node = head;
    while(node->prox != NULL) {
        node = (fila *) node->prox;
    }

    fila* new_node = (fila*)malloc(sizeof(fila));
    new_node->processo = process;
    node->prox = (struct fila *) new_node;
}

/**
 * Cria uma fila usando lista encadeada
 * @param processes array de processos já criados
 * @param n_processes tamanho do array de processos
 * @return ponteiro para o primeiro elemento da fila
 */
fila* create_queue(Process processes[], int n_processes) {
    fila* head = (fila*)malloc(sizeof(fila));
    fila* node = (fila*)malloc(sizeof(fila));

    head->processo = &processes[0];
    head->prox = (struct fila *) node;

    for(int i=1; i<n_processes; i++) {
        node->processo = &processes[i];
        node->prox = (struct fila *) (fila *) malloc(sizeof(fila));
        node = (fila *) node->prox;
    }

    return head;
}

// verifica se a fila está vazia
int is_empty(fila* head) {
    if(head == NULL) return 1;
    return 0;
}


/* FUNÇÕES PARA LIDAR COM ESCALONAMENTO */
// TODO: adicionar função que lida com preempção
/**
 *
 * @param head primeiro elemento da lista de processos
 * #@param process processo que está sendo atualmente executado
 * @return id do processo que está agora executando
 */
Process* execute_preemption(fila* head, Process* current_process) {
    // pega o próximo processo pronto da fila
    Process* next_to_exec = pop((fila **) head);
    printf("EXECUTANDO P%d", next_to_exec->pid);
    // se há um processo atualmente executando, coloca ele na fila novamente
    // aqui deve reduzir a prioridade
    if(current_process != NULL)
        push(head, current_process);
    return next_to_exec;
}

// TODO: adicionar função que lida com retorno de IO

// auxilia no registro do tempo em segundos
time_t seconds_passed(time_t start, time_t current) {
    return current - start;
}

// TODO: adicionar orquestrator do escalonamento (filas podem ser definidas aqui)
void execute_scheduler(Process processes[], int n_processes) {
    // cria uma fila com os processos
    // o ideal é ordená-los por tempo de chegada e prioridade e depois criar a fila
    fila* queue = create_queue(processes, n_processes);
    // criando variáveis de tempo para o quantum
    time_t start_time, current_time = 0;
    // variável para armazenar o processo que está sendo atualmente executado
    Process* current_process = NULL;
    // inicia a contagem do tempo
    start_time = time(NULL);
    // enquanto a fila de processos não estiver vazia, executa o escalonador
    while(!is_empty(queue)) {
        current_time = time(NULL);
        // se o tempo que o processo está rodando é igual ao quantum, ele sofre uma preempção
        if(seconds_passed(start_time, current_time) % QUANTUM == 0) {
            // um novo processo é posto em execução em detrimento do atual
            current_process = execute_preemption(queue, current_process);
        }
    }
}
