
#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

/*
 A simple matrix class
 c++ code
 Author: Jos de Jong, Nov 2007. Updated March 2010

 With this class you can:
 - create a 2D matrix with custom size
 - get/set the cell values
 - use operators +, -, *, /
 - use functions Ones(), Zeros(), Diag(), Det(), Inv(), Size()
 - print the content of the matrix

 Usage:
 you can create a matrix by:
 Matrix A;
 Matrix A = Matrix(rows, cols);
 Matrix A = B;

 you can get and set matrix elements by:
 A(2,3) = 5.6;    // set an element of Matix A
 value = A(3,1);   // get an element of Matrix A
 value = A.get(3,1); // get an element of a constant Matrix A
 A = B;        // copy content of Matrix B to Matrix A

 you can apply operations with matrices and doubles:
 A = B + C;
 A = B - C;
 A = -B;
 A = B * C;
 A = B / C;

 the following functions are available:
 A = Ones(rows, cols);
 A = Zeros(rows, cols);
 A = Diag(n);
 A = Diag(B);
 d = Det(A);
 A = Inv(B);
 cols = A.GetCols();
 rows = A.GetRows();
 cols = Size(A, 1);
 rows = Size(A, 2);

 you can quick-print the content of a matrix in the console with:
 A.Print();
 */

#include <cstdlib>
#include <cstdio>
#include <math.h>


// Declarations
class Matrix;
double Det(const Matrix& a);
Matrix Diag(const int n);
Matrix Diag(const Matrix& v);
Matrix Inv(const Matrix& a);
Matrix Ones(const int rows, const int cols);
int Size(const Matrix& a, const int i);
Matrix Zeros(const int rows, const int cols);


/**
add by keyvan
**/
Matrix vertCat(const Matrix& A, const Matrix& B);
Matrix horzCat(const Matrix& A, const Matrix& B);

/*
 * a simple exception class
 * you can create an exeption by entering
 *   throw Exception("...Error description...");
 * and get the error message from the data msg for displaying:
 *   err.msg
 */
class Exception
{
public:
    const char* msg;
    Exception(const char* arg)
    : msg(arg)
    {
    }
};



class Matrix
{
public:
    // constructor
    Matrix();

    // constructor
    Matrix(const int row_count, const int column_count);

    // assignment operator
    Matrix(const Matrix& a);

    // index operator. You can use this class like myMatrix(col, row)
    // the indexes are one-based, not zero based.
    double& operator()(const int r, const int c);

    // index operator. You can use this class like myMatrix.get(col, row)
    // the indexes are one-based, not zero based.
    // use this function get if you want to read from a const Matrix
    double get(const int r, const int c) const;

    // assignment operator
    Matrix& operator= (const Matrix& a);

    // add a double value (elements wise)
    Matrix& Add(const double v);

    // subtract a double value (elements wise)
    Matrix& Subtract(const double v);

    // multiply a double value (elements wise)
    Matrix& Multiply(const double v);

    // divide a double value (elements wise)
    Matrix& Divide(const double v);

    // addition of Matrix with Matrix
    friend Matrix operator+(const Matrix& a, const Matrix& b);

    // addition of Matrix with double
    friend Matrix operator+ (const Matrix& a, const double b);

    // addition of double with Matrix
    friend Matrix operator+ (const double b, const Matrix& a);

    // subtraction of Matrix with Matrix
    friend Matrix operator- (const Matrix& a, const Matrix& b);

    // subtraction of Matrix with double
    friend Matrix operator- (const Matrix& a, const double b);

    // subtraction of double with Matrix
    friend Matrix operator- (const double b, const Matrix& a);

    // operator unary minus
    friend Matrix operator- (const Matrix& a);

    // operator multiplication
    friend Matrix operator* (const Matrix& a, const Matrix& b);

    // multiplication of Matrix with double
    friend Matrix operator* (const Matrix& a, const double b);

    // multiplication of double with Matrix
    friend Matrix operator* (const double b, const Matrix& a);

    // division of Matrix with Matrix
    friend Matrix operator/ (const Matrix& a, const Matrix& b);

    // division of Matrix with double
    friend Matrix operator/ (const Matrix& a, const double b);

    // division of double with Matrix
    friend Matrix operator/ (const double b, const Matrix& a);

    /**
     * returns the minor from the given matrix where
     * the selected row and column are removed
     */
    Matrix Minor(const int row, const int col) const;

    /*
     * returns the size of the i-th dimension of the matrix.
     * i.e. for i=1 the function returns the number of rows,
     * and for i=2 the function returns the number of columns
     * else the function returns 0
     */
    int Size(const int i) const;

    // returns the number of rows
    int GetRows() const;

    // returns the number of columns
    int GetCols() const;

    // print the contents of the matrix
    void Print() const;

    /**
    added by keyvan
    **/

    double minColwise(const int colIndex) const;
    double maxColwise(const int colIndex) const;
    Matrix partial(const int staRow, const int endRow, const int staCol, const int endCol);

public:
    // destructor
    ~Matrix();

private:

    int rows;
    int cols;
    double** p;     // pointer to a matrix with doubles
};

#endif /* matrix_hpp */
