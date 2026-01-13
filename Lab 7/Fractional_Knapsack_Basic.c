#include <stdio.h>

//Simple max function using if-else
double max(double a, double b)
{
    if (a > b)
        return a;
    else
        return b;
}

double basicFractionalKnapsack(int val[], int wt[], int n, int W)
{  
    double bestValue = 0.0;
    
    double f1, f2, f3;
    //Try fractions 0, 0.1, 0.2 ... 1.0
    for ( f1 = 0; f1 <= 1.0; f1 = f1 + 0.1)
    {
        /* code */
        for (f2 = 0; f2 <= 1.0; f2 = f2 + 0.1)
        {
            /* code */
            for (f3 = 0; f3 <= 1.0; f3 = f3 + 0.1)
            {
                /* code */
                double usedWeight = f1 * wt[0] + f2 * wt[1] + f3 * wt[2];
                double usedValue = f1 * val[0] + f2 * val[1] + f3 * val[2];

                if (usedWeight <= W)
                {
                    /* code */
                    bestValue = max(bestValue, usedValue);
                }
            }
        }
        
    }
    return bestValue;

}

int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int n = 3;
    int W = 50;

    double result = basicFractionalKnapsack(val, wt, n, W);

    printf("Maximum Value = %.2f\n", result);

    return 0;
}
// Output:Maximum Value = 238.00
