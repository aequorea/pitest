## pitest
#### Pointerized insertion sort test

"Pointerizing" code is not exactly a time-honored speedup technique. If you look at the first edition of [K&R](https://archive.org/details/TheCProgrammingLanguageFirstEdition) that came out in 1978, on page 93 you'll find they say:

> "In C there is a strong relationship between pointers and arrays, strong enough that pointers and arrays should really be treated simultaneously. Any operation that can be achieved by array subscripting can also be done with pointers. The pointer version will in general be faster but, at least to the uninitiated, somewhat harder to grasp immediately."

The earliest benchmark I could find where pointerized code was directly compared with a non-pointerized routine was in the book "Writing efficient programs, 1982" by Jon Bentley. On page 95 we see tests of a pointerized insertion sort where the pointerized version compiled with optimizations ran more than twice as fast as the non-pointerized version (fragments M6 vs. M5). These tests were done by John Majernik on a PDP 11/70, a computer from 1975.

But as early as 1997 in an interesting series of benchmarks in the [October 1997 issue of Unix Review](http://web.archive.org/web/20010509103120/http://www.unixreview.com/articles/1997/9710/9710expbi/expbi.htm), Jon Bentley found that in the cases he was testing, pointerized code was rarely if ever faster than the normal array indexed code. In six cases on three different machines where he looked at optimized code for routines that accessed arrays and then had their inner loops pointerized, only one case showed any speedup, one case ran the same, and four cases actually ran slower when pointerized. He suggested, 

> "The displacement addressing modes of modern architectures make array indexing so fast that programmers (usually) need no longer bother with "pointerizing" array accesses."

Here we see that in recent times, at least with some architectures and compilers, some speed has returned.

In a manner similar to what has been done in the past, to test the speed of pointerized code, we compare the performance of an array indexed insertion sort routine:

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
    
which is substantially similar to the is2() routine found in [Jon Bentley's Unix Review article from Oct. 1997](http://web.archive.org/web/20010509103120/http://www.unixreview.com/articles/1997/9710/9710expbi/expbi.htm), with a "pointerized" version of the same:

    void pi_sort(int *lp, int *rp)
    {
        int *ip, *jp, t;
    
        for (ip=lp+1; ip<=rp; ip++)
        {
            t = *ip;
            for (jp=ip; jp>lp && *(jp-1) > t; jp--)
                *jp = *(jp-1);
            *jp = t;
        }
    }

We tested these routines on linux using the gcc compiler with -O3 optimization. We sorted arrays of 100,000 random integers. Here are some results. The percentages shown are the improvement of the pointerized routine over the indexed one.

    Intel(R) Core(TM) i5-4690 CPU @ 3.50GHz
    gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0

    100000: indexed 1127 ms, pointerized 901 ms -- 25.2 %


    Intel(R) Pentium(R) CPU  J2900  @ 2.41GHz
    gcc (Ubuntu 7.3.0-27ubuntu1~18.04) 7.3.0

    100000: indexed 4170 ms, pointerized 3685 ms -- 13.2 %
    
    
      ARMv7 Processor rev 4 (v7l)
    gcc (Raspbian 6.3.0-18+rpi1+deb9u1) 6.3.0 20170516

    100000: indexed 9073 ms, pointerized 8997 ms -- 0.8 %




