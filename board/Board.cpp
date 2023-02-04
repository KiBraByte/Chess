//
// Created by kilian on 1/21/2023.
//

#include <iostream>
#include "Board.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"

namespace jezz {
    Board::Board() : whites_turn(true) {
        //Kings
        pieces.insert({w_king, std::make_shared<King>(true)});
        pieces.insert({b_king, std::make_shared<King>(false)});

        //Queens
        pieces.insert({{0,'d'}, std::make_shared<Queen>(false)});
        pieces.insert({{7,'d'}, std::make_shared<Queen>(true)});

        //Rooks
        pieces.insert({{7,'a'}, std::make_shared<Rook>(true)});
        pieces.insert({{7,'h'}, std::make_shared<Rook>(true)});
        pieces.insert({{0,'a'}, std::make_shared<Rook>(false)});
        pieces.insert({{0,'h'}, std::make_shared<Rook>(false)});

        //knights
        pieces.insert({{7,'b'}, std::make_shared<Knight>(true)});
        pieces.insert({{7,'g'}, std::make_shared<Knight>(true)});
        pieces.insert({{0,'b'}, std::make_shared<Knight>(false)});
        pieces.insert({{0,'g'}, std::make_shared<Knight>(false)});

        //Bishop
        pieces.insert({{7,'c'}, std::make_shared<Bishop>(true)});
        pieces.insert({{7,'f'}, std::make_shared<Bishop>(true)});
        pieces.insert({{0,'c'}, std::make_shared<Bishop>(false)});
        pieces.insert({{0,'f'}, std::make_shared<Bishop>(false)});

        //Pawns
        for (Pos start{1, 'a'}; start.x < columns; ++start.x)
            pieces.insert({start, std::make_shared<Pawn>(false)});
        for (Pos start{6, 'a'}; start.x < columns; ++start.x)
         pieces.insert({start, std::make_shared<Pawn>(true)});

        all_legal_moves = calc_legal_moves(whites_turn);
    }

    Board::~Board() = default;


    void Board::print_board() const {
        std::cout << "\n\n";
        std::cout << "  ";
        for (int i{0}; i < columns; ++i) std::cout << i << ' ';
        std::cout << "\n";

        for (Pos pos(0,0); pos.y < rows; ++pos.y) {
            std::cout << pos.y << ' ';
            for (pos.x = 0; pos.x < columns; ++pos.x) {
                char c = pieces.count(pos) > 0 ? pieces.at(pos)->getAbbreviation() : '.';
                if (c != '.' && !pieces.at(pos)->isWhite()) c = (char)(c - (('A' - 'a')));
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }

    /*void Board::print_board(Piece::piece_map_t & pieces) {
        std::cout << "  ";
        for (int i{0}; i < columns; ++i) std::cout << i << ' ';
        std::cout << "\n";

        for (Pos pos(0,0); pos.y < rows; ++pos.y) {
            std::cout << pos.y << ' ';
            for (pos.x = 0; pos.x < columns; ++pos.x) {
                char c = pieces.count(pos) > 0 ? pieces.at(pos)->getAbbreviation() : '.';
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }*/

    // check if the move is legal, doesn't change the value of in_check
    bool Board::is_legal_move(const Move & move) {
        if (!pieces.count(move.from)) return false;
        if (pieces[move.from]->isWhite() != whites_turn) return false;
        if (!pieces[move.from]->calc_possible_moves(pieces, move.from)
                                .count({move.from, move.to, MoveType::NONE})) return false;

        //Check if due to the move your own King is in check
        std::shared_ptr<King> k_point = std::dynamic_pointer_cast<King>(pieces[get_own_king_pos(whites_turn)]);
        bool was_in_check = k_point->isInCheck();
        k_point->setInCheck(false);

        Piece::piece_map_t tmp_copy = pieces;
        move_piece(tmp_copy,move);

        //Position of own King
        for (auto & pair : tmp_copy)
            if (pair.second->isWhite() != whites_turn)
                Move::move_set moves = pair.second->calc_possible_moves(tmp_copy, pair.first);

        bool tmp = k_point->isInCheck();
        k_point->setInCheck(was_in_check);
        return !tmp;
    }

    bool Board::move(const Move & move) {
        if (!is_legal_move(move)) return false;

        Pos moved_to{move_piece(pieces, move)};
        if (!(moved_to == Pos{-1, -1}) && pieces.count(moved_to)) {
            pieces[moved_to]->increased_moved();
            if (pieces[moved_to]->getAbbreviation() == 'K') set_own_king_pos(whites_turn, moved_to);
            std::shared_ptr<King> k_point = std::dynamic_pointer_cast<King>(pieces[get_own_king_pos(whites_turn)]);
            if (k_point->isInCheck()) k_point->setInCheck(false);
        }


        whites_turn = !whites_turn;
        all_legal_moves.clear();
        all_legal_moves = calc_legal_moves(whites_turn);

       //for (auto & mv : all_legal_moves)
        //    std::cout << mv << '\n';


        if (all_legal_moves.empty()) {
            std::shared_ptr<King> k_point = std::dynamic_pointer_cast<King>(pieces[get_own_king_pos(whites_turn)]);
            calc_legal_moves(!whites_turn);
            if (k_point->isInCheck()) std::cout << "it is a win {Checkmate}" << '\n';
            else std::cout << "it is a win {stalemate}" << '\n';
        }

        return true;
    }

    Pos Board::get_own_king_pos(bool is_white) {
        return is_white ? w_king : b_king;
    }

    void Board::set_own_king_pos(bool is_white, Pos & new_pos) {
        is_white ? w_king = new_pos : b_king = new_pos;
    }

    /*bool Board::is_board_valid(Piece::piece_map_t &new_pieces) {
        return false;
    }*/

    /*void Board::calc_all_possible_moves() {
        //for (auto & pair : )
    }*/

    Pos Board::move_piece(Piece::piece_map_t &pieces, const Move & move) {
        Move::move_set moves = pieces[move.from]->calc_possible_moves(pieces,move.from);
        MoveType mt = moves.find(move)->type;

        int row = pieces[move.from]->isWhite() ? 7 : 0;

        switch (mt) {
            case MoveType::NORMAL:
            case MoveType::CHECK:
            case MoveType::TAKE:
                pieces[move.to] = pieces[move.from];
                pieces.erase(move.from);
                return move.to;
            case MoveType::CASTLE_NORMAL:
                pieces[{row, 5}] = pieces[{row, 7}];
                pieces[{row, 6}] = pieces[move.from];
                pieces.erase(move.from);
                pieces.erase({row, 7});
                return {row,6};
            case MoveType::CASTLE_QUEEN:
                pieces[{row,3}] = pieces[{row,0}];
                pieces[{row,2}] = pieces[move.from];
                pieces.erase(move.from);
                pieces.erase({row,0});
                return {row, 2};
            case MoveType::PROMOTION:
                pieces[move.to] = std::make_shared<Queen>(pieces[move.to]->isWhite());
                pieces.erase(move.from);
                return move.to;
            case MoveType::EN_PASSANT:
                pieces.erase(move.to);
                pieces[move.to + get_dirs_as_pos(pieces[move.from]->isWhite(), Dir::UP)] = pieces[move.from];
                pieces.erase(move.from);
                break;
            case MoveType::NONE:
                break;
        }

        return {-1,-1};
    }

    // where all pieces of the currents turn could move, sets in_check of king
    Move::move_set Board::calc_legal_moves(bool is_white) {
        Move::move_set legal_mvs, tmp_moves;
        for (auto & pos_piece : pieces) {
            if (pos_piece.second->isWhite() == is_white) {
               tmp_moves = pos_piece.second->calc_possible_moves(pieces, pos_piece.first);
               for (auto & mv : tmp_moves) {
                   if (is_legal_move( mv)) {
                       legal_mvs.insert(mv);
                   }
               }
            }
        }
        return legal_mvs;
    }
} // jezz