#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define PI 3.14
#define FILENAME "C:\\Users\\admin\\CLionProjects\\flita\\dz2\\adjacency_matrix_20.txt"
#define MAX_VERTICES 50
#define OFFSET 50


typedef struct coords {
    int x;
    int y;
} cd_t;

cd_t getCoords(int sides, int n) {
    cd_t A;
    int r = 100;
    A.x = r * cos(2 * PI * n / sides) + OFFSET;
    A.y = r * sin(2 * PI * n / sides) + OFFSET;
    return A;
}

void drawVertice(int n, int x, int y, HDC hdc, RECT rec ) {
    Ellipse(hdc, x + 100, y + 100, x + 130, y + 130);
    SetRect(&rec,x + 100, y + 100, x + 130, y + 130);
    char VerticeNumber[2];
    itoa(n,VerticeNumber, 10);
    DrawText(hdc, TEXT(VerticeNumber),1, &rec, DT_TOP|DT_LEFT);
}

int matrix[MAX_VERTICES][MAX_VERTICES];
//const int vertices = 5;


bool isBonded(int m[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int edges = 0;
    for (int j = 0; j < vertices; j++) {
        for (int i = 0; i < vertices; i++) {
            if (i==j) continue;
            if (m[i][j]) edges++;
        }
    }
    if (edges > ((vertices -1 ) * (vertices - 2)) / 2) return true;
    else return false;
}

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
    SystemParametersInfoA(SPI_SETFONTSMOOTHING, TRUE, NULL, 0);
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

    FILE* file = fopen(FILENAME, "r");


    if (file == NULL) {
        MessageBox(NULL, "Could not open file.", "Error", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    ShowWindow(hwnd, SW_MINIMIZE);
    UpdateWindow(hwnd);
    ShowWindow(hwnd, SW_NORMAL);

    char str[MAX_VERTICES];
    char element[2];
    const char sep[2] = " ";
    char *token;

    int vertices = (int)strlen(fgets(str, MAX_VERTICES, file))/2;
    printf("\n\t%d\n", vertices);
    fclose(file);
    file = fopen(FILENAME, "r");

    for (int j = 0; j < vertices; j++) {
        fgets(str, MAX_VERTICES, file);
        token = strtok(str, sep);
        strcpy(element, token);
        matrix[0][j] = atoi(element);
        for (int i = 1; i < vertices; i++) {
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

    if (isBonded(matrix, vertices)) {
        MessageBox(NULL, "Graph is bonded", "INFO", MB_ICONINFORMATION);
    }
    else MessageBox(NULL, "Graph is not bonded", "INFO", MB_ICONINFORMATION);


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


            char str[MAX_VERTICES];
            FILE* file = fopen(FILENAME, "r");
            int vertices = (int)strlen(fgets(str, MAX_VERTICES, file))/2;
            fclose(file);

            cd_t A;

            int* x = (int*) malloc(vertices*sizeof(int));
            int* y = (int*) malloc(vertices*sizeof(int));

            for (int i = 0; i < vertices; i++) {
                A = getCoords(vertices, i+1);
                x[i] = A.x; y[i] = A.y;
                printf("%d:%d ", A.x, A.y);
                drawVertice(i+1, A.x, A.y, hdc, rec);
            }
            printf("\n");



            //int x[5] = {100, 195, 5, 159, 41};
            //int y[5] = {200, 131, 131, 19, 19};
            //Ellipse(hdc, x[0] + 10, y[0] + 10, x[0] + 40, y[0] + 40);
            //SetRect(&rec,x[0] + 10, y[0] + 20, x[0] + 40, y[0] + 50);
            //DrawText(hdc, TEXT("1"),1, &rec, DT_TOP|DT_LEFT);
            //drawVertice(1, x[0], y[0], hdc, rec);
            //Ellipse(hdc, x[1] + 10, y[1] + 10, x[1] + 40, y[1] + 40);
            //SetRect(&rec,x[1] + 10, y[1] + 10, x[1] + 40, y[1] + 40);
            //DrawText(hdc, TEXT("2"),1, &rec, DT_TOP|DT_LEFT);
            //drawVertice(2, x[1], y[2], hdc, rec);

            //Ellipse(hdc, x[2] + 10, y[2] + 10, x[2] + 40, y[2] + 40);
            //SetRect(&rec,x[2] + 10, y[2] + 10, x[2] + 40, y[2] + 40);
            //DrawText(hdc, TEXT("3"),1, &rec, DT_TOP|DT_LEFT);
            //Ellipse(hdc, x[3] + 10, y[3] + 10, x[3] + 40, y[3] + 40);
            //SetRect(&rec,x[3] + 10, y[3] + 10, x[3] + 40, y[3] + 40);
            //DrawText(hdc, TEXT("4"),1, &rec, DT_TOP|DT_LEFT);
            //Ellipse(hdc, x[4] + 10, y[4] + 10, x[4] + 40, y[4] + 40);
            //SetRect(&rec,x[4] + 10, y[4] + 10, x[4] + 40, y[4] + 40);
            //DrawText(hdc, TEXT("5"),1, &rec, DT_TOP|DT_LEFT);

            for (int i = 0; i < vertices; i++) {
                printf("%d:%d ", x[i], y[i]);
                for (int j = 0; j < vertices; j++) {

                    if (matrix[i][j] != 0) {


                        hpen = CreatePen(PS_SOLID, matrix[i][j], RGB(0, 0, 0));
                        SelectObject(hdc, hpen);
                        MoveToEx(hdc, x[i] + 115, y[i] + 115, NULL);
                        LineTo(hdc, x[j] + 115, y[j] + 115);
                        if (i == j) {
                            AngleArc(hdc, x[i] + 115, y[i] + 115, 50, 30, 50);
                            LineTo(hdc, x[i] + 115, y[i] + 115);
                        }
                    }
                }
            }
            free(x); free(y);
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