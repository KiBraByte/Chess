//
// Created by kilian on 1/20/2023.
//
#include "utility.h"


namespace jezz {
    pos::pos(int y, int x) : x(x), y(y) {}

    int pos::get_2dInt() const {
        return y * columns + x;
    }

    pos pos::from_2dint_to_pos(int val) {
        return {(val / columns), (val % columns)};
    }

    pos::pos(int y, char x) : y(y), x(x - 'a'){}
}


