/* fila.h
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#pragma once

typedef struct fila Fila;
typedef struct no No;

Fila* fila_cria();

void fila_libera(Fila* f);

int fila_tamanho(Fila* f);

int fila_vazia(Fila* f);

void fila_insere(Fila* f, pthread_cond_t* v);

pthread_cond_t* fila_retira (Fila* f);
