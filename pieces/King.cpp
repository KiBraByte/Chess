#include "King.h"

namespace jezz {
    King::King(bool is_white) : Piece(INT32_MAX, is_white, 'K') {}

    Move::move_set King::calc_possible_moves(const Piece::piece_map_t &pieces,const Pos &curr_pos) {

        Move::move_set possible_moves;
        if (!pieces.count(curr_pos) && this != pieces.at(curr_pos).get()) return possible_moves;
        if (curr_pos.y > (rows - 1) || curr_pos.y < 0 || curr_pos.x > (columns - 1) || curr_pos.x < 0) return possible_moves;

        Pos p = {curr_pos + get_dirs_as_pos(is_white, Dir::UP)};

        auto check_pos_and_insert = [&]() {
            Move mv = check_pos(pieces,curr_pos, p);
            if (!(mv == Move::invalidMove)) possible_moves.insert(mv);
        };
        check_pos_and_insert();

        p = curr_pos + get_dirs_as_pos(is_white,Dir::DOWN);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::LEFT);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::RIGHT);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::LEFT);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::UP, Dir::RIGHT);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::DOWN, Dir::LEFT);
        check_pos_and_insert();
        p = curr_pos + get_dirs_as_pos(is_white,Dir::DOWN, Dir::RIGHT);
        check_pos_and_insert();

        Move::move_set tmp = check_castle(pieces, curr_pos);
        possible_moves.insert(tmp.begin(), tmp.end());

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

    Move::move_set King::check_castle(const Piece::piece_map_t &pieces, const Pos & curr_pos) {
        Move::move_set moves;
        int row = is_white ? 7 : 0;
        if (times_moved > 0) return moves;
        if (!pieces.count({row, 4}) || pieces.at({row, 4}).get() != this) return moves;
        if (isInCheck()) return moves;

        Pos rook_pos{row, 7};
        //a same colored rook who hasn't moved yet
        if (pieces.count(rook_pos) && pieces.at(rook_pos)->getAbbreviation() == 'R'
            && pieces.at(rook_pos)->isWhite() == is_white && pieces.at(rook_pos)->getTimesMoved() == 0)
            //if there are no pieces in between
            if (!pieces.count({row,5}) && !pieces.count({row,6}))
                moves.insert(Move{curr_pos, {row,7}, MoveType::CASTLE_NORMAL});

        Pos queen_rook_pos{row, 0};
        if (pieces.count(queen_rook_pos) && pieces.at(queen_rook_pos)->getAbbreviation() == 'R'
            && pieces.at(queen_rook_pos)->isWhite() == is_white && pieces.at(queen_rook_pos)->getTimesMoved() == 0)
            if (!pieces.count({row,1}) && !pieces.count({row,2}) && !pieces.count({row,3}))
                moves.insert(Move{curr_pos, {row,0}, MoveType::CASTLE_QUEEN});

        return moves;
    }

    bool King::valid_move(const Move &move) {
        return false;
    }
}
