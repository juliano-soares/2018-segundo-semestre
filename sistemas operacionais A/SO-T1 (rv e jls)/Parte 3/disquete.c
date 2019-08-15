/* disquete.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 3
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "disquete.h"

void cria_disquete() {
    FILE* disk = fopen(FILE_NAME, "rb");

    // se nao existir o arquivo imagem do disquete, inicializa um
    if (!disk) {
        char* v = (char*)calloc(CAPACIDADE, 1);
        disk = fopen(FILE_NAME, "wb");
        if (!disk) {
            printf("Problemas na criacao do disquete %s.\n", FILE_NAME);
            exit(0);
        }

        int escrito = fwrite(v, 1, CAPACIDADE, disk);
	}

    fclose(disk);
}

// transforma setor de numero linear em tupla
static void setor2tupla(int numlinear, int* cilindro, int* superficie, int* setor) {
    *cilindro = (numlinear / SETORES) % TRILHAS;
    *superficie = numlinear % (SETORES * TRILHAS);
    *setor = numlinear % SETORES;
}

// calcula o tempo de acesso ao setor
// todos os tempos estao em milissegundos (ms)
static float calcula_tempo_acesso(int numlinear) {
    int cilindro, superficie, setor;
    setor2tupla(numlinear, &cilindro, &superficie, &setor);

    //  dados do disquete
    float t_rotacao = 200.0;
    float t_busca_cilindro_adjacente = 6.0;

    clock_t cronometro = clock();
    static int cilindro_cabecote = 0;
    float t_desde_inicio_rotacao = (float)((int)(clock()*1000/CLOCKS_PER_SEC) % (int)t_rotacao);
    printf("Tempo desde ultima volta completada: %.0fms\n", t_desde_inicio_rotacao);

    // tempo de busca pelo cilindro certo
    int cilindros_de_distancia = (cilindro - cilindro_cabecote);
    if (cilindros_de_distancia < 0)
        cilindros_de_distancia *= -1;
    float t_busca_cilindro = cilindros_de_distancia * t_busca_cilindro_adjacente;
    printf("Move cabecote do cilindro %d para %d (dist %d) em %.0fms\n", cilindro_cabecote, cilindro, cilindros_de_distancia, t_busca_cilindro);
    
    // tempo de selecao do cabeçote (ou 1/10 do tempo de busca da trilha)
    float t_selecao_cabecote = t_busca_cilindro * 0.1;

    // tempo de espera rotacional
    float tempo_por_setor = t_rotacao / SETORES;
    int setor_atual = t_desde_inicio_rotacao / tempo_por_setor;
    int setores_de_distancia = setor - setor_atual;
    if (setores_de_distancia < 0)
        setores_de_distancia += SETORES;
    float t_espera_rotacional = tempo_por_setor * setores_de_distancia;
    printf("Espera rotacao do setor %d ate %d (dist %d) em %.0fms\n", setor_atual, setor, setores_de_distancia, t_espera_rotacional);

    // tempos de tranferencia
    float t_transferencia = 22.0;

    // atualiza posicao do cabecote pra a que ficou
    cilindro_cabecote = cilindro;

    return (t_busca_cilindro + t_selecao_cabecote + t_espera_rotacional + t_transferencia);
}

static void imprime_buffer(char* buffer) {
    int i;
    printf("Imprimindo buffer de dados...\n");
    for (i = 0; i < BYTES_SETOR; i++)
        printf("%d ", buffer[i]);
    printf("\n");
}

// escreve o dado do buffer no setor do arquivo imagem do disquete
static bool escrita_disquete(int setor, char* buffer) {
    FILE* disk = fopen(FILE_NAME, "rb");
    if (!disk) return false;

    long int offset = setor * BYTES_SETOR;
    int r = fseek(disk, offset, SEEK_SET);
    if (r) {
        printf("Falhou no salto para escrita do setor %d.\n", setor);
        return false;
    }

    int bytes_escritos = fwrite(buffer, 1, BYTES_SETOR, disk);

    fclose(disk);

    return true;
}

// le o dado do setor do arquivo imagem do disquete e coloca no buffer
static bool leitura_disquete(int setor, char* buffer) {
    FILE* disk = fopen(FILE_NAME, "rb");

    if (!disk) {
        printf("\nProblemas na abertura do arquivo para leitura.\n");
        printf("Verifique se %s existe e tente novamente.\n", FILE_NAME);
        return false;
    }

    long int offset = setor * BYTES_SETOR;
    int r = fseek(disk, offset, SEEK_SET);
    if (r) {
        printf("Falhou no salto para leitura do setor %d.\n", setor);
        return false;
    }

    int bytes_lidos = fread(buffer, 1, BYTES_SETOR, disk);

    fclose(disk);

    return true;
}

bool acessa_disquete(int setor, int tipo_acesso, char* buffer) {
    printf("Iniciando acesso de %s ao setor %d do disquete.\n", (tipo_acesso ? "ESCRITA" : "LEITURA"), setor);
    float tempo_acesso, tempo_espera;
    clock_t t_inicio;
    bool ok;

    t_inicio = clock();
    if (tipo_acesso == ESCRITA)
        ok = escrita_disquete(setor, buffer);
    else
        ok = leitura_disquete(setor, buffer);

    tempo_acesso = calcula_tempo_acesso(setor);
    // busy wait pq no linux o clock pausa com o sleep
    // e precisa dele para saber o tempo decorrido
    while ((clock() - t_inicio)*1000/CLOCKS_PER_SEC < tempo_acesso);

    printf(" - Tempo total de acesso: %.0fms\n\n", tempo_acesso);

    return ok;
}

bool acessa_disquete_entrelacamento(int fator, int setor, int tipo_acesso, char* buffer) {
    // se entrou numero linear do setor que nao existe, retorna
    if (setor >= TOTAL_SETORES)
        return false;

    // se nao ha entrelacamento, acessa direto
    if (fator == 0)
        return acessa_disquete(setor, tipo_acesso, buffer);

    // gera um vetor para guardar a posicao de cada setor
    int i, v[TOTAL_SETORES];
    for (i = 0; i < TOTAL_SETORES; i++)
        v[i] = -1;
    
    int pos = 0;
    for (i = 0; i < TOTAL_SETORES; i++) {
        // se a posicao ja esta ocupada, pula para proxima
        for (; v[pos%TOTAL_SETORES] != -1; pos++);

        // v[x] recebe o numero linear do setor
        // sendo a x posicao do setor no disco
        v[pos % TOTAL_SETORES] = i;

        // se ja obteve a posicao do setor que buscava,
        // nao eh mais necessario continuar o mapeamento
        if (i == setor) break;

        pos += fator + 1;
    }

    // resultado do entrelacamento
    //for (i = 0; i < TOTAL_SETORES; i++)
    //  printf("%d ", v[i]);
    //printf("\n");

    //printf("Setor %d com entrelacamento %d fica na posicao %d\n", setor, fator, pos%TOTAL_SETORES);

    return acessa_disquete(pos % TOTAL_SETORES, tipo_acesso, buffer);
}
