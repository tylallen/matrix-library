/*
  Filename    : kingdoms.cpp
  Author      : Tyler Allen
  Date        : 3/31/2026
  Description : Matrix class showcase using "Conway's Game of Life."
  License     : LGPLv3
*/

// --- System Declarations ---

# include <cstdlib>
# include <string>
# include <utility>
# include <chrono>
# include <thread>

# include "../include/matrix.hpp"

using namespace std::chrono_literals;

// --- Declarations ---

struct State {
    char symbol;
};

struct Coordinate {
    size_t x, y;
};

const std::vector<Coordinate> glider = { {1, 0}, {2, 1}, {0, 2}, {1, 2}, {2, 2} };
const std::vector<Coordinate> blinker = { {0, 0}, {0, 1}, {0, 2} };
const std::vector<Coordinate> block = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
const std::vector<Coordinate> pulsar = {
    {2, 0}, {3, 0}, {4, 0}, {8, 0}, {9, 10}, {10, 0},
    {0, 2}, {5, 2}, {7, 2}, {12, 2},
    {0, 3}, {5, 3}, {7, 3}, {12, 3},
    {0, 4}, {5, 4}, {7, 4}, {12, 4},
    {2, 5}, {3, 5}, {4, 5}, {8, 5}, {9, 5}, {10, 5},
    {2, 7}, {3, 7}, {4, 7}, {8, 7}, {9, 7}, {10, 7},
    {0, 8}, {5, 8}, {7, 8}, {12, 8},
    {0, 9}, {5, 9}, {7, 9}, {12, 9},
    {0, 10}, {5, 10}, {7, 10}, {12, 10},
    {2, 12}, {3, 12}, {4, 12}, {8, 12}, {9, 12}, {10, 12}
};

State
getCell (const size_t& x, const size_t& y);

const std::pair<size_t, size_t>
getNeighbors (const size_t& x, const size_t& y);

void
gofLoop (Matrix<State>& grid);

std::ostream& 
operator<< (std::ostream& os, const State& s);

void 
drawPattern (Matrix<State>& grid, const std::vector<Coordinate>& pattern, size_t offsetX, size_t offsetY);

// --- Main Method ---

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <Size> <Layout>";
        exit (EXIT_FAILURE);
    }

    std::string arg1 (argv[1]);
    std::string arg2 (argv[2]);
    unsigned long size = stoul (arg1);

    State cell;
    cell.symbol = '.';

    Matrix<State> grid (size, size, cell);
    
    if (arg2 == "glider") drawPattern (grid, glider, 0, 0);
    else if (arg2 == "blinker") drawPattern (grid, blinker, 0, 1);
    else if (arg2 == "block") drawPattern (grid, block, 0, 0);
    else if (arg2 == "pulsar") drawPattern (grid, pulsar, 1, 1);
    else
    {
        std::cerr << "Usage: " << argv[0] << " <Size> <Layout>";
        exit (EXIT_FAILURE);
    }

    while (true)
    {
        gofLoop (grid);
        std::cout << grid << std::endl;
        std::this_thread::sleep_for (250ms);
    }
}

// --- Implementations ---

State
getCell (const Matrix<State>& m, const size_t& x, const size_t& y)
{
    return m (x, y);
}

const std::pair<size_t, size_t>
getNeighbors (const Matrix<State>& m, const size_t& x, const size_t& y)
{
    std::pair<size_t, size_t> neighbors = {0, 0};
    for (int offsetY = -1; offsetY <= 1; ++offsetY)
    {
        for (int offsetX = -1; offsetX <= 1; ++offsetX)
        {
            if (offsetX == 0 && offsetY == 0) continue;

            size_t xPos = (x + m.columns () + offsetX) % m.columns ();
            size_t yPos = (y + m.rows () + offsetY) % m.rows ();

            State cell = getCell (m, xPos, yPos);
            if (cell.symbol == '.') neighbors.first++;
            else neighbors.second++;
        }
    }
    return neighbors;
}

void
gofLoop (Matrix<State>& grid)
{
    Matrix<State> newGrid = grid;
    for (size_t x = 0; x < grid.columns (); ++x)
    {
        for (size_t y = 0; y < grid.rows (); ++y)
        {
            State cell = grid (x, y);
            std::pair<size_t, size_t> neighbors = getNeighbors (grid, x, y); // OFF, ON
            size_t aliveCount = neighbors.second;

            if (cell.symbol == '.')
            {
                if (aliveCount == 3) newGrid (x, y).symbol = '#';
            }
            else
            {
                if (aliveCount > 3 || aliveCount < 2) newGrid (x, y).symbol = '.';
            }
        }
    }
    grid = newGrid;
}

void 
drawPattern (Matrix<State>& grid, const std::vector<Coordinate>& pattern, size_t offsetX, size_t offsetY)
{
    for (const auto& pos : pattern)
    {
        size_t xPos = (pos.x + offsetX) % grid.columns ();
        size_t yPos = (pos.y + offsetY) % grid.rows ();
        grid (xPos, yPos).symbol = '#';
    }
}

std::ostream& 
operator<< (std::ostream& os, const State& s)
{
    return os << s.symbol;
}