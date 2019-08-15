/* pacote.h
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#pragma once

#include "buffer.h"

typedef struct pacote {
    int setor;               // setor de acesso do pedido
    int operacao;            // operacao do pedido
    Buffer* buffer_resposta; // buffer do cliente para resposta
    char* dado;              // o dado para inserir ou lido
    bool ok;                 // confirmacao da operacao
} Pacote;

// aloca espaco para pacotes
Pacote* pacote_cria(int tam);

// libera o espaco de um pacote
void pacote_libera(Pacote* p);

// inicializa um pedido com os dados recebidos por parametro
Pacote pacote_pedido(int setor, int op, Buffer* buffer, char* d);

// atualiza os dados do pacote com a resposta
void pacote_att_resposta(Pacote* p, char* d, bool ok);
