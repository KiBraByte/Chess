#include "./board/Board.h"
#include <thread>
#include <chrono>
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
    jezz::Pos p1{ 7 ,6 }, p2{ 5,5 };
    jezz::Pos p3{ 0,6 }, p4{ 2,5 };

    jezz::Pos from{}, to{};
    while (1) {
        do {
            std::cout << "from: ";
            from = ask_pos();
            std::cout << "to: ";
            to = ask_pos();
            std::cout << "here" << '\n';
        } while (!b.move(jezz::Move{from, to}));
        b.print_board();

        /*b.move(jezz::Move{p1,p2});
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        b.move(jezz::Move{p3,p4});
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        b.move(jezz::Move{p2,p1});
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        b.move(jezz::Move{p4, p3});
        std::this_thread::sleep_for(std::chrono::milliseconds(10));*/
    }
    return 0;
}

