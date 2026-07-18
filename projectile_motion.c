    #include <plplot/plplot.h>
    #include <math.h>

    #define NPTS 200
    #define MAX_TIME 20.0f

    const double g = 9.81f;
    const double m = 10.0f;
    const double k = 2.0f;

    double μ = k * k / m;

    double a_x(float v_x) {
        return -μ * v_x;   
    }

    double a_y(float v_y) {
        return -g -μ * v_y;   
    }

    // a_x = - μ * v_x
    // a_y = - g - μ * v_y

    int main(int argc, char *argv[]) {
        
        double t[NPTS], y[NPTS], x[NPTS], v_y[NPTS], v_x[NPTS];
        double k1y, k2y, k3y, k4y, k1v, k2v, k3v, k4v, ky, kv;          
        double l1x, l2x, l3x, l4x, l1v, l2v, l3v, l4v, lx, lv;

        double h = MAX_TIME / (NPTS - 1);                                   // step size

        t[0] =    0.0f;                                                     // initial time
        x[0] =    0.0f;                                                     // initial horizontal position
        y[0] =    0.0f;                                                     // initial vertical   position
        v_x[0] = 10.0f;                                                     // initial horizontal velocity
        v_y[0] = 30.0f;                                                     // initial vertical   velocity
        
        for (int i = 0; i < NPTS; i++) {
            
            // Runge-Kutta 4th order method

            // For Vertical Axis
            k1y  = v_y[i];
            k1v  = a_y(v_y[i]);

            k2y  = v_y[i]       + k1v * h / 2;
            k2v  = a_y(v_y[i]   + k1v * h / 2);
            
            k3y  = v_y[i]       + k2v * h / 2;
            k3v  = a_y(v_y[i]   + k2v * h / 2);
            
            k4y  = v_y[i]       + k3v * h;
            k4v  = a_y(v_y[i]   + k3v * h);

            ky  = h * (k1y + 2  * k2y + 2 * k3y + k4y) / 6;
            kv  = h * (k1v + 2  * k2v + 2 * k3v + k4v) / 6;

            v_y[i+1] = v_y[i] + kv;
            y[i+1] =   y[i] + ky;

            // For Vertical Axis
            l1x  = v_x[i];
            l1v  = a_x(v_x[i]);

            l2x  = v_x[i]       + l1v * h / 2;
            l2v  = a_x(v_x[i]   + l1v * h / 2);
            
            l3x  = v_x[i]       + l2v * h / 2;
            l3v  = a_x(v_x[i]     + l2v * h / 2);
            
            l4x  = v_x[i]       + l3v * h;
            l4v  = a_x(v_x[i]     + l3v * h);

            lx  = h * (l1x + 2  * l2x + 2 * l3x + l4x) / 6;
            lv  = h * (l1v + 2  * l2v + 2 * l3v + l4v) / 6;

            v_x[i+1] = v_x[i] + lv;
            x[i+1] =   x[i] + lx;
            
            t[i+1] = t[i] + h;
            printf("x[%d] = %f, y[%d] = %f\n", i, x[i], i, y[i]);
        }

        plsdev("pngcairo");                                                 // set device     
        plsfnam("projectile_motion.png");                                   // set output file name
        
        plinit();                                                           // initialize plotting session
        plenv(0.0, 400, -400, 300, 0, 0);                              // (xmin, xmax, ymin, ymax, just, axis)  
        pllab("x (m)", "y (m)", "Projectile Motion with Netwonian Drag");   // define axis labels + title
        plline(NPTS, x, y);                                                 // draw line through n points
        plend();                                                            // end plotting session

        return 0;
    }