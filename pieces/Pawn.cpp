//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Pawn.h"
#include "King.h"

namespace jezz {
    Pawn::Pawn(bool is_white) : Piece(1,is_white,'P'){}

    Move::move_set Pawn::calc_possible_moves(const piece_map_t & pieces, const Pos & curr_pos) {
        //TODO: Implement


        Move::move_set possible_moves;

        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;
        //----------------------------Promotions---------------------------------------------
        if (curr_pos.y == (rows - 1)  || curr_pos.y == 0)
            possible_moves.insert({curr_pos, curr_pos, MoveType::PROMOTION});


        const Pos up_pos = curr_pos + get_dirs_as_pos(is_white, Dir::UP);                                    //Position when moved one field forward
        if ((up_pos.y == 0 || up_pos.y == rows - 1) && !pieces.count(up_pos))
            possible_moves.insert({curr_pos, up_pos, MoveType::PROMOTION});

        //-----------------------------Normal Move-------------------------------------------
        if (!pieces.count(up_pos))
            possible_moves.insert({curr_pos, up_pos, MoveType::NORMAL});

        if (!times_moved) {
            const Pos up_up_pos = curr_pos + get_dirs_as_pos(is_white, Dir::UP,
                                                             Dir::UP);                                    //Position when moved one field forward
            if (!pieces.count(up_up_pos))
                possible_moves.insert({curr_pos, up_up_pos, MoveType::NORMAL});
        }

        //----------------------------Take----------------------------------------------------
        auto check_for_take = [&](const Pos next_pos) {
            if (pieces.count((next_pos)) && !pieces.at(next_pos)->is_same_color(*this)) {
                if (pieces.at(next_pos)->getAbbreviation() == 'K') {
                    std::shared_ptr<King> kingp = std::dynamic_pointer_cast<King>(pieces.at(next_pos));
                    kingp->setInCheck(true);
                    possible_moves.insert({curr_pos, next_pos, MoveType::CHECK});
                }
                possible_moves.insert({curr_pos, next_pos, MoveType::TAKE});
            }
        };
        check_for_take(curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::RIGHT));                                //forward right
        check_for_take(curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::LEFT));                               //forward left


        auto check_for_en_passant = [&](const Pos & to) {
            int en_passant_row = is_white ? 3 : 4;
            if (curr_pos.y == en_passant_row) {
                if (pieces.count(to) && !is_same_color(*pieces.at(to))
                && pieces.at(to)->getTimesMoved() == 1 && !pieces.count(to + get_dirs_as_pos(is_white, Dir::UP)))
                    possible_moves.insert(Move{curr_pos, to, MoveType::EN_PASSANT});
            }
        };

        check_for_en_passant(curr_pos + get_dirs_as_pos(is_white, Dir::LEFT));
        check_for_en_passant(curr_pos + get_dirs_as_pos(is_white, Dir::RIGHT));

        return possible_moves;
    }

    bool Pawn::valid_move(const Move &move) {
        return false;
    }
}