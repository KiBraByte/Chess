#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "./Piece.h"
#include "../utility/utility.h"

namespace jezz {
    class King : public Piece{
    private:
        bool in_check{false};
        Move::move_set check_castle(const piece_map_t & pieces, const Pos & curr_pos);

    public:
        explicit King(bool is_white);

        Move::move_set calc_possible_moves(const piece_map_t &pieces, const Pos &curr_pos) override;

        [[nodiscard]] bool isInCheck() const;

        void setInCheck(bool inCheck);
    };
}
#endif //CHESS_KING_H
