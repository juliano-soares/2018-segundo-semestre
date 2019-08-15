/* desempenho.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 3
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

// gcc -o p3 desempenho.c disquete.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "disquete.h"

void mede_leitura_sequencial(int fator, int blocos) {
    int i, prox_setor = rand() % TOTAL_SETORES;
    char* buffer = (char*)malloc(BYTES_SETOR);

    clock_t t_inicio = clock();

    for (i = 0; i < blocos; i++) {
        acessa_disquete_entrelacamento(fator, prox_setor, LEITURA, buffer);
        prox_setor++;
        if (prox_setor >= TOTAL_SETORES)
            prox_setor = 0;
    }

    free(buffer);
    float tempo_total = (clock() - t_inicio)*1000/CLOCKS_PER_SEC;
    printf("   LEITURA SEQUENCIAL de %d blocos e fator %d:\n", blocos, fator);
    printf("   Tempo total: %.0fms\n   Tempo medio por bloco: %.0fms\n\n", tempo_total, tempo_total/blocos);
}

void mede_leitura_aleatoria(int fator, int blocos) {
    int i, prox_setor;
    char* buffer = (char*)malloc(BYTES_SETOR);

    clock_t t_inicio = clock();

    for (i = 0; i < blocos; i++) {
        prox_setor = rand() % TOTAL_SETORES;
        acessa_disquete_entrelacamento(fator, prox_setor, LEITURA, buffer);
    }

    free(buffer);
    float tempo_total = (clock() - t_inicio)*1000/CLOCKS_PER_SEC;
    printf("   LEITURA ALEATORIA de %d blocos e fator %d:\n", blocos, fator);
    printf("   Tempo total: %.0fms\n   Tempo medio por bloco: %.0fms\n\n", tempo_total, tempo_total/blocos);
}

void mede_escrita_sequencial(int fator, int blocos) {
    int i, j, prox_setor = rand() % TOTAL_SETORES;
    char* buffer = (char*)malloc(BYTES_SETOR);

    clock_t t_inicio = clock();

    for (i = 0; i < blocos; i++) {
        acessa_disquete_entrelacamento(fator, prox_setor, ESCRITA, buffer);
        prox_setor++;
        if (prox_setor >= TOTAL_SETORES)
            prox_setor = 0;
    }

    free(buffer);
    float tempo_total = (clock() - t_inicio)*1000/CLOCKS_PER_SEC;
    printf("   ESCRITA SEQUENCIAL de %d blocos e fator %d:\n", blocos, fator);
    printf("   Tempo total: %.0fms\n   Tempo medio por bloco: %.0fms\n\n", tempo_total, tempo_total/blocos);
}

void mede_escrita_aleatoria(int fator, int blocos) {
    int i, prox_setor;
    char* buffer = (char*)malloc(BYTES_SETOR);

    clock_t t_inicio = clock();

    for (i = 0; i < blocos; i++) {
        prox_setor = rand() % TOTAL_SETORES;
        acessa_disquete_entrelacamento(fator, prox_setor, ESCRITA, buffer);
    }

    free(buffer);
    float tempo_total = (clock() - t_inicio)*1000/CLOCKS_PER_SEC;
    printf("   ESCRITA ALEATORIA de %d blocos e fator %d:\n", blocos, fator);
    printf("   Tempo total: %.0fms\n   Tempo medio por bloco: %.0fms\n\n", tempo_total, tempo_total/blocos);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    cria_disquete();

    int fator = 3;
    int blocos = 10;

    int i;
    printf("\n\n   ESCRITA SEQUENCIAL ---\n\n");
    mede_escrita_sequencial(fator, blocos);

    printf("\n\n   LEITURA SEQUENCIAL ---\n\n");
    mede_leitura_sequencial(fator, blocos);

    printf("\n\n   ESCRITA ALEATORIA ---\n\n");
    mede_escrita_aleatoria (fator, blocos);

    printf("\n\n   LEITURA ALEATORIA ---\n\n");
    mede_leitura_aleatoria (fator, blocos);

    return 0;
}

