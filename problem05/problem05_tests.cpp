#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "solver.hpp"
#include "constants.hpp"

/* Provided test cases */

/* Matrix vector product tests */
TEST_CASE("Test matrix vector product dim 2", "[product]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {1, -2};
    double result[dim];
    double test[dim] = {-2, 8.1};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 3", "[product]")
{
    const int dim = 3;
    double matrix[dim][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector[dim] = {1, -2, 3};
    double result[dim];
    double test[dim] = {3, 0, 0};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 4", "[product]")
{
    const int dim = 4;
    double matrix[dim][CAP] = {{0, 10, 4, -2},
                               {-3, -17, 1, 2},
                               {1, 1, 1, 0},
                               {8, -34, 16, -10}};
    double vector[dim] = {4, 0, 2, 6};
    double result[dim];
    double test[dim] = {-4, 2, 6, 4};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

TEST_CASE("Test matrix vector product dim 5", "[product]")
{
    const int dim = 5;
    double matrix[dim][CAP] = {{1, 1, 0, 1, 0},
                               {1, 0, 1, 0, 1},
                               {0, 300, 0, -300, 0},
                               {0, 0, 150, 0, -150},
                               {45000, -22500, -45000, 0, 0}};
    double vector[dim] = {36.0 / 7.0, -81.0 / 7.0, 153.0 / 14.0, 129.0 / 7.0, -57.0 / 14.0};
    double result[dim];
    double test[dim] = {12, 12, -9000, 2250, 0};
    matrix_vector_product(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }
}

/* Test submatrix */
TEST_CASE("Test submatrix dim 2", "[solver]")
{
    const int dim = 2;
    int row = 0, col = 0;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double result[dim - 1][CAP];
    double test[dim - 1][CAP] = {-3.2};
    submatrix(matrix, row, col, result, dim);

    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }


    const int dim2 = 3;
    row = 1, col = 1;
    double matrix2[dim2][CAP] = {{0.4, 1.2, 6.3}, {1.7, -3.2, 2.9}, {-4.1, 0.8, 6.1}};
    double result2[dim2 - 1][CAP];
    double test2[dim2 - 1][CAP] = {{0.4, 6.3}, {-4.1, 6.1}};
    submatrix(matrix2, row, col, result2, dim2);

    for (int i = 0; i < dim2 - 1; i++)
    {
        for (int j = 0; j < dim2 - 1; j++)
        {
            REQUIRE(abs(result2[i][j] - test2[i][j]) <= THRESHOLD);
        }
    }


    const int dim3 = 4;
    row = 3, col = 1;
    double matrix3[dim3][CAP] = {{0.4, 1.2, 6.3, 9.1}, {1.7, -3.2, 2.9, -1.5}, {-4.1, 0.8, 6.1, -9.4}, {11.3, -1.2, 1.8, 3.3}};
    double result3[dim3 - 1][CAP];
    double test3[dim3 - 1][CAP] = {{0.4, 6.3, 9.1}, {1.7, 2.9, -1.5}, {-4.1, 6.1, -9.4}};
    submatrix(matrix3, row, col, result3, dim3);

    for (int i = 0; i < dim3 - 1; i++)
    {
        for (int j = 0; j < dim3 - 1; j++)
        {
            REQUIRE(abs(result3[i][j] - test3[i][j]) <= THRESHOLD);
        }
    }


    const int dim4 = 5;
    row = 4, col = 2;
    double matrix4[dim4][CAP] = {{0.4, 1.2, 6.3, 9.1, -0.9}, {1.7, -3.2, 2.9, -1.5, 4.4}, {-4.1, 0.8, 6.1, -9.4, 3.7}, {11.3, -1.2, 1.8, 3.3, 0.1}, {0.8, -8.1, 4.4, 2.5, 3.7}};
    double result4[dim4 - 1][CAP];
    double test4[dim4 - 1][CAP] = {{0.4, 1.2, 9.1, -0.9}, {1.7, -3.2, -1.5, 4.4}, {-4.1, 0.8, -9.4, 3.7}, {11.3, -1.2, 3.3, 0.1}};
    submatrix(matrix4, row, col, result4, dim4);

    for (int i = 0; i < dim4 - 1; i++)
    {
        for (int j = 0; j < dim4 - 1; j++)
        {
            REQUIRE(abs(result4[i][j] - test4[i][j]) <= THRESHOLD);
        }
    }
}

/* Test determinant */
TEST_CASE("Test determinant base case", "[solver]")
{
    double matrix[1][CAP] = {3.4};
    double test = 3.4;
    double result = determinant(matrix, 1);

    REQUIRE(abs(result - test) <= THRESHOLD);

    double matrix2[2][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double test2 = -3.32;
    double result2 = determinant(matrix2, 2);

    REQUIRE(abs(result2 - test2) <= THRESHOLD);

    double matrix3[3][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double test3 = 3;
    double result3 = determinant(matrix3, 3);

    REQUIRE(abs(result3 - test3) <= THRESHOLD);

    double matrix4[4][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double test4 = -1568;
    double result4 = determinant(matrix4, 4);

    REQUIRE(abs(result4 - test4) <= THRESHOLD);

    double matrix5[5][CAP] = {{1, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 300, 0, -300, 0}, {0, 0, 150, 0, -150}, {45000, -22500, -45000, 0, 0}};
    double test5 = 1.4175 * pow(10, 10);
    double result5 = determinant(matrix5, 5);

    REQUIRE(abs(result5 - test5) <= THRESHOLD);
}

/* Column replace tests */
TEST_CASE("Test col replace dim 2", "[solver]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {1, -2};
    double result[dim][CAP];
    int col = 0;
    double test[dim][CAP] = {{1, 1.2}, {-2, -3.2}};
    replace_column(matrix, col, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result[i][j] - test[i][j]) <= THRESHOLD);
        }
    }

    const int dim2 = 3;
    double matrix2[dim2][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector2[dim2] = {1, -2, 4};
    double result2[dim2][CAP];
    col = 0;
    double test2[dim2][CAP] = {{1, 1, 1}, {-2, -1, -1}, {4, 2, 1}};
    replace_column(matrix2, col, vector2, result2, dim2);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result2[i][j] - test2[i][j]) <= THRESHOLD);
        }
    }

    const int dim3 = 4;
    double matrix3[dim3][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double vector3[dim3] = {1, -2, 4, 6};
    double result3[dim3][CAP];
    col = 0;
    double test3[dim3][CAP] = {{1, 10, 4, -2}, {-2, -17, 1, 2}, {4, 1, 1, 0}, {6, -34, 16, -10}};
    replace_column(matrix3, col, vector3, result3, dim3);

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            REQUIRE(abs(result3[i][j] - test3[i][j]) <= THRESHOLD);
        }
    }

}

/* Test Cramer's rule */
TEST_CASE("Test cramer's rule dim 2", "[solver]")
{
    const int dim = 2;
    double matrix[dim][CAP] = {{0.4, 1.2}, {1.7, -3.2}};
    double vector[dim] = {-2, 8.1};
    double result[dim];
    double test[dim] = {1, -2};
    cramers_rule(matrix, vector, result, dim);

    for (int i = 0; i < dim; i++)
    {
        REQUIRE(abs(result[i] - test[i]) <= THRESHOLD);
    }

    const int dim2 = 3;
    double matrix2[dim2][CAP] = {{2, 1, 1}, {1, -1, -1}, {1, 2, 1}};
    double vector2[dim2] = {4, -1, 7};
    double result2[dim2];
    double test2[dim2] = {1, 4, -2};
    cramers_rule(matrix2, vector2, result2, dim2);

    for (int i = 0; i < dim2; i++)
    {
        REQUIRE(abs(result2[i] - test2[i]) <= THRESHOLD);
    }

    const int dim3 = 4;
    double matrix3[dim3][CAP] = {{0, 10, 4, -2}, {-3, -17, 1, 2}, {1, 1, 1, 0}, {8, -34, 16, -10}};
    double vector3[dim3] = {24, -26, 6, -52};
    double result3[dim3];
    double test3[dim3] = {1, 2, 3, 4};
    cramers_rule(matrix3, vector3, result3, dim3);

    for (int i = 0; i < dim3; i++)
    {
        REQUIRE(abs(result3[i] - test3[i]) <= THRESHOLD);
    }

    const int dim5 = 5;
    double matrix5[dim5][CAP] = {{1, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 300, 0, -300, 0}, {0, 0, 150, 0, -150}, {45000, -22500, -45000, 0, 0}};
    double vector5[dim5] = {7, 9, -600, -300, -135000};
    double result5[dim5];
    double test5[dim5] = {1, 2, 3, 4, 5};
    cramers_rule(matrix5, vector5, result5, dim5);

    for (int i = 0; i < dim5; i++)
    {
        REQUIRE(abs(result5[i] - test5[i]) <= THRESHOLD);
    }
}
