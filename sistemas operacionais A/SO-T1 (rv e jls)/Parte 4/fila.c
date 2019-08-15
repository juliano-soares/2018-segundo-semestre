/* fila.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "fila.h"

struct no {
    pthread_cond_t* info;
    struct no* prox;
};

struct fila {
    No* ini;
    No* fim;
    pthread_mutex_t mutex;
};


Fila* fila_cria() {
    Fila* f = (Fila*)malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    pthread_mutex_init(&f->mutex, NULL);
    return f;
}

void fila_libera(Fila* f) {
    No* q = f->ini;
    while (q != NULL) {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
}

int fila_tamanho(Fila* f) {
    No* no = f->ini;
    int cont = 0;
    while (no != NULL) {
        no = no->prox;
        cont++;
    }
    return cont;
}

int fila_vazia(Fila* f) {
    return (f->ini == NULL);
}

void fila_insere(Fila* f, pthread_cond_t* v) {
    No* n = (No*)malloc(sizeof(No));
    n->info = v;
    n->prox = NULL;

    pthread_mutex_lock(&f->mutex);
    if (f->fim == NULL)
        f->ini = n;
    else
        f->fim->prox = n;
    f->fim = n;
    //printf("-- FILA -- %p: inseriu %p (tamanho da fila: %d).\n\n", f, v, fila_tamanho(f));
    pthread_mutex_unlock(&f->mutex);
}

pthread_cond_t* fila_retira (Fila* f) {
    pthread_mutex_lock(&f->mutex);
    if (fila_vazia(f)) {
        //printf("\tNao ha dados para retirar da fila.\n\n");
        return NULL;
    }

    No* t = f->ini;
    pthread_cond_t* v = t->info;
    f->ini = t->prox;
    if (f->ini == NULL)
        f->fim = NULL;
    free(t);
    //printf("-- FILA -- %p: removeu %p (tamanho da fila: %d).\n\n", f, v, fila_tamanho(f));
    pthread_mutex_unlock(&f->mutex);
    return v;
}
