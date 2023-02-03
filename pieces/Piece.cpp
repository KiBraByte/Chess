//
// Created by kilian on 1/20/2023.
//

#include "Piece.h"
#include "King.h"
#include "Queen.h"

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

    /*const Move::move_set & Piece::get_possible_moves() const {
        return possible_moves;
    }*/

    bool Piece::is_same_color(Piece & other) const {
        return is_white == other.is_white;
    }

    std::ostream& operator<<(std::ostream& os, const Piece& piece) {
        return (os << piece.abbreviation << ' ' << piece.is_white << '\n');
    }

    Move::move_set Piece::calc_all_moves_in_dir(const Piece::piece_map_t &pieces, const Pos &start_pos, Dir dir1, Dir dir2, Dir dir3) {
       Move::move_set moves;
        for (Pos next_pos{start_pos}; Piece::in_bounds((next_pos += get_dirs_as_pos(is_white,dir1,dir2,dir3)));) {
            Move mv = check_pos(pieces, next_pos);
            if (mv.type != MoveType::NONE) moves.insert(mv);
            if (!could_still_move(pieces, next_pos)) break;
        }
        return moves;
    }

    /*void Piece::setPossibleMoves(const Move::move_set &possibleMoves) {
        possible_moves = possibleMoves;
    }*/

    jezz::Move Piece::check_pos(const piece_map_t& pieces ,const Pos& next_pos) {
        if (in_bounds(next_pos)) {
            if (!pieces.count(next_pos)) {
                return Move{next_pos, MoveType::NORMAL};
            } else if (!(pieces.at(next_pos)->is_same_color(*this))) {
                if (pieces.at(next_pos)->getAbbreviation() == 'K') {
                    std::shared_ptr<King> kingp = std::dynamic_pointer_cast<King>(pieces.at(next_pos));
                    kingp->setInCheck(true);
                    return Move{next_pos, jezz::MoveType::CHECK};
                }
                return Move{next_pos, jezz::MoveType::TAKE};
            }
        }
        return Move{{-1,-1}, MoveType::NONE};
    }

} // chesspiece