#include <iostream>
#include <cmath>   
#include <vector>
#include <functional>
#include <cassert>
#include <iomanip>
#include <chrono>


#include "writers.hpp"
#include "vectors.hpp"
#include "kutta.hpp"


// Source - https://stackoverflow.com/a/4609795
// Posted by user79758, modified by community. See post 'Timeline' for change history
// Retrieved 2026-06-07, License - CC BY-SA 4.0
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}



double cdot(const std::vector<double>& a, const std::vector<double>& b) {
	double sum = 0.0;
	for (size_t i = 0; i < a.size(); i++) {
		sum += a[i] * b[i];
	}
	return sum;
}


double norm(const std::vector<double>& a) {
	return pow(cdot(a, a), 0.5);
}


std::vector<double> calculate_relative_acceleration(
	const std::vector<double>& x,
	const std::vector<double>& y,
	const double a, // = Gm
	const double b // = K \eta G^2 m^2 c^-5
	) {

	std::vector<double> y_dot = 
		- a / pow(norm(x), 3) * x
	    - (8.0 / 5.0) * b / pow(norm(x), 3) * 
	    (
	        - (
	            18.0 * pow(norm(y), 2) 
	            + (2.0 / 3.0) * (a / norm(x)) 
	            - 25.0 * pow(cdot(x, y) / norm(x), 2)
	        ) 
	        * (cdot(x, y) / pow(norm(x), 2)) 
	        * x
	        +
	        (
	            6.0 * pow(norm(y), 2) 
	            - 2.0 * (a / norm(x)) 
	            - 15.0 * pow(cdot(x, y) / norm(x), 2)
	        ) 
	        * y
	    );

	return y_dot;
}


std::vector<double> pulsar(const std::vector<double>& q) {
	// the q vector contains
	// Z comprised of x and y vectors,
	// parameters m and v (4 numbers)
	/*
		q vector construction:
		- x (3 numbers),
		- y (3 numbers),
		- v (3 numbers),
		- m (1 number),
		- eta (1 number),
	*/
	const std::vector<double> x(q.begin(), q.begin() + 3);
	const std::vector<double> y(q.begin()+3, q.begin() + 6);

	const double a = q.at(6);
	const double b = q.at(7);

	const std::vector<double> new_y = 
		calculate_relative_acceleration(
			x, y, a, b
			);

	const std::vector<double> zeros = {0.0, 0.0};

	std::vector<double> output;
	output.reserve(8); // Pre-allocate memory
	output.insert(output.end(), y.begin(), y.end());
	output.insert(output.end(), new_y.begin(), new_y.end());
	output.insert(output.end(), zeros.begin(), zeros.end());

	return output;
}


std::vector<size_t> locate_extrema(
	const std::vector<double>& v
	) {
	if (v.size() <= 1) {
		return {};
	}
	std::vector<size_t> extrema;

	// find points where the differential changes sign
	int differential_sign = sgn(v.at(1) - v.at(0));

	for (size_t i = 0; i < v.size() - 1; i++) {
		int current_sign = sgn(v.at(i+1) - v.at(i));

		if (current_sign != differential_sign) {
			differential_sign = current_sign;
			// return the average of the two points
			extrema.push_back(i);
		} 
	}
	return extrema;
}


int main(void) {

    // We use strictly SI units: meters, kilograms, seconds.
    
    // a = G * m (Units: m^3 / s^2)
    const double a = 3.753e20 / 1e9; 
    
    // b = K * eta * (Gm)^2 / c^5 (Units: m * s)
    // Calculated with K = 1e6, eta = 0.2499, c = 299792458
    const double K_over_1e6 = 1e3;
    const double b = 1.453e4 / 1e3 * K_over_1e6;  

    const std::vector<double> x0 = {7.466e8 / 1e3, 0.0, 0.0};
    const std::vector<double> y0 = {0.0, 9.016e5 / 1e3, 0.0};

    std::vector<double> initial_condition;
    initial_condition.reserve(8);
    initial_condition.insert(
        initial_condition.end(), x0.begin(), x0.end()
    );
    initial_condition.insert(
        initial_condition.end(), y0.begin(), y0.end()
    );  

    const std::vector<double> model_parameters = {a, b};
    initial_condition.insert(
        initial_condition.end(), 
        model_parameters.begin(), model_parameters.end()
    );

    // -------------------------------------------------
    const double below_second_scaling = 1;
   	const double dt = 1.0 * below_second_scaling;

    const size_t steps = 24 * 3600 * 2 / 3 
    	* (1.0 / (double)below_second_scaling);


    std::cout 
        << "RK4 time evolution computation:" << std::endl
        << "Parameters:" << std::endl
        << ">> " << steps << " temporal steps" << std::endl
        << ">> " << dt << " of time increment [s]" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // ----------------------------------------------------
    std::vector<std::vector<double>> RK4_matrix = RK4(
        pulsar, initial_condition, dt, steps
    );
    // ----------------------------------------------------

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << std::endl << "Elapsed time: " 
        << elapsed.count() << " seconds" << std::endl << std::endl;

    std::vector<double> distances;
    distances.reserve(steps);

    for (size_t i = 0; i < RK4_matrix.size(); i++) {
        const std::vector<double> x(
            RK4_matrix.at(i).begin(),
            RK4_matrix.at(i).begin()+3
        );
        const double distance = norm(x);
        distances.push_back(distance);
    }

    write_1D("distances.csv", distances);

    const std::vector<size_t> extrema = locate_extrema(
    	distances
    	);
    std::cout << "Distances' size: " << distances.size() << std::endl;
    std::cout << "Extrema count: " << extrema.size() << std::endl;
    std::cout << "Extrema indices: " << extrema.size() << std::endl;
    
    for (size_t i = 0; i < extrema.size(); i++) {
    	std::cout << extrema.at(i) << std::endl;
    }
    

    const size_t max_1 = extrema.at(0);
    const size_t min_1 = extrema.at(1);
    const size_t max_2 = extrema.at(2);
    const size_t min_2 = extrema.at(3);

    // we picked the index to the left before, now we average
    const double averaged_distance_1 
    	= 0.5 * (distances.at(max_1) + distances.at(max_1 + 1));

    const double averaged_distance_2 
    	= 0.5 * (distances.at(max_2) + distances.at(max_2 + 1));

    std::cout << "Averaged distance 1: " 
    	<< averaged_distance_1 << std::endl;

    std::cout << "Averaged distance 2: " 
    	<< averaged_distance_2 << std::endl;

    const double distance_change 
    	= averaged_distance_1 - averaged_distance_2; // in km


    const double orbit_time_over_year = 7.752 * 3600.0 / 31557600;
    std::cout 
    	<< "Distance shrinkage: "
    	<< (distance_change / orbit_time_over_year) / (1e6 * K_over_1e6) * 1000.0 * 0.5 // i think this is double the result
    	<< " meters" << std::endl;
    std::cout 
    	<< "Time shrinkage: "
    	<< (((double)(min_1 - (min_2 - min_1)) * dt) / orbit_time_over_year) / (1e6 * K_over_1e6)
    	<< " seconds" << std::endl;

    return 0;
}