//
// Created by kilian on 1/22/2023.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Piece.h"

namespace jezz {
    class Rook : public Piece {
    private:
    public:
        Rook(int material, bool isWhite, char abbreviation);

        bool valid_move(Pos &from, Pos &to) override;

        void calc_possible_moves(piece_map_t &pieces, Pos &curr_pos) override;
    };

}


#endif //CHESS_ROOK_H
