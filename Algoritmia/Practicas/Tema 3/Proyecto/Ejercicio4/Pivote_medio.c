int partition(int arr[], int low, int high) {
    int pivot = arr[(low + high) / 2];
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
  
void quicksort_medio(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
  
        quicksort_medio(arr, low, pi);
        quicksort_medio(arr, pi + 1, high);
    }
}
