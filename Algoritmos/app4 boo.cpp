// Inclui as APIs do Windows necessárias para criar janelas, controles e timers
#include <windows.h>

// Identificadores usados para o menu e o botão
#define IDM_SCARE 101
#define IDC_BUTTON 102

// Função que executa a ação de "susto":
// - inicia um timer de 20 segundos
// - toca um som de sistema
// - exibe uma MessageBox com texto
// Recebe o handle da janela (HWND) para poder interagir com a UI
void do_scare(HWND hwnd) {
    // Som e mensagem de susto
    // Inicia timer para fechar a janela após 20 segundos (começa já ao apertar)
    // Parâmetros do SetTimer: (hwnd, idTimer, intervalo_ms, ponteiro_para_callback)
    // Usamos id=1 e 20000ms = 20 segundos
    SetTimer(hwnd, 1, 20000, NULL);
    // Toca um som do sistema para enfatizar o susto
    MessageBeep(MB_ICONHAND);
    // Exibe a mensagem de "Booo!" com ícone de exclamação
    MessageBox(hwnd, "Booo!", "Surpresa", MB_OK | MB_ICONEXCLAMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // Cria um botão filho (control) na janela principal
        // Parâmetros: (classe, texto, estilo, x, y, largura, altura, hwndPai, id, hInst, lParam)
        CreateWindow("BUTTON", "Aperte-me",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 50, 100, 30, hwnd, (HMENU)IDC_BUTTON, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        // Cria um menu e adiciona um item que executa a ação de "susto"
        HMENU hMen = CreateMenu();
        HMENU hSub = CreatePopupMenu();
        // AppendMenu adiciona uma entrada ao submenu com texto e ID
        AppendMenu(hSub, MF_STRING, IDM_SCARE, "Assustar");
        // Adiciona o submenu ao menu principal
        AppendMenu(hMen, MF_POPUP, (UINT_PTR)hSub, "Acao");
        SetMenu(hwnd, hMen);
        break;
    }
    case WM_COMMAND:
        // Tratar eventos de comando (clicar botão ou selecionar item do menu)
        // LOWORD(wParam) contém o identificador do controle ou do menu
        if (LOWORD(wParam) == IDC_BUTTON || LOWORD(wParam) == IDM_SCARE) {
            // Executa a função que mostra a surpresa e inicia o timer
            do_scare(hwnd);
        }
        break;
    case WM_TIMER:
        // Quando o timer com ID=1 expirar, fechamos a janela
        if (wParam == 1) {
            KillTimer(hwnd, 1); // cancelar o timer para evitar reaplicação
            DestroyWindow(hwnd); // fecha a janela (gerará WM_DESTROY)
        }
        break;
    case WM_DESTROY:
        // Indica ao sistema que a aplicação deve terminar
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow) {
    // Nome da classe de janela — usado no registro e na criação da janela
    const char CLASS_NAME[] = "MeuApp";

    // Descreve as propriedades da classe da janela
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc; // função que trata as mensagens da janela
    wc.hInstance = hInstance; // handle da instância do programa
    wc.lpszClassName = CLASS_NAME; // nome da classe

    // Registra a classe de janela para posterior criação
    RegisterClass(&wc);

    // Cria a janela principal com o estilo WS_OVERLAPPEDWINDOW
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Menu com botao", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInstance, NULL);

    // Verifica se a janela foi criada corretamente
    if (!hwnd) return 0;

    // Exibe a janela na tela
    ShowWindow(hwnd, nCmdShow);

    // Loop principal de mensagens: captura eventos e envia para WndProc
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Quando sair do loop, encerra o programa
    return 0;
}