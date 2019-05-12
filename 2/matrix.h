#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

class Matrix{
private:
    size_t rows;
    size_t cols;
    int **p;

public:
    class Row{
        friend class Matrix;
    public:
        int& operator[](size_t cols) const
        {
            if (cols >= parent.cols){
                throw std::out_of_range("out_of_range");
            }
            return parent.p[row][cols];
        }
    private:
        Row (Matrix& _parent, size_t _row):
                parent(_parent), row(_row)
        { }

        Matrix& parent;
        size_t row;
    };

    Row operator[](size_t row) const
    {
        if (row >= rows){
            throw std::out_of_range("out_of_range");
        }
        return *(new Row(const_cast<Matrix &>(*this), row));
    }

    Matrix() : cols(0), rows(0) { }

    Matrix(const size_t _rows, const size_t _cols): rows(_rows), cols(_cols), p (nullptr)
    {
        allocSpace();
        for (int i =0; i < _rows; ++i){
            for (int j = 0; j < _cols; ++j)
            {
                p[i][j] = 0;
            }
        }
    }


    Matrix(const Matrix& m): rows(m.rows), cols(m.cols)
    {
        allocSpace();
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < cols; ++j)
            {
                p[i][j] = m.p[i][j];
            }
        }
    }

    Matrix& operator= (const Matrix &matr)
    {
        if (this == &matr) {
            return *this;
        }

        if (rows != matr.rows || cols != matr.cols) {
            for (int i = 0; i < rows; ++i) {
                delete[] p[i];
            }
            delete[] p;

            rows = matr.rows;
            cols = matr.cols;
            allocSpace();
        }
        if(p !=matr.p && cols==matr.cols && rows==matr.rows)
        {
            for(int i=0;i<rows;i++)
                for(int j=0;j<cols;j++)
                    p[i][j]=matr.p[i][j];
        }
        return *this;
    }

    Matrix& operator*=(int num)
    {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                p[i][j] *= num;
            }
        }
        return *this;
    }

    size_t getColumns() {return cols;}
    size_t getRows() {return rows;}

    void allocSpace() {
        p = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            p[i] = new int[cols];
        }
    }

    bool operator== (const Matrix &matr) const {
        if (this == &matr)
            return true;
        if(cols != matr.cols || rows != matr.rows)
            return false;
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                if(p[i][j] != matr.p[i][j])
                    return false;
        return true;
    }

    bool operator!= (const Matrix &matr) const {
        return !(*this == matr);
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; ++i) {
            delete[] p[i];
        }
        delete[] p;
    }

};



#endif //MATRIX_MATRIX_H
