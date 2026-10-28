#include <stdio.h>

/* Returns the sum of all proper divisors of num. */
int sumProperDivisors(int num)
{
    int sum = 0;

    for (int d = 1; d <= num / 2; d++)
    {
        if (num % d == 0)
        {
            sum += d;
        }
    }

    return sum;
}

int main(void)
{
    int n;
    int pairCount = 0;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 1)
    {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    printf("Amicable pairs up to %d:\n", n);

    for (int a = 2; a <= n; a++)
    {
        int b = sumProperDivisors(a);

        /* b must be different from a and within the given limit.
           a < b ensures each pair is displayed only once. */
        if (b > a && b <= n)
        {
            if (sumProperDivisors(b) == a)
            {
                printf("(%d, %d)\n", a, b);
                pairCount++;
            }
        }
    }

    if (pairCount == 0)
    {
        printf("No amicable pairs found.\n");
    }

    printf("Total amicable pairs: %d\n", pairCount);

    return 0;
}
