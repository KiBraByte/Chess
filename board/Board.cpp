//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Board.h"

namespace jezz {
    Board::Board() : whites_turn(true) {
    }

    Board::~Board() = default;


    void Board::print_board() const {
        for (Pos pos(0,0); pos.y < rows; ++pos.y) {
            for (pos.x = 0; pos.x < columns; ++pos.x) {
                char c = pieces.count(pos) > 0 ? 'x' : '.';
                std::cout << c;
            }
            std::cout << '\n';
        }
    }
} // jezz