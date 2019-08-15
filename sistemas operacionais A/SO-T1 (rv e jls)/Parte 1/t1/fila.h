/* fila.h
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 1
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

typedef struct fila Fila;
typedef struct no No;

Fila* fila_cria();

void fila_libera(Fila* f);

int fila_tamanho(Fila* f);

int fila_vazia(Fila* f);

void fila_insere(Fila* f, pthread_cond_t* v);

pthread_cond_t* fila_retira (Fila* f);
