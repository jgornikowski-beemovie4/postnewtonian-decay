/*
 * Copyright (c) 2026 Jakub Górnikowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */


#include "kutta.hpp"


std::vector<double> RK4_step(
    std::function<std::vector<double>(std::vector<double>)> f,
    const std::vector<double>& p,
    const double dt
) {
	const size_t N = p.size();
	// p is the value of the vector at the previous step,
	// q is the new value
	const std::vector<double> k1 = f(p);

	std::vector<double> p_midpoint(N, 0.0);
	for (size_t i = 0; i < N; i++) {
		p_midpoint[i] = p[i] + 0.5 * dt * k1[i];
	}
	const std::vector<double> k2 = f(p_midpoint);

	std::vector<double> p_midpoint_refined(N, 0.0);
	for (size_t i = 0; i < N; i++) {
		p_midpoint_refined[i] = p[i] + 0.5 * dt * k2[i];
	}
	const std::vector<double> k3 = f(p_midpoint_refined);

	std::vector<double> p_endpoint(N, 0.0);
	for (size_t i = 0; i < N; i++) {
		p_endpoint[i] = p[i] + dt * k3[i];
	}
	const std::vector<double> k4 = f(p_endpoint);

	// output
	std::vector<double> q(N, 0.0);
	for (size_t i = 0; i < N; i++) {
		q[i] = p[i] + (1.0 / 6.0) * dt * (
			k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]
			);
	}
	return q;
}


std::vector<std::vector<double>> RK4(
	// function on the RHS of the runge kutta problem
	std::function<std::vector<double>(std::vector<double>)> f, 
    const std::vector<double>& initial_condition,
    const double dt,
    const size_t steps
) {
	// vector dimension (number of equations)
	const size_t N = initial_condition.size();

	std::vector<std::vector<double>> matrix(
		steps, std::vector<double>(N, 0.0)
		);
	// assign the first step to the 0-th row
	for (size_t i = 0; i < N; i++) {
		matrix[0][i] = initial_condition[i];
	}

	for (size_t i = 0; i < steps - 1; i++) {
		matrix[i+1] = RK4_step(
			f, matrix[i], dt
			);
	}
	return matrix;
}