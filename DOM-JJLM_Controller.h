//DOM-JJLM - Projeto Domino - Etapa 6
//23/09/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo

void criarPecas(); //Cria as pecas do jogo
void embaralhaPecas(); //Embaralha as pecas do jogo
void executajogo(); //Inicia o jogo
void iniciarjogo(); //Distribui as pecas entre os jogadores
void PrimeiraPeca(); //seleciona a primeira peca a ser jogada automaticamente
int qtdPecasJg(char jogador); //verifica quantas pecas tem um jogador
char PecaValida(int pj); //verifica se a peca e valida
void JogadaEsq(int pj); //Joga a peca na esquerda
void JogadaDir(int pj); //joga a peca na direita
booleano comprar(char jogador); //compra uma peca para um jogador
booleano depositoVazio(); //verifica se o deposito de pecas esta vazio
booleano passar(); //Passa o jogo se possivel
booleano PossivelJogar(); //Verifica se o jogador em questao tem pecas validas
void ftempo(int seg); //adiciona delay
void MenuPrin(); //comanda o menu principal
void MenuDeJogo(); //Comanda o submenu
void JogadaComp(); //Realiza a jogada do computador
booleano Fimdejogo(char jogador, int passou2vez); //Finaliza o jogo
void fclear(); //limpa o buffer do teclado
void gravaCadastro(); //Salva o jogo atual
void recuperaCadastro(); //Recupera um jogo anterior
