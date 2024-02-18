#include <stdio.h>
#include "header.h"
/*
 PSEUDO CÓDIGO PARA O ALGORITMO

 1. Inicializar uma lista vazia para processos prontos
 2. Inicializar a estrutura de dados de cada processo
 3. Enquanto houver processos prontos:
    a. Verifica se novos processos chegaram e adiciona em uma das filas
    b. Se a fila não estiver vazia:
        I. Pop um processo da fila
        II. Se o processo não estiver executado completamente:
            - Reduz sua prioridade
            - Push para a fila
        III. Se o processo estiver completo:
            - Calcula o turnaround
    c. Incrementa a unidade de tempo
 4. Calcula o turnaround médio
 5. Output
*/

int main() {
    // testando
    Process* process[2];
    process[0] = instantiate_process(1, 0, 1, 0, 0, 0, 0, 0, 0, NULL, 0);
    process[1] = instantiate_process(2, 0, 1, 0, 0, 0, 0, 0, 0, NULL, 0);

    printf("a");
    //execute_scheduler((Process *) process, 2);
    return 0;
}
