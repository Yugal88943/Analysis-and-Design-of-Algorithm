#include <stdio.h>

// Function to find trapped water using two pointers
int trapWater(int arr[], int n) {
    int left = 0, right = n-1;
    int leftMax = 0, rightMax = 0, water = 0;

    while (left < right) {
        if (arr[left] < arr[right]) {
            if (arr[left] >= leftMax)
                leftMax = arr[left];
            else
                water += leftMax - arr[left];
            left++;
        } else {
            if (arr[right] >= rightMax)
                rightMax = arr[right];
            else
                water += rightMax - arr[right];
            right--;
        }
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
