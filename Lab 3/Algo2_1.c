#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int maxSum = INT_MIN, currentSum = 0;

    for (int i = 0; i < n; i++) {
        currentSum += arr[i];
        if (currentSum > maxSum) maxSum = currentSum;
        if (currentSum < 0) currentSum = 0;  // reset if negative
    }

    printf("Largest Subarray Sum (Kadane's) = %d\n", maxSum);
    return 0;
}
