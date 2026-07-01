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