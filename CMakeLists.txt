cmake_minimum_required(VERSION 3.24)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp pieces/Piece.cpp pieces/Piece.h utility/utility.h utility/utility.cpp pieces/Pawn.cpp pieces/Pawn.h board/Board.cpp board/Board.h)
