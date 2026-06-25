#ifndef WRITERS_HPP
#define WRITERS_HPP


#include <vector>
#include <iostream>

/*
    Write to file
    The data of a 1D matrix u is saved inside "data.csv"
*/
void write_1D(
	const char* filename,
    const std::vector<double>& u
);


/*
    Write to file
    The data of a 2D matrix u is saved inside "data.csv"
*/
void write_2D(
	const char* filename,
    const std::vector<std::vector<double>>& u
);


#endif