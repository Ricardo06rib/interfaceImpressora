#include"lib.h"
/*

int main () {

    setlocale(LC_ALL, "Portuguese");

    //Alerta para execução
    printf("+-----------------------------------+\n");
    printf("|   Aviso!                          |\n");
    printf("|   Verifique se há alguma pasta    |\n");
    printf("|   com espaço no nome e tire       |\n");
    printf("|   para o funcionamento do         |\n");
    printf("|   programa                        |\n");
    printf("+-----------------------------------+\n\n");
    system("pause");
    system("cls");

    ListaDupla* l = criar_lista();
    int opcao = 0;

    //definindo tamanho de string da impressora
    char impressora[100] = "";

    //menu
    while(1){
        printf("Selecione a opção:\n\n");
        printf("1 -> Imprimir\n");
        printf("2 -> Adicionar arquivo na fila de impressão\n");
        printf("3 -> Visualizar a fila de impressão\n");
        printf("4 -> Selecionar impressora\n");
        printf("5 -> Sair\n\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){

        case 1:
            if(esta_vazia(l)) {
                //alert: fila vazia
                printf("ERRO - A fila de impressão está vazia\n\n");
                //flag para encerrar programa
                goto exit;
            }
            if(impressora[0] == '\0') {
                //alert: sem impressora
                printf("ERRO - Impressora não selecionada\n\n");
                goto exit;
            }
            //chama execução da impressora enquanto houver itens na fila
            while(!esta_vazia(l)){
                imprimir_frente(l);
                imprimir(remover_item(l), &impressora[0]);
                system("pause");
                system("cls");
            }
            break;

        //adicionando arquivo na fila (caminho + arquivo)
        case 2:
            char path[TAMANHO] = "";
            printf("Digite o path do arquivo: ");
            getchar();
            fgets(path, TAMANHO, stdin);
            path[strcspn(path, "\n")] = '\0';
            enqueue(l, path);
            break;

        //exibindo fila
        case 3:
            if(esta_vazia(l)) break;
            imprimir_frente(l);
            break;

        //exibindo impressoras
        case 4:
            printf("As opções de impressão são: \n\n");
            system("wmic printer get name");

            if(impressora[0] != '\0'){
                printf("\n\nA opção atual é: %s \n\n", impressora);
            }

            printf("Digite o nome da impressora: ");
            getchar();
            //coletando impressora selecionada
            fgets(impressora, 100, stdin);
            impressora[strcspn(impressora, "\n")] = '\0';
            break;

        case 5:
            goto exit;
            break;

        default:
            printf("\nERRO - Opção inválida\n\n");
            break;
        }
        getchar();
        exit:
        system("pause");
        system("cls");
        }
    destruir_lista(l);

    return 0;
}
*/

#include <windows.h>

#define ID_BTN 1
#define ID_BTN2 3
#define ID_EDIT 2

HBRUSH hbrBackground = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BTN) {
                char texto[256];
                GetWindowText(GetDlgItem(hwnd, ID_EDIT), texto, 256);

                MessageBox(hwnd, texto, "Texto digitado:", MB_OK);
            }

            if(LOWORD(wParam) == ID_BTN2){
                char texto[256];
                GetWindowText(GetDlgItem(hwnd, ID_EDIT), texto, 256);
                printf("%s", texto);

                ShowWindow(hwnd, 10);
            }

            break;

        case WM_CTLCOLORSTATIC:
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0, 255));
            SetBkMode(hdcStatic, TRANSPARENT);
            return (LRESULT) hbrBackground;
            break;

        case WM_DESTROY:
            if(hbrBackground != NULL) DeleteObject(hbrBackground);
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

    HWND hwnd = CreateWindow(
        "MinhaJanela",
        "janela",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 200,
        NULL, NULL,
        hInstance, NULL
    );

    // Texto fixo
    CreateWindow(
        "STATIC", "Digite algo:",
        WS_VISIBLE | WS_CHILD,
        20, 20, 100, 20,
        hwnd, NULL, hInstance, NULL
    );

    // Caixa de texto
    CreateWindow(
        "EDIT", "",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        20, 50, 200, 25,
        hwnd, (HMENU)ID_EDIT, hInstance, NULL
    );

    // Botão
    CreateWindow(
        "BUTTON", "Enviar",
        WS_VISIBLE | WS_CHILD,
        20, 90, 100, 30,
        hwnd, (HMENU)ID_BTN, hInstance, NULL
    );

    // Botão2
    CreateWindow(
        "BUTTON", "printa",
        WS_VISIBLE | WS_CHILD,
        200, 90, 100, 30,
        hwnd, (HMENU)ID_BTN2, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
