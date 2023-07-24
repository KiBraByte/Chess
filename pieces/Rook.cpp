#include "Rook.h"
namespace jezz {

    Rook::Rook(bool is_white) : Piece(5, is_white, 'R') {}

    Move::move_set Rook::calc_possible_moves(const Piece::piece_map_t &pieces,const Pos &curr_pos) {
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

        return possible_moves;
    }
}