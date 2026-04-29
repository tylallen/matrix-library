/*
  Filename    : matrix.tpp
  Author      : Tyler Allen
  Date        : 3/31/2026
  Description : Function implementation for the matrix library.
  License     : LGPLv3
*/

// --- System Declarations ---

// For cout override
# include <iostream>
// For setw
# include <iomanip>

// --- Constructors ---

template <typename T>
Matrix<T>::Matrix (const size_t& rowCount, const size_t& columnCount, const T& value)
    : _rows(rowCount),
      _columns(columnCount),
      _data(rowCount * columnCount, value)
{
}

template <typename T>
Matrix<T>::Matrix (const Matrix<T>& matrix)
    : _rows(matrix.rows ()),
      _columns(matrix.columns ()),
      _data(matrix._data)
{
}

template <typename T>
Matrix<T>::Matrix (const size_t& rowCount, const size_t& columnCount, const std::vector<T> v)
    : _rows(rowCount),
      _columns(columnCount),
      _data(v)
{
}

template <typename T>
Matrix<T>::Matrix (Matrix<T>&& other) noexcept
    : _rows(other._rows),
      _columns(other._columns),
      _data(std::move(other._data))
{
    other._rows = 0;
    other._columns = 0;
}

// --- Math Operators ---

// --- Addition ---

template <typename T> 
Matrix<T>& Matrix<T>::operator+= (const T& scalar)
{
    for (auto& element : _data)
    {
        element += scalar;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator+(const T& scalar) const
{
    Matrix<T> result(*this);
    result += scalar;
    return result;
}

template <typename T> 
Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& other)
{
    checkDimensions (other);
    auto otherIterator = other.begin ();
    for (auto& element : _data)
    {
        element += *otherIterator;
        ++otherIterator;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& other) const
{
    Matrix<T> result(*this);
    result += other;
    return result;
}

// --- Subtraction ---

template <typename T> 
Matrix<T>& Matrix<T>::operator-= (const T& scalar)
{
    for (auto& element : _data)
    {
        element -= scalar;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator-(const T& scalar) const
{
    Matrix<T> result(*this);
    result -= scalar;
    return result;
}

template <typename T> 
Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& other)
{
    checkDimensions (other);
    auto otherIterator = other.begin ();
    for (auto& element : _data)
    {
        element -= *otherIterator;
        ++otherIterator;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator- (const Matrix<T>& other) const
{
    Matrix<T> result(*this);
    result -= other;
    return result;
}

// --- Multiplication ---

template <typename T> 
Matrix<T>& Matrix<T>::operator*= (const T& scalar)
{
    for (auto& element : _data)
    {
        element *= scalar;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator*(const T& scalar) const
{
    Matrix<T> result(*this);
    result *= scalar;
    return result;
}

template <typename T> 
Matrix<T>& Matrix<T>::operator*= (const Matrix<T>& other)
{
    *this = *this * other;
    return *this;
}

// TODO: Implement optimizations to lower time complexity.
template <typename T> 
Matrix<T> Matrix<T>::operator* (const Matrix<T>& other) const
{
    checkValidMultiplication (other);

    Matrix<T> result(_rows, other._columns);
    
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < other._columns; ++j)
        {
            for (size_t k = 0; k < _columns; ++k)
            {
                result._data[i * other._columns + j] += _data[i * _columns + k] * other._data[k * other._columns + j];
            }
        }
    }
    return result;
}

// --- Division ---

template <typename T> 
Matrix<T>& Matrix<T>::operator/= (const T& scalar)
{
    for (auto& element : _data)
    {
        element /= scalar;
    }
    return *this;
}

template <typename T> 
Matrix<T> Matrix<T>::operator/(const T& scalar) const
{
    Matrix<T> result(*this);
    result /= scalar;
    return result;
}

// --- Getters and Attributes ---

template <typename T>
bool Matrix<T>::isSquare () const noexcept
{ 
    return (_rows == _columns);
}

template <typename T>
size_t Matrix<T>::rows () const noexcept
{ 
    return _rows; 
}

template <typename T> 
size_t Matrix<T>::columns () const noexcept
{
    return _columns;
}

template <typename T> 
size_t Matrix<T>::size () const noexcept
{
    return _data.size ();
}

template <typename T> 
typename Matrix<T>::iterator Matrix<T>::begin () noexcept
{
    return _data.begin ();
}

template <typename T> 
typename Matrix<T>::const_iterator Matrix<T>::begin () const noexcept
{
    return _data.begin ();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::cbegin () const noexcept
{
    return begin ();
}

template <typename T> 
typename Matrix<T>::iterator Matrix<T>::end () noexcept
{
    return _data.end ();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::end () const noexcept
{
    return _data.end ();
}

template <typename T>
typename Matrix<T>::const_iterator Matrix<T>::cend () const noexcept
{
    return end ();
}

template <typename T> 
T* Matrix<T>::data () noexcept
{
    return _data.data ();
}

template <typename T> 
const T* Matrix<T>::data () const noexcept
{
    return _data.data ();
}

// --- Matrix Operations ---

template <typename T>
Matrix<T> Matrix<T>::transpose () const noexcept
{
    Matrix<T> result (_columns, _rows);
    for (size_t row = 0; row < _rows; ++row)
    {
        for (size_t col = 0; col < _columns; ++col)
        {
            result(col, row) = (*this)(row, col);
        }
    }
    return result;
}

template <typename T> 
void Matrix<T>::clear () noexcept
{
    _data.clear ();
    _rows = 0;
    _columns = 0;
}

template <typename T> 
void Matrix<T>::resize (const size_t& rows, const size_t& cols, const T& value)
{
    _data.reserve (rows * cols);
    _data.resize (rows * cols, value);
    _rows = rows;
    _columns = cols;
}

template <typename T>
Matrix<T> Matrix<T>::slice (const size_t& x1, const size_t& x2, const size_t& y1, const size_t& y2)
{
    if (x2 <= x1 || y2 <= y1 || x2 > _rows || y2 > _columns)
    {
        throw std::out_of_range ("Invalid slice bounds.");
    }

    size_t newRows = x2 - x1;
    size_t newCols = y2 - y1;
    std::vector<T> subVector;
    subVector.reserve (newRows * newCols);

    for (size_t r = x1; r < x2; r++) 
    {
        for (size_t c = y1; c < y2; c++)
        {
            subVector.push_back (_data[r * _columns + c]);
        }
    }

    return Matrix<T> (newRows, newCols, subVector);
}

template <typename T>
Matrix<T> Matrix<T>::identity (const size_t& size)
{
    Matrix<T> identityMatrix (size, size, 0);
    for (size_t pos = 0; pos < size; ++pos)
    {
        identityMatrix (pos, pos) = 1;
    }
    return identityMatrix;
}

// TODO: Add more operations such as discriminant.

// --- Operator Overrides ---

template <typename T> 
T& Matrix<T>::operator() (const size_t& row, const size_t& col)
{
    checkBounds (row, col);
    return _data[row * _columns + col];
}

template <typename T> 
const T& Matrix<T>::operator() (const size_t& row, const size_t& col) const
{
    checkBounds (row, col);
    return _data[row * _columns + col];
}

template <typename U> 
std::ostream& operator<< (std::ostream& os, const Matrix<U>& matrix)
{
    size_t max_width = 0;
    for (const auto& val : matrix._data)
    {
        std::stringstream ss;
        ss << val;
        if (max_width < ss.str ().length ())
        {
            max_width = ss.str ().length ();
        }
    }

    size_t col = 0;
    os << "[ ";
    for (auto it = matrix.begin (); it != matrix.end (); ++it)
    {
        os << std::left << std::setw(max_width) << *it << " ";
        if ((col + 1) % matrix._columns == 0)
        {
            os << "]";
            if (col + 1 < matrix.size ())
            {
                os << "\n[ ";
            }
        }
        ++col;
    }
    return os << "\n";
}

template <typename T> 
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& other)
{
    if (this != &other)
    {
        _data = other._data;
        _rows = other._rows;
        _columns = other._columns;
    }
    return *this;
}

template <typename T> 
bool Matrix<T>::operator== (const Matrix<T>& other) const
{
    return (_data == other._data && _rows == other._rows && _columns == other._columns);
}

// --- Size Checking ---

template <typename T> 
void Matrix<T>::checkBounds (const size_t& row, const size_t& col) const
{
    if (row >= _rows || col >= _columns)
    {
        throw std::out_of_range("Index (row=" + std::to_string(row) + ", column=" + std::to_string(col) + ") is out of range for matrix size " + std::to_string(rows ()) + " x " + std::to_string(columns ()) + ".");
    }
}

template <typename T> 
void Matrix<T>::checkDimensions (const Matrix<T>& other) const
{
    if (_rows != other._rows || _columns != other._columns)
    {
        throw std::invalid_argument ("The dimensions of matrix A (" + std::to_string(_rows) + "x" + std::to_string(_columns) + ") does not equal B (" + std::to_string(other._rows) + "x" + std::to_string(other._columns) + ").");
    }
}

template <typename T> 
void Matrix<T>::checkValidMultiplication (const Matrix<T>& other) const
{
    if (_columns != other._rows)
    {
        throw std::invalid_argument ("Matrix A columns (" + std::to_string(_columns) + ") != Matrix B rows (" + std::to_string(other._rows) + ")");
    }
}