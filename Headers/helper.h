#pragma once
#include <windows.h>
#include<stdio.h>

#define ID_Texto -2
#define ID_Titulo -1

#define ID_Edit 0

#define ID_Imprimir 1
#define ID_VisualizarFila 2
#define ID_Arquivo 3
#define ID_Impressora 4
#define ID_MetodoImpressao 5
#define ID_Sair 6
#define ID_ImprimirInverso 7
#define ID_remover 8

#define ID_Frente 40
#define ID_Tras 41

#define NORMAL 400
#define BOLD 700

void mudaFonte(HWND janela, HFONT fonte);

HWND criarJanela(char* classe, char* titulo, int largura, int altura, HWND janelaPai, HINSTANCE hInstance);

HWND criarBotao(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarText(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HWND criarInput(HWND janela, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance);

HFONT criarFonte(int tamanho, int peso, char* fonte);

int abrirExplorer(HWND hwnd, char *caminho, DWORD tamanho);
