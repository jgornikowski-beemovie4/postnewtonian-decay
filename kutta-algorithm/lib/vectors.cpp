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


#include "vectors.hpp"

// Drukuje elegancko sformatowany wektor jako wiersz
std::ostream& operator<<(std::ostream& os, const std::vector<double>& v)
{
    os << "Vector: [ ";
    for (size_t i = 0; i < v.size(); i++)
    {
        os << std::fixed << std::setprecision(6) << v.at(i) << " ";
    }
    os << "]";
    return os;
}

// Poniższe kilka funckji ma za zadanie przedłużyć funkcjonalność wektorów dodając
// opcje takie jak mnożenie przez skalar czy sumowanie wektorów (które nie są
// zaimplementowane natywnie w ten sposób)

// Dodawanie wektorów
std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b)
{
    // Sprawdzenie równości wymiarów
    assert(a.size() == b.size() && "Vector addition size mismatch");

    std::vector<double> result;
    // Pre-zajęcie pamięci
    result.reserve(a.size());

    std::transform(a.begin(), a.end(), b.begin(), 
                   std::back_inserter(result), std::plus<double>());
    return result;
}

// Odejmowanie wektorów
std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b)
{
    assert(a.size() == b.size() && "Vector subtraction size mismatch");

    std::vector<double> result;
    result.reserve(a.size());

    std::transform(a.begin(), a.end(), b.begin(), 
                   std::back_inserter(result), std::minus<double>());
    return result;
}

// Lewostronne mnożenie przez skalar
std::vector<double> operator*(const double a, const std::vector<double>& v)
{
    std::vector<double> result;
    result.reserve(v.size());
    std::transform(v.begin(), v.end(), std::back_inserter(result),
                   [a](const double& element) { return a * element; });
    return result;
}

// Prawostronne mnożenie przez skalar
std::vector<double> operator*(const std::vector<double>& v, const double a)
{
    // Wykonuje mnożenie lewostronne ręcznie zamieniając kolejność argumentów
    return a * v; 
}

// Nadpisanie wektora pomnożonego o skalar
std::vector<double>& operator*=(std::vector<double>& v, const double a)
{
    std::transform(v.begin(), v.end(), v.begin(),
                   [a](const double& element) { return a * element; });
    return v;
}