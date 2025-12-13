#include"lib.h"

#define ID_Imprimir 3
#define ID_Arquivo 4
#define ID_impressora 5
#define ID_metodoImpressao 6
#define ID_visualizarFila 7
#define ID_EDIT 2

#define ID_TEXTO_FIXO 1

HBRUSH hbrBackground = NULL;

HFONT hFontArial30 = NULL;

char g_textoExibir[256] = "";
BOOL g_exibirTexto = FALSE;

HWND hBtnImprimir;
HWND hBtnArquivo;
HWND hBtnImpressora;
HWND hBtnMetodo;
HWND hBtnFila;
HWND hTextoFixo;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    switch (msg)
    {

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_Imprimir)
        {
            char texto[256];
            GetWindowText(GetDlgItem(hwnd, ID_EDIT), texto, 256);

            MessageBox(hwnd, texto, "Texto digitado:", MB_OK);
        }

        if (LOWORD(wParam) == ID_Arquivo)
        {
            //                hwnd = GetDesktopWindow();
            //                HDC hdc = GetWindowDC(hwnd);
            //                TextOut(hdc, 100, 100, "Texto na tela", 14);
            //                ReleaseDC(hwnd, hdc);
            hbrBackground = CreateSolidBrush(RGB(50, 50, 50));
            InvalidateRect(hwnd, NULL, TRUE);
        }

        if (LOWORD(wParam) == ID_impressora)
        {
        }

        if (LOWORD(wParam) == ID_visualizarFila)
        {
            strcpy(g_textoExibir, "Sua fila de impressao esta vazia.");

            g_exibirTexto = TRUE;

            InvalidateRect(hwnd, NULL, TRUE);
        }

        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (g_exibirTexto)
        {

            SelectObject(hdc, hFontArial30);

            SetBkMode(hdc, TRANSPARENT);

            SetTextColor(hdc, RGB(255, 0, 0));

            TextOut(
                hdc,
                50,
                150,
                g_textoExibir,
                strlen(g_textoExibir));
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_CTLCOLORSTATIC:
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 255));
        SetBkMode(hdcStatic, TRANSPARENT);
        return (LRESULT)hbrBackground;
        break;

    case WM_DESTROY:
        if (hbrBackground != NULL)
            DeleteObject(hbrBackground);
        if (hFontArial30 != NULL)
            DeleteObject(hFontArial30);
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    hbrBackground = CreateSolidBrush(RGB(255,255,255));
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MinhaJanela";
    wc.hbrBackground = hbrBackground;

    RegisterClass(&wc);

    hFontArial30 = CreateFont(
        24,
        0,
        0,
        0,
        FW_BOLD,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        "Arial"
    );

    HWND hwnd = CreateWindow(
        "MinhaJanela",
        "Trabalho do Wagner Moura que o Ricardao que fez",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        900, 620,
        NULL, NULL,
        hInstance, NULL
    );

    // Texto fixo
    hTextoFixo = CreateWindow(
        "STATIC", "Software de Impressao",
        WS_VISIBLE | WS_CHILD,
        20, 20, 600, 100,
        hwnd, (HMENU)ID_TEXTO_FIXO, hInstance, NULL
    );

    if (hTextoFixo != NULL && hFontArial30 != NULL) {
        SendMessage(hTextoFixo, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    // Caixa de texto
    CreateWindow(
        "EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        50, 185, 800, 25,
        hwnd, (HMENU)ID_EDIT, hInstance, NULL
    );

    hBtnImprimir = CreateWindow(
        "BUTTON", "Imprimir",
        WS_VISIBLE | WS_CHILD,
        50, 230, 800, 90,
        hwnd, (HMENU)ID_Imprimir, hInstance, NULL
    );
    if (hBtnImprimir != NULL && hFontArial30 != NULL) {
        SendMessage(hBtnImprimir, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    hBtnArquivo = CreateWindow(
        "BUTTON", "Adicionar arquivo",
        WS_VISIBLE | WS_CHILD,
        50, 340, 390, 90,
        hwnd, (HMENU)ID_Arquivo, hInstance, NULL
    );
    if (hBtnArquivo != NULL && hFontArial30 != NULL) {
        SendMessage(hBtnArquivo, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    hBtnImpressora = CreateWindow(
        "BUTTON", "Adicionar impressora",
        WS_VISIBLE | WS_CHILD,
        460, 340, 390, 90,
        hwnd, (HMENU)ID_impressora, hInstance, NULL
    );
    if (hBtnImpressora != NULL && hFontArial30 != NULL) {
        SendMessage(hBtnImpressora, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    hBtnMetodo = CreateWindow(
        "BUTTON", "Escolher metodo \r\nde impressao",
        WS_VISIBLE | WS_CHILD,
        50, 450, 390, 90,
        hwnd, (HMENU)ID_metodoImpressao, hInstance, NULL
    );
    if (hBtnMetodo != NULL && hFontArial30 != NULL) {
        SendMessage(hBtnMetodo, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    hBtnFila = CreateWindow(
        "BUTTON", "Visualizar fila de impressao",
        WS_VISIBLE | WS_CHILD | BS_MULTILINE,
        460, 450, 390, 90,
        hwnd, (HMENU)ID_visualizarFila, hInstance, NULL
    );
    if (hBtnFila != NULL && hFontArial30 != NULL) {
        SendMessage(hBtnFila, WM_SETFONT, (WPARAM)hFontArial30, TRUE);
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
