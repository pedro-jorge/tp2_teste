#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* útil para trabalhar com o tipo bool no formato de string */
typedef int bool;
#define true 1
#define false 0

/* definição do QUANTUM (devem alterar o valor aqui:) */
#define QUANTUM 10

/* definição dos tempos de duração de cada IO (devem alterar os valores aqui:)*/
#define DISCO_IO_DURATION 4
#define FITA_IO_DURATION 6
#define IMPRESSORA_IO_DURATION 10

typedef struct ProcessIO {
    int type;               // Tipo do IO. Ex: 0 = Disco; 1 = Fita; 2 = Impressora
    int activation_time;     // instante no tempo de execução do processo em que o IO será chamado (cuidado: é em relação ao processo e não ao tempo total!)
    int duration;            // duração deste tipo de IO
    int priority;            // com qual prioridade o processo irá retornar quando terminar este IO.
} ProcessIO;

typedef struct {
    /* atributos obrigatórios (PCB): */
    int pid;                     // PID do processo. Ex: P1
    int ppid;                    // PID do processo pai
    int priority;                    // Prioridade. Ex: 0 (baixa) e 1 (alta)
    int status;                      // Status do processo no instante t. Ex: 0 = Pronto, 1 = Bloqueado, 2 = Finalizado; deve iniciar como pronto = 0
    /* atributos opcionais (para ajudar na impl.): */
    int duration;                    // tempo de duração do processo
    int total_exec;                  // tempo total de execução até o momento (para manter controle de quando acabou)
    int activation_time;             // instante de ativação do processo
    int end_time;                    // instante de finalização do processo (útil para o cálculo do Turnaround)
    int num_ios;                     // número total de IOs que o processo chama
    struct ProcessIO *processIOs[10]; // lista com os IOs que o processo chama
    int io_return;                   // instante que processo retornará do IO que está sendo executado no momento
} Process;

typedef struct FILA
{
    Process* processo;
    struct fila *prox;
} fila;


Process* cria_processo();
ProcessIO* cria_processoIO();
Process* instantiate_process(int pid, int ppid, int priority, int status, int duration, int total_exec, int activation_time, int end_time, int num_ios,ProcessIO *processIOs, int io_return);
ProcessIO* instatiante_processIO(int type, int activation_time, int duration, int priority);
Process* pop(fila** head);
void push(fila* head, Process* process);
fila* create_queue(Process processes[], int n_processes);
int is_empty(fila* head);
Process* execute_preemption(fila* head, Process* current_process);
time_t seconds_passed(time_t start, time_t current) ;
void execute_scheduler(Process processes[], int n_processes);


#endif
