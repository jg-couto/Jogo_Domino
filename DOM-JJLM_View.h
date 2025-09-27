//DOM-JJLM - Projeto Domino - Etapa 6
//23/09/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo 

void apresentaMensagem(char msg[100]); //mostra uma mensagem na tela
int Txtmenuprin(); //mostra as opcoes do menu principal e captura a opcao do operador principal
void Mesa(); //apresenta a mesa
void apresentaPeca(char jogador); //apresenta as pecas de um jogador
int Txtmenudojogo(char jogador); //mostra as opcoes do menu do jogo e captura a opcao do operador principal
int Jogar(char jogador); //Captura o indice da peca a ser jogada
char escolherLado(); //Escolhe o lado da mesa onde a peca sera jogada
void MSGdelay(char jogador); //apresenta a mensagem do jogador que vai jogar
void regrasdojogo(); //apresenta as regras do jogo
void pecajogada(int d); //Apresenta a peca jogada por um jogador
void qtpecacomprada();//Apresenta quantas pecas foram compradas em uma rodada
void Passou(); //Apresenta se um jogador passou a vez
