#include "helper.h"

void mudaFonte(HWND janela, HFONT fonte) {
    if (janela != NULL && fonte != NULL) {
        SendMessage(janela, WM_SETFONT, (WPARAM)fonte, TRUE);
    }
}

HWND criarJanela(char* classe, char* titulo, int largura, int altura, HWND janelaPai, HINSTANCE hInstance) {
    HWND temp = CreateWindow(
        classe, titulo,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, largura, altura,
        janelaPai, NULL, hInstance, NULL
    );

    if(janelaPai != NULL) ShowWindow(temp, 0);

    return temp;
}

HWND criarBotao(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance) {
    HWND temp = CreateWindow(
        "BUTTON", texto,
        WS_VISIBLE | WS_CHILD,
        x, y, largura, altura,
        janela, (HMENU)ID, hInstance, NULL
    );
    mudaFonte(temp, criarFonte(24, NORMAL, "Arial"));

    return temp;
}

HWND criarText(HWND janela, char* texto, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance) {
    HWND temp = CreateWindow(
        "STATIC", texto,
        WS_VISIBLE | WS_CHILD,
        x, y, largura, altura,
        janela, (HMENU)ID, hInstance, NULL
    );

    if(ID == ID_Titulo) mudaFonte(temp, criarFonte(50, BOLD, "Arial"));
    if(ID == ID_Texto) mudaFonte(temp, criarFonte(24, NORMAL, "Arial"));
    
    return temp;
}

HWND criarInput(HWND janela, int x, int y, int largura, int altura, int ID, HINSTANCE hInstance) {
    HWND temp = CreateWindow(
        "EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        x, y, largura, altura,
        janela, (HMENU)ID, hInstance, NULL
    );
    mudaFonte(temp, criarFonte(24, NORMAL, "Arial"));
    
    return temp;
}

HFONT criarFonte(int tamanho, int peso, char* fonte) {
    return CreateFont(
        tamanho, 0, 0, 0,
        peso,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        fonte
    );
}

