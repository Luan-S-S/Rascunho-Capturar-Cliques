#include "pch.h"
#include <Windows.h>

WNDPROC OriginalWndProc = nullptr;
HWND hwnd = nullptr;

//Temtar mudar de W para A:
//FindWindowA
//SetWindowLongPtrA
//CallWindowProcA
//MessageBoxA

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //Com isto consseguimos processar o aimbot() capturando quando o botão é precionado e solto
    switch (msg)
    {
    case WM_RBUTTONDOWN: //Botão do aimbot precionado
        MessageBoxA(hwnd, "Botão direito PRECIONADO", "PRECIONADO", MB_OK);
        break;
    case WM_RBUTTONUP: //Botão do aimbot solto
        MessageBoxA(hwnd, "botão direito SOLTO", "SOLTO", MB_OK);
        break;
    default:
        break;
    }

    return CallWindowProcA(OriginalWndProc, hwnd, msg, wParam, lParam);
}

//Melhorar esta função aqui esta feia principalmente o retorno
DWORD WINAPI InterceptInput(LPVOID lpParam)
{
    hwnd = FindWindowA(NULL, "AssaultCube");
    if (!hwnd) {
        return 0;
    }
    OriginalWndProc = (WNDPROC)SetWindowLongPtrA(hwnd, GWLP_WNDPROC, (LONG_PTR)MyWndProc);
    return 1;

}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, NULL, InterceptInput, nullptr, NULL, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
