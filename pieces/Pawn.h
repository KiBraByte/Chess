//
// Created by kilian on 1/21/2023.
//


#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"
#include "../utility/utility.h"

namespace jezz {
    class Pawn : public Piece {
    private:
        int y_offset{};
    public:
        explicit Pawn(bool is_white);

        bool valid_move(Pos & from, Pos &  to) override;


        void calc_possible_moves(piece_map_t & pieces, Pos & curr_pos) override;
    };
}

#endif //CHESS_PAWN_H
