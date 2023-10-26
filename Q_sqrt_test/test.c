#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define INCOMPREHENSIBLE_NUMBER 100000000
#define NUMBER 0.748343

float randomFloat()
{
    return (float)rand() / (float)RAND_MAX;
} // Generate random float thanks: https://stackoverflow.com/questions/1694827/random-float-number

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
}

float S_rsqrt(float number)
{
    return 1 / sqrt(number);
}

double time_func(float (*func)(float number), float arr[])
{
    double time_spent;
    clock_t begin = clock();
    for (int i; i <= INCOMPREHENSIBLE_NUMBER; i++)
    {
        func(arr[i % 100]);
    }
    clock_t end = clock();

    return time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
}

double time_funcStatic(float (*func)(float number), float number)
{
    double time_spent;
    clock_t begin = clock();
    for (int i; i <= INCOMPREHENSIBLE_NUMBER; i++)
    {
        func(number);
    }
    clock_t end = clock();

    return time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
}

int main()
{
    float floatArray[100];
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        floatArray[i] = randomFloat();
    }

    printf("Q_rsqrt function took: %lf\n", time_func(Q_rsqrt, floatArray));
    printf("S_rsqrt function took %lf\n", time_func(S_rsqrt, floatArray));

    printf("Q_rsqrt function took: %lf\n", time_funcStatic(Q_rsqrt, NUMBER));
    printf("S_rsqrt function took %lf", time_funcStatic(S_rsqrt, NUMBER));

    // Strange when given a static number slow square root is better but with more numbers Quick square root is better

    return 0;
}