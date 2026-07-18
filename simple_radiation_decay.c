#include <plplot/plplot.h>
#include <math.h>

#define NPTS 200
#define MAX_TIME 3.0f

const double k = 2.0f;

double f(float y) {
    return -k * y;
}

// Standard: dy/dt = -ky
// Analytic: y = yo * e^(-kt)


int main(int argc, char *argv[]) {
    
    double t[NPTS], y[NPTS], k1, k2, k3, k4, k;          
    double h = MAX_TIME / (NPTS - 1);                     // step size

    y[0] = 5.0f;                                         // initial angle
    t[0] = 0.0f;                                         // initial time
    
    printf("Time Step: %f\n", h);

    for (int i = 0; i < NPTS; i++) {
        
        // Runge-Kutta 4th order method
        k1 = f(y[i]);
        k2 = f(y[i] + k1 * h / 2);
        k3 = f(y[i] + k2 * h / 2);
        k4 = f(y[i] + k3 * h);
        k  = h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;

        y[i+1] = y[i] + k;
        t[i+1] = t[i] + h;

        printf("t[%d] = %f, y[%d] = %f\n", i, t[i], i, y[i]);
    }

    plsdev("pngcairo");                                 // set device     
    plsfnam("simple_radiation.png");                    // set output file name
    
    plinit();                                           // initialize plotting session
    plenv(0.0, MAX_TIME, 0, 7, 0, 0);                   // (xmin, xmax, ymin, ymax, just, axis)  
    pllab("t (s)", "y ()", "Simple Radiation Decay");   // define axis labels + title
    plline(NPTS, t, y);                                 // draw line through n points
    plend();                                            // end plotting session

    return 0;
}