#include <stdio.h>

struct Item
{
    /* data */
    int value;
    int weight;
    double ratio;
};

void swap(struct Item *a, struct Item *b)
{
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Item arr[], int low, int high)
{
    double pivot = arr[high].ratio;
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(arr[j].ratio > pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[high]);
    return i + 1;
}

void quickSort(struct Item arr[], int low, int high)
{
    if (low < high)
    {
        /* code */
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    
}

double fractionalKnapsack(struct Item items[], int n, int W)
{
    double total = 0.0;

    for(int i = 0; i < n; i++)
    {
        if (W == 0)
        {
            /* code */
            break;
        }

        if (items[i].weight <= W)
        {
            /* code */
            total += items[i].value;
            W -= items[i].weight;
        }
        else
        {
            double fraction = (double)W / items[i].weight;
            total += items[i].value * fraction;
            W = 0;
        }
    }
    return total;
}

int main()
{
    struct Item items[3];

    items[0].value = 60;items[0].weight = 10;
    items[1].value = 100;items[1].weight = 20;
    items[2].value = 120;items[2].weight = 30;

    int n = 3, W = 50;

    for (int i = 0; i < n; i++)
    {
        /* code */
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    quickSort(items, 0, n-1);
    double ans = fractionalKnapsack(items, n, W);

    printf("Maximum Value = %.2f\n", ans);

    return 0;

}
// Output: Maximum Value = 240.00

