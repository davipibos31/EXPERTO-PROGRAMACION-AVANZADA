#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    // code to be measured

    QueryPerformanceCounter(&end);
    interval = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;

    printf("%f\n", interval);

    return 0;
}