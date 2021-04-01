#include "aliparlakci_Parlakci_Ali_hw4_matrix.h"

Matrix::Matrix()
{
    Matrix(0, 0);
}

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    matrix = new cell*[rows];

    for (int i = 0; i < rows; i++)
    {
        *(matrix+i) = new cell [cols];
    }
}

char Matrix::get(int row, int col)
{
    return matrix[row][col].value;
}

void Matrix::set(char value, int row, int col)
{
    matrix[row][col].value = value;
}