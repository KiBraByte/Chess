#include "Queen.h"

namespace jezz {

    Queen::Queen(bool is_white) : Piece(9, is_white, 'Q') {}

    Move::move_set Queen::calc_possible_moves(const Piece::piece_map_t &pieces, const Pos &curr_pos) {
        //-----------------moves/take--------------------------------
        Move::move_set possible_moves, tmp_moves;

        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;

        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::UP);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::DOWN);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::LEFT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::RIGHT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::UP, Dir::LEFT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::UP, Dir::RIGHT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::DOWN, Dir::LEFT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());
        tmp_moves = Piece::calc_all_moves_in_dir(pieces, curr_pos, Dir::DOWN, Dir::RIGHT);
        possible_moves.insert(tmp_moves.begin(), tmp_moves.end());

        return possible_moves;
    }
}

