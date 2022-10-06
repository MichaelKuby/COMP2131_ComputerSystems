#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000
#define AMOUNT 50
#define DELAY 0xfffffff

int sumarray(int input[AMOUNT])
{
    int i;
    int acc = 0;
    for (i = 0; i < AMOUNT; i++)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc += input[i];
    }
    return acc;
}

int sumarray1(int input[AMOUNT])
{
    int i;
    int acc = 0;
    int limit = AMOUNT-1;
    
    for (i = 0; i < limit; i+=2)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc = (acc + input[i]) + input[i+1];
    }

    for (; i < AMOUNT; i++)
        acc += input[i];

    return acc;
}

int sumarray2(int input[AMOUNT])
{
    int i;
    int acc = 0;
    int limit = AMOUNT-1;
    
    for (i = 0; i < limit; i+=2)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc += (input[i] + input[i+1]);
    }

    for (; i < AMOUNT; i++)
        acc += input[i];

    return acc;
}

int sumarray3(int input[AMOUNT])
{
    int i;
    int acc = 0;
    int limit = AMOUNT-4;

    for (i = 0; i < limit; i+=5)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc += (input[i] + input[i+1]);
        acc += (input[i+2] + input[i+3]);
        acc += input[i+4];
    }

    for (; i < AMOUNT; i++)
        acc += input[i];

    return acc;
}

int sumarray4(int input[AMOUNT])
{
    int i;
    int acc0 = 0;
    int acc1 = 0;
    int acc2 = 0;
    int acc3 = 0;
    int acc4 = 0;
    int limit = AMOUNT-4;

    for (i = 0; i < limit; i+=5)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc0 += input[i];
        acc1 += input[i+1];
        acc2 += input[i+2];
        acc3 += input[i+3];
        acc4 += input[i+4];
    }

    for (; i < AMOUNT; i++)
        acc0 += input[i];

    return acc0 + acc1 + acc2 + acc3 + acc4;
}

int sumarray5(int input[AMOUNT])
{
    int i;
    int acc0 = 0;
    int acc1 = 0;
    int acc2 = 0;
    int acc3 = 0;
    int acc4 = 0;
    int acc5 = 0;
    int acc6 = 0;
    int acc7 = 0;
    int acc8 = 0;
    int acc9 = 0;
    int limit = AMOUNT-4;

    for (i = 0; i < limit; i+=10)
    {
        int g;
        for (g = 0; g < DELAY; g++);
        acc0 += input[i];
        acc1 += input[i+1];
        acc2 += input[i+2];
        acc3 += input[i+3];
        acc4 += input[i+4];
        acc5 += input[i+5];
        acc6 += input[i+6];
        acc7 += input[i+7];
        acc8 += input[i+8];
        acc9 += input[i+9];
    }

    for (; i < AMOUNT; i++)
        acc0 += input[i];

    return (acc0 + acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7 + acc8 + acc9);
}

int main ()
{
    int array[AMOUNT];
    int i;
    srand(time(NULL));
    for (i = 0; i < AMOUNT; i++)
        array[i] = rand() % MAX; // use remainder operator to limit the size.
    
    int sum = sumarray(array);
    printf("The sum of the values of the array is %d\n", sum);

    int sum1 = sumarray1(array);
    printf("The sum of the values of the array is %d\n", sum1);

    int sum2 = sumarray2(array);
    printf("The sum of the values of the array is %d\n", sum2);

    int sum3 = sumarray3(array);
    printf("The sum of the values of the array is %d\n", sum3);

    int sum4 = sumarray4(array);
    printf("The sum of the values of the array is %d\n", sum4);

    int sum5 = sumarray5(array);
    printf("The sum of the values of the array is %d\n", sum5);

    exit (0);
}