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
        Move::move_set all_legal_moves;
        Pos w_king{7,'e'}, b_king{0,'e'};
        //std::vector<std::shared_ptr<Piece>> white_pieces_taken;
        //std::vector<std::shared_ptr<Piece>> black_pieces_taken;
        bool whites_turn;

        static Pos move_piece(Piece::piece_map_t & pieces, const Move & move);
    public:
        Board();
        ~Board();
        void print_board() const;
        //void print_board(Piece::piece_map_t & pieces);
        bool is_legal_move(const Move & move);
        bool move(const Move & move);
        Pos get_own_king_pos(bool is_white);
        void set_own_king_pos(bool is_white, Pos & new_pos);
        Move::move_set calc_legal_moves(bool is_white);
        //bool is_board_valid(Piece::piece_map_t & new_board);
        //void calc_all_possible_moves();
    };
} // jezz

#endif //CHESS_BOARD_H
