/* buffer.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "buffer.h"
#include "pacote.h"
#include "fila.h"

struct buffer {
    Pacote* buffer;        // o buffer de pacotes
    int tam;               // tamanho em pacotes do buffer
    int prox;              // proximo indice vazio/a ser escrito do buffer
    int usado;             // total de pacotes escritos no buffer
    Fila* fila_leitoras;   // fila para threads bloqueadas na remocao
    Fila* fila_escritoras; // fila para threads bloqueadas na insercao
    pthread_mutex_t mutex; // mutex para controlar o acesso as regioes criticas do buffer
};

Buffer* buffer_inicializa(int cap) {
    if (cap < 0)
        return NULL;

    Buffer *buf = (Buffer*)malloc(sizeof(Buffer));
    buf->buffer = pacote_cria(cap);
    buf->tam = cap;
    buf->prox = 0;
    buf->usado = 0;
    buf->fila_leitoras = fila_cria();
    buf->fila_escritoras = fila_cria();
    pthread_mutex_init(&buf->mutex, NULL);

    return buf;
}

void buffer_finaliza(Buffer* buf) {
    pacote_libera(buf->buffer);
    free(buf);
}

int buffer_usado(Buffer* buf) {
    pthread_mutex_lock(&buf->mutex);
    int n = buf->usado;
    pthread_mutex_unlock(&buf->mutex);
    return n;
}

// retorna o indice do inicio dos dados do buffer
static int buffer_inicio(Buffer* buf) {
    int ini = buf->prox - buf->usado;
    return (ini < 0 ? (ini + buf->tam) : ini);
}

// imprime os dados do buffer
static void imprime_buffer(Buffer* buf) {
    int i;
    printf("Imprimindo buffer %p...\n", buf);
    for (i = buffer_inicio(buf); i != buf->prox; i++) {
        if (i >= buf->tam)
            i = 0;
        printf("Buffer [%d]: %d | %s | %p | %s | %s\n", i, buf->buffer[i].setor, buf->buffer[i].operacao?"ESCRITA":"LEITURA", buf->buffer[i].buffer_resposta, (buf->buffer[i].operacao==0)?"null":buf->buffer[i].dado, buf->buffer[i].ok?"OK":"NOK");
    }
    printf("\n");
}

bool buffer_insere(Buffer* buf, void* p) {
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);

    pthread_mutex_lock(&buf->mutex);

    // se nao ha espaco, tranca a thread e poe na fila
    while (buf->usado >= buf->tam) {
        fila_insere(buf->fila_escritoras, &cond);
        pthread_cond_wait(&cond, &buf->mutex);
    }

    buf->buffer[buf->prox++] = *((Pacote*)p);
    buf->usado++;

    printf("\t++ Inseriu no buffer %p o pacote com setor %d, novo tamanho %d\n", buf, buf->buffer[buf->prox-1].setor, buf->usado);
    //imprime_buffer(buf);

    if (buf->prox == buf->tam)
        buf->prox = 0;

    // se havia thread esperando por um dado, libera ela
    if (!fila_vazia(buf->fila_leitoras))
        pthread_cond_signal(fila_retira(buf->fila_leitoras));

    pthread_mutex_unlock(&buf->mutex);

    return true;
}

bool buffer_remove(Buffer* buf, void* p) {
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);

    pthread_mutex_lock(&buf->mutex);

    // se nao ha dados para remover do buffer, tranca a thread
    while (buf->usado == 0) {
        fila_insere(buf->fila_leitoras, &cond);
        pthread_cond_wait(&cond, &buf->mutex);
    }

    *((Pacote*)p) = buf->buffer[buffer_inicio(buf)];
    buf->usado--;

    printf("\t-- Removeu do buffer %p o pacote com setor %d, novo tamanho %d\n", buf, (*((Pacote*)p)).setor, buf->usado);
    //imprime_buffer(buf);

    // se havia threads esperando liberar espaco para um novo dado, libera
    if (!fila_vazia(buf->fila_escritoras))
        pthread_cond_signal(fila_retira(buf->fila_escritoras));

    pthread_mutex_unlock(&buf->mutex);

    return true;
}
