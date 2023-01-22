//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Pawn.h"

namespace jezz {
    Pawn::Pawn(bool is_white) : Piece(1,is_white,'p'), y_offset(is_white ? -1 : 1){}

    bool Pawn::valid_move(Pos & from, Pos & to) {
        return is_white ? from.y - to.y == 1 : from.y - to.y == -1;
    }

    void Pawn::calc_possible_moves(piece_map_t & pieces, Pos & curr_pos) {
        if (this != pieces[curr_pos].get()) return;

        possible_moves.clear();
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return;

        //----------------------------Promotions---------------------------------------------
        Pos next_pos{curr_pos.y + y_offset, curr_pos.x};                                    //Position when moved one field forward
        if (curr_pos.y == (rows - 1)  || curr_pos.y == 0) {
            possible_moves.insert({curr_pos, MoveType::PROMOTION});
            return;
        }

        if ((next_pos.y == 0 || next_pos.y == rows - 1) && !pieces.count(next_pos))
            possible_moves.insert({next_pos, MoveType::PROMOTION});

        //-----------------------------Normal Move-------------------------------------------
        if (pieces.count(next_pos) == 0)
            possible_moves.insert({next_pos, MoveType::NORMAL});

        //----------------------------Take----------------------------------------------------
        auto check_for_take = [&pieces, this](Pos next_pos) {
            if (pieces.count((next_pos)) && !pieces[next_pos]->is_same_color(*this)) {
                if (pieces[next_pos]->getAbbreviation() == 'K') {
                    possible_moves.insert({next_pos, MoveType::CHECK});
                    //TODO: set is_check of King to true
                }
                else
                    possible_moves.insert({next_pos, MoveType::TAKE});
            }
        };
        check_for_take({curr_pos.y + y_offset, curr_pos.x + 1});                                //forward right
        check_for_take({curr_pos.y + y_offset, curr_pos.x - 1 });                               //forward left
    }
}