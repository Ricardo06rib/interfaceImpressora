#include "lib.h"
#include "helper.h"

ListaDupla *lista = NULL;

// cor do background
HBRUSH hbrBackground = NULL;

// fontes
HFONT textoTitulo = NULL;
HFONT textoNormal = NULL;
HFONT textoBotao = NULL;

char g_textoExibir[256] = "";
BOOL g_exibirTexto = FALSE;

// janela principal
HWND hBtnImprimir;
HWND hBtnArquivo;
HWND hBtnImpressora;
HWND hBtnMetodo;
HWND hBtnFila;
HWND hTextoFixo;
HWND hBtnSair;
HWND hBtnArquivoRemover;

// Janela impressora
HWND janelaImpressora;
HWND inputImpressora;
HWND textoImpressora;
HWND submitImpressora;

// Janela arquivo
HWND janelaArquivo;
HWND inputArquivo;
HWND textoArquivo;
HWND submitArquivo;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_Imprimir:
            // impressão depende do Pedro

            /*
            char texto[256];
            GetWindowText(GetDlgItem(hwnd, ID_Edit), texto, 256);

            MessageBox(hwnd, texto, "Texto digitado:", MB_OK);
            */

            break;

        case ID_Arquivo:
            ShowWindow(janelaArquivo, 1);
            break;

        case ID_SubmitArquivo:
            if (lista == NULL)
                lista = criar_lista();

            char texto[TAMANHO];
            GetWindowText(inputArquivo, texto, TAMANHO);
            printf("\n %s \n",texto);

            inserir_fim(lista, &texto[0]);
            
            ShowWindow(janelaArquivo, 0);

            SetWindowText(inputArquivo, "");
            break;


        case ID_Impressora:
            ShowWindow(janelaImpressora, 1);
            break;

        case ID_Sair:
            destruir_lista(lista);
            PostQuitMessage(0);
            break;

        case ID_Edit:
            break;

        default:
            printf("Comando nao realizado ainda\n");
            imprimir_frente(lista);
            break;
        }
        break;

    case WM_CTLCOLORSTATIC:
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LRESULT)hbrBackground;
    case WM_CLOSE:
        if (hwnd == janelaArquivo || hwnd == janelaImpressora)
        {
            ShowWindow(hwnd, 0);
            return 0;
        }
        break;
    case WM_DESTROY:
        if (hbrBackground != NULL)
            DeleteObject(hbrBackground);
        if (hwnd == GetActiveWindow() && GetParent(hwnd) == NULL)
            PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    setlocale(LC_ALL, "Portuguese");

    hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Default";
    wc.hbrBackground = hbrBackground;

    RegisterClass(&wc);

    // Janela principal -----------------------------------------------------------------------------------------------------------------------

    HWND hwnd = criarJanela("Default", "Software de Impressao", 900, 620, NULL, hInstance);

    hTextoFixo = criarText(hwnd, "Software de Impressao", 220, 40, 600, 100, ID_Titulo, hInstance);

    hBtnImprimir = criarBotao(hwnd, "Imprimir", 50, 120, 800, 90, ID_Imprimir, hInstance);

    hBtnArquivo = criarBotao(hwnd, "Adicionar arquivo", 50, 230, 390, 90, ID_Arquivo, hInstance); // 50, 340, 390, 90

    hBtnArquivoRemover = criarBotao(hwnd, "Remover arquivo", 460, 230, 390, 90, ID_remover, hInstance);

    hBtnImpressora = criarBotao(hwnd, "Adicionar impressora", 460, 340, 390, 90, ID_Impressora, hInstance);

    hBtnMetodo = criarBotao(hwnd, "Escolher metodo de impressao", 50, 450, 390, 90, ID_MetodoImpressao, hInstance);

    hBtnFila = criarBotao(hwnd, "Visualizar fila de impressao", 50, 340, 390, 90, ID_VisualizarFila, hInstance);

    hBtnSair = criarBotao(hwnd, "Sair", 460, 450, 390, 90, ID_Sair, hInstance);

    ShowWindow(hwnd, nCmdShow);

    // Janela adicionar arquivo---------------------------------------------------------------------------------------------------------------

    janelaArquivo = criarJanela("Default", "Path", 700, 200, hwnd, hInstance);

    textoArquivo = criarText(janelaArquivo, "Digite o path absoluto: ", 50, 20, 600, 30, ID_Texto, hInstance);

    inputArquivo = criarInput(janelaArquivo, 50, 55, 600, 30, ID_Edit, hInstance);

    submitArquivo = criarBotao(janelaArquivo, "Submit", 300, 100, 110, 40, ID_SubmitArquivo, hInstance);

    // Janela adicionar impressora------------------------------------------------------------------------------------------------------------

    janelaImpressora = criarJanela("Default", "Impressora", 700, 200, hwnd, hInstance);

    textoImpressora = criarText(janelaImpressora, "Digite o nome da impressora: ", 50, 20, 600, 30, ID_Texto, hInstance);

    inputImpressora = criarInput(janelaImpressora, 50, 55, 600, 30, ID_Edit, hInstance);

    submitImpressora = criarBotao(janelaImpressora, "Submit", 300, 100, 110, 40, ID_SubmitImpressora, hInstance);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
