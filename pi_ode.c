#define _USE_MATH_DEFINES  // Enables M_PI in math.h
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function prototypes
void dydt(double t, double *z, double *dzdt);
void rk4_step(void (*func)(double, double*, double*), double t, double *z, double h);

int main() {
    int max_iterations;
    
    // Ask user for number of iterations
    printf("Enter number of iterations: ");
    if (scanf("%d", &max_iterations) != 1 || max_iterations <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    FILE *fp = fopen("pi_convergence.csv", "w");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write CSV header
    fprintf(fp, "step_size,pi_estimate,error\n");

    double h = 0.1;           // Initial step size
    double pi_estimate = 0.0;
    int iteration = 0;

    while (iteration < max_iterations) {
        double z[2] = {1.0, 0.0};  // x(0), y(0)
        double t = 0.0;
        double t_final = 4.0;
        double prev_y = z[1];
        int found = 0;

        while (t <= t_final && !found) {
            // Detect sign change in y (from + to -)
            if (z[1] < 0 && prev_y > 0) {
                // Linear interpolation between steps
                double frac = -prev_y / (z[1] - prev_y);
                pi_estimate = t - h + frac * h;
                found = 1;
            }

            prev_y = z[1];
            rk4_step(dydt, t, z, h);
            t += h;
        }

        double error = fabs(pi_estimate - M_PI);
        fprintf(fp, "%.10f,%.10f,%.2e\n", h, pi_estimate, error);
        printf("Iteration %d: Step size: %.6f -> Pi est: %.10f, Error: %.2e\n", iteration, h, pi_estimate, error);

        h /= 2.0;  // Halve step size for next iteration
        iteration++;
    }

    printf("\n✅ Finished %d iterations.\n", max_iterations);
    fclose(fp);
    return 0;
}

// Define the ODE system: dx/dt = -y, dy/dt = x
void dydt(double t, double *z, double *dzdt) {
    dzdt[0] = -z[1]; // dx/dt = -y
    dzdt[1] =  z[0]; // dy/dt =  x
}

// RK4 integration step
void rk4_step(void (*func)(double, double*, double*), double t, double *z, double h) {
    double k1[2], k2[2], k3[2], k4[2];
    double z_temp[2];

    func(t, z, k1);
    for (int i = 0; i < 2; i++)
        z_temp[i] = z[i] + 0.5 * h * k1[i];
    func(t + 0.5*h, z_temp, k2);

    for (int i = 0; i < 2; i++)
        z_temp[i] = z[i] + 0.5 * h * k2[i];
    func(t + 0.5*h, z_temp, k3);

    for (int i = 0; i < 2; i++)
        z_temp[i] = z[i] + h * k3[i];
    func(t + h, z_temp, k4);

    for (int i = 0; i < 2; i++)
        z[i] += (h / 6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}