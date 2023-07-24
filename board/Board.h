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
    public:
        enum class Status {
            ON_GOING, DRAW, WHITE_WON, BLOCK_WON
        };
    private:
        Piece::piece_map_t pieces;
        Move::move_set all_legal_moves;
        Pos w_king{7,'e'}, b_king{0,'e'};
        std::vector<std::shared_ptr<Piece>> white_pieces_taken;
        std::vector<std::shared_ptr<Piece>> black_pieces_taken;
        bool whites_turn{true};
        Status status {Status::ON_GOING};

        static Pos move_piece(Piece::piece_map_t & pieces, const Move & move);
        const std::function<void(const Pos &)> add_to_taken = [&](const Pos & pos) {
            if (!pieces.count(pos)) return;
            if (pieces[pos]->isWhite()) white_pieces_taken.push_back(pieces[pos]);
            else black_pieces_taken.push_back(pieces[pos]);
        };
    public:
        Board();
        ~Board();
        void print_board() const;
        //void print_board(Piece::piece_map_t & pieces);
        bool is_legal_move(const Move & move);
        bool move(const Move & move);
        static Pos get_own_king_pos(const Piece::piece_map_t & piece_map, bool is_white) ;
        Move::move_set calc_legal_moves(bool is_white);
        //bool is_board_valid(Piece::piece_map_t & new_board);
        //void calc_all_possible_moves();

        Status getStatus() const;

        const std::vector<std::shared_ptr<Piece>> &getWhitePiecesTaken() const;

        const std::vector<std::shared_ptr<Piece>> &getBlackPiecesTaken() const;

        static bool calc_check(const Piece::piece_map_t & piece_map,bool white_king) ;

        bool isWhitesTurn() const;
    };
} // jezz

std::ostream & operator<<(std::ostream & os, jezz::Board::Status s);
#endif //CHESS_BOARD_H
