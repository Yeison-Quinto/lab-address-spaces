#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    printf("%d\n", getpid());
    int i = 0;
    int memoryToUse = atoi(argv[1]);
    int maxTime = argv[2] == NULL ? -1 : atoi(argv[2]);
    int flag = maxTime == -1 ? 1 : 0;
    double actualTime = 0;
    clock_t initialTime = clock();
    clock_t partialTime;
    memoryToUse = memoryToUse * pow(10, 6);
    char *p = malloc(memoryToUse);

    while (i < memoryToUse && (maxTime > (int)floor(actualTime) || flag == 1))
    {
        *(p + i) = 'h';
        i = (i + 1) % memoryToUse;
        partialTime = clock();
        actualTime = (double)(partialTime - initialTime) / CLOCKS_PER_SEC;
        // printf("i: %d \t", i);
        // printf("Tiempo actual: %.8lf\n", actualTime);
    }
    free(p);
    return 0;
}