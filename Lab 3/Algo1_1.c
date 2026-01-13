#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int maxSum = INT_MIN;

    // Brute force: check all subarrays
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
            if (sum > maxSum) maxSum = sum;
        }
    }

    printf("Largest Subarray Sum (Brute Force) = %d\n", maxSum);
    return 0;
}
