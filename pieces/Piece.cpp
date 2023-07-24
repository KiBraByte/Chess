#include "Piece.h"

namespace jezz {
    Piece::Piece(int material, bool is_white, char abb) : material(material),
                                    is_white(is_white), abbreviation(abb) {}

    int Piece::getMaterial() const {
        return material;
    }

    bool Piece::isWhite() const {
        return is_white;
    }

    char Piece::getAbbreviation() const {
        return abbreviation;
    }

    void Piece::increased_moved() {
       ++times_moved;
    }

    bool Piece::is_same_color(const Piece & other) const {
        return is_white == other.is_white;
    }

    std::ostream& operator<<(std::ostream& os, const Piece& piece) {
        return (os << piece.abbreviation);
    }

    Move::move_set Piece::calc_all_moves_in_dir(const Piece::piece_map_t &pieces, const Pos &start_pos, Dir dir1, Dir dir2, Dir dir3) {
       Move::move_set moves;
        for (Pos next_pos{start_pos}; Piece::in_bounds((next_pos += get_dirs_as_pos(is_white,dir1,dir2,dir3)));) {
            Move mv = check_pos(pieces,start_pos, next_pos);
            if (!(mv == Move::invalidMove)) moves.insert(mv);
            if (!could_still_move(pieces, next_pos)) break;
        }
        return moves;
    }

    jezz::Move Piece::check_pos(const piece_map_t& pieces, const Pos& from, const Pos& to) {
        if (in_bounds(to)) {
            if (!pieces.count(to))
                return Move{from, to, MoveType::NORMAL};
            else if (!(pieces.at(to)->is_same_color(*this)))
                return Move{from, to, jezz::MoveType::TAKE};
        }

        return Move::invalidMove;
    }

    int Piece::getTimesMoved() const {
        return times_moved;
    }
} // chesspiece