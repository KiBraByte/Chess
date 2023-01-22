//
// Created by kilian on 1/21/2023.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include <memory>
#include "../pieces/Piece.h"
#include "../utility/utility.h"
#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"

namespace jezz {


    class Board {
    private:
        Piece::piece_map_t pieces;
        bool whites_turn;
    public:
        Board();
        ~Board();
        void print_board() const;
    };
} // jezz

#endif //CHESS_BOARD_H
