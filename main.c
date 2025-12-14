#include"lib.h"
#include"helper.h"

ListaDupla *lista = NULL;

HBRUSH hbrBackground = NULL;

HFONT textoTitulo = NULL;
HFONT textoNormal = NULL;
HFONT textoBotao = NULL;

char g_textoExibir[256] = "";
BOOL g_exibirTexto = FALSE;

//janela principal
HWND hBtnImprimir;
HWND hBtnArquivo;
HWND hBtnImpressora;
HWND hBtnMetodo;
HWND hBtnFila;
HWND hTextoFixo;
HWND hBtnSair;

//janela add arquivo
HWND janelaArquivo;
HWND inputArquivo;
HWND textoArquivo;
HWND submitArquivo;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_Imprimir)
        {
            char texto[256];
            GetWindowText(GetDlgItem(hwnd, ID_Edit), texto, 256);

            MessageBox(hwnd, texto, "Texto digitado:", MB_OK);
        }

        if (LOWORD(wParam) == ID_Arquivo)
        {

            ShowWindow(janelaArquivo, 1);

//            hbrBackground = CreateSolidBrush(RGB(50, 50, 50));
//            InvalidateRect(hwnd, NULL, TRUE);

            char arquivo[TAMANHO];

            if(lista == NULL) lista = criar_lista();
            //inserir_fim(lista, GetWindowText(GetDlgItem(janelaArquivo, ID_EDIT), texto, 256););
        }

        if (LOWORD(wParam) == ID_Impressora)
        {
        }

        if (LOWORD(wParam) == ID_VisualizarFila)
        {

            char texto[256];
            GetWindowText(GetDlgItem(hwnd, ID_Edit), texto, 256);

            //strcpy(g_textoExibir, "Sua fila de impressao esta vazia.");

            //g_exibirTexto = TRUE;



//            hwnd = GetDesktopWindow();
//            HDC hdc = GetWindowDC(hwnd);
//            TextOut(hdc, 100, 100, "Texto na tela", 14);
//            ReleaseDC(hwnd, hdc);

            //InvalidateRect(hwnd, NULL, TRUE);
        }

        if (LOWORD(wParam) == ID_Sair)
        {

            //destruir_lista(l);
            PostQuitMessage;
        }

        break;

    // case WM_PAINT:
    // {
    //     PAINTSTRUCT ps;
    //     HDC hdc = BeginPaint(hwnd, &ps);

    //     if (g_exibirTexto)
    //     {

    //         SelectObject(hdc, hFontArial30);

    //         SetBkMode(hdc, TRANSPARENT);

    //         SetTextColor(hdc, RGB(255, 0, 0));

    //         TextOut(
    //             hdc,
    //             50,
    //             150,
    //             g_textoExibir,
    //             strlen(g_textoExibir));
    //     }

    //     EndPaint(hwnd, &ps);
    // }
    //break;

    case WM_CTLCOLORSTATIC:
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LRESULT)hbrBackground;
        break;

    case WM_DESTROY:
        if (hbrBackground != NULL) DeleteObject(hbrBackground);
        if (hwnd == GetActiveWindow() && GetParent(hwnd) == NULL) PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    hbrBackground = CreateSolidBrush(RGB(255,255,255));
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Default";
    wc.hbrBackground = hbrBackground;

    RegisterClass(&wc);

    // Janela principal -----------------------------------------------------------------------------------------------------------------------

    HWND hwnd = criarJanela("Default", "Software de Impressao", 900, 620, NULL, hInstance);

    hTextoFixo = criarText(hwnd, "Software de Impressao", 50, 20, 600, 100, ID_Titulo, hInstance);

    hBtnImprimir = criarBotao(hwnd, "Imprimir", 50, 230, 390, 90, ID_Imprimir, hInstance);

    hBtnArquivo = criarBotao(hwnd, "Adicionar arquivo", 50, 340, 390, 90, ID_Arquivo, hInstance);

    hBtnImpressora = criarBotao(hwnd, "Adicionar impressora", 460, 340, 390, 90, ID_Impressora, hInstance);

    hBtnMetodo = criarBotao(hwnd, "Escolher \r\nmetodo de impressao", 50, 450, 390, 90, ID_MetodoImpressao, hInstance);

    hBtnFila = criarBotao(hwnd, "Visualizar fila de impressao", 460, 230, 390, 90, ID_VisualizarFila, hInstance);

    hBtnSair = criarBotao(hwnd, "Sair", 460, 450, 390, 90, ID_Sair, hInstance);

    ShowWindow(hwnd, nCmdShow);

    // fim da Janela principal ---------------------------------------------------------------------------------------------------------------

    // Janela adicionar arquivo---------------------------------------------------------------------------------------------------------------

    janelaArquivo = criarJanela("Default", "Path", 700, 200, hwnd, hInstance);

    textoArquivo = criarText(janelaArquivo, "Digite o path absoluto: ", 50, 20, 600, 30, ID_Texto, hInstance);

    inputArquivo = criarInput(janelaArquivo, 50, 55, 600, 30, ID_Edit, hInstance);

    submitArquivo = criarBotao(janelaArquivo, "Submit", 300, 100, 110, 40, ID_SubmitArquivo, hInstance);

    // fim da adicionar arquivo---------------------------------------------------------------------------------------------------------------

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
