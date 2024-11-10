#ifndef _ODE_FUNCTION_H_
#define _ODE_FUNCTION_H_

#include <vector>

class OdeFunction
{
private:
    /* data */
public:
    OdeFunction(/* args */) = default;
    virtual ~OdeFunction() = default ;
    
    virtual std::vector<double> operator() (std::vector<double> x, double t) const = 0; // pure virtual function

};


class DampedHarmonicOscillator: public OdeFunction{

private:

    static constexpr double default_m {1}, default_k{1}, default_c{1};

    double pointMass;
    double springConst;
    double dampingCoeff;

public:

    DampedHarmonicOscillator();
    DampedHarmonicOscillator(double m);
    DampedHarmonicOscillator(double m, double k);
    DampedHarmonicOscillator(double m, double k, double c);

    std::vector<double> operator() (std::vector<double> x, double t) const override; 

};


class DoublePendulum: public OdeFunction{

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

    private:

        static constexpr double default_m1 {1}, default_m2{1};
        static constexpr double default_l1{1}, default_l2{1};
        static constexpr double default_g{10};

        double pointMass1;
        double pointMass2;
        double length1;
        double length2;
        double gravitationalAcceleration;
    
    public:

        DoublePendulum();
        DoublePendulum(double m1, double m2, double l1, double l2);
        DoublePendulum(double m1, double m2, double l1, double l2, double g);

        std::vector<double> operator() (std::vector<double> x, double t) const override;

};

#endif
