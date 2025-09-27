//DOM-JJLM - Projeto Domino - Etapa 6
//23/09/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo 

#include "DOM-JJLM_View.h"

void apresentaMensagem(char msg[100]) //Apresenta uma mensagem caso necessario
{
	printf("%s\n", msg);
}

int Txtmenuprin() //mostra as opcoes do menu principal e captura a opcao do operador principal
{
	int op;
	
	printf("\n\n|-------------------------------------------|\n");
	printf("| (1) - Iniciar novo jogo (2 jogadores).    |\n");
	printf("| (2) - Iniciar novo jogo (Vs. Computador). |\n");
	printf("| (3) - Retornar ao jogo atual.             |\n");
	printf("| (4) - Recuperar jogo salvo.               |\n");
	printf("| (5) - Salvar jogo.                        |\n");
	printf("| (6) - Regras do jogo.                     |\n");
	printf("| (0) - Sair do jogo.                       |\n");
	printf("|-------------------------------------------|\n");
	printf("|-> Opcao Selecionada: ");
	scanf("%d", &op);
		
	return op;
}

void Mesa() //apresenta a mesa
{
	printf("\n\n==================\n");
	printf("Mesa: ");
	for(int i=0; i<qtmesa; i++)
		printf("[%d|%d]", mesa[i].ladoE, mesa[i].ladoD);
	printf("\n\n==================\n");
}

void apresentaPeca(char jogador) //Apresenta as pecas de um jogador
{
	int cont=0;
	for(int k=0; k<28 ; k++)
	{
		if(pecas[k].status==jogador)
			{
			cont++;
			printf("%d.[%d|%d]  ", cont,  pecas[k].lado1, pecas[k].lado2);
			}
	}
}

int Txtmenudojogo(char jogador) //Apresenta o submenu do jogo e coleta a opcao do operador
{
	int opdojogo;
    
	printf("\nJogador %c Pecas: ", jogador); 
	apresentaPeca(jogador);
	printf("\n\n1 - Jogar\n");
	printf("2 - Comprar\n");
	printf("3 - Passar\n");
	printf("0 - Sair\n");
	printf("Opcao Selecionada: ");
	scanf("%d", &opdojogo);		
	
	return opdojogo;
}
	
int Jogar(char jogador) //Recolhe o indice da peca a ser jogada
{
	int k;
	int pj;
	int y; //Controla se a peca a ser jogada e valida ou nao
	int cont = 0; //Armazena qual o numero em sequencia da peca a ser armazenada
	int i = -1; // Cursor que percorrera as pecas do jogo 
	int jogada; //Recebera a opcao da peca a ser jogada que estara em ordem sequencial, nao coincidindo com o indice
	int erro=0; //Sentinela usada para identificar quando a tela devera ser apagada 
    
    if(jogcomp==2 && jogador=='2') //Se for a vez do computador, inicia um for para recolher o indice da primeira peca jogavel
    	{
    	for(k=7; k<28; k++)	
    		{
    		if(pecas[k].status=='2')	//Se a peca for do computador
				if(PecaValida(k)!='0') //Se for valida
					break;	//Sai do loop
			}
		
		return k; //Retorna o indice k da peca jogada
		}
	
	do
	{
		y=0; //inicia a variavel que armazena a peca a ser jogada e valida ou nao como 0 para que caso a peca nao seja valida, ao final das verificacoes o loop continue para que o jogador selecione outra peca
		cont=0; 
		i=-1;
				
		if(erro==0) //Se nao houver erros a tela sera limpada
		system("cls");
		
		erro=0;
	   	
		Mesa(); //mostra a mesa
		
		//Apresenta o texto que recolhera a peca que o jogador que jogar
		printf("\nPecas com os lados %d ou %d sao possiveis.\n", mesaE, mesaD);
		printf("\nPecas disponiveis: ");
		apresentaPeca(jogador);
		printf("\n\nQue peca deseja jogar? (Digite 0 para desistir de jogar)");
		scanf("%d", &jogada);
		
		if(jogada==0) //Se jogada for = 0
			{
			return 99; //Retorna 99, um indice inexistente para que haja a verificacao no menu de que a escolha nao foi feita e que o jogador desistiu da jogada
			}
		
		//Se a jogada estiver fora do campo das pecas possuidas pelo jogador apresenta a mensagem de erro 
		if(jogada<1 || jogada>qtdPecasJg(jogador))															
		{
			system("cls");
			printf("\nVoce nao possui essa peca! Digite um numero entre 1 e %d para selecionar uma peca de sua mao.", qtdPecasJg(jogador));
			erro++; //Adiciona 1 a erro [ara que a tela nao seja apagada
		}   
	        
	    else //Se a jogada estiver dentro do campo das pecas possuidas pelo jogador
		{
			do //inicia o loop que recolhera o indice da peca escolhida pelo jogador
		    {
			   i++;
			   if(pecas[i].status==jogador)
				  cont++;		
		    }while(cont!=jogada);
	
		    pj=i; //pj recebe o indice da jogada
			
			if(PecaValida(pj)!='0')	//Se a peca for valida
				y=1; //y recebe 1 para quebrar o loop
			
			else //Se a peca nao for valida apresenta a mensagem de erro
				{
				system("cls"); 
				printf("Essa peca nao e valida em nenhum lugar da mesa");
				erro++;
				}
		} 
	
	}while(y==0);
	
	return pj; //retorna o valor do indice da peca jogada
}

void MSGdelay(char jogador) //Apresenta a mensagem com delay para que o jogador se prepare para jogar 
{
	printf("\nJogador %c, Sente-se para jogar, e' sua vez!! (Pecas disponiveis em breve)\n", jogador);
	ftempo(0);
}

char escolherLado() //Permite que o lado da mesa onde a peca sera jogada seja escolhido
{
	char x = NULL;
	while (x != 'E' && x != 'D')
	{
	fclear();	
	printf("\nEscolha o lado da Mesa: Esquerdo/Direito (E/D): ");
	scanf("%c",&x);
	x = toupper(x); 
	}
	
	return x;
}

void regrasdojogo()// apresenta as regras do jogo 
{
	    system("cls");
		printf("\n\n|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    	printf("| 1.  Cada jogador inicia com sete peca aleatoriamente.                                                                                                                                   |\n");
    	printf("| 2.  Antes do jogo/rodada comecar cada jogador pode comprar quantas pecas quiserem.                                                                                                      |\n");
    	printf("| 3.  O jogo inicia com o jogador que tiver com a peca de lados iguais maior. Caso nao haja, joga quem tiver com a peca de maior soma dos lados.                                          |\n");
     	printf("| 4.  Os jogadores devem colocar pecas que tenham os mesmos numeros das pecas que se encontram nas 2 pontas do jogo.                                                                      |\n");
    	printf("| 5.  Quando o jogador coloca sua peca sobre a mesa seu turno acaba e passa-se entao ao proximo jogador.                                                                                  |\n");
    	printf("| 6.  Se um jogador nao puder jogar devera comprar no monte disponivel, se nao houver pecas no monte passara o turno ao seguinte jogador                                                  |\n");
    	printf("| 7.  O jogador so podera passar a jogada nas seguintes condicoes: se ele nao possuir nenhuma peca possivel de ser colocada na mesa e se não houver mais pecas livres a serem compradas. |\n");
    	printf("| 8.  Vence a partida o jogador que jogar a sua ultima peca.                                                                                                                              |\n");
    	printf("| 9.  Caso nenhum jogador possua peca a ser jogadas, e o montante de compra esteja vazio, vence aquele que tiver menos pecas em seu poder                                                 |\n");
    	printf("| 9.1 No caso de empate do item acima, os jogadores devem contar os pontos das pecas que ficaram, o jogador com menos pontos vence a partida                                              |\n");
        printf("|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n\n\n\n");
}

void pecajogada(int d) //Apresenta a peca jogada por um jogador
{
	if(jogcomp==2 && jogador=='2')
		printf("--> O computador jogou a peca: [%d|%d]\n", mesa[d].ladoE, mesa[d].ladoD);	
	
	else
		printf("--> O jogador %c jogou a peca: [%d|%d]\n",jogador,mesa[d].ladoE,mesa[d].ladoD);
}

void qtpecacomprada() //Apresenta quantas pecas foram compradas em uma rodada
{
	if(jogcomp==2 && jogador=='2')
		printf("--> O computador comprou %d pecas\n", qtcompra);	
	
	else
		printf("--> O jogador %c comprou %d pecas\n", jogador, qtcompra);
}
void Passou() //Apresenta se um jogador passou a vez
{
	if(jogcomp==2 && jogador=='2')
		printf("--> O computador passou a vez\n");
	
	else
		printf("--> O jogador %c passou a vez\n",jogador);
}
