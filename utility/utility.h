//
// Created by kilian on 1/20/2023.
//

#ifndef CHESS_UTILITY_H
#define CHESS_UTILITY_H
namespace jezz {
    constexpr int rows = 8, columns = 8;

    struct pos {
        int x;
        int y;

        pos(int y, int x);
        pos(int y, char x);

        [[nodiscard]] int get_2dInt() const;

        static pos from_2dint_to_pos(int val);
    };
}

#endif //CHESS_UTILITY_H
