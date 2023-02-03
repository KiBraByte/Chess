//
// Created by kilian on 1/20/2023.
//

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

        Pos(int y, int x);

        Pos(int y, char x);

        Pos() = default;

        [[nodiscard]] int get_2dInt() const;

        static Pos from_2dint_to_pos(int val);

        bool operator==(const Pos &o) const;

        Pos &operator+=(const Pos &o);
    };

    Pos operator+(const Pos & first, const Pos & second);

    enum class MoveType {
        NONE, NORMAL, CHECK, TAKE, PROMOTION, EN_PASSANT
    };
    enum class Dir {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    struct Move : public Pos {
        typedef std::unordered_set<Move, std::hash<Pos>> move_set;
        MoveType type;

        Move(int y, int x);

        Move(int y, int x, MoveType type);

        Move(int y, char x, MoveType type);

        Move(Pos pos, MoveType type);

        explicit Move(Pos pos);
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
}
#endif //CHESS_UTILITY_H
