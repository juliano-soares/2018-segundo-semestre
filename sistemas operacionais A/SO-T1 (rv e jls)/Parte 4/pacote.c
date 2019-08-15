/* pacote.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "pacote.h"
#include "disquete.h"

Pacote* pacote_cria(int tam) {
    return (Pacote*)malloc(tam * sizeof(Pacote));
}

void pacote_libera(Pacote* p) {
    free(p);
}

Pacote pacote_pedido(int setor, int op, Buffer* buffer, char* d) {
    Pacote p;
    p.setor = setor;
    p.operacao = op;
    p.buffer_resposta = buffer;
    p.dado = (char*)malloc(BYTES_SETOR);
    if (d != NULL)
        strncpy(p.dado, d, BYTES_SETOR);
    p.ok = 0;

    if (op == LEITURA)
        printf("\t\t<> Criou o pacote pedido LEITURA: setor %d | buffer %p\n", setor, buffer);
    else
        printf("\t\t<> Criou o pacote pedido ESCRITA: setor %d | buffer %p | dado %s\n", setor, buffer, d);
    
    return p;
}

void pacote_att_resposta(Pacote* p, char* d, bool ok) {
    if (p->operacao == LEITURA && d != NULL)
        strncpy(p->dado, d, BYTES_SETOR);
    p->ok = ok;

    if (p->operacao == LEITURA)
        printf("\t\t<> Atualizou o pacote p/ resposta: buffer %p | dado \"%s\" | ok %d\n", p->buffer_resposta, d, ok);
    else
        printf("\t\t<> Atualizou o pacote p/ resposta: buffer %p | ok %d\n", p->buffer_resposta, ok);
}
