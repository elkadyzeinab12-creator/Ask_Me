#include <bits/stdc++.h>
#include "AskMeManager.h"
#ifdef _WIN32
#include <windows.h>
#endif
void colors_organization();

int main() {
    colors_organization();
    AskMeManager system;
    std::cout << "\n Welcome!\n";
    system.Run();
    return 0;
}

void colors_organization() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}
