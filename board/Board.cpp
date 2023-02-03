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
                if (c != '.' && !pieces.at(pos)->isWhite()) c = c - ('A' - 'a');
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }

    void Board::print_board(Piece::piece_map_t & pieces) {
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
    }

    bool Board::valid_move(Pos &from, Pos &to) {
        if (!pieces.count(from)) return false;
        if (pieces[from]->isWhite() != whites_turn) return false;
        if (!pieces[from]->calc_possible_moves(pieces, from).count({to, MoveType::NONE})) return false;

        //Check if due to the move your own King is in check
        Piece::piece_map_t tmp_copy = pieces;
        tmp_copy[to] = tmp_copy[from];
        tmp_copy.erase(from);

        //Position of own King
        Pos k_pos{};
        for (auto & pair : tmp_copy) {
            if (pair.second->getAbbreviation() == 'K' && pair.second->isWhite() == whites_turn)
                k_pos = pair.first;
            pair.second->calc_possible_moves(tmp_copy, pair.first);
        }

        std::shared_ptr<King> k_point = std::dynamic_pointer_cast<King>(tmp_copy[k_pos]);
        bool tmp = k_point->isInCheck();
        k_point->setInCheck(false);
        return !tmp;
    }

    bool Board::move(Pos &from, Pos &to) {
        if (!valid_move(from, to)) return false;


        pieces[to] = pieces[from];
        pieces.erase(from);

        pieces[to]->increased_moved();
        if (pieces[to]->getAbbreviation() == 'K') set_own_king_pos(whites_turn, to);

        whites_turn = !whites_turn;
        return true;
    }

    Pos Board::get_own_king_pos(bool is_white) {
        return is_white ? w_king : b_king;
    }

    void Board::set_own_king_pos(bool is_white, Pos & new_pos) {
        is_white ? w_king = new_pos : b_king = new_pos;
    }

    bool Board::is_board_valid(Piece::piece_map_t &new_pieces) {
        return false;
    }

    void Board::calc_all_possible_moves() {
        //for (auto & pair : )
    }
} // jezz