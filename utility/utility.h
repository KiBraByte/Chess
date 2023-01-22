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


    struct Pos {
        int x;
        int y;

        Pos(int y, int x);
        Pos(int y, char x);
        Pos() = default;

        [[nodiscard]] int get_2dInt() const;

        static Pos from_2dint_to_pos(int val);

        bool operator==(const Pos & o) const;
    };

    enum class MoveType {
        NONE, NORMAL, CHECK, TAKE, EN_PASSANT
    };

    struct Move : Pos{
        typedef std::unordered_set<Move, std::hash<Pos>> move_set;
        MoveType type;

        Move(int y, int x);
        Move(int y, int x, MoveType type);
        Move(int y, char x, MoveType type);
        Move(Pos & pos, MoveType type);
        Move(Pos & pos);


        friend std::ostream& operator<< (std::ostream& os, const Move & move);
    };
}

namespace std {
    template<> struct hash<jezz::Pos> {
        std::size_t operator()(const jezz::Pos & p) const;
    };
}

#endif //CHESS_UTILITY_H
