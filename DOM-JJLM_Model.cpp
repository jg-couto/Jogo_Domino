//DOM-JJLM - Projeto Domino - Etapa 6
//23/09/2023
//Grupo: JJLM
//Luis Augusto Coelho de Souza
//Joao Guilherme Costa Couto
//Matheus Heimrath Barbosa
//Joao Alfredo 

#include "DOM-JJLM_Model.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef int booleano; 

typedef struct Peca //Inicia o novo tipo de dado Peca que será usado para armazenar as informacoes sobre todas as pecas do jogo
	{
		int lado1; //Armazena o numero de um lado da peca
		int lado2; //Armazena o numero de outro lado da peca
		char status; 
	}tipoPeca;
	
struct Mesa //inicia a estrutura mesa para reservar o lado esquerdo e direito das pecas jogadas na mesa
{
	int ladoE;
	int ladoD;
	
}mesa[28];
	
	tipoPeca pecas[28];
 	tipoPeca aux;
 	
struct Jogo
{
 int qtmesaJogo; //qtd.de pecas na mesa
 char jogadorJogo; //jogador atual
 int jogadorComp; //Sentinela que indica se o jogador 2 e o computador
 char vezD;
 int mesaDJogo; //extremidade direita da mesa
 int mesaEJogo; //extremidade esquerda da mesa
 int passoudevez; //Salva quantas vezes o jogo foi passado antes de ser fechado
 int qtdcomprada; //Salva quantas vezes compraram antes do jogo ser fechado
} sitJogo; //situacao do jogo
