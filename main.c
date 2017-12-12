
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>



double num_random() {
    double num = (double) random() / (double) RAND_MAX;
    if((double) random() / (double) RAND_MAX < 0.5) {
        num *= -1;
    }
    return num;
}

int main(int argc, char* argv[]) {
    long int number_tosses, number_in_circle;
    int thread_count, i;
    double x, y, distance;

    if (argc != 3)
    thread_count = strtol(argv[1], NULL, 10);
    number_tosses = strtoll(argv[2], NULL, 10);
    if (thread_count < 1 || number_tosses < 1) {
        printf("Invalid Inputs");
    }

    number_in_circle =0;
    srandom(0);
    omp_set_num_threads(thread_count);
#pragma omp parallel for num_threads(thread_count) \
      reduction(+: number_in_circle) private(x, y, distance)
    for (i = 0; i < number_tosses; i++) {
        x = num_random();
        y = num_random();
        distance = x*x + y*y;

        if (distance <= 1) {
            number_in_circle += 1;
        }
    }
    double pi = 4*number_in_circle/((double) number_tosses);
    printf("Value of PI= %.14f\n", pi);
    return 0;
}  /* main */




