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
    Matrix(int row, int col);
    void search(const std::string &bitString) const;
    void set(char value, int row, int col);
    char get(int row, int col);
private:
    cell** matrix;
    int rows;
    int cols;
};

#endif