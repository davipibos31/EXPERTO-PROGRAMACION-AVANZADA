int partition_aleatorio(int arr[], int low, int high) {
    int random_idx = low + rand() % (high - low + 1);
    int pivot = arr[random_idx];
    int i = low - 1;
    int j = high + 1;
  
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
  
        do {
            j--;
        } while (arr[j] > pivot);
  
        if (i >= j)
            return j;
  
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
  
void quicksort_aleatorio(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_aleatorio(arr, low, high);
  
        quicksort_aleatorio(arr, low, pi);
        quicksort_aleatorio(arr, pi + 1, high);
    }
}
