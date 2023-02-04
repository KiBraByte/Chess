#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "./Piece.h"
#include "../utility/utility.h"

namespace jezz {
    class King : public Piece{
    private:
        bool in_check{false}, in_checkmate{false};
        Move::move_set check_castle(const piece_map_t & pieces, const Pos & curr_pos);

    public:
        explicit King(bool is_white);

        bool valid_move(const Move &move) override;

        Move::move_set calc_possible_moves(const piece_map_t &pieces, const Pos &curr_pos) override;

        bool isInCheck() const;

        void setInCheck(bool inCheck);

        bool isInCheckmate() const;

        void setInCheckmate(bool inCheckmate);
    };
}
#endif //CHESS_KING_H
