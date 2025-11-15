#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include <cstdlib>
#include <string>

#include "constants.hpp"

/* Provided functions */
int index(int row, int col)
{
    /* Calculates a 1D index from a row and column.
        A 2D matrix can be represented in memory with a 1D array,
        assuming that indices 0 to COLS-1 are the items in the first row,
        indices COLS to 2*COLS-1 are the items in the second row, etc.
        So if we want to access data at a specific row and column,
        we calculate that index as row*COLS + column
    */
    return row * COLS + col;
}

int column_index(std::string field)
{
    /* Uses parallel arrays to determine the integer column index
        given the string field name.
        FIELDS is defined in constants.hpp. This function does a linear
        search over the FIELDS array to find and return the index of the
        column with the specified field name.
        Returns -1 if field name is not valid.
    */
    for (int c = 0; c < COLS; c++)
    {
        if (FIELDS[c] == field)
        {
            return c;
        }
    }
    return -1;
}

void initialize(double *database)
{
    /* Fills the dynamic array database with data from the constant DATA.
        Note the use of the index function to get the index for the dynamic array
        database, versus using double brackets for the the static 2D array DATA.
    */
    for (int r = 0; r < ENTRIES; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            database[index(r, c)] = DATA[r][c];
        }
    }
}

/* Functions to implement */
bool search(const std::string field, const double value,
            const double *database, const int rows)
{
    // Find column index for given field
    int col = -1;
    for (int i = 0; i < COLS; i++){
        if (FIELDS[i] == field){
            col = i;
            break;
        }
    }
    // Invalid field name
    if (col == -1)
        return false;
    
    // Search each row for given value in that column
    for (int row = 0; row < rows; row++){
        int idx = index(row, col);
        if (std:: abs(database[idx] - value) < THRESHOLD)
            return true;
    }
    return false;
}

bool add_entry(const double new_row[],
               double *&database, int &rows)
{
    // Check for duplicate ID
    if (search("ID", new_row[0], database, rows))
        return false;
    
    // Allocate a larger array
    double *new_database = new double[(rows + 1) * COLS];

    // Copy old data to new array
    for (int i = 0; i < rows * COLS; i++){
        new_database[i] = database[i];
    }

    // Copy new row to the end
    for (int col = 0; col < COLS; col++){
        new_database[rows * COLS + col] = new_row[col];
    }

    // Free old memory
    delete[] database;

    // Update pointer and row count
    database = new_database;
    rows++;

    // Success
    return true;
}

bool remove_entry(const double id,
                  double *&database, int &rows)
{
    // Check if ID exists
    if (!search("ID", id, database, rows))
        return false;
    
    // Find which row has ID 
    int remove_row = -1;
    for (int r = 0; r < rows; r++){
        int idx = r * COLS;
        if (std::abs(database[idx] - id) < THRESHOLD){
            remove_row = r;
            break;
        }
    }

    // Not found
    if (remove_row == -1)
        return false;

    // Allocate a smaller array
    double *new_database = new double[(rows - 1) * COLS];

    // Copy all rows but removed
    int new_index = 0;
    for (int r = 0; r < rows; r++){
        if (r != remove_row){
            for(int c = 0; c < COLS; c++){
                new_database[new_index++] = database[index(r, c)];
            }
        }
    }

    // Free old memory
    delete[] database;

    // Update pointer and row count
    database = new_database;
    rows--;

    // Success
    return true;

}

#endif