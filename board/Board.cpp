//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Board.h"

namespace jezz {
    Board::Board() : whites_turn(true) {
        pieces.insert({{1,1}, std::make_shared<Pawn>(true)});

        Pos p{1,1};

        pieces[{1,1}]->calc_possible_moves(pieces,p);
        for (auto & pair : pieces)
            std::cout << *pair.second << "\n";

        for (auto & pair : pieces[{1,1}]->get_possible_moves()  )
            std::cout << pair << "\n";

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