#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H

#include<functional>
#include <memory>
#include <unordered_set>
#include<iostream>

namespace jezz {
    constexpr int rows = 8, columns = 8;

    //-----------------------------------------struct, enums -----------------------------------
    struct Pos {
        int x;
        int y;
        const static Pos invalidPos;

        Pos(int y, int x) noexcept;

        Pos(int y, char x) noexcept;

        Pos() = default;

        bool operator==(const Pos &o) const;

        Pos &operator+=(const Pos &o);
    };

    Pos operator+(const Pos & first, const Pos & second);

    enum class MoveType {
        NONE, NORMAL, TAKE, PROMOTION, EN_PASSANT, CASTLE_NORMAL, CASTLE_QUEEN
    };
    enum class Dir {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    struct Move {
        typedef std::unordered_set<Move> move_set;
        Pos from, to;
        MoveType type;
        const static Move invalidMove;

        Move(int from_y, int from_x, int to_y, int to_x) noexcept;

        Move(int from_y, int from_x, int to_y, int to_x, MoveType mt) noexcept;

        Move(Pos from, Pos to, MoveType mv) noexcept;

        explicit Move(Pos from, Pos to) noexcept;

        bool operator==(const Move &m) const;
    };
    //----------------------------------------Functions--------------------------------------------------

    //Pos get_dirs_as_pos(Dir dir, bool is_white = true);
    //Pos get_dirs_as_pos(Dir dir, Dir dir2, bool is_white = true);

    Pos get_dirs_as_pos(bool is_white, Dir dir, Dir dir2 = Dir::NONE, Dir dir3 = Dir::NONE);

    template <typename Enumeration>
    auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type {
            return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }
    //-----------------------------------<< Operator overrides---------------------------------------
    std::ostream& operator<< (std::ostream& os, const Pos & pos);

    std::ostream& operator<< (std::ostream& os, const MoveType & move_type);

    std::ostream& operator<< (std::ostream& os, const Move & move);
}

//------------------------------------------Hash functions for Pos (Move), Dir --------------------------------------
namespace std {
    template<> struct hash<jezz::Pos> {
        std::size_t operator()(const jezz::Pos & p) const;
    };

    template<> struct hash<jezz::Dir> {
        std::size_t operator()(const jezz::Dir & d) const;
    };

    template<> struct hash<jezz::Move> {
        std::size_t operator()(const jezz::Move & m) const;
    };
}
#endif //CHESS_UTILITY_H
