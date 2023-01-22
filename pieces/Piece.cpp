//
// Created by kilian on 1/20/2023.
//

#include "Piece.h"

namespace jezz {
    Piece::Piece(int material, bool is_white, char abb) : material(material),
                                    is_white(is_white), abbreviation(abb) {}

    int Piece::getMaterial() const {
        return material;
    }

    bool Piece::isWhite() const {
        return is_white;
    }

    char Piece::getAbbreviation() const {
        return abbreviation;
    }

    void Piece::increased_moved() {
       ++times_moved;
    }

    const Move::move_set & Piece::get_possible_moves() const {
        return possible_moves;
    }

    bool Piece::is_same_color(Piece & other) const {
        return is_white == other.is_white;
    }

    std::ostream& operator<<(std::ostream& os, const Piece& piece) {
        return (os << piece.abbreviation << ' ' << piece.is_white << '\n');
    }


} // chesspiece