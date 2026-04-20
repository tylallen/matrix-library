/*
  Filename   : tests.cpp
  Author     : Tyler M. Allen
  Description: Test methods of the matrix class.
*/   

// --- System Declarations ---

#include "catch_amalgamated.hpp"

// --- Local Declarations ---

#include "../include/matrix.hpp"

// --- Test Cases ---

// --- SECTION 1: Construction & Memory ---

TEST_CASE("Matrix Construction and Memory Management", "[matrix][setup]") {
    SECTION("Default and Sized Constructors") {
        Matrix<int> empty;
        CHECK(empty.rows() == 0);
        CHECK(empty.columns() == 0);

        Matrix<int> m(3, 4, 10);
        CHECK(m.rows() == 3);
        CHECK(m.columns() == 4);
        CHECK(m.size() == 12);
        CHECK(m(2, 3) == 10);
    }

    SECTION("Copy and Move Semantics") {
        Matrix<int> original(2, 2, 5);
        
        Matrix<int> copy(original); // Copy Constructor
        CHECK(copy == original);
        
        Matrix<int> moved(std::move(original)); // Move Constructor
        CHECK(moved.rows() == 2);
        CHECK(moved(0,0) == 5);
        // Note: original is now in a valid but unspecified state
    }

    SECTION("Self-Assignment Guard") {
        Matrix<int> a(2, 2, 1);
        a = a; // Should not crash or corrupt memory
        CHECK(a(0,0) == 1);
    }
}

// --- SECTION 2: Accessors & Safety ---

TEST_CASE("Matrix Access and Bounds Safety", "[matrix][access]") {
    Matrix<double> m(2, 2, 1.0);

    SECTION("Coordinate Access (Non-const)") {
        m(0, 1) = 5.5;
        CHECK(m(0, 1) == Catch::Approx(5.5));
    }

    SECTION("Coordinate Access (Const)") {
        const Matrix<double>& const_m = m;
        CHECK(const_m(0, 0) == Catch::Approx(1.0));
    }

    SECTION("Bounds Checking Exceptions") {
        CHECK_THROWS_AS(m(2, 0), std::out_of_range);
        CHECK_THROWS_AS(m(0, 2), std::out_of_range);
        CHECK_THROWS_AS(m(5, 5), std::out_of_range);
    }

    SECTION("Data Pointer Access") {
        double* ptr = m.data();
        REQUIRE(ptr != nullptr);
        ptr[0] = 9.9;
        CHECK(m(0, 0) == Catch::Approx(9.9));
    }
}

// --- SECTION 3: Mathematical Operations ---

TEST_CASE("Matrix Arithmetic and Logic", "[matrix][math]") {
    Matrix<int> a(2, 2, 1);
    Matrix<int> b(2, 2, 2);
    Matrix<int> c(2, 2, 4);

    SECTION("Addition & Subtraction") {
        auto res_add = a + b;
        CHECK(res_add(0,0) == 3);
        
        auto res_sub = b - a;
        CHECK(res_sub(0,0) == 1);
        
        a += b;
        CHECK(a(0,0) == 3);

        // Dimension Mismatch
        Matrix<int> wrong_size(3, 3);
        CHECK_THROWS_AS(a + wrong_size, std::invalid_argument);
    }

    SECTION("Division") {
        auto res_div = a / 1;
        CHECK(res_div(0,0) == 1);
        
        c /= 2;
        CHECK(a(0,0) == 2);
    }

    SECTION("Scalar Operations") {
        auto res = a * 10;
        CHECK(res(1,1) == 10);
        
        a *= 2;
        CHECK(a(0,0) == 2);
    }

    SECTION("Matrix Multiplication (Dot Product)") {
        Matrix<int> m1(2, 3, 1); // 2x3
        Matrix<int> m2(3, 2, 2); // 3x2
        auto res = m1 * m2;      // Result 2x2
        
        REQUIRE(res.rows() == 2);
        REQUIRE(res.columns() == 2);
        // Each element = (1*2 + 1*2 + 1*2) = 6
        CHECK(res(0,0) == 6);

        // Invalid multiplication dimensions
        Matrix<int> invalid(4, 4);
        CHECK_THROWS_AS(m1 * invalid, std::invalid_argument);
    }

    SECTION("Equality Operators") {
        Matrix<int> c(2, 2, 1);
        CHECK(a == c);
        CHECK_FALSE(a == b);
    }
}

// --- SECTION 4: Advanced Utilities ---

TEST_CASE("Matrix Utilities and Transformations", "[matrix][util]") {
    SECTION("Transpose") {
        Matrix<int> m(2, 3);
        m(0, 1) = 10;
        m(1, 2) = 20;
        
        auto t = m.transpose();
        REQUIRE(t.rows() == 3);
        REQUIRE(t.columns() == 2);
        CHECK(t(1, 0) == 10);
        CHECK(t(2, 1) == 20);
    }

    SECTION("Resize and Clear") {
        Matrix<int> m(2, 2, 1);
        m.resize(4, 4, 0);
        CHECK(m.rows() == 4);
        CHECK(m.size() == 16);
        CHECK(m(0,0) == 1); // Preserved
        CHECK(m(3,3) == 0); // Filled

        m.clear();
        CHECK(m.size() == 0);
        CHECK(m.rows() == 0);
    }

    SECTION("IsSquare Logic") {
        Matrix<int> m1(2, 2);
        Matrix<int> m2(2, 3);
        CHECK(m1.isSquare());
        CHECK_FALSE(m2.isSquare());
    }
}

// --- SECTION 5: STL Compatibility ---

TEST_CASE("Matrix Iterators", "[matrix][iter]") {
    Matrix<int> m(2, 2, 0);
    m(0,0) = 1; m(0,1) = 2; m(1,0) = 3; m(1,1) = 4;

    SECTION("Range-based for loop support") {
        int sum = 0;
        for (const auto& val : m) {
            sum += val;
        }
        CHECK(sum == 10);
    }

    SECTION("Const Iterators") {
        const Matrix<int> cm = m;
        auto it = cm.cbegin();
        CHECK(*it == 1);
        CHECK(*(it + 3) == 4);
    }
}

// --- SECTION 6: Adversarial & Limits ---

TEST_CASE("Matrix Stress Tests", "[matrix][heavy]") {
    SECTION("Numeric Limits") {
        double max_d = std::numeric_limits<double>::max();
        Matrix<double> m(1, 1, max_d);
        m *= 2.0;
        CHECK(std::isinf(m(0,0)));
    }

    SECTION("Degenerate Matrix (Zero size)") {
        Matrix<int> m(0, 0);
        CHECK_NOTHROW(m.transpose());
        CHECK(m.transpose().size() == 0);
        
        // Multiplying by zero matrix
        Matrix<int> other(0, 5);
        auto res = m * other;
        CHECK(res.size() == 0);
    }
}
