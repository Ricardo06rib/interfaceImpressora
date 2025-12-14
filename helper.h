#pragma once

#include <windows.h>

//formatacao
#define ID_Texto -2
#define ID_Titulo -1

//input
#define ID_Edit 0

//comandos botoes principais
#define ID_Imprimir 1
#define ID_VisualizarFila 2
#define ID_Arquivo 3
#define ID_Impressora 4
#define ID_MetodoImpressao 5
#define ID_Sair 6
#define ID_remover 7

//botoes derivados de janelaArquivo
#define ID_SubmitArquivo 30

//botoes derivados de janelaImpressora
#define ID_SubmitImpressora 40

//fontes
#define NORMAL 400
#define BOLD 700

void mudaFonte(HWND janela, HFONT fonte);

HWND criarJanela(char* classe, char* titulo, int largura, int altura, HWND janelaPai, HINSTANCE hInstance);

HWND criarBotao(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarText(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarInput(HWND janela, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);


HFONT criarFonte(int tamanho, int peso, char* fonte);
