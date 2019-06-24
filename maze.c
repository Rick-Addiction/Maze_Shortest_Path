//HENRIQUE RACHTI ASSUMPÇÃO - 31580548	
//BRUNO CESAR ROCHA SALGADO - 31544010




#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point *elementos;//fila de pontos
  int first, last;
} TFila;

void cria_fila (TFila *F) {  
  F->elementos = (Point *) calloc(N, sizeof(Point));
  F->first = 0;
  F->last = 0;
}

int vazia(TFila *F){
	return F->first == F->last;
}

int cheia(TFila *F){
	return F->last == N;	
}

void insere_fila (TFila *F, Point elemento) {
  if (cheia(F)) {
    printf("Erro: Fila ja esta cheia!\n");
  }
  else {
    F->last++;
    F->elementos[F->last] = elemento;
  }
}

void remove_fila (TFila *F) {
  if (vazia(F)) {
    printf("Erro: Fila ja esta vazia!\n");
  }
  else 
    F->first++;
}

Point primeiroDaFila (TFila *F) {
  if (vazia(F)) {
    printf("Erro: Fila ja esta vazia!\n");
  }
  else 
    return (F->elementos[(F->first + 1)]);
}

//imprime o labirinto, considerando nos campos com -1, é impresso um X, simulando uma parede
void imprime_labirinto(int labirinto[][N], int n) {
  int i, j;

  printf("\n");
  for (i=0; i<=n+1; i++) {
    for (j=0; j<=n+1; j++)
    if(i==0||i==n+1)
    printf("= ");
    else if(j==0||j==n+1)
    printf("| ");
    else if (labirinto[i][j] == -1)
	printf("H ");
	else if (labirinto[i][j] == -3)
	printf("- ");
	else if (labirinto[i][j] == -4)
	printf("  ");
      else 
	printf("%d ", labirinto[i][j]);

    printf("\n");
  }
  printf("\n");
}

void mede_vizinhos(int labirinto[][N], Point p, TFila *F) {
  Point p2;

//eh feita a verificacao se os vizinhos do ponto a ser considerado no momento ja foi visitado e entao é inserido no vizinho o numero do ponto
//que esta sendo considerado mais 1 no labirinto, identificando a distancia que foi percorrida a partir do ponto de destino
//Posteriormente, o ponto a ser estudado se torna o vizinho, e ele é inserido na fila

//desce
  if (labirinto[p.x+1][p.y] == -2) {
    labirinto[p.x+1][p.y] = labirinto[p.x][p.y] + 1;
    p2.x = p.x+1;
    p2.y = p.y;
    insere_fila(F, p2);
  } 
  
//sobe  
  if (labirinto[p.x-1][p.y] == -2) {
    labirinto[p.x-1][p.y] = labirinto[p.x][p.y] + 1;
    p2.x = p.x-1;
    p2.y = p.y;
    insere_fila(F, p2);
  } 
//a direita
  if (labirinto[p.x][p.y+1] == -2) {
    labirinto[p.x][p.y+1] = labirinto[p.x][p.y] + 1;
    p2.x = p.x;
    p2.y = p.y+1;
    insere_fila(F, p2);
  } 
//a esquerda  
  if (labirinto[p.x][p.y-1] == -2) { 
    labirinto[p.x][p.y-1] = labirinto[p.x][p.y] + 1;
    p2.x = p.x;
    p2.y = p.y-1;
    insere_fila(F, p2);
  } 
}

void limpa_labirinto(int labirinto[][N], int n) {
  // Coloca -2 em todas as posições que não são uma parede, para demonstrar que não foram verificadas
  int i, j;

  for (i=1; i<=n; i++) 
    for (j=1; j<=n; j++)
      if (labirinto[i][j] != -1)
	labirinto[i][j] = -2;
}

void busca_menor_caminho(int labirinto[][N], int n, Point p) {

  TFila F;
  Point p2;
  
  cria_fila(&F);
  limpa_labirinto(labirinto, n);//todos os espaços validos do labirinto recebem o valor -2

  
  labirinto[p.x][p.y] = 0;//o ponto de destino recebe o valor 0
  insere_fila(&F, p);//o ponto de destino é inserido na fila

 //Enquanto a fila não estiver vazia, executar a verificao dos caminhos
  while (!vazia(&F)) {
    p2 = primeiroDaFila(&F);
    mede_vizinhos(labirinto, p2, &F);//numerar os seus vizinhos livres com o número do ponto acrescido de 1 e colocar os novos pontos (vizinhos) na fila.
    remove_fila(&F);//remover o ponto em que se estava verificando da fila
    
    //Após a fila estiver vazia, todos os campos foram verificados
  }
}

Point anterior(int labirinto[][N], Point p) {
  Point p2;// ponto auxiliar

/*verifica se o de baixo do ponto tem um numero a mais do que o ponto que se deseja encontrar o anterior, sendo que o ponto auxiliar
irá receber as coodernadas desse ponto de baixo, senao, se o de cima do ponto tem um numero a mais do que o ponto que se deseja 
encontrar o anterior o ponto auxiliar irá receber as coodernadas desse ponto de cima 
*/
  if (labirinto[p.x+1][p.y] == labirinto[p.x][p.y] - 1) {
    p2.x = p.x+1;
    p2.y = p.y;
  }
  else if (labirinto[p.x-1][p.y] == labirinto[p.x][p.y] - 1) {
    p2.x = p.x-1;
    p2.y = p.y;
} 
/*verifica se o da direita do ponto tem um numero a mais do que o ponto que se deseja encontrar o anterior, sendo que o ponto auxiliar
irá receber as coodernadas desse ponto da direita, e se o da esquerda do ponto tem um numero a mais do que o ponto que se deseja 
encontrar o anterior o ponto auxiliar irá receber as coodernadas desse ponto da esquerda 
*/
  if (labirinto[p.x][p.y+1] == labirinto[p.x][p.y] - 1) {
    p2.x = p.x;
    p2.y = p.y+1;
  } 
  if (labirinto[p.x][p.y-1] == labirinto[p.x][p.y] - 1) { 
    p2.x = p.x;
    p2.y = p.y-1;
  } 
  return (p2);
}

void caminho_encontrado(int labirinto[][N], int n, Point p) {
  
  Point p2;
  int labirinto_caminho[N][N];
  int i,j;
  
  for(i=0;i<=n;i++)
  	for(j=0;j<=n;j++)
  		if(labirinto[i][j]!=-1)
  		labirinto_caminho[i][j]	= -4;
  		else 
  		labirinto_caminho[i][j]	= labirinto[i][j];
  		
  if (labirinto[p.x][p.y] == -2)//verifica se identificou um momento onde não há mais caminhos até o ponto de destino
    printf("Não há caminho.\n\n");
  else {
    p2 = p;
    printf("\nCaminho:\n");
    while (labirinto[p2.x][p2.y] != 0) {//do ponto de chegada até o ponto final, é apresentado o caminho através da verificação dos pontos
	  printf("(%d,%d)\n", p2.x, p2.y);// com respectivos antecessores , alcançando até o 0 que éo valor armazenado no ponto de destino
	  labirinto_caminho[p2.x][p2.y]=-3;
      p2 = anterior(labirinto, p2);      
    }
    printf("(%d,%d)\n\n", p2.x, p2.y); 
    labirinto_caminho[p2.x][p2.y]=-3;
    imprime_labirinto(labirinto_caminho,n);
  }
}

main() {
  FILE *input;
  char nome[N], resp;

  int n;//tamanho do labirinto
  int labirinto[N][N];//labirinto
  int i, j;
  int fora; 
  Point partida;//posicao de partida no labirinto
  Point destino;//posicao de chegada no labirinto  

  if ((input = fopen("input.txt", "r")) == NULL) {
    printf("Nao foi possivel ler o arquivo input.txt\n");
  }

  //Leitura do arquivo
  fscanf(input, "%d ", &n);
  
  for (i=1; i<=n; i++) {
    labirinto[i][0] = -1;
    for (j=1; j<=n; j++)
      fscanf(input, "%d ", &labirinto[i][j]);
    labirinto[i][n+1] = -1;
  }
  for (j=1; j<=n; j++) {
    labirinto[0][j]   = -1;
    labirinto[n+1][j] = -1;
  }
  fclose(input);

  
  imprime_labirinto(labirinto, n);

  
    do {
      printf("Digite a posicao inicial: ");
      scanf("%d %d", &partida.x, &partida.y);
      //fora = (partida.x <= 0 || partida.x > m || partida.y <= 0 || partida.y > n);
      if (fora || labirinto[partida.x][partida.y] == -1) 
	printf("Posicao invalida!\n");
    } while (partida.x <= 0 || partida.x > n || partida.y <= 0 || partida.y > n || labirinto[partida.x][partida.y] == -1);//verifica se passa dos limites do labirinto ou se é uma parede
    
    
    printf("A partida eh em (%d,%d).\n", partida.x, partida.y);
    do {
      printf("Digite a posicao final: ");
      scanf("%d%d", &destino.x, &destino.y);
      //fora = (destino.x <= 0 || destino.x > m || destino.y <= 0 || destino.y > n);
      if (destino.x <= 0 || destino.x > n || destino.y <= 0 || destino.y > n || labirinto[destino.x][destino.y] == -1) //verifica se passa dos limites do labirinto ou se é uma parede
	printf("Posicao invalida!\n");
    } while (fora || labirinto[destino.x][destino.y] == -1);
    printf("O destino eh em (%d,%d).\n", destino.x, destino.y);
    busca_menor_caminho(labirinto, n, destino);

    
    //imprime_labirinto(labirinto, m, n);//labirinto com as distâncias

    caminho_encontrado(labirinto, n, partida);//mostra o caminho encontrado
    double x = 0;
    scanf("%d",&x);
   
  
}

