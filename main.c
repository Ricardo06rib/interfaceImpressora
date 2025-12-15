#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>

#include "headers/helper.h"
#include "headers/lista.h"
#include "headers/printer.h"

//modo de impressão
int impressao = 0;
//0-> frente para tras
//1-> tras para frente

//cor
HBRUSH hbrBackground = NULL;

//janela Principal
HWND hwnd;
HWND hTextoFixo;
HWND hBtnImprimir;
HWND hBtnArquivo;
HWND hBtnArquivoRemover;
HWND hBtnMetodo;
HWND hBtnFila;
HWND hBtnSair;

//janela metodo de impressao
HWND janelaMetodo;
HWND botao1Metodo;
HWND botao2Metodo;

ListaDupla *lista = NULL;
HWND hEditArquivo = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {

    case WM_CREATE:
        lista = criar_lista();

        hTextoFixo = criarText(hwnd, "Software de Impressao", 220, 40, 600, 100, ID_Titulo, NULL);
        mudaFonte(hTextoFixo, criarFonte(40, 1700, "Arial"));

        hBtnImprimir = criarBotao(hwnd, "Imprimir", 50, 120, 800, 90, ID_Imprimir,  NULL);

        hBtnArquivo = criarBotao(hwnd, "Adicionar arquivo", 50, 230, 390, 90, ID_Arquivo,  NULL);

        hBtnArquivoRemover = criarBotao(hwnd, "Remover arquivo", 460, 230, 390, 90, ID_remover, NULL);

        hBtnMetodo = criarBotao(hwnd, "Escolher metodo de impressao", 460, 340, 390, 90, ID_MetodoImpressao,  NULL);

        hBtnFila = criarBotao(hwnd, "Visualizar fila de impressao", 50, 340, 390, 90, ID_VisualizarFila,  NULL);

        hBtnSair = criarBotao(hwnd, "Sair", 50, 450, 800, 90, ID_Sair,  NULL);

        break;

    case WM_COMMAND:
    {

        switch (LOWORD(wParam))
        {
        case ID_Arquivo:
        {
            if(lista == NULL) lista = criar_lista();

            char caminho[MAX_PATH];

            if(!abrirExplorer(hwnd, caminho, MAX_PATH)){
                break;}

            if (strlen(caminho) == 0)
            {
                MessageBoxA(hwnd, "Informe o caminho do arquivo.", "Erro", MB_ICONERROR);
                break;
            }

            if (GetFileAttributesA(caminho) == INVALID_FILE_ATTRIBUTES)//ver isso dps
            {
                MessageBoxA(hwnd, "Arquivo nao encontrado.", "Erro", MB_ICONERROR);
                break;
            }

            inserir_fim(lista, caminho);
            MessageBoxA(hwnd, "Arquivo adicionado a fila.", "Fila", MB_OK);
            SetWindowTextA(hEditArquivo, "");
            break;
        }


        case ID_ImprimirInverso:
        {
            if (esta_vazia(lista)) {
                MessageBoxA(hwnd, "Fila vazia", "Erro", MB_ICONERROR);
                break;
            }

            char impressora[256];
            DWORD tam = sizeof(impressora);

            if (!GetDefaultPrinterA(impressora, &tam)) {
                MessageBoxA(hwnd, "Nenhuma impressora padrao encontrada", "Erro", MB_ICONERROR);
                break;
            }

            impressoraTrasPFrente(lista, impressora);

            MessageBoxA(hwnd, "Impressao inversa concluida.", "OK", MB_OK);
            break;
        }

        case ID_Imprimir:
        {
            if (esta_vazia(lista)) {
            MessageBoxA(hwnd, "Fila vazia", "Erro", MB_ICONERROR);
            break;
            }

            char impressora[256];
            DWORD tam = sizeof(impressora);

            if (!GetDefaultPrinterA(impressora, &tam)) {
                MessageBoxA(hwnd, "Nenhuma impressora padrao encontrada", "Erro", MB_ICONERROR);
                break;
            }

            impressoraFrentePTras(lista, impressora);

            MessageBoxA(hwnd, "Impressao concluida.", "OK", MB_OK);
            break;
}

        case ID_VisualizarFila:
            {
            MessageBoxA(hwnd, imprimir_frente(lista), "Fila de impressao", MB_OK);
            imprimir_frente(lista);
            break;
            }

        case ID_remover:
        {
            if(esta_vazia(lista)){
                MessageBoxA(hwnd, "Fila vazia", "Item removido", MB_OK);
                break;
            }
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Ultimo arquivo removido:\n\nArquivo %s", lista->fim->arquivo);
            MessageBoxA(hwnd, buffer, "Item removido", MB_OK);
            remover_item(lista, lista->fim->arquivo);
            break;
        }

        case ID_MetodoImpressao:
            {
                ShowWindow(janelaMetodo, 1);
                break;
            }

        case ID_Sair:
            DestroyWindow(hwnd);
            break;
        }
        break;
    }


        case WM_SIZE:
        {
        RECT rc;
        GetClientRect(hwnd, &rc);

        int larguraJanela = rc.right - rc.left;
        int alturaJanela  = rc.bottom - rc.top;

        // botão ocupa 50% da largura e 10% da altura
        int larguraBotao = larguraJanela * 40/100;
        int alturaBotao  = alturaJanela * 10/100;

        int XbotaoEsq = larguraJanela * 5/100;
        int XbotaoDir = larguraJanela * 5/100 + larguraBotao + larguraJanela * 5/100;

        int Ybotao = alturaJanela * 40/100;

        int larguraTexto = 500;
        int alturaTexto = 50;


        MoveWindow(hTextoFixo,          (larguraJanela - 375) / 2,   (alturaJanela * 40/100 - alturaTexto) / 2, larguraTexto, alturaTexto, TRUE);

        MoveWindow(hBtnImprimir,        XbotaoEsq,   Ybotao + 0*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        MoveWindow(hBtnArquivo,         XbotaoDir,   Ybotao + 0*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        MoveWindow(hBtnArquivoRemover,  XbotaoEsq,   Ybotao + 1*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        MoveWindow(hBtnMetodo,          XbotaoDir,   Ybotao + 1*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        MoveWindow(hBtnFila,            XbotaoEsq,   Ybotao + 2*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        MoveWindow(hBtnSair,            XbotaoDir,   Ybotao + 2*(alturaBotao + alturaJanela * 5/100), larguraBotao, alturaBotao, TRUE);
        break;
        }


    case WM_DESTROY:
        destruir_lista(lista);
        if (hbrBackground != NULL) DeleteObject(hbrBackground);
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//WndProc da janela de seleção
LRESULT CALLBACK WndProcMetodo(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            criarText(janelaMetodo, "Escolha o metodo de impressao:", 40, 20, 500, 40, 0, NULL);
//
//            hMetodoFrente = CreateWindow(
//                "BUTTON", "Frente para Tras",
//                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
//                40, 70, 220, 40,
//                hwnd, (HMENU)ID_METODO_FRENTE, NULL, NULL);
//
//            hMetodoInverso = CreateWindow(
//                "BUTTON", "Tras para Frente",
//                WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
//                40, 120, 220, 40,
//                hwnd, (HMENU)ID_METODO_INVERSO, NULL, NULL);
//
//            // Define padrão
//            SendMessage(hMetodoFrente, BM_SETCHECK, BST_CHECKED, 0);
//            impressao = 0;
//
//            hMetodoOK = criarBotao(
//                hwnd, "OK",
//                300, 120, 120, 40,
//                ID_METODO_OK, NULL);

        break;
    }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
//                case ID_METODO_FRENTE:
//                    impressao = 0;
//                break;
//
//                case ID_METODO_INVERSO:
//                    impressao = 1;
//                break;
//
//                case ID_METODO_OK:
//                    ShowWindow(hwnd, SW_HIDE);
//                break;
            }
            break;
        }

        case WM_CLOSE:
            ShowWindow(hwnd, SW_HIDE); // não destrói, só esconde
            return 0;
        }

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"IMPRESSORA_APP";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = hbrBackground;

    WNDCLASS wcMetodo = {0};
    wcMetodo.lpfnWndProc   = WndProcMetodo;
    wcMetodo.hInstance     = hInstance;
    wcMetodo.lpszClassName = L"JANELA_METODO";
    wcMetodo.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcMetodo.hbrBackground = hbrBackground;


    RegisterClass(&wc);
    RegisterClass(&wcMetodo);
    SetProcessDPIAware();

    // Cria Janela Principal
    HWND hwnd = criarJanela("IMPRESSORA_APP", "Software de Impressão", 900, 620, NULL, hInstance);

    // Cria Janela de Escolha de Metodo
    janelaMetodo = criarJanela("JANELA_METODO", "Selecao de Metodo", 600, 220, hwnd, hInstance);
    ShowWindow(janelaMetodo, 0);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
