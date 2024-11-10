#include <cmath>


double* dampedHarmonicOscillator(double* X, double t){

    ++t; //unused variable 

    
    const double m {8}; // point mass
    const double k {0.5}; // spring constant
    const double c {3.2}; // damping coefficient
    
    const double& x {X[0]};
    const double& xDot {X[1]};
    
    double xDoubleDot {};
    xDoubleDot = - c/m * xDot - k/m * x;

    double* Xdot {nullptr};
    Xdot = new double[2]{xDot, xDoubleDot};

    return Xdot;
}


double* doublePendulum(double* x, double t){

    /*
    
    d/dt [θ1, θ2, dθ1/dt, dθ2/dt]^T = F(θ1, θ2, dθ1/dt, dθ2/dt) =

    = [dθ1/dt, dθ2/dt, g1(θ1, θ2, dθ1/dt, dθ2/dt), g2(θ1, θ2, dθ1/dt, dθ2/dt)]^T

    g1 = (f1 - a1*f2)/(1 - a1*a2)

    g2 = (f2 - a2*f1)/(1 - a1*a2)

    a1 = l2/l1 * ( m2/(m1 + m2) ) * cos(θ1 - θ2)
    a2 = l1/l2 * cos(θ1 - θ2)

    f1 = - l2/l1 * ( m2/(m1 + m2) ) * dθ2/dt * sin(θ1 - θ2) - g/l1 * sin(θ1)
    f2 = l1/l2 * dθ1/dt * sin(θ1 - θ2) - g/l2 * sin(θ2)

    */

    ++t; //unused variable 
    
    const double m1{1}, m2{1};  // point mass
    const double l1{1}, l2{1};  // rod length
    const double g{10};         // gravitational acceleration

    const double& theta1{x[0]}, theta2{x[1]};
    const double& theta1_dot {x[2]}, theta2_dot{x[3]};

    double f1{}, f2{}, a1{}, a2{}, g1{}, g2{};
    f1 = (
        - l2/l1 * ( m2/(m1 + m2) ) * theta2_dot * sin(theta1 - theta2) 
        - g/l1 * sin(theta1)
    );

    f2 = l1/l2 * theta1_dot * sin(theta1 - theta2) - g/l2 * sin(theta2) ;

    a1 = l2/l1 * ( m2/(m1 + m2) ) * cos(theta1 - theta2) ;
    a2 = l1/l2 * cos(theta1 - theta2) ;

    g1 = (f1 - a1*f2)/(1 - a1*a2) ;
    g2 = (f2 - a2*f1)/(1 - a1*a2) ;


    double* xDot {nullptr};
    xDot = new double[4]{theta1_dot, theta2_dot, g1, g2};

    return xDot;

}
