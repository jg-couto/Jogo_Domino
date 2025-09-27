//DOM-JJLM - Projeto Domino - Etapa 6
//23/09/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

#include "DOM-JJLM_Controller.h"
#include "DOM-JJLM_View.cpp"

void criarPecas()
{	
	int i=0, s; 
	
	for(int j=0; j<7; j++) //Este comando preenche o lado 1 das pecas
		for(int k=j; k<7; k++) //Este comando preenche o lado 2 das pecas 
			{
				pecas[i].lado1=j; 
				pecas[i].lado2=k;
				i++; //Acrescenta 1 ao indice para mudar a peca que esta sendo montada 
			}
}

void embaralhaPecas()
{
	int s;
	srand(time(NULL));
	//Embaralha as pecas do jogo	
	for(int x=0; x<28; x++) //Realiza a passagem por todas as pecas
		{
			aux=pecas[x]; //A variavel aux recebe os lados 1 e 2 da peca selecionada pelo comando for acima para guardar essa peca
			s=rand()%28; //O valor aleatorio de rand() e dividido por 28 e o seu resto que varia entre 0 e 27 sera armazenado na variavel s, usada posteriormente para selecionar uma peca aleatoria
			pecas[x]=pecas[s]; //A peca selecionada pelo for recebe os valores da peca selecionada aleatoriamente
			pecas[s]=aux; //Por fim, a peca aleatoria recebe os valores da peca selecionada por x  por meio da variavel aux. Assim completa-se a troca de lugar das pecas
		}
}

void executajogo()
	{
		embaralhaPecas(); //Embaralha as pecas do jogo
		MenuPrin(); //Abre o menu principal
	}
	
void PrimeiraPeca() //Encontra a primeira peca do jogo
{
	int i, pj, dupla; //Inicia as variaveis
	pj = -1; //Inicia o indice da primeira peca jogada como -1
	dupla = -1; //Inicia a variavel que ira armazenar tanto o lado da peca de lados iguais maior e para armazenar a maior soma entre os lados de uma peca

	for(i = 0; i < 14; i++) //Roda pelas primeiras 14 pecas pertencentes aos jogadores
		{
		if(pecas[i].lado1 == pecas[i].lado2) //Encontra pecas com lados iguais
			{
			if(pecas[i].lado1 > dupla) //Dupla armazena o maior lado de uma peca e compara com os maiores lados de outras pecas com lados iguais
				{
				dupla = pecas[i].lado1;
				pj = i;
				}
			}
		}

	if(pj == -1) //Se nao houverem pecas com lados iguais a peca com maior soma entre os lados sera jogada
		{
		dupla = 0; 
		
		for(i = 0; i < 14; i++) //Dupla armazenara a maior soma entre os lados de uma peca e compara com o mesmo em outras pecas
			{
			if(pecas[i].lado1 + pecas[i].lado2 > dupla)
				{
				dupla = pecas[i].lado1 + pecas[i].lado2;
				pj = i; 
				}
 			}
 		}
 
	vez = pecas[pj].status; //vez recebe o jogador que jogou a primeira peca
	
	//O vetor estrutura mesa e atualizada recebendo a primeira peca
	mesa[0].ladoE = pecas[pj].lado1; 
	mesa[0].ladoD = pecas[pj].lado2;
	mesaE = mesa[0].ladoE;
	mesaD = mesa[0].ladoD;
	
	qtmesa++; //qtmesa recebe mais 1 para indicar nova peca na mesa
	pecas[pj].status = 'M'; //a peca jogada recebe o status de que esta na mesa
}
	
void iniciarjogo() 
{
	int k;
	
	for(k=0; k<7; k++)
	{
		pecas[k].status = '1';	//pecas jogador 1
	}
	for(k=7; k<14; k++)
	{
		pecas[k].status = '2';	//pecas jogador 2
	}
	for(k=14; k<28; k++)
	{
		pecas[k].status = '0';	//pecas no deposito
	}
	
	PrimeiraPeca(); //Encontra a primeira peca do jogo
	
	jogador = vez = (vez=='1') ? '2':'1'; //troca o jogador que jogou a peca
	//Apresenta a mensagem identificando quem jogou a primeira peca
	if (jogador=='2')
		apresentaMensagem("O jogador 1 realizou a primeira jogada!");
	else
		apresentaMensagem("O jogador 2 realizou a primeira jogada!");
}

int qtdPecasJg(char jogador) //Encontra quantas pecas um determinado jogador tem
{
	int cont=0;
	for(int k=0; k<28 ; k++)
	{
		if(pecas[k].status==jogador) // Se a peca em que o cursor k esta for do jogador cont recebe +1 para sinalizar que ha uma peca do jogador
			{
			cont++;
			}
	}
	return cont;
}

char PecaValida(int pj) //Indica se a peca e ou nao valida para ser jogada
{
	int possivel = 0; 
	char lado = '0'; //lado recebe 0 para indicar que se nao houver como jogar em lado nenhum depois dos testes, a peca e invalida para mesa
	
	if(pecas[pj].lado1 == mesaD || pecas[pj].lado2 == mesaD) //Verifica se e possivel jogar no lado direito
		{
			lado = 'D'; //lado recebe d para indicar que e possivel jogar no lado direito
			possivel++; //possivel recebe +1 para indicar que ha +1 possibilidade
			
		}
		
	if(pecas[pj].lado2 == mesaE || pecas[pj].lado1 == mesaE)
		{
			lado = 'E';	  //lado recebe E para indicar que e possivel jogar no lado esquerdo
			possivel++;  //possivel recebe +1 para indicar que ha +1 possibilidade
			
		}
	
	if(possivel==2) //Se houver 2 possibilidades de jogo lado recebe A para indicar que em ambos os lados pode haver jogada
		{
			lado = 'A';
			
		}
	
	return lado; //retorna lado
}

void JogadaEsq(int pj) //Realiza a jogada na esquerda da mesa
{
	
	for(int i = qtmesa; i > 0; i--) //Joga a mesa para direita
		mesa[i] = mesa[i-1];
	
	if (pecas[pj].lado2 == mesaE) //Se for possivel jogar diretamente 
		{//Atualiza o vetor mesa
		mesa[0].ladoE = pecas[pj].lado1;
		mesa[0].ladoD = pecas[pj].lado2;
		}
	
	else //Se nao for joga a peca invertida
		{//Atualiza o vetor mesa
		mesa[0].ladoE = pecas[pj].lado2;
		mesa[0].ladoD = pecas[pj].lado1;
		}

	mesaE = mesa[0].ladoE; //atualiza a variavel mesaE que armazena o lado extremo Esquerdo da mesa
	qtmesa++; //qtmesa recebe +1 para indicar nova peca na mesa
	pecas[pj].status = 'M'; //atualiza o status da mesa
}

void JogadaDir(int pj) //Realiza a jogada na direita da mesa
{
	
	
	if (pecas[pj].lado1 == mesaD) //Se for possivel jogar diretamente 
		{//Atualiza o vetor mesa
		mesa[qtmesa].ladoE = pecas[pj].lado1;
		mesa[qtmesa].ladoD = pecas[pj].lado2;
		}
	
	else //Se nao for joga a peca invertida
		{//Atualiza o vetor mesa
		mesa[qtmesa].ladoE = pecas[pj].lado2;
		mesa[qtmesa].ladoD = pecas[pj].lado1;
		}

	mesaD = mesa[qtmesa].ladoD; //atualiza a variavel mesaD que armazena o lado extremo Direito da mesa
	qtmesa++; //qtmesa recebe +1 para indicar nova peca na mesa
	pecas[pj].status = 'M'; //atualiza o status da mesa
}

booleano depositoVazio() //se o deposito de pecas estiver vazio retorna TRUE
{
	for(int i = 0; i < 28; i++)
		{
		if (pecas[i].status == '0')
		return FALSE;
		}
		
	return TRUE;
}	

booleano comprar(char jogador) //Se for possivel comprar adiciona uma peca a um jogador especifico e retorna TRUE
{
	int i = 14; 
	
	while(i < 28) //Se houver peca disponivel a adiciona na mao do jogador
	{
	if (pecas[i].status == '0')
		{
		pecas[i].status = jogador;
		return TRUE;
		}
	i++;
	}
	
	if (i >= 28) //Se nao, apresenta a mensagem de erro
		{
		system("cls");
		apresentaMensagem("\nO deposito esta vazio. Tente jogar ou passe a vez se nao for possivel.");
		return FALSE;
		}
}

booleano passar() //Passa a vez do jogador caso nao haja pecas para comprar e jogar 
{
	if (depositoVazio()==FALSE || PossivelJogar()==TRUE) 
		{
		system("cls");
		apresentaMensagem("\nPassagem bloqueada. Voce ainda pode jogar e/ou comprar");
		return FALSE;
		}

	else
		{
		jogador = vez = (vez=='1') ? '2':'1';
		return TRUE;
		}
}

booleano PossivelJogar() //Verifica se o jogador em questao possui alguma peca jogavel retornando TRUE se sim
{
	int jogavel=0;
	for(int k=0; k<28 ; k++)
	{
		if(pecas[k].status==jogador)
			if(PecaValida(k)!='0')
				jogavel++; //Le todas as pecas de um jogador e verifica se elas sao jogaveis adicionando +1 em jogavel se positivo
	}
	
	if(jogavel!=0)
		return TRUE; 
	
	else
		return FALSE;
}

void ftempo(int seg) //Adiciona delay 
{
	time_t lt1, lt2;
	lt1 = time(NULL);
	lt2 = lt1;
	
	while(difftime(lt2, lt1) < seg)
		lt2 = time(NULL);
}

void MenuPrin() //Apresenta o menu principal
{
	int op; //Inicia a variavel que recebe a opcao do menu
	
	do
	{
		op=Txtmenuprin(); //Apresenta o texto do menu e recebe a opcao do operador
		
		switch(op)
			{
				case 0: //Para 0, o programa e finalizado
					break;
				
				case 1: //Para 1, o programa inicia o jogo com 2 jogadores
					system("cls");
					qtmesa=0; //Zera a quantidade de pecas na mesa para comecar um novo jogo
					jogcomp=0; //Define como zero para indicar que o computador nao esta jogando 
					embaralhaPecas(); //Embaralha as pecas de novo para um proximo jogo
					iniciarjogo(); //Inicia o jogo distribuindo as pecas entre os jogadores e jogando a primeira peca
					MenuDeJogo();
					break;
				
				case 2: //Para 2, o programa inicia o jogo com 1 jogador
					system("cls");
					qtmesa=0;//Zera a quantidade de pecas na mesa para comecar um novo jogo
					embaralhaPecas(); //Embaralha as pecas de novo para um proximo jogo
					jogcomp=2;//Define como 2 para indicar que o computador esta jogando
					iniciarjogo(); //Inicia o jogo distribuindo as pecas entre os jogadores e jogando a primeira peca
					MenuDeJogo();
					break;
				
				case 3: //Para 3, retorna ao jogo atual
					system("cls");
					if(qtmesa!=0)
						MenuDeJogo();
					else
						apresentaMensagem("Nenhum jogo foi iniciado.");
					break;
				
				case 4:  //Para 4, recupera os dados de um jogo anterior
					system("cls");
					recuperaCadastro();
					MenuDeJogo();
					break;
				
				case 5: //Para 5, Salva o jogo atual
					gravaCadastro();
					break;
					
				case 6:  //Para 6, mostra as regras do jogo
					regrasdojogo();
					break;
					
				default: //Caso a opcao seja diferente de um numero valido apresenta a mensagem de erro
					system("cls");
					apresentaMensagem("Digito invalido, tente um entre 0 e 6.");	
					break;
			}
	}while(op!=0); //Se a opcao for 0 fecha o programa
}

void MenuDeJogo() //inicia o menu de jogo
{
	int pj;
	int verifdelay=0; //Inicia a variavel que controlara a mensagem que indica quem e o jogador e o delay entre o aparecimento das pecas. Para 0 a mensagem e apresentada com delay, para 1, a mensagem e apresentada sem delay
	int opdojogo; //Inicia a variavel que armazena a opcao do operador
		
	do
	{
		Mesa(); //Apresenta a mesa
		
		if(jogcomp==2 && jogador=='2') //Se o computador estiver jogando e for sua vez
			{
			JogadaComp(); //Inicia a jogada do computador
			if(Fimdejogo(jogador, passou2vez)==TRUE) //Se apos a passagem passou2vez atingir 2, isso indicara que nenhum jogador pode jogar, assim o jogo estara terminado
				{
				ftempo(5);
				qtmesa=0; //Apaga as pecas da funcao mesa para o vetor ser reconstruido em novo jogo
				embaralhaPecas(); //Embaralha as pecas para comecar o jogo novamente
				break;
				}
			continue; //Caso a vez nao tenha sido trocada na funcao anterior este trecho entra em loop ate o computador jogar ou passar
			}
		
		if(verifdelay==0) //Se for 0, apresenta a mensagem com delay
			MSGdelay(jogador); //Apresenta a mensagem de quem esta jogado
			
		opdojogo=Txtmenudojogo(jogador); //Apresenta as opcoes do jogo e recebe a opcao do operador
		
		switch(opdojogo)
			{
				case 0: //Para 0, sai do jogo
					break; 
				
				case 1: //Para 1, inicia a jogada de uma peca
					
					if(PossivelJogar()==FALSE) //Se o operador nao tiver pecas validas para jogar, impede que ele jogue para reduzir o tempo escolhendo pecas invalidas
						{
						system("cls");
						apresentaMensagem("Voce nao tem pecas disponiveis para jogar. Tente comprar!");
						verifdelay=1; //Apresenta a mensagem de quem vai jogar sem delay
						continue; //Retorna ao menu de jogo para o usuario comprar ou passar a vez
						}
					
					pj = Jogar(jogador); //Inicia a funcao que coleta o indice da peca a ser jogada
					
					if(pj==99) //se pj for = 99, foi definido que isso representa que o jogador desistiu da jogada
						{
						verifdelay=1; //Nao apresenta delay pois o jogador nao sera trocado
						system("cls"); 
						break; //Fim da opcao 1 para que o jogador selecione outra opcao
						}
					
					if(PecaValida(pj)=='A') //Se a peca valida for = A,ou seja, pode ser jogada em qualquer lado permite que o jogador escolha o lado da jogada
						{
						if(escolherLado()=='E')
							{
							JogadaEsq(pj);
							verifdelay=0; //Agora apresenta delay pois havera troca de jogadores
							}
							
						else
							{
							JogadaDir(pj);
							verifdelay=0;
							}
						}
					
					else //Se a peca valida so puder ser jogada em apenas um lado realiza a jogada automaticamente
						{
							if(PecaValida(pj)=='E')
								{
								JogadaEsq(pj);
								verifdelay=0; //Agora apresenta delay pois havera troca de jogadores
								}
							else
								{
								JogadaDir(pj);
								verifdelay=0; //Agora apresenta delay pois havera troca de jogadores
								}	
						}
						
					if(Fimdejogo(jogador, passou2vez)==TRUE) //Verifica se o jogo Terminou (no caso de todas as pecas terem sido jogadas). Apresentando mensagem caso haja vitoria
						{
						ftempo(5);
						opdojogo=0; //Fecha o menu de jogo
						qtmesa=0; //Apaga as pecas da funcao mesa para o vetor ser reconstruido em novo jogo
						embaralhaPecas(); //Embaralha as pecas de novo para um proximo jogo
						break;
						}	
						
					passou2vez=0; //Zera a sentinela passou2vez para indicar que um dos jogadores ainda pode jogar
					system("cls");
					
					if(qtcompra!=0)
						qtpecacomprada(); //Se o jogador tiver comprado pecas, apresenta que a quantidade de pecas compradas depois da jogada
						
			
					qtcompra=0; //Zera a quantidade de pecas compradas para que o contador reinicie para o proximo jogador
					jogador = vez = (vez=='1') ? '2':'1'; //Troca de jogador ao terminar a jogada 
					break; //finaliza o caso 1
				
				case 2: //Para 2, inicia a opcao de compra
					if(comprar(jogador)==TRUE) //Efetua a compra de uma peca se possivel
					{
					verifdelay=1; //Agora apresenta delay pois havera troca de jogadores
					qtcompra++;	//qtcompra recebe +1 indicando peca comprada
					system("cls");
					}	
					else //Se nao for possivel comprar nao apresenta delay e mostra uma mensagem de erro ao jogador
					{
						verifdelay=1;
					}	
		
					break;//Finaliza o caso 2
					
				case 3: //Para 3, inicia a opcao de passar a vez
					if(passar()==TRUE) //Se for possivel passar
						{
						passou2vez++; //Adiciona 1 a passou2vez para indicar que houve uma passagem
						system("cls");
						verifdelay=0; //Agora apresenta delay pois havera troca de jogadores
						jogador = vez = (vez=='1') ? '2':'1'; //Troca de jogador para apresentar a mensagem corretamente
						Passou(); //Apos a passagem, apresenta que o jogador passou sua vez
						jogador = vez = (vez=='1') ? '2':'1'; //Troca de jogador para finalizar a passagem
						}	
						
					else //Se nao fro possivel passar apresenta mensagem de erro ao jogador e nao troca de vez
					{
					verifdelay = 1;
					}
					
					if(Fimdejogo(jogador, passou2vez)==TRUE) //Se apos a passagem passou2vez atingir 2, isso indicara que nenhum jogador pode jogar, assim o jogo estara terminado
						{
						ftempo(5);
						opdojogo=0; //Fecha o menu de jogo
						qtmesa=0; //Apaga as pecas da funcao mesa para o vetor ser reconstruido em novo jogo
						embaralhaPecas(); //Embaralha as pecas para comecar o jogo novamente
						break;
						}
						
					if(qtcompra!=0)
						qtpecacomprada(); //Se o jogador tiver comprado pecas, apresenta que a quantidade de pecas compradas depois da jogada
					
					qtcompra=0;//Zera a quantidade de pecas compradas para que o contador reinicie para o proximo jogador
					
					break; //Finaliza o caso 3
					
				default: //Caso a opcao seja diferente de um numero valido apresenta a mensagem de erro
					system("cls");
					apresentaMensagem("Digito invalido, tente um entre 0 e 3.");
					verifdelay = 1;
					break;
			}
	}while(opdojogo!=0);
}

void JogadaComp() //Realiza a jogada do computador
{
	int pj; //Armazena o indice da peca jogada pelo computador
	int s; //Armazena um valor aleatorio entre 0 e 1 para selecionar a jogada na esquerda ou direita
	char lado; //Recolhe o lado onde e possivel jogar
	int lateral; //Recolhe o indice da peca jogada  
	
		if(PossivelJogar()==TRUE) //Se o computador puder jogar
			{
			pj = Jogar(jogador); //pj recolhe o indice da peca
			
			lado=PecaValida(pj); //Lado recebe onde é possivel jogar
			
			if(lado=='E') //Se for na esquerda joga na esquerda
			{
			JogadaEsq(pj);
			lateral=0;
			}
				
			
			else if(lado=='D') //Se for na direita joga na direita
			{
			JogadaDir(pj);	
			lateral=qtmesa;
			--lateral;
			}
				
				
			else if(lado=='A') //Se for em ambos os lados
			{
				srand(time(NULL));
				s=rand()%2; //Calcula um numero aleatorio entre 0 e 1 para escolher entre direita e esquerda
				if(s==0) //Se for 0 joga na esquerda
				{
					JogadaEsq(pj);
					lateral=0; //lateral recebe zero para indicar que a peca foi jogada na esquerda (recebe indice 0)
				}
					
				else //Se for 1 joga na direita
				{
					JogadaDir(pj);
					lateral=qtmesa; //Lateral recebe indice qtmesa-1 para indicar que a peca foi jogada na direita
					--lateral;
				}	
			}
				
			system("cls");
			pecajogada(lateral); //Apresenta qual a peca jogada utilizando lateral
			
			if(qtcompra!=0) // Apresenta quantas pecas o computador comprou antes de jogar
				qtpecacomprada();
			
			qtcompra=0; //zera o contador para proxima jogada
			passou2vez=0; //Zera a sentinela passou2vez para indicar que um dos jogadores ainda pode jogar
			jogador = vez = (vez=='1') ? '2':'1'; //Troca a vez
			}
			
		else if(comprar(jogador)==TRUE) //Se nao puder jogar e puder comprar
			{
			qtcompra++;	//Adiciona +1 a qtcompra
			system("cls");	
			}
			
		else //Se nao puder comprar e jogar passa a vez
			{
			system("cls");
			
			if(qtcompra!=0)
				qtpecacomprada(); //Apresenta quantas pecas foram compradas 
			
			Passou(); //Apresenta que o computador passou
			passar(); //Passa a vez 
			qtcompra=0; //zera o contador de qtcompra para a proxima jogada
			passou2vez++; //adiciona 1 ao contador de vezes passadas para saber se o jogo terminou
			}
			
		
}

booleano Fimdejogo(char jogador, int passou2vez) //Verifica se o jogo terminou e finaliza a partida 
{
	int Jog1; //Inicia a variavel que recebe quantas pecas possui o jogador atual
	int Jog2; //Inicia a variavel que recebe quantas pecas possui o outro jogador 
	int pontosjg1=0;
	int pontosjg2=0;
	char UltimoJog=jogador;
	
	if(jogador=='1') 
		{
		Jog1 = qtdPecasJg(jogador); //recebe quantas pecas possui o jogador atual
		jogador = vez = (vez=='1') ? '2':'1'; //troca o jogador
		Jog2 = qtdPecasJg(jogador); //recebe quantas pecas possui o outro jogador 
		}
	
	else
		{
		Jog2 = qtdPecasJg(jogador); //recebe quantas pecas possui o outro jogador 
		jogador = vez = (vez=='1') ? '2':'1'; //troca o jogador
		Jog1 = qtdPecasJg(jogador); //recebe quantas pecas possui o jogador atual
		}
	
	if(Jog1==0) //Se um jogador nao tiver nenhuma peca apresenta a mensagem de vitoria desse jogador 
		{
			apresentaMensagem("FIM DE JOGO! O JOGADOR 1 VENCEU PORQUE NAO POSSUI MAIS PECAS!!!!");
			
			if(jogador=='1')
				{
				apresentaMensagem("Pecas Jogador 1: ");
				apresentaPeca(jogador);
				
				jogador = vez = (vez=='1') ? '2':'1';
				
				if(jogcomp==2)
					apresentaMensagem("\nPecas computador: ");
				
				else	
					apresentaMensagem("\nPecas Jogador 2: ");
					
				apresentaPeca(jogador);	
				}
			
			else
				{
				jogador = vez = (vez=='1') ? '2':'1';
				apresentaMensagem("Pecas Jogador 1: ");
				apresentaPeca(jogador);
				
				jogador = vez = (vez=='1') ? '2':'1';
					
				if(jogcomp==2)
					apresentaMensagem("\nPecas computador: ");
				
				else	
					apresentaMensagem("\nPecas Jogador 2: ");
					
				apresentaPeca(jogador);	
				}
			jogador=UltimoJog; //Retorna ao ultimo jogador do jogo
			vez=UltimoJog; //Retorna ao ultimo jogador do jogo
			return TRUE;	
		}
				
	else if(Jog2==0)
			{
			if(jogcomp==2)
				apresentaMensagem("FIM DE JOGO! O COMPUTADOR VENCEU PORQUE NAO POSSUI MAIS PECAS!!!!");	
				
			else
				apresentaMensagem("FIM DE JOGO! O JOGADOR 2 VENCEU PORQUE NAO POSSUI MAIS PECAS!!!!");
				
			if(jogador=='2')
				{
				if(jogcomp==2)
					apresentaMensagem("\nPecas computador: ");
				
				else	
					apresentaMensagem("\nPecas Jogador 2: ");
					
				apresentaPeca(jogador);	
				
				jogador = vez = (vez=='1') ? '2':'1';
					
				apresentaMensagem("\nPecas Jogador 1: ");
				apresentaPeca(jogador);	
				}
			
			else
				{
				jogador = vez = (vez=='1') ? '2':'1';
				if(jogcomp==2)
					apresentaMensagem("\nPecas computador: ");
				
				else	
					apresentaMensagem("\nPecas Jogador 2: ");
					
				apresentaPeca(jogador);	
				
				jogador = vez = (vez=='1') ? '2':'1';
					
				apresentaMensagem("\nPecas Jogador 1: ");
				apresentaPeca(jogador);
				}
			jogador=UltimoJog; //Retorna ao ultimo jogador do jogo
			vez=UltimoJog; //Retorna ao ultimo jogador do jogo
			return TRUE;
			}
				
		 //retorna verdadeiro se acabou o jogo
		
	else if (passou2vez==2) //Verifica se o jogo foi passado 2 vezes 
		{
			if(Jog1>Jog2) //Se o jogador 1 tiver mais pecas que o outro, o jogador 2 ganhou o jogo. Senao, entao o jogador 1 venceu
				{ 	
				if(jogcomp==2)
					apresentaMensagem("FIM DE JOGO! O COMPUTADOR VENCEU PORQUE POSSUI MENOS PECAS !!!!\n");
				
				else
					apresentaMensagem("FIM DE JOGO! O JOGADOR 2 VENCEU PORQUE POSSUI MENOS PECAS !!!!\n");
				
				if(jogador == '2')
					{	
					if(jogcomp==2)
						apresentaMensagem("\nPecas computador: ");
				
					else	
						apresentaMensagem("\nPecas Jogador 2: ");
					
					apresentaPeca(jogador);	
					
					jogador = vez = (vez=='1') ? '2':'1';
					
					apresentaMensagem("\nPecas Jogador 1: ");
					apresentaPeca(jogador);
					}
					
				else 
					{
					jogador = vez = (vez=='1') ? '2':'1';
					if(jogcomp==2)
						apresentaMensagem("\nPecas computador: ");
				
					else	
						apresentaMensagem("\nPecas Jogador 2: ");
					
					apresentaPeca(jogador);	
					
					jogador = vez = (vez=='1') ? '2':'1';
					
					apresentaMensagem("\nPecas Jogador 1: ");
					apresentaPeca(jogador);
					}
				}
			
			
			else if(Jog2>Jog1) //Se o jogador 1 tiver mais pecas que o outro, o jogador 2 ganhou o jogo. Senao, entao o jogador 1 venceu
				{
					apresentaMensagem("FIM DE JOGO! O JOGADOR 1 VENCEU PORQUE POSSUI MENOS PECAS !!!!\n");
					
					if(jogador=='1')
						{	
						apresentaMensagem("Pecas Jogador 1: ");
						apresentaPeca(jogador);
				
						jogador = vez = (vez=='1') ? '2':'1';
					
						if(jogcomp==2)
							apresentaMensagem("\nPecas computador: ");
				
						else	
							apresentaMensagem("\nPecas Jogador 2: ");
					
						apresentaPeca(jogador);		
						}
			
					else
						{
						jogador = vez = (vez=='1') ? '2':'1';
						apresentaMensagem("Pecas Jogador 1: ");
						apresentaPeca(jogador);
				
						jogador = vez = (vez=='1') ? '2':'1';
					
						if(jogcomp==2)
							apresentaMensagem("\nPecas computador: ");
				
						else	
							apresentaMensagem("\nPecas Jogador 2: ");
					
						apresentaPeca(jogador);	
						}
					
				}
	
			else if(Jog1==Jog2) //Se os jogadores tiverem a mesma quantidade de pecas vencera o que tiver menos pontos
				{
				for(int k=0; k<28; k++)
					{
						if(pecas[k].status=='1') //Coleta a quantidade de pontos dos lados das pecas do jogador 1
							pontosjg1 = pontosjg1 + pecas[k].lado1 + pecas[k].lado2;
								
						else if(pecas[k].status=='2') //Coleta a quantidade de pontos dos lados das pecas do jogador 2
							pontosjg2 = pontosjg2 + pecas[k].lado1 + pecas[k].lado2;
					}
					
				if(pontosjg1>pontosjg2)
					{
						if(jogcomp==2)
							apresentaMensagem("FIM DE JOGO! O COMPUTADOR VENCEU PORQUE POSSUI MENOS PONTOS");
						
						else
							apresentaMensagem("FIM DE JOGO! O JOGADOR 2 VENCEU PORQUE POSSUI MENOS PONTOS");
					
						if(jogador == '2')
							{	
							if(jogcomp==2)
								apresentaMensagem("\nPecas computador: ");
				
							else	
								apresentaMensagem("\nPecas Jogador 2: ");
					
							apresentaPeca(jogador);	
					
							jogador = vez = (vez=='1') ? '2':'1';
					
							apresentaMensagem("\nPecas Jogador 1: ");
							apresentaPeca(jogador);
							}
					
						else 
							{
							jogador = vez = (vez=='1') ? '2':'1';
							if(jogcomp==2)
								apresentaMensagem("\nPecas computador: ");
				
							else	
								apresentaMensagem("\nPecas Jogador 2: ");
					
							apresentaPeca(jogador);	
					
							jogador = vez = (vez=='1') ? '2':'1';
					
							apresentaMensagem("\nPecas Jogador 1: ");
							apresentaPeca(jogador);
							}
					}
				
				else
					{ 
						apresentaMensagem("FIM DE JOGO! O JOGADOR 1 VENCEU PORQUE POSSUI MENOS PONTOS");
					
						if(jogador == '1')
							{
								apresentaMensagem("Pecas Jogador 1: ");
								apresentaPeca(jogador);
							
								jogador = vez = (vez=='1') ? '2':'1';
						
								if(jogcomp==2)
									apresentaMensagem("\nPecas computador: ");
				
								else	
									apresentaMensagem("\nPecas Jogador 2: ");
					
								apresentaPeca(jogador);	
							}
					
							else
								{
								jogador = vez = (vez=='1') ? '2':'1';
								apresentaMensagem("Pecas Jogador 1: ");
								apresentaPeca(jogador);
							
								jogador = vez = (vez=='1') ? '2':'1';
					
								if(jogcomp==2)
									apresentaMensagem("\nPecas computador: ");
				
								else	
									apresentaMensagem("\nPecas Jogador 2: ");
					
								apresentaPeca(jogador);	
								}
					}
				}
		jogador=UltimoJog; //Retorna ao ultimo jogador do jogo
		vez=UltimoJog; //Retorna ao ultimo jogador do jogo
		return TRUE; //retorna verdadeiro se acabou o jogo
		}
	jogador=UltimoJog; //Retorna ao ultimo jogador do jogo
	vez=UltimoJog;	//Retorna ao ultimo jogador do jogo
	return FALSE;  //retorna falso se o jogo nao acabou
}

void fclear() //limpa o buffer do teclado
{
	int ch;
	while( (ch = fgetc(stdin)) != EOF && ch != '\n');
}

void gravaCadastro() //Salva os arquivos do jogo atual
{
    if(qtmesa == 0) //Se o jogo nao tiver comecado
   		{
        apresentaMensagem("Sem jogo a ser gravado");
        return;
    	}
    if(Fimdejogo(jogador, passou2vez) == TRUE) //Se o jogo tiver terminado
    	{
        apresentaMensagem("Jogo terminado nao pode ser gravado");
        return;
        }
        
    int i; 
    FILE *fp; //Inicia o arquivo que armazena as pecas
    FILE *fpm; //Inicia o arquivo que armazena a mesa
    FILE *fps; //Inicia o arquivo que armazena os dados do jogo
 
    //dados do Jogo a ser salvo
    sitJogo.qtmesaJogo = qtmesa;
    sitJogo.jogadorJogo = jogador;
    sitJogo.mesaDJogo = mesaD;
    sitJogo.mesaEJogo = mesaE;
    sitJogo.passoudevez = passou2vez;
    sitJogo.vezD = vez;
    sitJogo.jogadorComp = jogcomp; 
    sitJogo.qtdcomprada = qtcompra;
    
	//Evita que haja erros na abertura dos arquivos de salvamento    
    if((fp = fopen("CAD_DOMINO", "w")) == NULL)
        {
        apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto para cadastrar");
        return;
        }
        
    if((fpm = fopen("CAD_MESA", "w")) == NULL)
        {
        apresentaMensagem("O arquivo CAD_MESA nao pode ser aberto para cadastrar");
        return;
        }
        
    if((fps = fopen("CAD_JOGO", "w")) == NULL)
        {
        apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto para cadastrar");
        return;
        }
 	//Coleta os dados da mesa, das pecas e do jogo e os armazena em seus respectivos arquivos
    for(i = 0; i < 28; i++)
        {
		if(fwrite(&pecas[i], sizeof(struct Peca), 1, fp) != 1)
        	{
            apresentaMensagem("Erro na gravacao do arquivo CAD_DOMINO");
			break;
            }
        }
        
    for (i = 0; i < 28; i++)
        {
        if (fwrite(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
            {
			apresentaMensagem("Erro na gravacao do arquivo CAD_MESA");
			break;
           	}
        }
        
    if(fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
        apresentaMensagem("Erro na gravacao do arquivo CAD_JOGO");
    
	//Fecha os arquivos        
    fclose(fps); 
    fclose(fpm);
    fclose(fp);
    //Apresenta mensagem de sucesso indicando arquivo salvo com sucesso
    apresentaMensagem("Gravados os arquivos CAD_DOMINO, CAD_MESA e CAD_JOGO");
}  

void recuperaCadastro() //Recupera os arquivos de um jogo anterior
{
    int i;
    FILE *fp;
    FILE *fpm;
    FILE *fps;
 	
 	//Evita que haja erros na abertura dos arquivos de salvamento 
    if((fp = fopen("CAD_DOMINO", "r")) == NULL)
    	{
        apresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto");
        return;
        }
        
    if((fpm = fopen("CAD_MESA", "r")) == NULL)
        {
        apresentaMensagem("O arquivo CAD_MESA nao pode ser aberto");
        return;
        }
        
    if((fps = fopen("CAD_JOGO", "r")) == NULL)
        {
        apresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto");
        return;
        }
        
    //Realiza a leitura dos arquivos de armazenamento da mesa, pecas dos dados de jogo    
    for(i = 0; i < 28; i++)
        {
        if(fread(&pecas[i], sizeof(struct Peca), 1, fp) != 1)
            {
            apresentaMensagem("Erro na leitura do arquivo CAD_DOMINO");
            break;
            }
        }
        
    for(i = 0; i < 28; i++)
        {
        if(fread(&mesa[i], sizeof(struct Mesa), 1, fpm) != 1)
            {
            apresentaMensagem("Erro na leitura do arquivo CAD_MESA");
            break;
            }
        }
        
    if(fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1) 
        apresentaMensagem("Erro na leitura do arquivo CAD_JOGO");
    
	//Fecha os arquivos de salvamento       
    fclose(fps);
    fclose(fpm);
    fclose(fp);
        
    //Recolhe os dados do jogo anterior e os atribui as respectivas variaveis
    qtmesa = sitJogo.qtmesaJogo;
    jogador = sitJogo.jogadorJogo;
    mesaD = sitJogo.mesaDJogo;
    mesaE = sitJogo.mesaEJogo;
    passou2vez = sitJogo.passoudevez;
    vez =  sitJogo.vezD; 
    jogcomp = sitJogo.jogadorComp;
    qtcompra = sitJogo.qtdcomprada;
    
    //Apresenta mensagem de sucesso na recuperacao do jogo
    apresentaMensagem("Retornando ao jogo recuperado");
 
}


