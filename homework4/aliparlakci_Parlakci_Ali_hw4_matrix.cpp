#include "aliparlakci_Parlakci_Ali_hw4_matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(const Matrix &copy)
{
    rows = copy.rows;
    cols = copy.cols;
    matrix = new cell*[rows];

    for (int i = 0; i < rows; i++)
    {
        *(matrix+i) = new cell [cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char value;
            bool flag;
            copy.get(i, j, value, flag);
            set(i, j, value, flag);
        }
    }
}

Matrix::Matrix(int r, int c) : rows(r), cols(c)
{
    matrix = new cell*[rows];

    for (int i = 0; i < rows; i++)
    {
        *(matrix+i) = new cell [cols];
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] *(matrix+i);
    }
    delete[] matrix;
}

void Matrix::size(int &row, int &col) const
{
    row = rows;
    col = cols;
}

void Matrix::get(int row, int col, char &value, bool &flag) const
{
    cell* c = *(matrix+row)+col;
    value = c->value;
    flag = c->flag;
}

char Matrix::getVal(int row, int col) const
{
    cell* c = *(matrix+row)+col;
    return c->value;
}

bool Matrix::getFlag(int row, int col) const
{
    cell* c = *(matrix+row)+col;
    return c->flag;
}

void Matrix::set(int row, int col, char value, bool flag)
{
    cell* c = *(matrix+row)+col;
    c->value = value;
    c->flag = flag;
}

void Matrix::setVal(int row, int col, char value)
{
    cell* c = *(matrix+row)+col;
    c->value = value;
}

void Matrix::setFlag(int row, int col, bool flag)
{
    cell* c = *(matrix+row)+col;
    c->flag = flag;    
}