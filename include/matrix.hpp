/*
  Filename    : matrix.hpp
  Author      : Tyler Allen
  Date        : 3/31/2026
  Description : Header file for the matrix library.
  License     : LGPLv3
*/

// --- System Declarations ---

# pragma once

// For data
# include <vector>
// For cout override
# include <iostream>

// --- Class Declaration ---

/**
 * @class Matrix
 * @brief A template-based 2D mathematical matrix.
 * @tparam T The type of data stored in the matrix (e.g. int, long, string).
 */
template <typename T>
class Matrix
{

    public:

        using value_type = T;
        using iterator = typename std::vector<value_type>::iterator;
        using const_iterator = typename std::vector<value_type>::const_iterator;

        /** @brief Creates a matrix of size rowCount x columnCount filled with value. Defaults to 0x0 with T() if no parameters given.*/
        Matrix (const size_t& rowCount=0, const size_t& columnCount=0, const T& value = T ());
        /** @brief Construct a new matrix using a vector. */
        Matrix (const size_t& rowCount, const size_t& columnCount, const std::vector<T> v);
        /** @brief Copy constructor. Performs a deep copy of another matrix. */
        Matrix (const Matrix<T>& matrix);
        /** @brief Move constructor. Transfers ownership to a new matrix. */
        Matrix (Matrix<T>&& other) noexcept;
        /** @brief Deletes a matrix. */
        ~Matrix () = default;

        /**
         * @brief Adds scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T> 
         */
        Matrix<T>
        operator+ (const T& scalar) const;
        /**
         * @brief Adds scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T>&
         */
        Matrix<T>&
        operator+= (const T& scalar);

        /**
         * @brief Adds values from other matrix to this.
         * @param other 
         * @return Matrix<T>& 
         */
        Matrix<T>&
        operator+= (const Matrix<T>& other);
        /**
         * @brief Adds values from other matrix to this.
         * @param other 
         * @return Matrix<T>
         */
        Matrix<T>
        operator+ (const Matrix<T>& other) const;

        /**
         * @brief Subtracts scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T> 
         */
        Matrix<T>
        operator- (const T& scalar) const;
        /**
         * @brief Subtracts scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T>&
         */
        Matrix<T>&
        operator-= (const T& scalar);

        /**
         * @brief Subtracts values from other matrix to this.
         * @param other 
         * @return Matrix<T>& 
         */
        Matrix<T>&
        operator-= (const Matrix<T>& other);
        /**
         * @brief Subtracts values from other matrix to this.
         * @param other 
         * @return Matrix<T>
         */
        Matrix<T>
        operator- (const Matrix<T>& other) const;

        /**
         * @brief Multiplies scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T> 
         */
        Matrix<T>
        operator* (const T& scalar) const;
        /**
         * @brief Multiplies scalar to all elements in matrix.
         * @param scalar 
         * @return Matrix<T>&
         */
        Matrix<T>&
        operator*= (const T& scalar);

        /**
         * @brief Multiplies values from other matrix to this.
         * @param other 
         * @return Matrix<T>& 
         */
        Matrix<T>&
        operator*= (const Matrix<T>& other);
        /**
         * @brief Multiplies values from other matrix to this.
         * @note Requires this->columns() == other.rows().
         * @param other Matrix to multiply with this.
         * @return Matrix<T> A new matrix representing the product.
         * @throws std::invalid_argument If inner dimensions do not match.
         */
        Matrix<T>
        operator* (const Matrix<T>& other) const;

        /**
         * @brief Divides all elements in a matrix by scalar value.
         * @param scalar 
         * @return Matrix<T> 
         */
        Matrix<T>&
        operator/= (const T& scalar);

        /**
         * @brief Divides all elements in a matrix by scalar value.
         * @param scalar 
         * @return Matrix<T> 
         */
        Matrix<T>
        operator/ (const T& scalar) const;

        /** @brief Returns true if matrix is valid square matrix or false otherwise. */
        bool 
        isSquare () const noexcept;
        /** @brief Returns number of rows. */
        size_t
        rows () const noexcept;
        /** @brief Returns number of columns. */
        size_t 
        columns () const noexcept;
        /** @brief Returns total number of elements in matrix. */
        size_t
        size () const noexcept;

        /** @brief Returns an iterator to the beginning of the matrix. */
        iterator
        begin () noexcept;
        /** @brief Returns an const_iterator to the beginning of the matrix. */
        const_iterator
        begin () const noexcept;
        /** @brief Returns an const_iterator to the beginning of the matrix. */
        const_iterator
        cbegin () const noexcept;

        /** @brief Returns an iterator to the end of the matrix. */
        iterator
        end () noexcept;
        /** @brief Returns an const_iterator to the end of the matrix. */
        const_iterator
        end () const noexcept;
        /** @brief Returns a const_iterator to the end of the matrix. */
        const_iterator
        cend () const noexcept;

        /** @brief Returns a pointer to the underlying data of the matrix. */
        T*
        data () noexcept;
        /** @brief Returns a const pointer to the underlying data of the matrix. */
        const T*
        data () const noexcept;

        /**
         * @brief Returns a matrix with flipped dimensions. Does not modify current matrix.
         * @return Matrix<T> 
         */
        Matrix<T>
        transpose () const noexcept;

        /**
         * @brief Deletes all data and sets rows and columns to 0.
         */
        void
        clear () noexcept;

        /**
         * @brief Resizes a matrix to new dimensions.
         * @details Deletes existing data if needed; new spaces are filled with 'value'.
         * @param rows New number of rows.
         * @param cols New number of columns.
         * @param value Fill value for the elements.
         */
        void
        resize (const size_t& rows, const size_t& cols, const T& value = T ());

        /**
         * @brief Returns a submatrix from (x1, x2, y1, y2).
         * @param x1
         * @param x2 
         * @param y1 
         * @param y2 
         * @return Matrix<T>
         */
        Matrix<T>
        slice (const size_t& x1, const size_t& x2, const size_t& y1, const size_t& y2);

        /**
         * @brief Returns an identity matrix of size.
         * @param size 
         * @return Matrix<T>
         */
        static Matrix<T>
        identity(const size_t& size);

        /**
         * @brief Returns an ostream for printing matrix in readable format.
         * @tparam U Type of matrix elements.
         * @param os 
         * @param matrix 
         * @return std::ostream& 
         */
        template <typename U> friend std::ostream&
        operator<< (std::ostream& os, const Matrix<U>& matrix);
        
        /**
         * @brief Accesses the element at specified coordinates.
         * @param row Zero-based index of the row.
         * @param col Zero-based index of the column.
         * @return T& Reference to the element at (row, col).
         * @throws std::out_of_range if the row or col exceeds matrix dimensions.
         */
        T&
        operator() (const size_t& row, const size_t& col);

        /**
         * @brief Accesses the element at specified coordinates.
         * @param row Zero-based index of the row.
         * @param col Zero-based index of the column.
         * @return T& Reference to the element at (row, col).
         * @throws std::out_of_range if the row or col exceeds matrix dimensions.
         */
        const T&
        operator() (const size_t& row, const size_t& col) const;
        
        /**
         * @brief Assignment operator. Sets matrix to another.
         * @param other 
         * @return Matrix<T>& 
         */
        Matrix<T>&
        operator= (const Matrix<T>& other);

        /**
         * @brief Equality operator. Checks if size and data are equal.
         * @param other 
         * @return true 
         * @return false 
         */
        bool
        operator== (const Matrix<T>& other) const;

    private:

        size_t _rows, _columns;
        std::vector<T> _data;

        /** 
         * @brief Checks to see if position (row, column) is valid.
         * @throws std::out_of_range if position is not valid for matrix dimensions.
         */
        void
        checkBounds (const size_t& row, const size_t& col) const;

        /** 
         * @brief Checks to see if matrices have the same dimensions.
         * @throws std::invalid_argument if dimensions do not match.
         */
        void
        checkDimensions (const Matrix<T>& other) const;

        /** 
         * @brief Checks to see if matrix multiplication is valid.
         * @throws std::invalid_argument if inner dimensions do not match.
         */
        void
        checkValidMultiplication (const Matrix<T>& other) const;

};

// --- Include Implementation ---

# include "matrix.tpp"