#include "./board/Board.h"
#include <sstream>
#include <string>
#include <thread>

//TODO:: cannot castle when in check, checkmate error ?
jezz::Pos ask_pos() {
    int y, x;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (ss >> y && ss >> x && ss.eof()) break;
    }
    return {y,x};
}

int main() {
    jezz::Board b{};
    b.print_board();

    jezz::Pos from{}, to{};
    while (!b.isCheckMate() && !b.isStaleMate()) {
        std::cout << "White pieces taken: ";
         for (auto & p : b.getWhitePiecesTaken())
             std::cout << *p << ' ';
         std::cout << '\n';
         std::cout << "Black pieces taken: ";
         for (auto & p : b.getBlackPiecesTaken())
             std::cout << *p << ' ';
         std::cout << '\n';

         do {
             std::cout << "from: ";
             from = ask_pos();
             std::cout << "to: ";
             to = ask_pos();
         } while (!b.move(jezz::Move{from, to}));
         b.print_board();
    }
}

