//
// Created by kilian on 1/21/2023.
//

#include "Piece.h"

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

namespace jezz {
    class Pawn : public Piece {
    public:
        explicit Pawn(bool is_white);
        bool valid_move(pos & from, pos &  to) override;
        bool valid_take(pos & from, pos &  to) override;
    };
}

#endif //CHESS_PAWN_H
