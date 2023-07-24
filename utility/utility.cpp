#include "utility.h"

namespace jezz {
    const Pos Pos::invalidPos = {-1,-1};
    Pos::Pos(int y, int x) noexcept : x(x), y(y) {}

    Pos::Pos(int y, char x) noexcept : y(y), x(x - 'a'){}

    bool Pos::operator==(const Pos &o) const {
       return (o.x == x)  && (o.y == y);
    }

    Pos &Pos::operator+=(const Pos &o) {
        y += o.y; x += o.x;
        return *this;
    }

    Pos operator+(const Pos & first, const Pos & second) {
       return {(first.y + second.y), (first.x + second.x)};
    }

    std::ostream &operator<<(std::ostream &os, const Pos &pos) {
        return (os << "y: " << pos.y << " x: " << pos.x);
    }

    const Move Move::invalidMove = {Pos::invalidPos,Pos::invalidPos, MoveType::NONE};


    bool Move::operator==(const Move &m) const {
        return (from.y == m.from.y)  &&  (from.x == m.from.x)
        && (to.y == m.to.y) && (to.y == m.to.y);
    }

    Move::Move(Pos from, Pos to) noexcept : Move(from, to, MoveType::NONE) {}

    Move::Move(Pos from, Pos to, MoveType mv) noexcept : from(from), to(to), type(mv){}

    Move::Move(int from_y, int from_x, int to_y, int to_x, MoveType mt) noexcept :
    Move(Pos(from_y, from_x), Pos(to_y, to_x), mt){}

    Move::Move(int from_y, int from_x, int to_y, int to_x) noexcept :
    Move(from_y, from_x, to_y, to_x, MoveType::NONE){}

    std::ostream &operator<<(std::ostream &os, const Move &move) {
        return (os << "FROM: {" << move.from << "} " << "TO: {" << move.to << " }" << ' ' << move.type);
    }

    std::ostream& operator<< (std::ostream& os, const MoveType & move_type) {
        switch (move_type){
            case MoveType::NONE : return os << "NONE" ;
            case MoveType::NORMAL: return os << "NORMAL";
            case MoveType::TAKE: return os << "TAKE";
            case MoveType::PROMOTION: return os << "PROMOTION";
            case MoveType::EN_PASSANT: return os << "EN_PASSANT";
            case MoveType::CASTLE_NORMAL: return os << "CASTLE_NORMAL";
            case MoveType::CASTLE_QUEEN: return os << "CASTLE_QUEEN";
        }

        return os << static_cast<std::uint16_t>(move_type);
    }


    std::unordered_map<Dir, Pos> dir_as_pos = {{Dir::DOWN, {1,0}}, {Dir::UP, {-1,0}},
                                               {Dir::LEFT, {0,-1}},{Dir::RIGHT, {0,1}},
                                               {Dir::NONE, {0,0}}};

    Pos get_dirs_as_pos(bool is_white, Dir dir, Dir dir2,Dir dir3) {
        Pos pos ((dir_as_pos[dir] + dir_as_pos[dir2] + dir_as_pos[dir3]));
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

std::size_t std::hash<jezz::Move>::operator()(const jezz::Move &m) const {
    return std::hash<jezz::Pos>()(m.from) ^ std::hash<jezz::Pos>()(m.to);
}

