/* main.c
 *
 * Trabalho de Sistemas Operacionais A
 *               Parte 4
 * Grupo:
 *    Rafael Vales
 *    Juliano Soares
*/

// gcc -o p4 main.c pacote.c buffer.c disquete.c fila.c -pthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "disquete.h"
#include "buffer.h"
#include "pacote.h"

// configura ordem de retiradas dos pedidos da thread servidora
#define RETIRADA_PEDIDOS FCFS
#define FCFS 0
#define ELEVADOR 1

#define N_CLIENTES 8
#define PEDIDOS_POR_CLIENTE 1

static void pedidos_ordena_elevador(Pacote* p, int tam) {
    static bool up = true;         // direcao
    static int cilindro_atual = 0; // posicao inicial

    int dif, prox, dif_prox = 0;
    int i, j, cilindro_j;
    Pacote tmp;

    // ordem dos cilindros na entrada
    //for (i = 0; i < tam; i++)
    //    printf("%d ", pega_cilindro(p[i].setor));
    //printf("\n");

    for (i = 0; i < tam; i++) {
        prox = -1;
        // seleciona o mais proximo no sentido atual
        for (j = i; j < tam; j++) {
            cilindro_j = pega_cilindro(p[j].setor);
            // se estiver na direcao contraria, pula pro proximo
            if ((up && cilindro_j < cilindro_atual) || (!up && cilindro_atual < cilindro_j))
                continue;
            dif = (up ? cilindro_j - cilindro_atual : cilindro_atual - cilindro_j); // abs da diferenca
            if (dif < dif_prox || prox == -1) {
                prox = j;
                dif_prox = dif;
            }
        }

        if (prox == -1) { // se nao achou mais nenhum no sentido
            up = !up;     // inverte a direcao
            i--;          // repete o passo
        } else if (i != prox) { // se achou, swapa
            tmp = p[i];
            p[i] = p[prox];
            p[prox] = tmp;
            cilindro_atual = pega_cilindro(p[i].setor);
        }
    }

    // ordem dos cilindros na saida
    //for (i = 0; i < tam; i++)
    //    printf("%d ", pega_cilindro(p[i].setor));
    //printf("\n");
}

void* servidor(void* buffer_servidora) {
    int i, tam;
    bool ok;
    Pacote p;

    // calcula o total de pedidos que serao processados
    // para saber quando encerrar o laco e a thread
    int pedidos_restantes = N_CLIENTES * PEDIDOS_POR_CLIENTE;

    while (pedidos_restantes > 0) {
        // verifica se ha pedidos esperando no buffer compartilhado
        tam = buffer_usado(buffer_servidora);
        if (tam <= 0)
            continue;

        // le os dados do buffer e coloca em um vetor, fazendo uma fila de pedidos recebidos e nao processados
        Pacote* pedidos = pacote_cria(tam); // cria um vetor de pacotes com "tam" posicoes
        for (i = 0; i < tam; i++)
            buffer_remove(buffer_servidora, (void*)(&pedidos[i]));

        // se estiver configurada para retirar os pedidos usando elevador,
        // chama funcao para arrumar a ordem, senao ja esta ok em fcfs
        if (RETIRADA_PEDIDOS == ELEVADOR)
            pedidos_ordena_elevador(pedidos, tam);
        
        // processa os pedidos e insere no buffer do cliente a resposta
        for (i = 0; i < tam; i++) {
            ok = acessa_disquete(pedidos[i].setor, pedidos[i].operacao, pedidos[i].dado);
            pacote_att_resposta(&pedidos[i], pedidos[i].dado, ok); // atualiza o pedido com a resposta
            buffer_insere(pedidos[i].buffer_resposta, (void*)&pedidos[i]); // poe no buffer do cliente
        }

        pedidos_restantes -= tam;
        pacote_libera(pedidos);
    }
}

void* cliente(void* buffer_servidora) {
    char dado[] = "abcdefghijkl";
    Pacote p;

    int buffer_size = PEDIDOS_POR_CLIENTE;
    Buffer* buffer = buffer_inicializa(buffer_size);
    int pedidos_enviados = 0;
    int pedidos_recebidos = 0;

    // apenas sai do laco depois que tiver recebido resposta para todos pedidos de acesso
    while (pedidos_recebidos < PEDIDOS_POR_CLIENTE) {
        // se ainda nao enviou todos pedidos pre definidos, envia
        if (pedidos_enviados < PEDIDOS_POR_CLIENTE) {
            if (rand()%2 == LEITURA) {
                p = pacote_pedido(rand()%TOTAL_SETORES, LEITURA, buffer, NULL);
                buffer_insere(buffer_servidora, (void*)&p);
            } else {
                p = pacote_pedido(rand()%TOTAL_SETORES, ESCRITA, buffer, dado);
                buffer_insere(buffer_servidora, (void*)&p);
            }
            pedidos_enviados++;
        }

        // verifica se ha respostas do servidor no seu buffer
        while (buffer_usado(buffer) > 0) {
            // remove uma resposta do seu buffer
            buffer_remove(buffer, (void*)&p);
            // verifica o resultado da operacao e faz o que quiser
            if (p.ok)
                printf("\t\tPacote OK (buffer %p).\n", buffer);
            else
                printf("\t\tPacote falhou (buffer %p).\n", buffer);
            pedidos_recebidos++;
        }
    }

    buffer_finaliza(buffer);
}   

int main(int argc, char const *argv[]) {
    int i;
    pthread_t t_servidor;
    pthread_t t_clientes[N_CLIENTES];
    cria_disquete();

    int buffer_size = N_CLIENTES*PEDIDOS_POR_CLIENTE+1;
    Buffer* buffer_servidora = buffer_inicializa(buffer_size);
    printf("Buffer servidor: %p\n\n", buffer_servidora);

    // cria 1 thread servidora e N clientes
    pthread_create(&t_servidor, NULL, servidor, (void*)buffer_servidora);
    for(i = 0; i < N_CLIENTES; i++)
        if (pthread_create(&(t_clientes[i]), NULL, cliente, (void*)buffer_servidora) != 0)
            i--; // se a i-esima thread nao foi criada com sucesso, repete

    pthread_join(t_servidor, NULL);
    for(i = 0; i < N_CLIENTES; i++)
        pthread_join(t_clientes[i], NULL);

    buffer_finaliza(buffer_servidora);
    printf("\nFinalizado com sucesso.\n");

    return 0;
}
