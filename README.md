# pitest
### Pointerized insertion sort test

"Pointerizing" code is not exactly a time-honored speedup technique. If you look at the first edition of [K&R](https://archive.org/details/TheCProgrammingLanguageFirstEdition) that came out in 1978, on page 93 you'll find they say:

> "In C there is a strong relationship between pointers and arrays, strong enough that pointers and arrays should really be treated simultaneously. Any operation that can be achieved by array subscripting can also be done with pointers. The pointer version will in general be faster but, at least to the uninitiated, somewhat harder to grasp immediately."

The earliest benchmark I could find where pointerized code was directly compared with a non-pointerized routine was in the book "Writing efficient programs, 1982" by Jon Bentley. On page 95 we see tests of a pointerized insertion sort where the pointerized version compiled with optimizations ran more than twice as fast as the non-pointerized version (fragments M6 vs. M5). These tests were done by John Majernik on a PDP 11/70, a computer from 1975.

But as early as 1997 in an interesting series of benchmarks in the [October 1997 issue of Unix Review](http://web.archive.org/web/20010509103120/http://www.unixreview.com/articles/1997/9710/9710expbi/expbi.htm), Jon Bentley found that in the cases he was testing, pointerized code was rarely if ever faster than the normal array indexed code. In six cases on three different machines where he looked at optimized code for routines that accessed arrays and then had their inner loops pointerized, only one case showed significant speedup, one case ran the same, and four cases actually ran slower when pointerized. He suggested, 

> "The displacement addressing modes of modern architectures make array indexing so fast that programmers (usually) need no longer bother with "pointerizing" array accesses."

Here we show that things can change. In the 21st century with some architectures and compilers, although it's not quite like the 70s all over again, some speed has returned.

Here we compare the performance of an array indexed insertion sort routine:

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


We tested these routines on linux using the gcc compiler with -O3 optimizations on three different computers. We sorted arrays of 100,000 random integers. The percentage speed improvement of the pointerized insertion sort over the array indexed one were:

    Intel Core I5: 24.5 %
    AMD Athlon 64:  6.3 %
     Raspberry pi:  0.3 %
 
So at least on the x64 machines, some advantage can be gained from pointerized code, and even on the Raspberry pi, nothing was lost from the pointerization.

More complete data may be found [here](https://github.com/aequorea/pisort/tree/master/bm).

If you would like to try out the benchmark, make sure you have installed gcc, download the archive and run bench.py. To reduce the possibility of "linker bias" tilting the results, it builds and tests six different versions of the benchmark executable where the three different object files are linked in six different ways. The data is collected and averaged over runs of these executables.
