### Exercise 04 – OpenMP Parallel For and Collapse

The program was compiled and executed using 4 OpenMP threads:

```bash
gcc -fopenmp exercise04.c -o exercise04
OMP\_NUM\_THREADS=4 ./exercise04
```

### Without `collapse(2)`

The code:

```c
#pragma omp parallel for
for (int r = 1; r <= 5; r++)
    for (int k = 1; k <= 10; k++) {
        printf("r = %d, k = %d, thread # = %d\\n",
               r, k, omp\_get\_thread\_num());
    }
```

parallelizes only the outer `r` loop.

There are 5 outer-loop iterations:

```text
r = 1, 2, 3, 4, 5
```

These iterations are distributed among the available threads. Once a thread receives an `r` value, that same thread executes the complete inner `k` loop from `1` to `10`.

For example:

```text
Thread 0 → r = 1 and r = 2
Thread 1 → r = 3
Thread 2 → r = 4
Thread 3 → r = 5
```

Therefore, the inner `k` loop is not separately parallelized.

### With `collapse(2)`

The directive was changed to:

```c
#pragma omp parallel for collapse(2)
```

The two nested loops are combined into one iteration space.

Since:

```text
5 r iterations × 10 k iterations = 50 iterations
```

OpenMP distributes these 50 `(r, k)` combinations among the available threads.

For 4 threads, the workload is approximately:

```text
Thread 0 → 13 iterations
Thread 1 → 13 iterations
Thread 2 → 12 iterations
Thread 3 → 12 iterations
```

The output shows that a single `r` value can now be divided between different threads. For example, one thread may execute:

```text
r = 2, k = 1
r = 2, k = 2
r = 2, k = 3
```

while another thread continues with:

```text
r = 2, k = 4
...
r = 2, k = 10
```

Conclusion: Without `collapse(2)`, only the outer `r` loop is divided among the threads, with each thread executing the complete inner `k` loop for its assigned `r` values.



With `collapse(2)`, the two nested loops are combined into a single set of 50 `(r, k)` iterations, allowing the iterations to be distributed more evenly across the available threads.

## 

