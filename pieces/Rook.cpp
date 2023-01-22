//
// Created by kilian on 1/22/2023.
//

#include "Rook.h"
namespace jezz {

    Rook::Rook(bool is_white) : Piece(5, is_white, 'r') {}

    bool Rook::valid_move(Pos &from, Pos &to) {
        return false;
    }

    void Rook::calc_possible_moves(Piece::piece_map_t &pieces, Pos &curr_pos) {
        if (this != pieces[curr_pos].get()) return;

        //returns if the rook can keep going in this direction
        auto check_pos = [&pieces, this](Pos & next_pos) {
            if (!pieces.count(next_pos)) {
                possible_moves.insert({next_pos, MoveType::NORMAL});
                return true;
            }
            else if (!pieces[next_pos]->is_same_color(*this)) {
                possible_moves.insert({next_pos,
                                       pieces[next_pos]->getAbbreviation() == 'K' ?
                                       MoveType::CHECK : MoveType::TAKE});
            }
            return false;
        };

        //-----------------moves/take--------------------------------
        for (Pos next_pos{curr_pos}; (next_pos += get_dirs_as_pos(Dir::DOWN)).y < rows;)
            if(!check_pos(next_pos)) break;
        for (Pos next_pos{curr_pos}; (next_pos += get_dirs_as_pos(Dir::UP)).y >= 0;)
            if(!check_pos(next_pos)) break;
        for (Pos next_pos{curr_pos}; (next_pos += get_dirs_as_pos(Dir::RIGHT)).x < columns;)
            if(!check_pos(next_pos)) break;
        for (Pos next_pos{curr_pos}; (next_pos += get_dirs_as_pos(Dir::LEFT)).x >= 0;)
            if(!check_pos(next_pos)) break;
    }
}