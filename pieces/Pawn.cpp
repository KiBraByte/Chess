//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Pawn.h"
#include "King.h"

namespace jezz {
    Pawn::Pawn(bool is_white) : Piece(1,is_white,'P'), y_offset(is_white ? -1 : 1){}

    bool Pawn::valid_move(Pos & from, Pos & to) {
        return is_white ? from.y - to.y == 1 : from.y - to.y == -1;
    }

    Move::move_set Pawn::calc_possible_moves(const piece_map_t & pieces, const Pos & curr_pos) {
        //TODO: Implement


        Move::move_set possible_moves;

        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;
        //----------------------------Promotions---------------------------------------------
        if (curr_pos.y == (rows - 1)  || curr_pos.y == 0)
            possible_moves.insert({curr_pos, MoveType::PROMOTION});


        const Pos up_pos = curr_pos + get_dirs_as_pos(is_white, Dir::UP);                                    //Position when moved one field forward
        if ((up_pos.y == 0 || up_pos.y == rows - 1) && !pieces.count(up_pos))
            possible_moves.insert({up_pos, MoveType::PROMOTION});

        //-----------------------------Normal Move-------------------------------------------
        if (!pieces.count(up_pos))
            possible_moves.insert({up_pos, MoveType::NORMAL});

        if (!times_moved) {
            const Pos up_up_pos = curr_pos + get_dirs_as_pos(is_white, Dir::UP,
                                                             Dir::UP);                                    //Position when moved one field forward
            if (!pieces.count(up_up_pos))
                possible_moves.insert({up_up_pos, MoveType::NORMAL});
        }

        //----------------------------Take----------------------------------------------------
        auto check_for_take = [&pieces, this](const Pos next_pos) {
            if (pieces.count((next_pos)) && !pieces.at(next_pos)->is_same_color(*this)) {
                if (pieces.at(next_pos)->getAbbreviation() == 'K') {
                    std::shared_ptr<King> kingp = std::dynamic_pointer_cast<King>(pieces.at(next_pos));
                    kingp->setInCheck(true);
                    return Move{next_pos, MoveType::CHECK};
                }
                else return Move{next_pos, MoveType::TAKE};
            }
            return Move{{-1,-1}, MoveType::NONE};
        };

        Move mv = check_for_take({curr_pos.y + y_offset, curr_pos.x + 1});                                //forward right
        if (mv.type != MoveType::NONE) possible_moves.insert(mv);
        mv = check_for_take({curr_pos.y + y_offset, curr_pos.x - 1 });                               //forward left
        if (mv.type != MoveType::NONE) possible_moves.insert(mv);

        return possible_moves;
    }
}