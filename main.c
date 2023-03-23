#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_VERTICES 5

int matrix[MAX_VERTICES][MAX_VERTICES];
const int vertices = 5;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HWND hwnd;
    WNDCLASS wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
    wc.lpszClassName = "MyClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if(!RegisterClass(&wc))
    {
        printf("This Program Requires Windows NT\n");
        MessageBox(NULL, "This Program Requires Windows NT",
                   "Error", MB_ICONEXCLAMATION);
        return 1;
    }
    hwnd = CreateWindow("MyClass",
                        "Graph Visualization",
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        640, 480,
                        NULL, NULL, hInstance, NULL);

    FILE* file = fopen("C:\\Users\\admin\\CLionProjects\\flita\\dz2\\adjacency_matrix_5.txt", "r");
    if (file == NULL) {
        MessageBox(NULL, "Could not open file.", "Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    ShowWindow(hwnd, SW_MINIMIZE);
    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_NORMAL);

    char str[12];
    char element[2];
    const char sep[2] = " ";
    char *token;

    for (int j = 0; j < 5; j++) {
        fgets(str, 12, file);
        token = strtok(str, sep);
        strcpy(element, token);
        matrix[0][j] = atoi(element);
        for (int i = 1; i < 5; i++) {
            token = strtok(NULL, sep);
            strcpy(element, token);
            matrix[i][j] = atoi(element);
        }
    }
    fclose(file);
    printf("File have been read successfully. Data:\n");
    for (int j = 0; j < vertices; j++) {
        for (int i = 0; i < vertices; i++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }



    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rec;
            HPEN hpen = NULL;

            int x[5] = {100, 195, 5, 159, 41};
            int y[5] = {200, 131, 131, 19, 19};
            Ellipse(hdc, x[0] + 10, y[0] + 10, x[0] + 40, y[0] + 40);
            SetRect(&rec,x[0] + 10, y[0] + 20, x[0] + 40, y[0] + 50);
            DrawText(hdc, TEXT("1"),1, &rec, DT_TOP|DT_LEFT);
            Ellipse(hdc, x[1] + 10, y[1] + 10, x[1] + 40, y[1] + 40);
            SetRect(&rec,x[1] + 10, y[1] + 10, x[1] + 40, y[1] + 40);
            DrawText(hdc, TEXT("2"),1, &rec, DT_TOP|DT_LEFT);
            Ellipse(hdc, x[2] + 10, y[2] + 10, x[2] + 40, y[2] + 40);
            SetRect(&rec,x[2] + 10, y[2] + 10, x[2] + 40, y[2] + 40);
            DrawText(hdc, TEXT("3"),1, &rec, DT_TOP|DT_LEFT);
            Ellipse(hdc, x[3] + 10, y[3] + 10, x[3] + 40, y[3] + 40);
            SetRect(&rec,x[3] + 10, y[3] + 10, x[3] + 40, y[3] + 40);
            DrawText(hdc, TEXT("4"),1, &rec, DT_TOP|DT_LEFT);
            Ellipse(hdc, x[4] + 10, y[4] + 10, x[4] + 40, y[4] + 40);
            SetRect(&rec,x[4] + 10, y[4] + 10, x[4] + 40, y[4] + 40);
            DrawText(hdc, TEXT("5"),1, &rec, DT_TOP|DT_LEFT);

            for (int i = 0; i < vertices; i++) {
                for (int j = 0; j < vertices; j++) {
                    if (matrix[i][j] != 0) {
                        hpen = CreatePen(PS_SOLID, matrix[i][j], RGB(0, 0, 0));
                        SelectObject(hdc, hpen);
                        MoveToEx(hdc, x[i] + 25, y[i] + 25, NULL);
                        LineTo(hdc, x[j] + 25, y[j] + 25);
                        if (i == j) {
                            AngleArc(hdc, x[i] + 25, y[i] + 25, 50, 30, 50);
                            LineTo(hdc, x[i] + 25, y[i] + 25);
                        }
                    }
                }
            }
            EndPaint(hwnd, &ps);
            DeleteObject(hpen);
            GetStockObject(DC_PEN);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}