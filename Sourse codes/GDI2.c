#include <windows.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")

DWORD WINAPI shake( LPVOID lpParam ) {
    HDC hdc;
    int w = GetSystemMetrics( 0 );
    int h = GetSystemMetrics( 1 );
    while (1) {
        hdc = GetDC( 0 );
        BitBlt( hdc, rand( ) % 50, rand( ) % 50, w, h, hdc, rand( ) % 50, rand( ) % 50, SRCCOPY );
        Sleep( 10 );
        ReleaseDC( 0, hdc );
    }
    return 0;
}

DWORD WINAPI SlowFade( LPVOID lpParam ) {
    int w = GetSystemMetrics( 0 );
    int h = GetSystemMetrics( 1 );
    while (1) {
        HDC hdc = GetDC( 0 );
        HBRUSH brush = CreateSolidBrush( RGB( rand( ) % 255, rand( ) % 255, rand( ) % 255 ) );
        SelectObject( hdc, brush );
        BitBlt( hdc, 0, 0, w, h, hdc, -1, 0, 0x1900ac010e );
        BitBlt( hdc, 0, 0, w, h, hdc, w - 1, 0, SRCCOPY );
        DeleteObject( brush );
        ReleaseDC( 0, hdc );
    }
    return 0;
}

DWORD WINAPI SlowTrain( LPVOID lpParam ) {
    int w = GetSystemMetrics( 0 );
    int h = GetSystemMetrics( 1 );
    while (1) {
        HDC hdc = GetDC( 0 );
        HBRUSH brush = CreateSolidBrush( RGB( rand( ) % 255, rand( ) % 255, rand( ) % 255 ) );
        BitBlt( hdc, 0, 0, w, h, hdc, -1, 0, SRCCOPY );
        BitBlt( hdc, 0, 0, w, h, hdc, w - 1, 0, SRCCOPY );
        BitBlt( hdc, 0, 0, w, h, hdc, 0, -1, SRCCOPY );
        BitBlt( hdc, 0, 0, w, h, hdc, 0, h - 1, SRCCOPY );
        DeleteObject( brush );
        ReleaseDC( 0, hdc );
    }
    return 0;
}

DWORD WINAPI Viberate( LPVOID lpParam ) {
    while (1) {
        HDC hdc = GetDC( 0 );
        int x = GetSystemMetrics( 0 );
        int y = GetSystemMetrics( 1 );
        StretchBlt( hdc, -5, -5, x + 10, y + 10, hdc, 0, 0, x, y, SRCCOPY );
        StretchBlt( hdc, 5, 5, x - 10, y - 10, hdc, 0, 0, x, y, SRCCOPY );
        ReleaseDC( 0, hdc );
    }
    return 0;
}

VOID WINAPI sound1( ) {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof( buffer ); ++t)
        buffer[t] = ( char ) ( t * ( t >> 2 | t >> 4 | t >> 8 ) );

    WAVEHDR header = { buffer, sizeof( buffer ), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutWrite( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutUnprepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutClose( hWaveOut );
}

VOID WINAPI sound2( ) {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof( buffer ); ++t)
        buffer[t] = ( char ) ( t * ( t >> 8 | t >> 5 | t >> 8 ) );

    WAVEHDR header = { buffer, sizeof( buffer ), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutWrite( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutUnprepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutClose( hWaveOut );
}

VOID WINAPI sound3( ) {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof( buffer ); ++t)
        buffer[t] = ( char ) ( t * (t >> 6 | t << 1 ) );

    WAVEHDR header = { buffer, sizeof( buffer ), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutWrite( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutUnprepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutClose( hWaveOut );
}

VOID WINAPI sound4( ) {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen( &hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL );
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof( buffer ); ++t)
        buffer[t] = ( char ) ( ( t ^ ( t >> 6 | t << 1 ) ) * ( t >> 5 | t << 3 | t >> 3 ) | t >> 2 | t << 1 );

    WAVEHDR header = { buffer, sizeof( buffer ), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutWrite( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutUnprepareHeader( hWaveOut, &header, sizeof( WAVEHDR ) );
    waveOutClose( hWaveOut );
}

int main( ) {

    if (MessageBoxW( 0, L"Run GDI2.exe?", L"GDI2.exe", MB_YESNO | MB_ICONWARNING ) == IDNO) {
        ExitProcess( 0 );
    }
    else
    {
        if (MessageBoxW( 0, L"Are you sure?", L"GDI2.exe", MB_YESNO | MB_ICONWARNING ) == IDNO) {
            ExitProcess( 0 );
        }
        else
        {

            Sleep( 5000 );
            HANDLE thread1 = CreateThread( 0, 0, shake, 0, 0, 0 );
            sound1( );
            Sleep( 30000 );
            TerminateThread( thread1, 0 );
            CloseHandle( thread1 );
            RedrawWindow( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
            Sleep( 1000 );
            HANDLE thread2 = CreateThread( 0, 0, SlowFade, 0, 0, 0 );
            sound2( );
            Sleep( 30000 );
            TerminateThread( thread2, 0 );
            CloseHandle( thread2 );
            RedrawWindow( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
            Sleep( 1000 );
            HANDLE thread3 = CreateThread( 0, 0, SlowTrain, 0, 0, 0 );
            sound3( );
            Sleep( 30000 );
            TerminateThread( thread3, 0 );
            CloseHandle( thread3 );
            RedrawWindow( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
            Sleep( 1000 );
            HANDLE thread4 = CreateThread( 0, 0, Viberate, 0, 0, 0 );
            sound4( );
            Sleep( 30000 );
        }
    }
}