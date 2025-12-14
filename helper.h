#pragma once

#include <windows.h>

#define ID_Imprimir 3
#define ID_Arquivo 4
#define ID_Impressora 5
#define ID_MetodoImpressao 6
#define ID_VisualizarFila 7
#define ID_Sair 8
#define ID_SubmitArquivo 9
#define ID_Edit 2

#define ID_Titulo -1
#define ID_Texto -2

void mudaFonte(HWND janela, HFONT fonte);

HWND criarJanela(char* classe, char* titulo, int largura, int altura, HWND janelaPai, HINSTANCE hInstance);

HWND criarBotao(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarText(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarInput(HWND janela, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

#define NORMAL 400
#define BOLD 700

HFONT criarFonte(int tamanho, int peso, char* fonte);