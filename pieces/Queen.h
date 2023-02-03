//
// Created by kilian on 1/22/2023.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "./Piece.h"
#include "../utility/utility.h"
namespace jezz {
    class Queen : public Piece{
    public:
        explicit Queen(bool is_white);

        bool valid_move(Pos &from, Pos &to) override;

        Move::move_set calc_possible_moves(const piece_map_t &pieces, const Pos &curr_pos) override;

    };
}


#endif //CHESS_QUEEN_H
