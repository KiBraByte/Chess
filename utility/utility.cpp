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

    Pos &Pos::operator+=(const Pos &o) {
        y += o.y; x += o.x;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Pos &pos) {
        return (os << "y: " << pos.y << " x: " << pos.x << "\n");
    }

    Move::Move(int y, int x) : Move(y, x, MoveType::NONE){}

    Move::Move(int y, int x, MoveType type) : Pos(y,x), type(type) {}

    Move::Move(int y, char x, MoveType type) : Pos(y,x) , type(type){}

    Move::Move(Pos pos, MoveType type) : Pos(pos), type(type) {}

    Move::Move(Pos pos) : Move(pos, MoveType::NONE) {}

    std::ostream &operator<<(std::ostream &os, const Move &move) {
        return (os << "y: " << move.y << " x: " << move.x << ' ' << move.type <<  "\n");
    }

    std::ostream& operator<< (std::ostream& os, const MoveType & move_type) {
        switch (move_type){
            case MoveType::NONE : return os << "NONE" ;
            case MoveType::NORMAL: return os << "NORMAL";
            case MoveType::TAKE: return os << "TAKE";
            case MoveType::CHECK: return os << "CHECK";
            case MoveType::PROMOTION: return os << "PROMOTION";
            case MoveType::EN_PASSANT: return os << "EN_PASSANT";
        }

        return os << static_cast<std::uint16_t>(move_type);
    }


    std::unordered_map<Dir, Pos> dir_as_pos = {{Dir::DOWN, {1,0}}, {Dir::UP, {-1,0}},
                                                              {Dir::LEFT, {0,-1}},{Dir::RIGHT, {0,1}}};

    Pos get_dirs_as_pos(Dir dir, bool is_white) {
        Pos pos (dir_as_pos[dir]);
        pos.y *= (is_white ? 1 : -1);
        return pos;
    }

    Pos get_dirs_as_pos(Dir dir, Dir dir2, bool is_white) {
        Pos pos ((dir_as_pos[dir] += dir_as_pos[dir2]));
        pos.y *= (is_white ? 1 : -1);
        return pos;
    }
}

std::size_t std::hash<jezz::Pos>::operator()(const jezz::Pos &p) const {
    return std::hash<int>()(p.y) ^ std::hash<int>()(p.x);
}

std::size_t std::hash<jezz::Dir>::operator()(const jezz::Dir &d) const {
    return std::hash<int>()(jezz::as_integer(d));
}

