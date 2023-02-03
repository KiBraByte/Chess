//
// Created by kilian on 1/22/2023.
//

#include "King.h"

namespace jezz {

    King::King(bool is_white) : Piece(INT32_MAX, is_white, 'K') {}

    bool King::valid_move(Pos &from, Pos &to) {
        return false;
    }

    Move::move_set King::calc_possible_moves(const Piece::piece_map_t &pieces,const Pos &curr_pos) {

        Move::move_set possible_moves;
        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;

        Move mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::UP));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::DOWN));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::LEFT));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::RIGHT));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::LEFT));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::RIGHT));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::DOWN, Dir::LEFT));
        possible_moves.insert(mv);
        mv = Piece::check_pos(pieces, curr_pos + get_dirs_as_pos(is_white,Dir::DOWN, Dir::RIGHT));
        possible_moves.insert(mv);

        return possible_moves;
    }

    bool King::isInCheck() const {
        return in_check;
    }

    void King::setInCheck(bool inCheck) {
        in_check = inCheck;
    }

    bool King::isInCheckmate() const {
        return in_checkmate;
    }

    void King::setInCheckmate(bool inCheckmate) {
        in_checkmate = inCheckmate;
    }

}
