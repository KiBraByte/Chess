//
// Created by kilian on 1/21/2023.
//
#include <vector>
#include <memory>
#include "../pieces/Piece.h"
#include "../utility/utility.h"
#include "../pieces/Pawn.h"
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

namespace jezz {

    class Board {
    private:
        Piece** board = new Piece*[rows * columns]{nullptr};
    public:
        Board();
        ~Board();
        void print_board() const;
    };
} // jezz

#endif //CHESS_BOARD_H
