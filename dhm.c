#include <plplot/plplot.h>
#include <math.h>

#define NPTS 200
#define MAX_TIME 20.0f

const double c = 0.4f;
const double k = 4.0f;
const double m = 1.0f;

double f(float y, float v) {
    return (-c/m) * v + (-k/m) * y;   
}


int main(int argc, char *argv[]) {
    
    double t[NPTS], y[NPTS], v[NPTS];
    double k1y, k2y, k3y, k4y, k1v, k2v, k3v, k4v, ky, kv;          
    double h = MAX_TIME / (NPTS - 1);                              // step size

    t[0] = 0.0f;                                                   // initial time
    v[0] = 0.0f;                                                   // initial velocity
    y[0] = 5.0f;                                                   // initial position
    
    for (int i = 0; i < NPTS; i++) {
        
        // Runge-Kutta 4th order method
        k1y  = v[i];
        k1v  = f(y[i], v[i]);

        k2y  = v[i]   + k1v * h / 2;
        k2v  = f(y[i] + k1y * h / 2, v[i]   + k1v * h / 2);
        
        k3y  = v[i]   + k2v * h / 2;
        k3v  = f(y[i] + k2y * h / 2, v[i]   + k2v * h / 2);
        
        k4y  = v[i]   + k3v * h;
        k4v  = f(y[i] + k3y * h,     v[i]   + k3v * h);

        ky  = h * (k1y + 2  * k2y + 2 * k3y + k4y) / 6;
        kv  = h * (k1v + 2  * k2v + 2 * k3v + k4v) / 6;

        v[i+1] = v[i] + kv;
        y[i+1] = y[i] + ky;
        t[i+1] = t[i] + h;

        printf("t[%d] = %f, y[%d] = %f\n", i, t[i], i, y[i]);
    }

    plsdev("pngcairo");                                             // set device     
    plsfnam("shm.png");                                             // set output file name
    
    plinit();                                                       // initialize plotting session
    plenv(0.0, MAX_TIME, -7, 7, 0, 0);                               // (xmin, xmax, ymin, ymax, just, axis)  
    pllab("t (s)", "y (m)", "Damped Harmonic Oscillator");          // define axis labels + title
    plline(NPTS, t, y);                                             // draw line through n points
    plend();                                                        // end plotting session

    return 0;
}