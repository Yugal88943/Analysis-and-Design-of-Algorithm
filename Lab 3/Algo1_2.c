#include <stdio.h>

// Function to find trapped water using left-right arrays
int trapWater(int arr[], int n) {
    if (n <= 2) return 0; // Not enough bars to trap water

    int left[n], right[n];
    int water = 0;

    // Compute left max
    left[0] = arr[0];
    for (int i = 1; i < n; i++)
        left[i] = (arr[i] > left[i-1]) ? arr[i] : left[i-1];

    // Compute right max
    right[n-1] = arr[n-1];
    for (int i = n-2; i >= 0; i--)
        right[i] = (arr[i] > right[i+1]) ? arr[i] : right[i+1];

    // Calculate trapped water
    for (int i = 0; i < n; i++) {
        int level = (left[i] < right[i]) ? left[i] : right[i];
        if (level > arr[i])
            water += level - arr[i];
    }

    return water;
}

int main() {
    int n;
    printf("Enter number of blocks: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d block heights: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int result = trapWater(arr, n);
    printf("Total trapped water = %d units\n", result);

    return 0;
}
