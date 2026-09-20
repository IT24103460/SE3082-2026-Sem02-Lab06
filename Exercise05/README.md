### Exercise 05 – Fibonacci Using OpenMP Tasks

The recursive Fibonacci program was parallelized using OpenMP tasks.

The program was compiled and executed using 4 threads:

```bash
gcc -fopenmp exercise05.c -o exercise05
OMP\_NUM\_THREADS=4 ./exercise05
```

For `n = 25`, the program produced:

```text
Fibonacci(25) = 75025
```

The calls `fib(n-1)` and `fib(n-2)` are executed as separate OpenMP tasks, allowing available threads to process the recursive calculations in parallel. `taskwait` ensures that both tasks finish before their results are added.

Conclusion: OpenMP task parallelization enables the independent recursive Fibonacci calculations to run concurrently across multiple threads.

### 

