//
//  matrix.cpp
//  matrix
//
//  Created by Keyvan Zare Rami on 2/10/18.
//  Copyright © 2018 Keyvan Zare Rami. All rights reserved.
//

#include "matrix.h"



// constructor
Matrix::Matrix()
{
    //printf("Executing constructor Matrix() ...\n");
    // create a Matrix object without content
    p = NULL;
    rows = 0;
    cols = 0;
}

// constructor
Matrix::Matrix(const int row_count, const int column_count)
{
    // create a Matrix object with given number of rows and columns
    p = NULL;

    if (row_count > 0 && column_count > 0)
    {
        rows = row_count;
        cols = column_count;

        p = new double*[rows];
        for (int r = 0; r < rows; r++)
        {
            p[r] = new double[cols];

            // initially fill in zeros for all values in the matrix;
            for (int c = 0; c < cols; c++)
            {
                p[r][c] = 0;
            }
        }
    }
}

// assignment operator
Matrix::Matrix(const Matrix& a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        // copy the values from the matrix a
        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
}

// index operator. You can use this class like myMatrix(col, row)
// the indexes are one-based, not zero based.
double& Matrix::operator()(const int r, const int c)
{
    if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
    {
        return p[r-1][c-1];
    }
    else
    {
        throw Exception("Subscript out of range");
    }
}

// index operator. You can use this class like myMatrix.get(col, row)
// the indexes are one-based, not zero based.
// use this function get if you want to read from a const Matrix
double Matrix::get(const int r, const int c) const
{
    if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
    {
        return p[r-1][c-1];
    }
    else
    {
        throw Exception("Subscript out of range");
    }
}

// assignment operator
Matrix& Matrix::operator= (const Matrix& a)
{
    rows = a.rows;
    cols = a.cols;
    p = new double*[a.rows];
    for (int r = 0; r < a.rows; r++)
    {
        p[r] = new double[a.cols];

        // copy the values from the matrix a
        for (int c = 0; c < a.cols; c++)
        {
            p[r][c] = a.p[r][c];
        }
    }
    return *this;
}

// add a double value (elements wise)
Matrix& Matrix::Add(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] += v;
        }
    }
    return *this;
}

// subtract a double value (elements wise)
Matrix& Matrix::Subtract(const double v)
{
    return Add(-v);
}

// multiply a double value (elements wise)
Matrix& Matrix::Multiply(const double v)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            p[r][c] *= v;
        }
    }
    return *this;
}

// divide a double value (elements wise)
Matrix& Matrix::Divide(const double v)
{
    return Multiply(1/v);
}

// addition of Matrix with Matrix
Matrix operator+(const Matrix& a, const Matrix& b)
{
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix res(a.rows, a.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c = 0; c < a.cols; c++)
            {
                res.p[r][c] = a.p[r][c] + b.p[r][c];
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

// addition of Matrix with double
Matrix operator+ (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Add(b);
    return res;
}
// addition of double with Matrix
Matrix operator+ (const double b, const Matrix& a)
{
    Matrix res = a;
    res.Add(b);
    return res;
}

// subtraction of Matrix with Matrix
Matrix operator- (const Matrix& a, const Matrix& b)
{
    // check if the dimensions match
    if (a.rows == b.rows && a.cols == b.cols)
    {
        Matrix res(a.rows, a.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c = 0; c < a.cols; c++)
            {
                res.p[r][c] = a.p[r][c] - b.p[r][c];
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

// subtraction of Matrix with double
Matrix operator- (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Subtract(b);
    return res;
}
// subtraction of double with Matrix
Matrix operator- (const double b, const Matrix& a)
{
    Matrix res = -a;
    res.Add(b);
    return res;
}

// operator unary minus
Matrix operator- (const Matrix& a)
{
    Matrix res(a.rows, a.cols);

    for (int r = 0; r < a.rows; r++)
    {
        for (int c = 0; c < a.cols; c++)
        {
            res.p[r][c] = -a.p[r][c];
        }
    }

    return res;
}

// operator multiplication
Matrix operator* (const Matrix& a, const Matrix& b)
{
    // check if the dimensions match
    if (a.cols == b.rows)
    {
        Matrix res(a.rows, b.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c_res = 0; c_res < b.cols; c_res++)
            {
                for (int c = 0; c < a.cols; c++)
                {
                    res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
                }
            }
        }
        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

// multiplication of Matrix with double
Matrix operator* (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Multiply(b);
    return res;
}
// multiplication of double with Matrix
Matrix operator* (const double b, const Matrix& a)
{
    Matrix res = a;
    res.Multiply(b);
    return res;
}

// division of Matrix with Matrix
Matrix operator/ (const Matrix& a, const Matrix& b)
{
    // check if the dimensions match: must be square and equal sizes
    if (a.rows == a.cols && a.rows == a.cols && b.rows == b.cols)
    {
        Matrix res(a.rows, a.cols);

        res = a * Inv(b);

        return res;
    }
    else
    {
        // give an error
        throw Exception("Dimensions does not match");
    }

    // return an empty matrix (this never happens but just for safety)
    return Matrix();
}

// division of Matrix with double
Matrix operator/ (const Matrix& a, const double b)
{
    Matrix res = a;
    res.Divide(b);
    return res;
}

// division of double with Matrix
Matrix operator/ (const double b, const Matrix& a)
{
    Matrix b_matrix(1, 1);
    b_matrix(1,1) = b;

    Matrix res = b_matrix / a;
    return res;
}

/**
 * returns the minor from the given matrix where
 * the selected row and column are removed
 */
Matrix Matrix::Minor(const int row, const int col) const
{
    Matrix res;
    if (row > 0 && row <= rows && col > 0 && col <= cols)
    {
        res = Matrix(rows - 1, cols - 1);

        // copy the content of the matrix to the minor, except the selected
        for (int r = 1; r <= (rows - (row >= rows)); r++)
        {
            for (int c = 1; c <= (cols - (col >= cols)); c++)
            {
                res(r - (r > row), c - (c > col)) = p[r-1][c-1];
            }
        }
    }
    else
    {
        throw Exception("Index for minor out of range");
    }

    return res;
}

/*
 * returns the size of the i-th dimension of the matrix.
 * i.e. for i=1 the function returns the number of rows,
 * and for i=2 the function returns the number of columns
 * else the function returns 0
 */
int Matrix::Size(const int i) const
{
    if (i == 1)
    {
        return rows;
    }
    else if (i == 2)
    {
        return cols;
    }
    return 0;
}

// returns the number of rows
int Matrix::GetRows() const
{
    return rows;
}

// returns the number of columns
int Matrix::GetCols() const
{
    return cols;
}

// print the contents of the matrix
void Matrix::Print() const
{
    if (p != NULL)
    {
        printf("[");
        for (int r = 0; r < rows; r++)
        {
            if (r > 0)
            {
                printf(" ");
            }
            for (int c = 0; c < cols-1; c++)
            {
                printf("%.2f, ", p[r][c]);
            }
            if (r < rows-1)
            {
                printf("%.2f;\n", p[r][cols-1]);
            }
            else
            {
                printf("%.2f]\n", p[r][cols-1]);
            }
        }
    }
    else
    {
        // matrix is empty
        printf("[ ]\n");
    }
}

// destructor
Matrix::~Matrix()
{
    // clean up allocated memory
    for (int r = 0; r < rows; r++)
    {
        delete p[r];
    }
    delete p;
    p = NULL;
}




/*
 * i.e. for i=1 the function returns the number of rows,
 * and for i=2 the function returns the number of columns
 * else the function returns 0
 */
int Size(const Matrix& a, const int i)
{
    return a.Size(i);
}


/**
 * returns a matrix with size cols x rows with ones as values
 */
Matrix Ones(const int rows, const int cols)
{
    Matrix res = Matrix(rows, cols);

    for (int r = 1; r <= rows; r++)
    {
        for (int c = 1; c <= cols; c++)
        {
            res(r, c) = 1;
        }
    }
    return res;
}

/**
 * returns a matrix with size cols x rows with zeros as values
 */
Matrix Zeros(const int rows, const int cols)
{
    return Matrix(rows, cols);
}


/**
 * returns a diagonal matrix with size n x n with ones at the diagonal
 */
Matrix Diag(const int n)
{
    Matrix res = Matrix(n, n);
    for (int i = 1; i <= n; i++)
    {
        res(i, i) = 1;
    }
    return res;
}

/**
 * returns a diagonal matrix
 * @param  v a vector
 * @return a diagonal matrix with the given vector v on the diagonal
 */
Matrix Diag(const Matrix& v)
{
    Matrix res;
    if (v.GetCols() == 1)
    {
        // the given matrix is a vector n x 1
        int rows = v.GetRows();
        res = Matrix(rows, rows);

        // copy the values of the vector to the matrix
        for (int r=1; r <= rows; r++)
        {
            res(r, r) = v.get(r, 1);
        }
    }
    else if (v.GetRows() == 1)
    {
        // the given matrix is a vector 1 x n
        int cols = v.GetCols();
        res = Matrix(cols, cols);

        // copy the values of the vector to the matrix
        for (int c=1; c <= cols; c++)
        {
            res(c, c) = v.get(1, c);
        }
    }
    else
    {
        throw Exception("Parameter for diag must be a vector");
    }
    return res;
}

/*
 * returns the determinant of Matrix a
 */
double Det(const Matrix& a)
{
    double d = 0;    // value of the determinant
    int rows = a.GetRows();
    int cols = a.GetRows();

    if (rows == cols)
    {
        // this is a square matrix
        if (rows == 1)
        {
            // this is a 1 x 1 matrix
            d = a.get(1, 1);
        }
        else if (rows == 2)
        {
            // this is a 2 x 2 matrix
            // the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
            d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
        }
        else
        {
            // this is a matrix of 3 x 3 or larger
            for (int c = 1; c <= cols; c++)
            {
                Matrix M = a.Minor(1, c);
                //d += pow(-1, 1+c) * a(1, c) * Det(M);
                d += (c%2 + c%2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
            }
        }
    }
    else
    {
        throw Exception("Matrix must be square");
    }
    return d;
}

// swap two values
void Swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

/*
 * returns the inverse of Matrix a
 */
Matrix Inv(const Matrix& a)
{
    Matrix res;
    double d = 0;    // value of the determinant
    int rows = a.GetRows();
    int cols = a.GetRows();

    d = Det(a);
    if (rows == cols && d != 0)
    {
        // this is a square matrix
        if (rows == 1)
        {
            // this is a 1 x 1 matrix
            res = Matrix(rows, cols);
            res(1, 1) = 1 / a.get(1, 1);
        }
        else if (rows == 2)
        {
            // this is a 2 x 2 matrix
            res = Matrix(rows, cols);
            res(1, 1) = a.get(2, 2);
            res(1, 2) = -a.get(1, 2);
            res(2, 1) = -a.get(2, 1);
            res(2, 2) = a.get(1, 1);
            res = (1/d) * res;
        }
        else
        {
            // this is a matrix of 3 x 3 or larger
            // calculate inverse using gauss-jordan elimination
            //   http://mathworld.wolfram.com/MatrixInverse.html
            //   http://math.uww.edu/~mcfarlat/inverse.htm
            res = Diag(rows);   // a diagonal matrix with ones at the diagonal
            Matrix ai = a;    // make a copy of Matrix a

            for (int c = 1; c <= cols; c++)
            {
                // element (c, c) should be non zero. if not, swap content
                // of lower rows
                int r;
                for (r = c; r <= rows && ai(r, c) == 0; r++)
                {
                }
                if (r != c)
                {
                    // swap rows
                    for (int s = 1; s <= cols; s++)
                    {
                        Swap(ai(c, s), ai(r, s));
                        Swap(res(c, s), res(r, s));
                    }
                }

                // eliminate non-zero values on the other rows at column c
                for (int r = 1; r <= rows; r++)
                {
                    if(r != c)
                    {
                        // eleminate value at column c and row r
                        if (ai(r, c) != 0)
                        {
                            double f = - ai(r, c) / ai(c, c);

                            // add (f * row c) to row r to eleminate the value
                            // at column c
                            for (int s = 1; s <= cols; s++)
                            {
                                ai(r, s) += f * ai(c, s);
                                res(r, s) += f * res(c, s);
                            }
                        }
                    }
                    else
                    {
                        // make value at (c, c) one,
                        // divide each value on row r with the value at ai(c,c)
                        double f = ai(c, c);
                        for (int s = 1; s <= cols; s++)
                        {
                            ai(r, s) /= f;
                            res(r, s) /= f;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (rows == cols)
        {
            throw Exception("Matrix must be square");
        }
        else
        {
            throw Exception("Determinant of matrix is zero");
        }
    }
    return res;
}

/**
  added by keyvan
**/

/* find min value of a column*/
double Matrix::minColwise(const int colIndex) const
{
    double y = p[0][colIndex-1];

    for (int r = 1; r <= rows; r++)
    {
        if ( y > p[r-1][colIndex-1] )
        {
            y = p[r-1][colIndex-1];
        }
    }
    return y;
}

/* find max value of a column*/
double Matrix::maxColwise(const int colIndex) const
{
    double y = p[0][colIndex-1];

    for (int r = 1; r <= rows; r++)
    {
        if ( y < p[r-1][colIndex-1] )
        {
            y = p[r-1][colIndex-1];
        }
    }
    return y;
}

Matrix vertCat(const Matrix& A, const Matrix& B)
{

    int rowsA = A.GetRows();
    int colsA = A.GetCols();
    int rowsB = B.GetRows();

    Matrix C ;

    if(rowsA == 0 && rowsB != 0)
    {
        C = B;
    }else if(rowsA != 0 && rowsB == 0)
    {
        C = A;
    }else if(rowsA != 0 && rowsB != 0)
    {
        C = Matrix(rowsA+rowsB, colsA);

        for(int i=1; i<=rowsA; i=i+1)
        {
            for(int j=1; j<=colsA; j=j+1)
            {
                C(i,j)= A.get(i,j);
            }
        }

        for(int i=1; i<=rowsB; i=i+1)
        {
            for(int j=1; j<=colsA; j=j+1)
            {
                C(i+rowsA,j) = B.get(i,j);
            }
        }
    }

    return C;
}

Matrix horzCat(const Matrix& A, const Matrix& B)
{

    int rowsA = A.GetRows();
    int colsA = A.GetCols();
    int rowsB = B.GetRows();
    int colsB = B.GetCols();

    Matrix C ;

    if(rowsA == 0 && rowsB != 0)
    {
        C = B;
    }else if(rowsA != 0 && rowsB == 0)
    {
        C = A;
    }else if(rowsA != 0 && rowsB != 0)
    {
        C = Matrix(rowsA, colsA+colsB);

        for(int i=1; i<=rowsA; i=i+1)
        {
            for(int j=1; j<=colsA; j=j+1)
            {
                C(i,j)= A.get(i,j);
            }
        }

        for(int i=1; i<=rowsB; i=i+1)
        {
            for(int j=1; j<=colsB; j=j+1)
            {
                C(i,j+colsA) = B.get(i,j);
            }
        }
    }

    return C;
}


Matrix Matrix::partial(const int staRow, const int endRow, const int staCol, const int endCol)
{
    Matrix res = Matrix(endRow-staRow+1, endCol-staCol+1);

    // copy the content of the matrix to the minor, except the selected
    for (int r = staRow; r <= endRow; r = r+1)
    {
        for (int c = staCol; c <= endCol; c = c+1)
        {
            res(r-staRow+1, c-staCol+1) = p[r-1][c-1];
        }
    }

    return res;
}
