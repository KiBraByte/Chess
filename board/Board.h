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
#include "../pieces/Bishop.h"
#include "../pieces/Queen.h"

namespace jezz {


    class Board {
    private:
        Piece::piece_map_t pieces;
        Pos w_king{7,'e'}, b_king{0,'e'};
        bool whites_turn;
    public:
        Board();
        ~Board();
        void print_board() const;
        void print_board(Piece::piece_map_t & pieces);
        bool valid_move(Pos & from, Pos & to);
        bool move(Pos & from, Pos & to);
        Pos get_own_king_pos(bool is_white);
        void set_own_king_pos(bool is_white, Pos & new_pos);
        bool is_board_valid(Piece::piece_map_t & new_board);
        void calc_all_possible_moves();
    };
} // jezz

#endif //CHESS_BOARD_H
