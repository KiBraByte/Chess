//
// Created by kilian on 1/20/2023.
//
#include "utility.h"


namespace jezz {
    Pos::Pos(int y, int x) : x(x), y(y) {}

    Pos::Pos(int y, char x) : y(y), x(x - 'a'){}
    int Pos::get_2dInt() const {
        return y * columns + x;
    }

    Pos Pos::from_2dint_to_pos(int val) {
        return {(val / columns), (val % columns)};
    }

    bool Pos::operator==(const Pos &o) const {
       return (o.x == x)  && (o.y == y);
    }


    Move::Move(int y, int x) : Move(y, x, MoveType::NONE){}

    Move::Move(int y, int x, MoveType type) : Pos(y,x), type(type) {}

    Move::Move(int y, char x, MoveType type) : Pos(y,x) , type(type){}

    Move::Move(Pos & pos, MoveType type) : Pos(pos), type(type) {}

    Move::Move(Pos & pos) : Move(pos, MoveType::NONE) {}

    std::ostream &operator<<(std::ostream &os, const Move &move) {
        return (os << "y: " << move.y << " x: " << move.x << "\n");
    }
}

std::size_t std::hash<jezz::Pos>::operator()(const jezz::Pos &p) const {
    return std::hash<int>()(p.y) ^ std::hash<int>()(p.x);
}
