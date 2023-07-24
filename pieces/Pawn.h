#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "Piece.h"
#include "../utility/utility.h"

namespace jezz {
    class Pawn : public Piece {
    private:
    public:
        explicit Pawn(bool is_white);
        Move::move_set calc_possible_moves(const piece_map_t & pieces, const Pos & curr_pos) override;
    };
}
#endif //CHESS_PAWN_H
