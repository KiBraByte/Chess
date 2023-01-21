//
// Created by kilian on 1/21/2023.
//

#include <cmath>
#include "Pawn.h"

namespace jezz {
    Pawn::Pawn(bool is_white) : Piece(1,is_white,'P'){}

    bool Pawn::valid_move(pos & from, pos & to) {
        return is_white ? from.y - to.y == 1 : from.y - to.y == -1;
    }

    bool Pawn::valid_take(pos &from, pos &to) {
        return std::abs(from.x - to.x) == 1 &&
                (valid_move(from, to));
    }
}