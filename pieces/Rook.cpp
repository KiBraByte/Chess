//
// Created by kilian on 1/22/2023.
//

#include "Rook.h"
namespace jezz {

    Rook::Rook(int material, bool isWhite, char abbreviation) : Piece(material, isWhite, abbreviation) {}

    bool Rook::valid_move(Pos &from, Pos &to) {
        return false;
    }

    void Rook::calc_possible_moves(Piece::piece_map_t &pieces, Pos &curr_pos) {
        if (this != pieces[curr_pos].get()) return;

        //-----------------moves/take--------------------------------
        for (Pos next_pos{curr_pos}; (++curr_pos.y) < rows;) {
            if (!pieces.count(next_pos))
                possible_moves.insert({next_pos, MoveType::NORMAL});
            else if (!pieces[next_pos]->is_same_color(*this))
                possible_moves.insert({next_pos,
                                       pieces[next_pos]->getAbbreviation() == 'K' ?
                                       MoveType::CHECK : MoveType::TAKE});

        }

    }

}