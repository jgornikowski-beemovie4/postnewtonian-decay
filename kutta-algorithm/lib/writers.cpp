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


#include "writers.hpp"

/*
    Write to file
    The data of a 1D matrix u is saved inside "data.csv"
*/
void write_1D(
	const char* filename,
    const std::vector<double>& u
) {
	const size_t size = u.size();

    FILE *f = fopen(filename, "w");

    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < size - 1; i++) {
        fprintf(f, "%lf,", u[i]);
    }
    fprintf(f, "%lf", u[size-1]);

    fclose(f);
}


/*
    Write to file
    The data of a 2D matrix u is saved inside "data.csv"
*/
void write_2D(
	const char* filename,
    const std::vector<std::vector<double>>& u
) {
    const size_t steps = u.size();
    const size_t N = u.at(0).size();

    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (size_t i = 0; i < steps; i++) {
        for (size_t j = 0; j < N-1; j++) {
            fprintf(f, "%lf,", u[i][j]);
        }
        fprintf(f, "%lf\n", u[i][N-1]);
    }

    fclose(f);
}