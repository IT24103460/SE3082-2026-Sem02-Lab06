### Exercise 02 – OpenMP Single

The program was compiled and executed using 4 OpenMP threads:

```bash
gcc -fopenmp exercise02.c -o exercise02
OMP\_NUM\_THREADS=4 ./exercise02
```

The output shows that all four threads are created and execute the normal statements inside the parallel region.

However, the code inside:

```c
#pragma omp single
{
    printf("Inside Single # %d\\n", omp\_get\_thread\_num());
    printf("Exiting Single\\n");
}
```

is executed by **only one thread**.

Different executions showed different threads entering the `single` section, for example:

```text
Inside Single # 1
Inside Single # 2
Inside Single # 3
```

This shows that `#pragma omp single` does **not select a specific thread number**. Any one thread from the parallel team can execute the single section.

After the single section finishes, all threads continue and execute:

```c
printf("Hi again from thread # %d\\n", omp\_get\_thread\_num());
```

There is also an implicit barrier at the end of the `single` region, which causes the other threads to wait until the thread executing the `single` section has completed.



Conclusion: `#pragma omp single` ensures that a specific section of code is executed only once by a single thread, while the remaining threads skip that section. The thread selected to execute the section is not predetermined and may vary each time the program runs.



