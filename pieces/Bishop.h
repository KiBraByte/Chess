//
// Created by kilian on 1/22/2023.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "./Piece.h"
namespace jezz {
    class Bishop : public Piece {
    public:
        explicit Bishop(bool is_white);

        bool valid_move(const Move & move) override;

        Move::move_set calc_possible_moves(const piece_map_t &pieces, const Pos &curr_pos) override;
    };
}


#endif //CHESS_BISHOP_H
