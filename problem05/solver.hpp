#ifndef _SOLVER_HPP
#define _SOLVER_HPP

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>


#include "constants.hpp"

void matrix_vector_product(const double matrix[][CAP],
                           const double vector[],
                           double result[], const int dim)
{
    // loop over rows of matrix
    for (int i = 0; i < dim; i++)
    {
        // initialize product element for this row
        result[i] = 0;
        // loop over columns of matrix
        for (int j = 0; j < dim; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void submatrix(const double matrix[][CAP],
               int row, int col,
               double result[][CAP], const int dim)
{
    int r = 0, c = 0;
    for(int i = 0; i < dim; i++){
        if (i != row){
            c = 0;
            for(int j = 0; j < dim; j++){
                if(j != col){
                    result[r][c] = matrix[i][j];
                    c++;
                }
            }
            r++;
        }    
    }
}

double determinant(const double matrix[][CAP], const int dim)
{
    if (dim == 1)
        return matrix[0][0];
    
    if (dim == 2)
        return((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));

    double det = 0.0;
    double sub[CAP][CAP];

    for (int k = 0; k < dim; k++){
        submatrix(matrix, 0, k, sub, dim);
        double minor = determinant(sub, dim-1);
        det += pow(-1, k) * matrix[0][k] * minor;
    }

    return det;
    
}

void replace_column(const double matrix[][CAP],
                    int col, const double vector[],
                    double result[][CAP], const int dim)
{
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){
            if (j == col)
                result[i][j] = vector[i];
            else
                result[i][j] = matrix[i][j];
        }
    }
}

void cramers_rule(const double matrix[][CAP],
                  const double vector[],
                  double result[], const int dim)
{
    double detA = determinant(matrix, dim);
    double temp[CAP][CAP];
    for (int i = 0; i < dim; i++){
        replace_column(matrix, i, vector, temp, dim);
        double detDj = determinant(temp, dim);
        result[i] = detDj / detA;
    }
}

int parse_file_input(std::string filename,
                     double matrix[][CAP],
                     double vector[])
{
    std:: ifstream file_read(filename);
    std:: string line;
    int N = 0;
    int A = 0;
    int B = 0;
    bool aFlag = false;
    bool bFlag = false;
    
    while (getline(file_read, line)){
        // Get Dimensions
        if (line[0] == 'N'){
            int posEq = line.find('=');
            N = std:: atoi(line.substr(posEq + 1).c_str());
        }

        // Start of matrix A
        if (line[0] == 'A'){
            aFlag = true;
            bFlag = false;
        }

        // Start of vector b
        if (line[0] == 'b'){
            aFlag = false;
            bFlag = true;
        }

        // Read matrix A
        if ((line[0] != 'N') && (line[0] != 'A') && (line[0] != 'b') && aFlag && !bFlag) {
            int col = 0;
            for (int i = 0; i < line.size(); i++) { 
                std::string num_str;
                while (i < line.size()) {
                    num_str += line[i++];
                }
                if (col >= N) return -1; // too many entries in this row
                matrix[A][col++] = std::atof(num_str.c_str());
            }
            if (col != N) return -1; // row does not have expected number of elements
            A++;
        }

        if ((line[0] != 'N') && (line[0] != 'A') && (line[0] != 'b') && bFlag) {
            int col = 0;
            for (size_t i = 0; i < line.size(); i++) {
                std::string num_str;
                while (i < line.size()) {
                    num_str += line[i++];
                }
                if (col >= 1) return -1; // only 1 value per row for b
                vector[B++] = std::atof(num_str.c_str());
            }
        }
    }

    if (A != N || B != N)
        return -1;

    return 0;
    

}

#endif