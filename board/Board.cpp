#include <iostream>
#include "Board.h"
#include "../pieces/King.h"
#include "../pieces/Knight.h"

namespace jezz {
    Board::Board() {
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
        std::cout << "\n  ";
        for (int i{0}; i < columns; ++i) std::cout << i << ' ';
        std::cout << "\n";

        for (Pos pos(0,0); pos.y < rows; ++pos.y) {
            std::cout << pos.y << ' ';
            for (pos.x = 0; pos.x < columns; ++pos.x) {
                
   
                char c = pieces.count(pos) > 0 ? pieces.at(pos)->getAbbreviation() : '.';
                if (pieces.count(pos) && !pieces.at(pos)->isWhite())
                    //std::cout << "\033[1;31m" << c << "\033[0m ";
                    std::cout << (char)(c - ('A' - 'a')) << ' ';
                else std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }
    // check if the move is legal, doesn't change the value of in_check
    bool Board::is_legal_move(const Move & move) {
        if (status != Status::ON_GOING) return false;
        if (!pieces.count(move.from)) return false;
        if (pieces[move.from]->isWhite() != whites_turn) return false;
        if (!pieces[move.from]->calc_possible_moves(pieces, move.from)
                                .count({move.from, move.to, MoveType::NONE})) return false;

        if ((move.type == MoveType::CASTLE_QUEEN || move.type == MoveType::CASTLE_NORMAL) && calc_check(pieces,whites_turn)) return false;

        //Check if due to the move your own King is in check
        Piece::piece_map_t tmp_copy = pieces;
        move_piece(tmp_copy,move);

        return !calc_check(tmp_copy, whites_turn);
    }

    bool Board::move(const Move & move) {
        if (!all_legal_moves.count(move)) return false;

        if ((all_legal_moves.find(move)->type == MoveType::TAKE || all_legal_moves.find(move)->type == MoveType::EN_PASSANT) && pieces.count(move.to))
            add_to_taken(move.to);

        Pos moved_to{move_piece(pieces, move)};
        if (!(moved_to == Pos{-1, -1}) && pieces.count(moved_to))
            pieces[moved_to]->increased_moved();
        else return false;


        whites_turn = !whites_turn;
        all_legal_moves.clear();
        all_legal_moves = calc_legal_moves(whites_turn);

        for (auto & mv : all_legal_moves)
            std::cout << mv << '\n';

        if (all_legal_moves.empty()) {
            bool is_checkmate = calc_check(pieces, whites_turn);
            if (is_checkmate)
                status = whites_turn ? Status::BLOCK_WON : Status::WHITE_WON;
            else status = Status::DRAW;
        }

        return true;
    }

    Pos Board::get_own_king_pos(const Piece::piece_map_t & piece_map, bool is_white) {
        for (auto & pair : piece_map)
            if (pair.second->getAbbreviation() == 'K' && pair.second->isWhite() == is_white) return pair.first;
        return Pos::invalidPos;
    }

    Pos Board::move_piece(Piece::piece_map_t &pieces, const Move & move) {
        Move::move_set moves = pieces[move.from]->calc_possible_moves(pieces,move.from);
        MoveType mt = moves.find(move)->type;

        int row = pieces[move.from]->isWhite() ? (rows - 1) : 0;

        switch (mt) {
            case MoveType::TAKE:
            case MoveType::NORMAL:
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
                   if (is_legal_move(mv))
                       legal_mvs.insert(mv);
               }
            }
        }
        return legal_mvs;
    }
    const std::vector<std::shared_ptr<Piece>> &Board::getWhitePiecesTaken() const {
        return white_pieces_taken;
    }

    const std::vector<std::shared_ptr<Piece>> &Board::getBlackPiecesTaken() const {
        return black_pieces_taken;
    }

    bool Board::calc_check(const Piece::piece_map_t & piece_map, bool white_king) {
        Pos king_pos = get_own_king_pos(piece_map, white_king);
        //TODO: THROW EXCEPTION
        if (king_pos == Pos::invalidPos) return false;

        return std::any_of(piece_map.begin(), piece_map.end(), [=](auto& entry) {
            if (entry.second->isWhite() == white_king) return false;
            return (bool) entry.second->calc_possible_moves(piece_map, entry.first).count(Move{entry.first, king_pos});
        });
    }

    Board::Status Board::getStatus() const {
        return status;
    }

    bool Board::isWhitesTurn() const {
        return whites_turn;
    }
} // jezz
std::ostream &operator<<(std::ostream &os, jezz::Board::Status s) {
    switch (s){
        case jezz::Board::Status::ON_GOING: return (os << "ON_GOING");
        case jezz::Board::Status::DRAW: return (os << "DRAW");
        case jezz::Board::Status::WHITE_WON: return (os << "WHITE_WON");
        case jezz::Board::Status::BLOCK_WON: return (os << "BLACK_WON");
    }

    return os << static_cast<std::uint16_t>(s);
}
