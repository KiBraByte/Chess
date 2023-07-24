#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "Piece.h"

namespace jezz {
    class Rook : public Piece {
    public:
        explicit Rook(bool is_white);
        Move::move_set calc_possible_moves(const piece_map_t &pieces,const Pos &curr_pos) override;
    };

}
#endif //CHESS_ROOK_H
