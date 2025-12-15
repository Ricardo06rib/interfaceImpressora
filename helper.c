#include "headers/helper.h"
#include <windows.h>

void mudaFonte(HWND janela, HFONT fonte) {
    SendMessage(janela, WM_SETFONT, (WPARAM)fonte, TRUE);
}

HWND criarJanela(char* classe, char* titulo, int largura, int altura, HWND pai, HINSTANCE h) {
    HWND w = CreateWindow(
        classe, titulo,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        largura, altura,
        pai, NULL, h, NULL
    );
    return w;
}

HWND criarBotao(HWND j, char* t, int x, int y, int w, int h, int id, HINSTANCE i) {
    HWND b = CreateWindow("BUTTON", t, WS_CHILD|WS_VISIBLE,
        x,y,w,h,j,(HMENU)id,i,NULL);
    mudaFonte(b, criarFonte(20, NORMAL, "Arial"));
    return b;
}

HWND criarText(HWND j, char* t, int x, int y, int w, int h, int id, HINSTANCE i) {
    HWND s = CreateWindow("STATIC", t, WS_CHILD|WS_VISIBLE,
        x,y,w,h,j,(HMENU)id,i,NULL);
    mudaFonte(s, criarFonte(id==ID_Titulo?40:20, id==ID_Titulo?BOLD:NORMAL, "Arial"));
    return s;
}

HWND criarInput(HWND j, int x, int y, int w, int h, int id, HINSTANCE i) {
    HWND e = CreateWindow(
                        "EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,
        x,y,w,h,j,(HMENU)id,i,NULL);
    mudaFonte(e, criarFonte(20,NORMAL,"Arial"));
    return e;
}

HFONT criarFonte(int t, int p, char* f) {
    return CreateFont(t,0,0,0,p,0,0,0,DEFAULT_CHARSET,0,0,0,0,f);
}

int abrirExplorer(HWND hwnd, char *caminho, DWORD tamanho) {

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn,sizeof(ofn));

    caminho[0] = '\0';

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = caminho;
    ofn.nMaxFile = tamanho;
    ofn.lpstrFilter =
        ".pdf";


    ofn.nFilterIndex = 1;
    ofn.Flags =
        OFN_PATHMUSTEXIST  |
        OFN_FILEMUSTEXIST  |
        OFN_EXPLORER;

return GetOpenFileNameA(&ofn);
}


