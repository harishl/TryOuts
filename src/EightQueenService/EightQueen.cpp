
#include <array>
#include <cstdio>
#include <stdexcept>
#include <algorithm>

#include "EightQueen.hpp"

namespace EightQueenLambda
{
using namespace std;

void EightQueenBoard::printBoard() const
{
    printf("\n");
    int i = 0; 
    int j = 0;
    for (const auto r : eightQueenBoard)
    {
        for (const auto c : r)
        {
            printf(" [%d,%d]:",i,j);
            if (c) { printf("X "); }
            else { printf("O "); }
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}

void EightQueenBoard::reset() 
{
    currentQueenCount = 0;
    eightQueenBoard = {};
}

bool EightQueenBoard::toggleQueen(size_t r, size_t c)
{
    if (eightQueenBoard[r][c])
    {
        currentQueenCount--;
        eightQueenBoard[r][c] = false;
    }
    else
    {
        if ((currentQueenCount+1) > static_cast<unsigned short>(boardSz))
        {
            printf("Too many queens!");
            return false;
        }
        currentQueenCount++;
        eightQueenBoard[r][c] = true;
    }
    return true;
}

bool EightQueenBoard::verifySolution() const
{
    // if there are not 8 queens in the board, solution is invalid
    if (currentQueenCount != 8)
    {
        printf("fewer than %lu queens are placed on the board", boardSz);
        return false;
    }

    // For a valid solution - each row must have 1 queen and each column must have 1 queen
    for (size_t i=0; i<boardSz; ++i)
    {
        const auto& row = eightQueenBoard[i];
        int queensCount = count(row.cbegin(), row.cend(), true);
        if (queensCount != 1) { return false; }
        queensCount = 0;
        for (size_t j=0; j<boardSz; ++j) { if (eightQueenBoard[j][i]) { queensCount++; } }
        if (queensCount != 1) { return false; }
    }

    // check for diagonal collisions
    auto checkPlusPlus = [&board=eightQueenBoard, sz=static_cast<int>(boardSz)] (int r, int c)
    {
        do { ++r; ++c; } while (r<sz && c<sz && !board[r][c]);
        if (r==sz || c==sz) { return false; } // no collision
        else { return true; } // collision with queen at board[r][c]
    };

    auto checkPlusMinus = [&board=eightQueenBoard, sz=static_cast<int>(boardSz)] (int r, int c)
    {
        do { ++r; --c; } while (r<sz && c>-1 && !board[r][c]);
        if (r==sz || c==-1) { return false; } // no collision
        else { return true; } // collision with queen at board[r][c]
    };

    auto checkMinusPlus = [&board=eightQueenBoard, sz=static_cast<int>(boardSz)] (int r, int c)
    {
        do { --r; ++c; } while (r>-1 && c<sz && !board[r][c]);
        if (r==-1 || c==sz) { return false; } // no collision
        else { return true; } // collision with queen at board[r][c]
    };

    auto checkMinusMinus = [&board=eightQueenBoard] (int r, int c)
    {
        do { --r; --c; } while (r>-1 && c>-1 && !board[r][c]);
        if (r==-1 || c==-1) { return false; } // no collision
        else { return true; } // collision with queen at board[r][c]
    };

    for (size_t i=0; i<boardSz; ++i)
    {
        const auto& row = eightQueenBoard[i];
        // find index of column where queen is placed
        size_t j = 0;
        for (; j<boardSz && !row[j]; ++j) {}
        if(checkPlusPlus(i,j) || checkPlusMinus(i,j) 
            || checkMinusPlus(i,j) || checkMinusMinus(i,j))
        {
            return false;
        }
    }
    return true;
}
}