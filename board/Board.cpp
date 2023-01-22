//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Board.h"

namespace jezz {
    Board::Board() : whites_turn(true) {
        Pos r_pos{1,1}, p1_pos{6,1}, p2_pos{1,7};
        pieces.insert({r_pos, std::make_shared<Rook>(true)});
        pieces.insert({p1_pos, std::make_shared<Pawn>(true)});
        pieces.insert({p2_pos, std::make_shared<Pawn>(false)});

        pieces[r_pos]->calc_possible_moves(pieces,r_pos);
        for (auto const & m : pieces[r_pos]->get_possible_moves())
           std::cout << m << '\n';
    }

    Board::~Board() = default;


    void Board::print_board() const {
        for (Pos pos(0,0); pos.y < rows; ++pos.y) {
            for (pos.x = 0; pos.x < columns; ++pos.x) {
                char c = pieces.count(pos) > 0 ? pieces.at(pos)->getAbbreviation() : '.';
                std::cout << c;
            }
            std::cout << '\n';
        }
    }
} // jezz