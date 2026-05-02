#include <windows.h>
#include <time.h>

#define DURATION_MS (120 * 1000)   // 2 minutes
#define EFFECT_TIME (10 * 1000)    // 10 seconds

void effect1(HDC hdc, int w, int h)
{
    for (int i = 0; i < 2000; i++)
    {
        int x = rand() % w;
        int y = rand() % h;
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }
}

void effect2(HDC hdc, int w, int h)
{
    for (int i = 0; i < 100; i++)
    {
        Rectangle(hdc,
                  rand() % w, rand() % h,
                  rand() % w, rand() % h);
    }
}

void effect3(HDC hdc, int w, int h)
{
    for (int i = 0; i < 200; i++)
    {
        MoveToEx(hdc, rand() % w, rand() % h, NULL);
        LineTo(hdc, rand() % w, rand() % h);
    }
}

void effect4(HDC hdc, int w, int h)
{
    BitBlt(hdc, 10, 10, w - 20, h - 20, hdc, 0, 0, SRCCOPY);
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 120] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = (char)((9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 0);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

    Sleep(120000);

    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
int result1 = MessageBox(
    NULL,
    "Run GDI?",
    "Message",
    MB_YESNO | MB_ICONWARNING
);

if (result1 == IDNO)
{
    return 0;
}

int result2 = MessageBox(
    NULL,
    "Are u sure?",
    "Message",
    MB_YESNO | MB_ICONWARNING
);

if (result2 == IDNO)
{
    return 0;
}

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sound1, NULL, 0, NULL);

    HDC hdc = GetDC(NULL);
    if (!hdc) return 1;

    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    DWORD startTime = GetTickCount();

    while (GetTickCount() - startTime < DURATION_MS)
    {
        DWORD elapsed = GetTickCount() - startTime;
        int currentEffect = (elapsed / EFFECT_TIME) % 4;

        switch (currentEffect)
        {
        case 0: effect1(hdc, w, h); break;
        case 1: effect2(hdc, w, h); break;
        case 2: effect3(hdc, w, h); break;
        case 3: effect4(hdc, w, h); break;
        }

        Sleep(30);
    }

    ReleaseDC(NULL, hdc);
    return 0;
}