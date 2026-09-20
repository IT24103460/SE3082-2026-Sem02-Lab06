#include <omp.h>
#include <stdio.h>

#define NPOINTS 1000
#define MAXITER 2000

int main() {

    const double xmin = -2.0;
    const double xmax = 0.5;
    const double ymin = 0.0;
    const double ymax = 1.125;

    long long numoutside = 0;

    double dx = (xmax - xmin) / NPOINTS;
    double dy = (ymax - ymin) / NPOINTS;

    double tstart = omp_get_wtime();

    /*
     * Each thread gets its own section of the outer loop.
     * numoutside is combined safely using reduction.
     */
    #pragma omp parallel reduction(+:numoutside)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        int start_row = thread_id * NPOINTS / num_threads;
        int end_row = (thread_id + 1) * NPOINTS / num_threads;

        for (int i = start_row; i < end_row; i++) {

            double cy = ymin + i * dy;

            for (int j = 0; j < NPOINTS; j++) {

                double cx = xmin + j * dx;

                double zx = 0.0;
                double zy = 0.0;

                int iteration = 0;

                while (iteration < MAXITER) {

                    double zx2 = zx * zx;
                    double zy2 = zy * zy;

                    /*
                     * |z| > 2
                     * Equivalent to:
                     * zx^2 + zy^2 > 4
                     */
                    if (zx2 + zy2 > 4.0) {
                        numoutside++;
                        break;
                    }

                    double new_zy = 2.0 * zx * zy + cy;
                    double new_zx = zx2 - zy2 + cx;

                    zx = new_zx;
                    zy = new_zy;

                    iteration++;
                }
            }
        }
    }

    double tstop = omp_get_wtime();

    long long total_points =
        (long long)NPOINTS * NPOINTS;

    long long numinside =
        total_points - numoutside;

    /*
     * We calculated only the upper half.
     * Multiply by 2 because the Mandelbrot set
     * is symmetric about the real axis.
     */
    double box_area =
        (xmax - xmin) * (ymax - ymin);

    double area =
        2.0 * box_area *
        ((double)numinside / total_points);

    printf("Total points   = %lld\n", total_points);
    printf("Inside points  = %lld\n", numinside);
    printf("Outside points = %lld\n", numoutside);

    printf("Estimated Mandelbrot area = %.8f\n", area);

    printf("Execution time = %f seconds\n",
           tstop - tstart);

    return 0;
}