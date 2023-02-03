#include "./board/Board.h"
//TODO: Throw exception if out of bounds, implement en passant, castle, check mate
jezz::Pos ask_pos() {
    int y, x;
    std::cout << "y and x\n";
    std::cin >> y >> x;
    std::cout << '\n';
    return {y,x};
}


int main() {
    jezz::Board b{};
    b.print_board();

    jezz::Pos from{}, to{};
    while (1) {
        do {
            std::cout << "from: ";
            from = ask_pos();
            std::cout << "to: ";
            to = ask_pos();
        } while (!b.move(from, to));
        b.print_board();
    }
    return 0;
}

