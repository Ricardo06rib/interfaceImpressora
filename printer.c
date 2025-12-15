#include "headers/printer.h"

#include <windows.h>
#include <stdio.h>
#include <string.h>

void imprimir_pdf(const char *arquivo)
{
    ShellExecuteA(
        NULL,
        "print",
        arquivo,
        NULL,
        NULL,
        SW_HIDE
    );
}

void imprimir_bmp_gdi(const char *arquivo, const char *impressora)
{
    HBITMAP hBmp = (HBITMAP)LoadImageA(
        NULL,
        arquivo,
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE | LR_CREATEDIBSECTION
    );

    if (!hBmp) return;

    HDC hdcPrinter = CreateDCA(NULL, impressora, NULL, NULL);
    if (!hdcPrinter) {
        DeleteObject(hBmp);
        return;
    }

    BITMAP bmp;
    GetObject(hBmp, sizeof(BITMAP), &bmp);

    HDC hdcMem = CreateCompatibleDC(hdcPrinter);
    SelectObject(hdcMem, hBmp);

    DOCINFOA di = { sizeof(DOCINFOA), "Impressao BMP" };
    StartDocA(hdcPrinter, &di);
    StartPage(hdcPrinter);

    int larguraPagina  = GetDeviceCaps(hdcPrinter, HORZRES);
    int alturaPagina   = GetDeviceCaps(hdcPrinter, VERTRES);

    StretchBlt(
        hdcPrinter,
        0, 0,
        larguraPagina, alturaPagina,
        hdcMem,
        0, 0,
        bmp.bmWidth, bmp.bmHeight,
        SRCCOPY
    );

    EndPage(hdcPrinter);
    EndDoc(hdcPrinter);

    DeleteDC(hdcMem);
    DeleteDC(hdcPrinter);
    DeleteObject(hBmp);
}
void imprimir_txt_raw(const char *arquivo, const char *impressora)
{
    FILE *f = fopen(arquivo, "r");
    if (!f) return;

    HANDLE hPrinter;
    DWORD written;
    DOC_INFO_1A di = { "TXT RAW", NULL, "RAW" };

    if (!OpenPrinterA((LPSTR)impressora, &hPrinter, NULL)) {
        fclose(f);
        return;
    }

    StartDocPrinterA(hPrinter, 1, (LPBYTE)&di);
    StartPagePrinter(hPrinter);

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), f)) {
        WritePrinter(hPrinter, buffer, (DWORD)strlen(buffer), &written);
    }

    EndPagePrinter(hPrinter);
    EndDocPrinter(hPrinter);
    ClosePrinter(hPrinter);
    fclose(f);
}

/* GDI = IMPRESSORA NORMAL/PDF, FICA RUIM PRA TESTAR PORQUE A VIRTUAL PRINTER NÃO GERA O ARQUIVO CORRETAMENTE
*/
void imprimir_txt_gdi(const char *arquivo, const char *impressora)
{
    FILE *f = fopen(arquivo, "r");
    if (!f) return;

    HDC hdc = CreateDCA(NULL, impressora, NULL, NULL);
    if (!hdc) {
        fclose(f);
        return;
    }

    DOCINFOA di;
    ZeroMemory(&di, sizeof(di));
    di.cbSize = sizeof(di);
    di.lpszDocName = "Impressao TXT";

    StartDocA(hdc, &di);
    StartPage(hdc);

    char linha[512];
    int y = 100;
    int x = 100;

    while (fgets(linha, sizeof(linha), f)) {
        TextOutA(hdc, x, y, linha, (int)strlen(linha));
        y += 20;
    }

    EndPage(hdc);
    EndDoc(hdc);
    DeleteDC(hdc);
    fclose(f);
}

/*SELETOR MUITO FODA OLHA QUE FODA!!!!!!!/*/

void imprimir_arquivo(const char *arquivo, const char *impressora)
{
    const char *ext = strrchr(arquivo, '.');
    if (!ext) return;

    /* TXT / IN */
    if (_stricmp(ext, ".txt") == 0 || _stricmp(ext, ".ini") == 0)
    {
        if (_stricmp(impressora, "Generic / Text Only") == 0 ||
            _stricmp(impressora, "TesteTXT") == 0)
        {
            imprimir_txt_raw(arquivo, impressora);
        }
        else
        {
            imprimir_txt_gdi(arquivo, impressora);
        }
        return;
    }

    /* BMP */
    if (_stricmp(ext, ".bmp") == 0)
    {
        imprimir_bmp_gdi(arquivo, impressora);
        return;
    }
       if (_stricmp(ext, ".pdf") == 0)
    {
        imprimir_pdf(arquivo);
        return;
    }
}

void impressoraFrentePTras(ListaDupla *l, const char *nomeImpressora)
{
    while (!esta_vazia(l)) {
        imprimir_arquivo(l->inicio->arquivo, nomeImpressora);
        remover_item(l, l->inicio->arquivo);
    }
}
void impressoraTrasPFrente(ListaDupla *l, const char *nomeImpressora)
{
    while (!esta_vazia(l)) {
        imprimir_arquivo(l->fim->arquivo, nomeImpressora);
        remover_item(l, l->fim->arquivo);
    }
}








//-----------------------------------------

char* imprimir_frente(ListaDupla *l)
{
    if (l == NULL || esta_vazia(l))
    {
        char *msg = (char*)malloc(32);
        strcpy(msg, "Fila vazia");
        return msg;
    }

    // tamanho máximo estimado
    char *buffer = (char*)malloc(2048);
    buffer[0] = '\0';

    No *aux = l->inicio;

    int i = 0;
    char temp[50];

    while (aux != NULL)
    {
        i++;
        snprintf(temp, sizeof(temp), "Arquivo %d: -> |", i);
        strcat(buffer, temp);
        strcat(buffer, aux->arquivo);
        strcat(buffer, "|\n");
        aux = aux->proximo;
    }

    return buffer;
}
