#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IDC_BUTTON_0        101
#define IDC_BUTTON_1        102
#define IDC_BUTTON_2        103
#define IDC_BUTTON_3        104
#define IDC_BUTTON_4        105
#define IDC_BUTTON_5        106
#define IDC_BUTTON_6        107
#define IDC_BUTTON_7        108
#define IDC_BUTTON_8        109
#define IDC_BUTTON_9        110
#define IDC_BUTTON_PLUS     111
#define IDC_BUTTON_MINUS    112
#define IDC_BUTTON_MULTIPLY 113
#define IDC_BUTTON_DIVIDE   114
#define IDC_BUTTON_EQUALS   115
#define IDC_BUTTON_DECIMAL  116
#define IDC_BUTTON_CLEAR    117
#define IDC_BUTTON_BACKSPACE 118

#define BUTTON_WIDTH  60
#define BUTTON_HEIGHT 60
#define BUTTON_MARGIN 10

typedef struct {
    const char *text;
    int id;
    int x, y;
    int width, height;
} ButtonInfo;

ButtonInfo g_buttons[] = {
    {"C", IDC_BUTTON_CLEAR, 10, 70, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"<-", IDC_BUTTON_BACKSPACE, 80, 70, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"/", IDC_BUTTON_DIVIDE, 150, 70, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"*", IDC_BUTTON_MULTIPLY, 220, 70, BUTTON_WIDTH, BUTTON_HEIGHT},

    {"7", IDC_BUTTON_7, 10, 140, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"8", IDC_BUTTON_8, 80, 140, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"9", IDC_BUTTON_9, 150, 140, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"+", IDC_BUTTON_PLUS, 220, 140, BUTTON_WIDTH, BUTTON_HEIGHT},

    {"4", IDC_BUTTON_4, 10, 210, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"5", IDC_BUTTON_5, 80, 210, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"6", IDC_BUTTON_6, 150, 210, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"-", IDC_BUTTON_MINUS, 220, 210, BUTTON_WIDTH, BUTTON_HEIGHT},

    {"1", IDC_BUTTON_1, 10, 280, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"2", IDC_BUTTON_2, 80, 280, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"3", IDC_BUTTON_3, 150, 280, BUTTON_WIDTH, BUTTON_HEIGHT},
    {"=", IDC_BUTTON_EQUALS, 220, 280, BUTTON_WIDTH, BUTTON_HEIGHT},

    {"0", IDC_BUTTON_0, 10, 350, 130, BUTTON_HEIGHT},
    {".", IDC_BUTTON_DECIMAL, 150, 350, BUTTON_WIDTH, BUTTON_HEIGHT}
};

HWND g_hMainWindow = NULL;
HWND g_hDisplay = NULL;

char g_szInputBuffer[256] = "0";
double g_dFirstOperand = 0.0;
double g_dSecondOperand = 0.0;
char g_cOperator = '\0';
BOOL g_bNewOperation = TRUE;

void AtualizarDisplay() {
    SetWindowText(g_hDisplay, g_szInputBuffer);
}

void AdicionarNumero(char digit) {
    if (g_bNewOperation) {
        strcpy_s(g_szInputBuffer, sizeof(g_szInputBuffer), "");
        g_bNewOperation = FALSE;
    }

    if (strcmp(g_szInputBuffer, "0") == 0 && digit == '0') {
        return;
    }

    if (strlen(g_szInputBuffer) < sizeof(g_szInputBuffer) - 2) {
        if (strcmp(g_szInputBuffer, "0") == 0) {
            g_szInputBuffer[0] = digit;
            g_szInputBuffer[1] = '\0';
        } else {
            strncat_s(g_szInputBuffer, sizeof(g_szInputBuffer), &digit, 1);
        }
    }

    AtualizarDisplay();
}

void AdicionarDecimal() {
    if (g_bNewOperation) {
        strcpy_s(g_szInputBuffer, sizeof(g_szInputBuffer), "0");
        g_bNewOperation = FALSE;
    }

    if (!strchr(g_szInputBuffer, '.')) {
        strcat_s(g_szInputBuffer, sizeof(g_szInputBuffer), ".");
    }

    AtualizarDisplay();
}

void DefinirOperador(char operador) {
    g_dFirstOperand = atof(g_szInputBuffer);
    g_cOperator = operador;
    g_bNewOperation = TRUE;
}

void Calcular(HWND hwnd) {
    g_dSecondOperand = atof(g_szInputBuffer);

    double result = 0.0;

    switch (g_cOperator) {
        case '+':
            result = g_dFirstOperand + g_dSecondOperand;
            break;

        case '-':
            result = g_dFirstOperand - g_dSecondOperand;
            break;

        case '*':
            result = g_dFirstOperand * g_dSecondOperand;
            break;

        case '/':
            if (g_dSecondOperand != 0) {
                result = g_dFirstOperand / g_dSecondOperand;
            } else {
                MessageBox(hwnd, "Divisao por zero!", "Erro", MB_OK | MB_ICONERROR);
                return;
            }
            break;

        default:
            return;
    }

    sprintf_s(g_szInputBuffer, sizeof(g_szInputBuffer), "%.2f", result);
    AtualizarDisplay();

    g_bNewOperation = TRUE;
    g_cOperator = '\0';
}

void Limpar() {
    strcpy_s(g_szInputBuffer, sizeof(g_szInputBuffer), "0");

    g_dFirstOperand = 0;
    g_dSecondOperand = 0;
    g_cOperator = '\0';
    g_bNewOperation = TRUE;

    AtualizarDisplay();
}

void ApagarUltimo() {
    int len = strlen(g_szInputBuffer);

    if (len > 1) {
        g_szInputBuffer[len - 1] = '\0';
    } else {
        strcpy_s(g_szInputBuffer, sizeof(g_szInputBuffer), "0");
    }

    AtualizarDisplay();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);

            switch (wmId) {

                case IDC_BUTTON_0:
                case IDC_BUTTON_1:
                case IDC_BUTTON_2:
                case IDC_BUTTON_3:
                case IDC_BUTTON_4:
                case IDC_BUTTON_5:
                case IDC_BUTTON_6:
                case IDC_BUTTON_7:
                case IDC_BUTTON_8:
                case IDC_BUTTON_9: {
                    char digit = (char)('0' + (wmId - IDC_BUTTON_0));
                    AdicionarNumero(digit);
                    break;
                }

                case IDC_BUTTON_DECIMAL:
                    AdicionarDecimal();
                    break;

                case IDC_BUTTON_PLUS:
                    DefinirOperador('+');
                    break;

                case IDC_BUTTON_MINUS:
                    DefinirOperador('-');
                    break;

                case IDC_BUTTON_MULTIPLY:
                    DefinirOperador('*');
                    break;

                case IDC_BUTTON_DIVIDE:
                    DefinirOperador('/');
                    break;

                case IDC_BUTTON_EQUALS:
                    Calcular(hwnd);
                    break;

                case IDC_BUTTON_CLEAR:
                    Limpar();
                    break;

                case IDC_BUTTON_BACKSPACE:
                    ApagarUltimo();
                    break;
            }

            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "CalculatorWindowClass";

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 0;
    }

    g_hMainWindow = CreateWindowEx(
        0,
        "CalculatorWindowClass",
        "Calculadora em C",
        WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        300,
        460,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (g_hMainWindow == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
        return 0;
    }

    g_hDisplay = CreateWindowEx(
        0,
        "STATIC",
        "0",
        WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_BORDER,
        10,
        10,
        260,
        45,
        g_hMainWindow,
        (HMENU)100,
        hInstance,
        NULL
    );

    int totalButtons = sizeof(g_buttons) / sizeof(g_buttons[0]);

    for (int i = 0; i < totalButtons; i++) {
        CreateWindow(
            "BUTTON",
            g_buttons[i].text,
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            g_buttons[i].x,
            g_buttons[i].y,
            g_buttons[i].width,
            g_buttons[i].height,
            g_hMainWindow,
            (HMENU)g_buttons[i].id,
            hInstance,
            NULL
        );
    }

    ShowWindow(g_hMainWindow, nCmdShow);
    UpdateWindow(g_hMainWindow);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}