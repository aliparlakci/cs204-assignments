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

void Matrix::get(int row, int col, char &value, bool &flag) const
{
    cell* c = *(matrix+row)+col;
    value = c->value;
    flag = c->flag;
}

void Matrix::set(int row, int col, char value, bool flag=false)
{
    cell* c = *(matrix+row)+col;
    c->value = value;
    c->flag = flag;
}