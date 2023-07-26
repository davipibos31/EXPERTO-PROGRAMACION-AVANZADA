void shell_sort(int arr[], int n) {
    int i, j, gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            int temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
