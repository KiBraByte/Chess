cmake_minimum_required(VERSION 3.20.2)
project(Chess)

set(CMAKE_CXX_STANDARD 17)
add_executable(Chess main.cpp pieces/Piece.cpp utility/utility.h utility/utility.cpp pieces/Pawn.cpp pieces/Pawn.h board/Board.cpp board/Board.h pieces/Rook.cpp pieces/Rook.h pieces/Knight.cpp pieces/Knight.h pieces/Bishop.cpp pieces/Bishop.h pieces/King.cpp pieces/Queen.cpp pieces/Queen.h pieces/Piece.h pieces/King.h Game.cpp)
