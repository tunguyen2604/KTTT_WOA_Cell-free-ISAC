#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 20          
#define MAX_ITER 20  
#define X_MIN -10     
#define X_MAX  10    

double f(double x) {
    return x*x - 2*x + 1;
}

double rand_double(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

int main() {
    srand(time(NULL));

    double whales[N];      
    double best_x;         
    double best_f = 1e7;  

    for (int i = 0; i < N; i++) {
        whales[i] = rand_double(X_MIN, X_MAX);
        double val = f(whales[i]);
        if (val < best_f) {
            best_f = val;
            best_x = whales[i];
        }
    }

    for (int t = 0; t < MAX_ITER; t++) {
        double a = 2.0 - 2.0 * (double)t / MAX_ITER;  

        for (int i = 0; i < N; i++) {
            double r1 = (double)rand() / RAND_MAX;
            double r2 = (double)rand() / RAND_MAX;

            double A = 2.0 * a * r1 - a;   // vector A
            double C = 2.0 * r2;           // vector C

            double p = (double)rand() / RAND_MAX;  

            double new_x;

            if (p < 0.5) {
                if (fabs(A) < 1) {
                    // encircling
                    double D = fabs(C * best_x - whales[i]);
                    new_x = best_x - A * D;
                } else {
                    // search for prey (exploration)
                    int rand_idx = rand() % N;
                    double rand_x = whales[rand_idx];
                    double D = fabs(C * rand_x - whales[i]);
                    new_x = rand_x - A * D;
                }
            } else {
                // spiral updating
                double b = 1;
                double l = rand_double(-1, 1);
                double D = fabs(best_x - whales[i]);
                new_x = D * exp(b * l) * cos(2 * 3.14 * l) + best_x;
            }

            if (new_x < X_MIN) new_x = X_MIN;
            if (new_x > X_MAX) new_x = X_MAX;

            whales[i] = new_x;

            double val = f(new_x);
            if (val < best_f) {
                best_f = val;
                best_x = new_x;
            }
        }
        printf("Loop %d:\n", t+1);
        printf("x = %.6f\n", best_x);
        printf("f(x) = %.10f\n", best_f);
    }

    

    return 0;
}
