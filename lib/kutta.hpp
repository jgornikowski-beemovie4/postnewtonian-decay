#ifndef KUTTA_HPP
#define KUTTA_HPP


#include <iostream>
#include <cmath>
#include <functional>
#include <vector>


std::vector<double> RK4_step(
    std::function<std::vector<double>(std::vector<double>)> f,
    const std::vector<double>& p,
    const double dt
);


std::vector<std::vector<double>> RK4(
	// function on the RHS of the runge kutta problem
	std::function<std::vector<double>(std::vector<double>)> f, 
    const std::vector<double>& initial_condition,
    const double dt,
    const size_t steps
);


#endif