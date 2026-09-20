### Exercise 01 – OpenMP Barrier



The program was compiled using OpenMP and executed with different thread counts:

```bash
OMP\_NUM\_THREADS=1 ./exercise01
OMP\_NUM\_THREADS=2 ./exercise01
OMP\_NUM\_THREADS=3 ./exercise01
OMP\_NUM\_THREADS=4 ./exercise01
```

The output shows that all threads first execute:

```c
printf("thread # %d\\n", th);
```

Then they reach:

```c
#pragma omp barrier
```

The barrier causes each thread to pause until all other threads have reached the same point in the program. Once every thread reaches the barrier, they are allowed to continue executing the statements that follow it. For instance, when using 4 threads, all four `thread #` messages are displayed before any `Outside Barrier` message is printed. The execution order may vary because the threads run concurrently.



Conclusion: `#pragma omp barrier` provides synchronization by ensuring that no thread proceeds past the barrier until all threads have reached it.



