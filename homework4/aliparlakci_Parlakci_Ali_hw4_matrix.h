#ifndef _MATRIX_H
#define _MATRIX_H

#include <string>

struct cell
{
    char value;
    bool flag;
    cell() : value('-'), flag(false){};
    cell(char v, bool f=false) : value(v), flag(f){}; 
};

class Matrix
{
public:
    Matrix();
    Matrix(const Matrix &copy);
    Matrix(int row, int col);
    ~Matrix();
    void size(int &row, int &col) const;
    void get(int row, int col, char &value, bool &flag) const;
    void set(int row, int col, char value, bool flag=false);
private:
    cell** matrix;
    int rows;
    int cols;
};

#endif