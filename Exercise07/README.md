### Exercise 07 – Mandelbrot Set Using OpenMP

The Mandelbrot area calculation was parallelized using OpenMP and tested with 1, 2, 3, and 4 threads.

```bash
OMP\_NUM\_THREADS=1 ./exercise07
OMP\_NUM\_THREADS=2 ./exercise07
OMP\_NUM\_THREADS=3 ./exercise07
OMP\_NUM\_THREADS=4 ./exercise07
```

### Results

Threads | Execution Time

1 | 1.843485 s

2 | 1.668519 s

3 | 1.264360 s

4 | 0.987326 s



All runs produced identical results:

```text
Total points   = 1000000
Inside points  = 268716
Outside points = 731284
Estimated Mandelbrot area = 1.51152750
```

OpenMP divides the Mandelbrot grid among the available threads. A reduction is used to safely combine the number of outside points calculated by each thread.

Conclusion : The result remained identical for all thread counts, while execution time decreased as more threads were used. The 4-thread execution was the fastest at approximately `0.987` seconds.

