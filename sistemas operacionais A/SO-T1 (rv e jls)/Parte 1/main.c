/* main.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 1
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

// gcc -o p1 main.c buffer.c fila.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#include "buffer.h"

#define N_THREADS_ESCRITORAS 4
#define N_THREADS_LEITORAS   1
#define BUFFER_SIZE 512

// total de dados que serao adicionados/removidos pelas threads
// deve ser um numero multiplo e maior que o numero de threads escritoras ou leitoras
// caso nao seja multiplo, ele vai considerar o multiplo menor mais proximo
#define TOTAL_DADOS 8192

void* escrita(void* buf) {
    int i, j, size;
    char* str;

    // porcentagem min e max do tamanho do dado em relacao ao tamanho do buffer
    float min = 0.0, max = 0.5;

    for (i = 0; i < (TOTAL_DADOS / N_THREADS_ESCRITORAS); i++) {
    	size = BUFFER_SIZE*min + (rand()%(int)(BUFFER_SIZE*max-BUFFER_SIZE*min));
        str = (char*)malloc(size*sizeof(char)+1);
        
        // preenche com qualquer coisa, apenas para o dado ficar reconhecivel se imprimir o buffer
        for (j = 0; j < size-1; j++)
            str[j] = j%26 + 'a';
        str[j] = '\0';

        buffer_insere(buf, str, size);
        free(str);
    }
}

void* leitura(void* buf) {
    int i, tam, cap = BUFFER_SIZE;
    char* p;

    for (i = 0; i < (TOTAL_DADOS / N_THREADS_LEITORAS); i++) {
        p = (char*)malloc(cap);
        buffer_remove(buf, p, cap, &tam);
        free(p);
    }
}

int main(int argc, char const *argv[]) {
    int i;
    pthread_t t_escritoras[N_THREADS_ESCRITORAS];
    pthread_t t_leitoras[N_THREADS_LEITORAS];
    srand(time(NULL));

    Buffer* buf = buffer_inicializa(BUFFER_SIZE);

    for(i = 0; i < N_THREADS_ESCRITORAS; i++)
        if (pthread_create(&(t_escritoras[i]), NULL, escrita, (void*)buf) != 0) i--;
    for(i = 0; i < N_THREADS_LEITORAS; i++)
        if (pthread_create(&(t_leitoras[i]), NULL, leitura, (void*)buf) != 0) i--;

    for(i = 0; i < N_THREADS_ESCRITORAS; i++)
        pthread_join(t_escritoras[i], NULL);
    for(i = 0; i < N_THREADS_LEITORAS; i++)
        pthread_join(t_leitoras[i], NULL);

    buffer_finaliza(buf);

    return 0;
}
