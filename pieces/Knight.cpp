#include "Knight.h"
namespace jezz {

    Knight::Knight(bool is_white) : Piece(3,is_white,'N') {}

    Move::move_set Knight::calc_possible_moves(const Piece::piece_map_t &pieces, const Pos &curr_pos) {
        //-----------------moves/take--------------------------------
        Pos p((curr_pos + get_dirs_as_pos(is_white, Dir::UP,Dir::UP,Dir::RIGHT)));
        Move::move_set possible_moves;

        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;

        auto check_pos_and_insert = [&]() {
            Move mv = check_pos(pieces, curr_pos, p);
            if (!(mv == Move::invalidMove)) possible_moves.insert(mv);
        };
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white,Dir::UP,Dir::UP,Dir::LEFT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::DOWN,Dir::DOWN,Dir::RIGHT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::DOWN,Dir::DOWN,Dir::LEFT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::UP,Dir::RIGHT,Dir::RIGHT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::UP,Dir::LEFT,Dir::LEFT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::DOWN,Dir::RIGHT,Dir::RIGHT);
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white, Dir::DOWN,Dir::LEFT,Dir::LEFT);
        check_pos_and_insert();

        return possible_moves;
    }
}