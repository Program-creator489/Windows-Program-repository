#include <windows.h>
#include <cstdlib>
#include <ctime>

int main() {
    // Hide console window
    HWND console = GetConsoleWindow();
    if (console) {
        ShowWindow(console, SW_HIDE);
    }

    POINT p;
    srand((unsigned int)time(nullptr));

    while (true) {
        // Stop if ESC is pressed
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            break;
        }

        GetCursorPos(&p);

        int dx = (rand() % 11) - 5; // -5 to +5
        int dy = (rand() % 11) - 5;

        SetCursorPos(p.x + dx, p.y + dy);

        Sleep(10); // speed control
    }

    return 0;
}
