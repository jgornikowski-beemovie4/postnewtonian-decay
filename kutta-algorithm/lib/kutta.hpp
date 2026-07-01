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