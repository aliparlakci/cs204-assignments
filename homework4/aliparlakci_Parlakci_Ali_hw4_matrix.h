#ifndef _MATRIX_H
#define _MATRIX_H

#include <string>

class Matrix
{
public:
    void Matrix();
    void Matrix(int row, int col);
    void search(const string &bitString) const;
    void set(int value, int row, int col);
    void get(int row, int col);
private:
};

#endif