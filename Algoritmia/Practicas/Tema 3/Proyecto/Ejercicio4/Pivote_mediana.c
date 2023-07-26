int find_median(int arr[], int low, int high) {
    int mid = (low + high) / 2;
  
    if (arr[mid] < arr[low])
        swap(&arr[mid], &arr[low]);
    if (arr[high] < arr[low])
        swap(&arr[high], &arr[low]);
    if (arr[mid] < arr[high])
        swap(&arr[mid], &arr[high]);
  
    return arr[high];
}
  
int partition_mediana(int arr[], int low, int high) {
    int pivot = find_median(arr, low, high);
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
  
void quicksort_mediana(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_mediana(arr, low, high);
  
        quicksort_mediana(arr, low, pi);
        quicksort_mediana(arr, pi + 1, high);
    }
}
