#include "fw.h"

#define CREDIT            \
    "lwman (LWMAN) 0.1\n" \
    "This is free software; see the source for copying conditions.\n"

#define CLASS_NAME "lwman"
#define APP_NAME "lwman"

#define WS_NONE 0

#define IDC_ST_CREDIT (10000)
#define IDC_BT_BROWSE (10001)
#define IDC_BT_LOAD (10002)
#define IDC_IN_PATH (10003)
#define IDC_ST_PREVIEW (10010)
#define IDC_ST_DETAILS (10100)
#define IDC_ST_DETAILS_DESC (10200)
#define IDC_BT_SET (11000)

#define WIDTH 420
#define HEIGHT 620

#define MARGIN 10
#define SPACING 5
#define COL_HV 20
#define COL_H(c) (c * (COL_HV + SPACING) + MARGIN)
#define COL_L ((HEIGHT - 2 * MARGIN - SPACING) / (COL_HV + SPACING) - 1) // 22

void InitWindow(void);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main(void)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc;
    MEMSET0(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT(CLASS_NAME);
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        TEXT(CLASS_NAME),
        TEXT(APP_NAME),
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH + 5, HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hwnd == NULL)
        exit(-1);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    MEMSET0(msg);
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void CreateChild(HWND hwnd, LPCTSTR lpszCls, int style, int column, int span, int x, int width, size_t id, LPCTSTR lpszContent)
{
    CreateWindow(
        lpszCls,
        lpszContent,
        WS_CHILD | WS_VISIBLE | style,
        x + MARGIN, COL_H(column), width, COL_HV * span + (span - 1) * SPACING,
        hwnd,
        (HMENU)id,
        GetModuleHandle(NULL),
        NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        const int width = WIDTH - 2 * MARGIN;
        const int btW = 60;

        // credit field
        CreateChild(hwnd, TEXT("STATIC"), WS_NONE, 0, 2, 0, width, IDC_ST_CREDIT, TEXT(CREDIT));

        // browse button
        CreateChild(hwnd, TEXT("BUTTON"), WS_NONE, 2, 2, width - btW, btW, IDC_BT_BROWSE, TEXT("Browse"));
        // path field
        CreateChild(hwnd, TEXT("EDIT"), WS_BORDER, 2, 2, 0, width - (btW + SPACING), IDC_IN_PATH, TEXT("C:\\Users\\"));
        // load button
        CreateChild(hwnd, TEXT("BUTTON"), WS_NONE, 4, 1, 0, width, IDC_BT_LOAD, TEXT("Load"));

        // preview header
        CreateChild(hwnd, TEXT("STATIC"), WS_NONE, 6, 1, 0, width, IDC_ST_PREVIEW, TEXT("Preview"));

        // info header
        CreateChild(hwnd, TEXT("STATIC"), WS_NONE, COL_L - 7, 1, 0, width, IDC_ST_DETAILS, TEXT("Details"));
        // info desc
        CreateChild(hwnd, TEXT("STATIC"), WS_VSCROLL | SS_WHITERECT, COL_L - 6, 5, 0, width, IDC_ST_DETAILS_DESC, TEXT("Details.Desc"));

        // set button
        CreateChild(hwnd, TEXT("BUTTON"), WS_NONE, COL_L - 1, 2, 0, width, IDC_BT_SET, TEXT("Set"));

        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        return 0;

    case WM_COMMAND:
    {
        WORD hiword = HIWORD(wParam);
        switch (LOWORD(wParam))
        {
        case IDC_BT_BROWSE:
            break;
        case IDC_BT_LOAD:
            break;
        case IDC_BT_SET:
            break;
        }
        return 0;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
