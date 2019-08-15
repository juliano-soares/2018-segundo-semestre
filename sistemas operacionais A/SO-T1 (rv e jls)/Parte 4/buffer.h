/* buffer.h
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

#pragma once

typedef struct buffer Buffer;

// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser possível usar-se quantos buffers se quiser.
// Retorna um ponteiro para o buffer alocado, ou NULL se der problema.
Buffer* buffer_inicializa(int cap);

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior são perdidos.
// A memória alocada na inicialização deve ser liberada.
// Após esta chamada, o buffer não pode mais ser utilizado.
void buffer_finaliza(Buffer* buf);

// retorna o total de dados presentes no buffer.
int buffer_usado(Buffer* buf);

// insere em ``buf`` o dado apontado por ``p``, contendo o pacote.
// retorna ``false`` (e não altera o estado do buffer) caso não seja
// possível.
// retorna ``true`` caso o dado tenha sido inserido no buffer.
bool buffer_insere(Buffer* buf, void* p);

// remove o próximo dado de ``buf``, colocando-o na região apontada por ``p``,
// Retorna ``true`` se for bem sucedido, e ``false`` caso contrário.
bool buffer_remove(Buffer* buf, void* p);
