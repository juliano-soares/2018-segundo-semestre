/* buffer.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 1
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include "buffer.h"
#include "fila.h"

// tamanho do header eh 4, os bytes do inteiro
// que corresponde ao tamanho do dado
#define HEADER_SIZE sizeof(int)

struct buffer {
    unsigned char* buffer; // o buffer/vetor de bytes para armazenar os dados
    int tam;               // tamanho em bytes do buffer
    int prox;              // proximo indice vazio/a ser escrito do buffer
    int usado;             // total de bytes escritos no buffer
    Fila* fila_leitoras;   // fila para threads bloqueadas na remocao
    Fila* fila_escritoras; // fila para threads bloqueadas na insercao
    pthread_mutex_t mutex; // mutex para controlar o acesso a regioes criticas do buffer
};

Buffer* buffer_inicializa(int cap) {
    if (cap < 0)
        return NULL;
    Buffer *buf = (Buffer*)malloc(sizeof(Buffer));
    buf->buffer = (char*)malloc(cap);
    buf->tam = cap;
    buf->prox = 0;
    buf->usado = 0;
    buf->fila_leitoras = fila_cria();
    buf->fila_escritoras = fila_cria();
    pthread_mutex_init(&buf->mutex, NULL);
    printf("Buffer %p criado.\n\n", buf);

    return buf;
}

void buffer_finaliza(Buffer* buf) {
	printf("Buffer %p finalizado.\n\n", buf);
    free(buf->buffer);
    free(buf);
}

// Obtem o indice do inicio das escritas do buffer
static int buffer_inicio(Buffer* buf) {
    int ini = buf->prox - buf->usado;
    return (ini < 0 ? (ini + buf->tam) : ini);
}

// Obtem a qtd de bytes livres no buffer
static int buffer_livre(Buffer* buf) {
    return buf->tam - buf->usado;
}

// Imprime os dados de um buffer
// funcao auxiliar para visualizar o conteudo do buffer
static void buffer_imprime(Buffer* buf) {
    printf("Imprimindo buffer %p (pos. usadas = %d .. %d) (%d bytes usados): \n", buf, buffer_inicio(buf), buf->prox, buf->usado);

    int i, dado = (buffer_inicio(buf) >= buf->prox ? 1 : 0);
    for (i = 0; i < buf->tam; i++) {
    	// se o indice atual eh igual a posicao do inicio das escritas no buffer, entao ativa o "dado"
    	// para entrar no if de baixo e printar o conteudo do buffer
        if (buffer_inicio(buf) == i) dado = 1;
        // se o indice atual eh igual a posicao do final das escritas no buffer, entao desativa o "dado"
        // para parar de entrar no if e printar apenas -, ja que sao posicoes vazias
        else if (buf->prox == i) dado = 0;

        if (dado && buf->usado != 0)
            if (buf->buffer[i] >= 'a' && buf->buffer[i] <= 'z')
                printf("%c ", buf->buffer[i]);
            else
                printf("%d ", buf->buffer[i]);
        else
            printf("- ");
    }
    printf("\n\n");
}

bool buffer_insere(Buffer* buf, void *p, int tam) {
    if (tam < 0 || tam > buf->tam)
        return false;

    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);

    pthread_mutex_lock(&buf->mutex);

    // bloqueia a thread caso o tamanho necessario para a escrita do dado
    // (tamanho do dado + tamanho do header) seja maior que o tamanho disponivel
    while (buffer_livre(buf) < (HEADER_SIZE + tam)) {
        fila_insere(buf->fila_escritoras, &cond);
        pthread_cond_wait(&cond, &buf->mutex);
    }

    int i;
    char* dado = (char*)p;

    // bitwise pra criar o header com os bits de um int que indica o tamanho
    // de bytes do dado (4 posicoes, cada byte do int alocado em uma delas)
    for (i = 0; i < HEADER_SIZE; i++) {
        // caso o indice do proximo byte a ser escrito chegue no
        // final, retorna para o inicio, andando circularmente
        if (buf->prox == buf->tam)
            buf->prox = 0;
        buf->buffer[buf->prox++] = (tam << (8*i) >> 24);
    }

    // transfere cada byte do dado para o buffer
    for (i = 0; i < tam; i++) {
        if (buf->prox == buf->tam)
            buf->prox = 0;
        buf->buffer[buf->prox++] = dado[i];
    }

    // incrementa o tamanho do dado somado ao tamanho do header
    // na variavel que indica a quantia de bytes ocupadas do buffer
    buf->usado += (HEADER_SIZE + tam);

    printf(" + Dado INSERIDO:\n");
    printf("\tThread: %p\n", &cond);
    printf("\tDado: %s\n", (char*)p);
    printf("\tTamanho: %ld + %d = %ld\n", HEADER_SIZE, tam, HEADER_SIZE+tam);
    printf("\tUsado do buffer: %d\n\n", buf->usado);

    buffer_imprime(buf);
    
    // retira da fila a thread para ler o dado, caso haja alguma esperando
    if (!fila_vazia(buf->fila_leitoras))
        pthread_cond_signal(fila_retira(buf->fila_leitoras));

    pthread_mutex_unlock(&buf->mutex);

    return true;
}

bool buffer_remove(Buffer* buf, void *p, int cap, int *tam) {
    pthread_cond_t cond;
    pthread_cond_init(&cond, NULL);

    pthread_mutex_lock(&buf->mutex);

    // bloqueia a thread caso nao haja dados no buffer
    while (buf->usado == 0) {
        fila_insere(buf->fila_leitoras, &cond);
        pthread_cond_wait(&cond, &buf->mutex);
    }

    char* dado = (char*)p;
    int inicio_dado = buffer_inicio(buf);
    int i, tam_dado = 0x00;

    // bitwise pra pegar o header que indica o tamanho em bytes do dado
    for (i = 1; i <= HEADER_SIZE; i++) {
        if (inicio_dado == buf->tam)
            inicio_dado = 0;
        tam_dado |= buf->buffer[inicio_dado++] << 8*(HEADER_SIZE-i);
    }

    // transfere cada byte do buffer para o espaco de destino enquanto
    // nao terminar o dado e nao ter atingido a capacidade do espaco
    for (i = 0; (i < tam_dado) && (i < cap); i++) {
        if (inicio_dado == buf->tam)
            inicio_dado = 0;
        dado[i] = buf->buffer[inicio_dado++];
    }

    buf->usado -= (HEADER_SIZE + tam_dado);
    *tam = i;

    printf(" - Dado REMOVIDO:\n");
    printf("\tThread: %p\n", &cond);
    printf("\tCapacidade: %d\n", cap);
    printf("\tDado: %s\n", (char*)p);
    printf("\tTamanho: %d\n", *tam);
    printf("\tUsado do buffer: %d\n\n", buf->usado);

    buffer_imprime(buf);

    if (!fila_vazia(buf->fila_escritoras))
        pthread_cond_signal(fila_retira(buf->fila_escritoras));

    pthread_mutex_unlock(&buf->mutex);

    return true;
}
