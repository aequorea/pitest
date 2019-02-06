/*
** pitest.c -- test performance of pointerized insertion sort
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long int ulli;

#define ELEMENTS 100000

int A1[ELEMENTS];

// pointerized insertion sort

void pi_sort(int *lp, int *rp)
{
    int *ip, *jp, t;
    
    for (ip = lp+1; ip <= rp; ip++)
    {
        t = *ip;
        for (jp = ip; jp > lp && *(jp-1) > t; jp--)
            *jp = *(jp-1);
        *jp = t;
    }
}

// array indexed insertion sort

void ai_sort(int x[], int *rp)
{ 
    int n = rp-x+1;
    int i, j, t;
 
    for (i = 1; i < n; i++) 
    {
        t = x[i];
        for (j = i; j > 0 && x[j-1] > t; j--)
            x[j] = x[j-1];
        x[j] = t;
    }
}

// get time in nanoseconds

static ulli ns_time()
{
    struct timespec ts;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);   
    return (ulli) ts.tv_sec * 1000000000 + (ulli) ts.tv_nsec;
}

// time a sort routine

ulli time_sort(int *A1, int elements, void (*sort)(int*, int*))
{
    for (int i = 0; i < elements; i++) A1[i] = rand();
    ulli begin = ns_time();
    sort(A1, A1+elements-1);
    return (ns_time()-begin);
}

// entry point

int main()
{
    srand(ns_time());
    ulli ai_time = time_sort(A1, ELEMENTS, ai_sort);
    ulli pi_time = time_sort(A1, ELEMENTS, pi_sort);
    double ratio = (double) pi_time/ (double) ai_time;    
    ulli ai_ms = ai_time/1000000;
    ulli pi_ms = pi_time/1000000;
    double percent = 100.0*(1.0-ratio)/ratio;
    printf(" %d: pointerized %llu ms, array indexed %llu ms -- %2.1lf %%\n", ELEMENTS, pi_ms, ai_ms, percent);
}

