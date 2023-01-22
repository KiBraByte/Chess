//
// Created by kilian on 1/20/2023.
//
#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <unordered_set>
#include "../utility/utility.h"
#include <iostream>

namespace jezz {

    class Piece {
    public:
        typedef std::unordered_map<Pos, std::shared_ptr<Piece>> piece_map_t;

    protected:
        int material{}, times_moved{0};
        bool is_white{};
        char abbreviation{};
        Move::move_set possible_moves;

    public:
        Piece(int material, bool is_white, char abbreviation);
        virtual ~Piece() = default;

        virtual bool valid_move(Pos & from, Pos & to) = 0;
        virtual void calc_possible_moves(piece_map_t & pieces, Pos & curr_pos) = 0;

        const Move::move_set & get_possible_moves() const;
        int getMaterial() const;
        bool isWhite() const;
        char getAbbreviation() const;
        void increased_moved();
        bool is_same_color(Piece & is_white) const;

        friend std::ostream& operator<<(std::ostream & os, const Piece & piece);
    };
} // chesspiece

#endif //CHESS_PIECE_H
