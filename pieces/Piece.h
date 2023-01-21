//
// Created by kilian on 1/20/2023.
//
#include "../utility/utility.h"
#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

namespace jezz {

    class Piece {
    protected:
        int material{};
        bool is_white{};
        char abbreviation{};
    public:
        Piece(int material, bool is_white, char abbreviation);
        virtual ~Piece() = default;

        virtual bool valid_move(pos & from, pos & to) = 0;
        virtual bool valid_take(pos & from, pos & to) = 0;

        int getMaterial() const;

        bool isWhite() const;

        char getAbbreviation() const;

    };

} // chesspiece

#endif //CHESS_PIECE_H
