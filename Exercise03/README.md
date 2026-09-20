### Exercise 03 – OpenMP Master

The program was compiled and executed using 4 OpenMP threads:

```bash
gcc -fopenmp exercise03.c -o exercise03
OMP\_NUM\_THREADS=4 ./exercise03
```

The output shows that all four threads execute the normal code inside the parallel region.

However, the block inside:

```c
#pragma omp master
{
    printf("Inside Master # %d\\n", omp\_get\_thread\_num());
    printf("Exiting Master\\n");
}
```

is executed **only by thread 0**.

In every execution, the output contains:

```text
Inside Master # 0
```

This shows that `#pragma omp master` always assigns the specified section to the master thread, which is thread 0. The other threads skip the master section and continue executing the rest of the code.



Unlike `#pragma omp single`, the `master` directive does not include an implicit barrier. Therefore, the other threads can continue without waiting for thread 0 to complete the master section.



Conclusion: `#pragma omp master` ensures that only thread 0 executes a particular section of code. The other threads skip this section, and no automatic synchronization occurs after the master block.



