#include <stdio.h>

#define abs(x) ((x)>0?(x):-(x))

/* recebe vetor e a direcao (d)
 * Movimentos (alfabeto) : 
 *		cima 			d=0
 *		direita 		d=1
 *		baixo			d=2
 *		esquerda 	d=3
 */
 enum {cima, direita,baixo,esquerda};

// variaveis de controle
int swap_indices[9][4] =
{	{-1 , 1,  3, -1},
	{-1 , 2,  4,  0},
	{-1 ,-1,  5,  1},
	{ 0 , 4,  6, -1},
	{ 1 , 5,  7,  3},
	{ 2 ,-1,  8,  4},
	{ 3 , 7, -1, -1},
	{ 4 , 8, -1,  6},
	{ 5 ,-1, -1,  7}
};
int posicao_livre = 0 ;

// exibe a matriz (recebe vetor)
#define show(v) {for(int i=0;i<9;i++) printf("%i%c",v[i],(i+1)%3==0?'\n':' ');}

// troca dois valores do vetor (recebe vetor, indice i, e indice j)
#define swap(v,i,j) {v[i]^=v[j]; v[j]^=v[i]; v[i]^=v[j];}

// move o espaço vazio para uma direção
#define move(v,d) { swap(v,posicao_livre,swap_indices[posicao_livre][d]); posicao_livre = swap_indices[posicao_livre][d];} 

/* verifica se é possivel mover*/
#define can_move(v,d) (swap_indices[posicao_livre][d]>0) ? 1 : 0

/* quantas posições são compatíveis */
int heuristica_1(int a[],int b[])
{
	int c = 0 ;
	for(int i=0;i<9;i++) c+=(a[i]==b[i]) ;
	return c;
}

/* distancia de manhattan */
int heuristica_2(int a[],int b[])
{
	int i,j,c=0;
	for(i=0;i<9;i++)
	{
		for(j=0;a[i]!=b[j];j++);
		// calculo da distancia + conversão de indices
		c += abs( i%3 - j%3 ) + abs( i/3 - j/3 ) ;
	}
	return c;
}

/*
 * vetor com as funcções heuristicas (o user pode escolher
 * entre heu[0](a,b) ou heu[1](a,b) )
 */ 
int (*heu[]) (int*,int*) ={ heuristica_1 , heuristica_2 };

int main()
{
	int at[9]= {0,1,2,3,4,5,6,7,8};
	int fn[9]= {1,0,2,3,4,5,7,8,6};
	
	if(can_move(at,direita)) move(at,direita);
	
	printf("%i\n",(heu[0])(at,fn));
	show(at);
}
