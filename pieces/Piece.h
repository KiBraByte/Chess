#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <unordered_set>
#include "../utility/utility.h"
#include <iostream>

namespace jezz {

    class Piece {
    public:
        typedef std::unordered_map<Pos, std::shared_ptr<Piece>> piece_map_t;
    protected:
        const int material{};
        const bool is_white{};
        const char abbreviation{};

        const std::function<bool(const piece_map_t& ,const Pos&)> could_still_move = [](const piece_map_t & pieces, const Pos & next_pos) {
            return !pieces.count(next_pos);
        };
        const std::function<bool(const Pos &)> in_bounds = [](const Pos & pos) {
            return pos.y >= 0 && pos.y < rows && pos.x >= 0 && pos.x < columns;
        };

        Move::move_set calc_all_moves_in_dir(const piece_map_t & pieces, const Pos & start_pos, Dir dir1, Dir dir2 = Dir::NONE, Dir dir3 = Dir::NONE);
        jezz::Move check_pos(const piece_map_t&, const Pos&, const Pos&);

        int times_moved{0};
    public:
        Piece(int material, bool is_white, char abbreviation);
        virtual ~Piece() = default;
        virtual Move::move_set calc_possible_moves(const piece_map_t & pieces, const Pos & curr_pos) = 0;

        [[nodiscard]] int getMaterial() const;
        [[nodiscard]] bool isWhite() const;
        [[nodiscard]] char getAbbreviation() const;
        void increased_moved();
        [[nodiscard]] bool is_same_color(const Piece & is_white) const;

        [[nodiscard]] int getTimesMoved() const;

        friend std::ostream& operator<<(std::ostream & os, const Piece & piece);
    };
} // chesspiece
#endif
