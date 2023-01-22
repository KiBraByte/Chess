//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Pawn.h"

namespace jezz {
    Pawn::Pawn(bool is_white) : Piece(1,is_white,'P'), y_offset(is_white ? -1 : 1){}

    bool Pawn::valid_move(Pos & from, Pos & to) {
        return is_white ? from.y - to.y == 1 : from.y - to.y == -1;
    }

    void Pawn::calc_possible_moves(piece_map_t & pieces, Pos & curr_pos) {
        if (this != pieces[curr_pos].get()) return;

        possible_moves.clear();
        Pos tmp_move{};
        if (pieces.count((tmp_move = {curr_pos.y + y_offset,curr_pos.x})) == 0)
            possible_moves.insert({tmp_move, MoveType::NORMAL});

        if (pieces.count((tmp_move = {curr_pos.y + y_offset,curr_pos.x + 1})) == 1 && !is_same_color(*pieces[tmp_move]))
            possible_moves.insert({tmp_move, MoveType::TAKE});

        if (pieces.count((tmp_move = {curr_pos.y + y_offset,curr_pos.x - 1})) == 1 && !is_same_color(*pieces[tmp_move]))
            possible_moves.insert({tmp_move, MoveType::TAKE});

    }
}