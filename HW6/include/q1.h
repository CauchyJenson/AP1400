#ifndef Q1_H
#define Q1_H
#include<functional>
#include<cmath>
namespace q1{

const double delta = 1e-5;

double gradient_descent(double init, double step, std::function<double(double)> func);

template<typename T, typename F>
T gradient_descent(T init, T step){
    return gradient_descent(init, step, F());
}

double gradient_descent(double init, double step, std::function<double(double)> func){
    auto x = init;
    double d = (func(x + delta) - func(x))/delta;
    while(abs(d) > delta){
        x -= step * d;
        d = (func(x + delta) - func(x))/delta;
    }
    return x;
}

}

#endif //Q1_H