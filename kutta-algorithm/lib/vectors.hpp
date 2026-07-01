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


#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <functional>

// Drukuje elegancko sformatowany wektor jako wiersz
std::ostream& operator<<(std::ostream& os, const std::vector<double>& v);

// Dodawanie wektorów
std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b);

// Odejmowanie wektorów
std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b);

// Lewostronne mnożenie przez skalar
std::vector<double> operator*(const double a, const std::vector<double>& v);

// Prawostronne mnożenie przez skalar
std::vector<double> operator*(const std::vector<double>& v, const double a);

// Nadpisanie wektora pomnożonego o skalar
std::vector<double>& operator*=(std::vector<double>& v, const double a);

#endif