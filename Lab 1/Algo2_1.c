// Find Max & Min element from Array
// Algorithm 2 (Efficient – Pairwise Comparison)

#include <stdio.h>

int main() {
    int n, i;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int max, min;

    // Initialization
    if (n % 2 == 0) {
        if (arr[0] > arr[1]) {
            max = arr[0];
            min = arr[1];
        } else {
            max = arr[1];
            min = arr[0];
        }
        i = 2; // start from index 2
    } else {
        max = min = arr[0];
        i = 1; // start from index 1
    }

    // Process in pairs
    while (i < n - 1) {
        if (arr[i] > arr[i+1]) {
            if (arr[i] > max) max = arr[i];
            if (arr[i+1] < min) min = arr[i+1];
        } else {
            if (arr[i+1] > max) max = arr[i+1];
            if (arr[i] < min) min = arr[i];
        }
        i += 2;
    }

    printf("Maximum = %d\n", max);
    printf("Minimum = %d\n", min);

    return 0;
}

