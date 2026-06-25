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