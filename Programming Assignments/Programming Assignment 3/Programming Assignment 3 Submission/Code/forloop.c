#include <stdio.h>
#include <stdlib.h>

long forsum (long start, long finish)
{ 
    long acc = start;
    long i; 

    for (i = start+1; i <= finish; i++)
    {
        acc += i;
    }
    return acc;    
}

long dosum (long start, long finish)
{
    long acc = start;
    long i = start+1; 

    do
    {
        acc += i;
        i++;
    } while (i <= finish);
    return acc;
}

long whilesum (long start, long finish)
{
    long acc = start;
    long i = start+1; 

    while (i <= finish)
    {
        acc += i;
        i++;
    }    
    return acc;
}

long gotosum (long start, long finish)
{
    long acc = start;
    long i = start +1;

    loop:
        acc += i;
        i++;
        if (i <= finish)
            goto loop;
    return acc;
}

int main ()
{
    long a = 5;
    long b = 5;
    long c = dosum(a, b);
    printf("The sum of all of the numbers a - b = %ld\n", c);
}