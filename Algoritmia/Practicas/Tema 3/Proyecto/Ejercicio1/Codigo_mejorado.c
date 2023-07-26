void burbuja_mejorada(int arr[], int n) {
    int i, j;
    int intercambios;
    for (i = 0; i < n - 1; i++) {
        intercambios = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                intercambios++;
            }
        }
        if (intercambios == 0) {
            // Si no se hicieron intercambios en la pasada, el arreglo está ordenado.
            break;
        }
    }
}
