/* disquete.h
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#pragma once

#include <stdbool.h>

#define FILE_NAME "disk"
#define FACES   2	// numero de faces
#define TRILHAS 40  // numero trilhas por face
#define SETORES 9   // numero de setores por trilha
#define TOTAL_SETORES (SETORES * TRILHAS * FACES)
#define BYTES_SETOR 512
#define CAPACIDADE (BYTES_SETOR * TOTAL_SETORES)

#define LEITURA 0
#define ESCRITA 1

// cria o arquivo imagem do disquete, se nao houver um
void cria_disquete();

// acessa o disquete sem entrelacamento de setores
bool acessa_disquete(int setor, int tipo_acesso, char* buffer);

// acessa o disquete utilizando a tecnica de entrelacamento de setores
bool acessa_disquete_entrelacamento(int fator, int setor, int tipo_acesso, char* buffer);

// retorna o cilindro correspondente ao setor numlinear
int pega_cilindro(int numlinear);