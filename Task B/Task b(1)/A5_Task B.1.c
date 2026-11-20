#include <stdio.h>

long long calls = 0;

/* Linear Recursive Power */
long long power_linear(long long base, int exp)
{
    calls++;

    if (exp == 0)
        return 1;

    return base * power_linear(base, exp - 1);
}

/* Divide and Conquer Recursive Power */
long long power_fast(long long base, int exp)
{
    long long half, sq;

    calls++;

    if (exp == 0)
        return 1;

    half = power_fast(base, exp / 2);
    sq = half * half;

    if (exp % 2 != 0)
        return base * sq;

    return sq;
}

/* Duplicate Recursive Call Version */
long long power_fast_dup(long long base, int exp)
{
    long long sq;

    calls++;

    if (exp == 0)
        return 1;

    sq = power_fast_dup(base, exp / 2) *
         power_fast_dup(base, exp / 2);

    if (exp % 2 != 0)
        return base * sq;

    return sq;
}

/* Recursive Digital Root */
long long digital_root_rec(long long n)
{
    long long sum = 0;

    if (n < 0)
        n = -n;

    if (n < 10)
        return n;

    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }

    return digital_root_rec(sum);
}

/* Iterative Square and Multiply Power */
long long power_iterative(long long base, int exp)
{
    long long result = 1;
    long long b = base;
    int e = exp;

    while (e > 0)
    {
        if (e % 2 == 1)
            result *= b;

        b *= b;
        e /= 2;
    }

    return result;
}

int main(void)
{
    int ns[4] = {10, 100, 1000, 10000};
    int i, n;

    /* Complete the Code Check */
    calls = 0;
    printf("linear: %lld in ",
           power_linear(2, 30));
    printf("%lld calls\n", calls);

    calls = 0;
    printf("fast  : %lld in ",
           power_fast(2, 30));
    printf("%lld calls\n", calls);

    calls = 0;
    printf("fast_dup: %lld in ",
           power_fast_dup(2, 30));
    printf("%lld calls\n", calls);

    /* Validation Tests */
    printf("\n--- Validation Tests ---\n");

    printf("digital_root(0) = %lld\n",
           digital_root_rec(0));

    printf("digital_root(1) = %lld\n",
           digital_root_rec(1));

    printf("digital_root(9875) = %lld\n",
           digital_root_rec(9875));

    printf("digital_root(123456) = %lld\n",
           digital_root_rec(123456));

    printf("power_linear(5, 0) = %lld, power_fast(5, 0) = %lld\n",
           power_linear(5, 0), power_fast(5, 0));

    printf("power_linear(5, 1) = %lld, power_fast(5, 1) = %lld\n",
           power_linear(5, 1), power_fast(5, 1));

    printf("power_linear(3, 4) = %lld, power_fast(3, 4) = %lld, iter = %lld\n",
           power_linear(3, 4),
           power_fast(3, 4),
           power_iterative(3, 4));

    /* Call Count Comparison */
    printf("\n--- Call Counts (base = 1) ---\n");

    for (i = 0; i < 4; i++)
    {
        n = ns[i];

        calls = 0;
        power_linear(1, n);
        printf("n=%5d -> linear calls: %lld", n, calls);

        calls = 0;
        power_fast(1, n);
        printf(" | fast calls: %lld\n", calls);
    }

    return 0;
}
