/*
    NOME: JULIANO LEONARDO SOARES
    TURMA DE PROGRAMACAO E ANALISE DE ALGORITMOS 2018
*/
#include <stdio.h>

#define	andares		25	///a altura do edificio nos andares
#define cap_MAX	50	    ///qual a capacidade do elevador?
#define MAXINT  100007

int paradas[cap_MAX];     ///Em que andar todos saem?
int N_passageiros;		  ///número de pilotos
int N_paradas;			  ///número de paradas permitidas
int m[andares+1][cap_MAX];///tabela de custo de programação dinâmica
int p[andares+1][cap_MAX];///tabela pai de programação dinâmica

andar_passado(int anterior, int atual){
	int nsteps=0;/// distância total percorrida
	int i;		 /// contador

	for (i=1; i<=N_passageiros; i++)
		if ((paradas[i] > anterior) && (paradas[i] <= atual))
			nsteps += min(paradas[i]-anterior, atual-paradas[i]);

	return(nsteps);
}

int otimizar_andar(){
	int i,j,k;		  ///contadores
	int custo;		  ///espaço reservado para os custos
	int ultima_parada;///última parada do elevador
	for (i=0; i<=andares; i++) {
		m[i][0] = andar_passado(0,MAXINT);
		p[i][0] = -1;
	}
	for (j=1; j<=N_paradas; j++)
		for (i=0; i<=andares; i++) {
			m[i][j] = MAXINT;
			for (k=0; k<=i; k++) {
			     custo = m[k][j-1] - andar_passado(k,MAXINT) +
				andar_passado(k,i) + andar_passado(i,MAXINT);
			     if (custo < m[i][j]) {
			     	m[i][j] = custo;
				p[i][j] = k;
			     }
			}
		}
	ultima_parada = 0;
	for (i=1; i<=andares; i++)
		if (m[i][N_paradas] < m[ultima_parada][N_paradas])
			ultima_parada = i;
	return(ultima_parada);
}

refazer_caminho(int ult_andar, int falta_parar){
	if (falta_parar > 1)
		refazer_caminho( p[ult_andar][falta_parar], falta_parar-1);
	printf("%d\n",ult_andar);
}

print_matrix(m)
int m[andares+1][cap_MAX];{
	int i,j;// contador
    for (j=0; j<=N_paradas; j++) {
        for (i=0; i<=andares; i++)
            printf("%3d",m[i][j]);
            printf("\n");
    }
}

int min(int a, int b){
	if (a < b)return(a);
	else return(b);
}

main(){
	int i,j;// contador
	int ultima_parada;
    printf("Escreva o numero de paradas:\n");
	scanf("%d",&N_paradas);
	printf("Escreva o numero de passageiros:\n");
	scanf("%d",&N_passageiros);

    printf("Escreva o andar de parada de cada passageiro:\n");
	for (i=1; i<=N_passageiros; i++)
		scanf("%d",&(paradas[i]));

    for (i=1; i<=N_passageiros; i++)
        printf("%d\n",paradas[i]);

	ultima_parada = otimizar_andar();
	print_matrix(&m);
	printf("\n");
	print_matrix(&p);
	printf("custo = %d\n",m[ultima_parada][N_paradas]);
	refazer_caminho(ultima_parada,N_paradas);
    return 0;
}
