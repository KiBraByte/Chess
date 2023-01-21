//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Board.h"

namespace jezz {
    Board::Board() {
        board[pos{0,'a'}.get_2dInt()] = new Pawn(true);
    }

    Board::~Board() {
        for (int i{0}; i < rows * columns; ++i)
            delete board[i];

        delete[] board;
    }

    void Board::print_board() const {
        pos curr_pos {0,0};
        for (int i{0}; i < rows; curr_pos.y = ++i) {
            for (int j{0}; j < columns; curr_pos.x = ++j) {
               char piece = board[curr_pos.get_2dInt()] ? board[curr_pos.get_2dInt()]->getAbbreviation() : '.';
               std::cout << piece;
            }
            std::cout << '\n';
        }
    }
} // jezz