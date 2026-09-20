### Exercise 06 – Array Multiplication Using Strip Mining

The program performs element-wise multiplication of two arrays of size `1,000,000`:

```c
C\[i] = A\[i] \* B\[i];
```

The array is divided into fixed-size strips of `1024` elements. OpenMP distributes these strips among multiple threads, while `#pragma omp simd` allows vectorized processing inside each strip.

The program was compiled using:

```bash
gcc -std=c11 -O2 -fopenmp exercise06.c -o exercise06
```

The results were correct for all tested thread counts:

```text
C\[0] = 6.00
C\[999999] = 6.00
```

Execution times:

```text
1 Thread  = 0.009612 seconds
2 Threads = 0.008849 seconds
3 Threads = 0.005010 seconds
4 Threads = 0.007130 seconds
```

The execution time generally improved when multiple threads were used, although small timing variations can occur because of thread scheduling and system load.

Conclusion :Strip mining divides the large array into smaller blocks, OpenMP distributes those blocks among threads, and SIMD processes multiple elements efficiently inside each strip.

