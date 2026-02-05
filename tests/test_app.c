#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int* arr = malloc(100 * sizeof(int));
    for (int i = 0; i < 100; ++i) arr[i] = i;
    arr = realloc(arr, 200 * sizeof(int));
    memset(arr, 0, 200 * sizeof(int));
    free(arr);
    return 0;
}
