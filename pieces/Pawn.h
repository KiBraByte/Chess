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
    public:
        explicit Pawn(bool is_white);

        bool valid_move(const Move &move) override;

        Move::move_set calc_possible_moves(const piece_map_t & pieces, const Pos & curr_pos) override;
    };
}

#endif //CHESS_PAWN_H
