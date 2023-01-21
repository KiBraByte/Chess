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

} // chesspiece