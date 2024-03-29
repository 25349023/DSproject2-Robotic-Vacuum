#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>

struct Point
{
    short x, y;
    Point(int _x = 0, int _y = 0): x(_x), y(_y) {}

    bool operator ==(const Point &oth){
        return x == oth.x && y == oth.y;
    }
    bool operator !=(const Point &oth){
        return x != oth.x || y != oth.y;
    }
    Point operator -(const Point &oth){
        return Point(x - oth.x, y - oth.y);
    }
};


struct Cell {
    char kind;
    bool cleaned;
    short neighbor;
    int steps, step_wrt_ldc;

    Cell(): kind('1'), cleaned(false), neighbor(0), steps(0), step_wrt_ldc(-1) {}

    bool is_charger() {
        return kind == 'R';
    }

    bool can_walk(){
        return kind != '1';
    }

    bool need_to_clean(){
        return can_walk() && !cleaned;
    }
};


class Robot;

class Board {
    int rows, cols;
    Cell **floor; 

public:
    Board(int r, int c): rows(r), cols(c), floor(nullptr) {
        floor = new Cell* [r];
        for (int i = 0; i < r; i++){
            floor[i] = new Cell[c];
        }
    }

    ~Board(){
        for (int i = 0; i < rows; i++){
            delete[] floor[i];
        }
        delete[] floor;
    }

    Cell* operator [](const int index){
        return floor[index];
    }

    Cell& operator [](const Point& p){
        return floor[p.x][p.y];
    }

    void print_step_map();
    void print_wrt_step_map();
    void print_neighbor_map();

    friend Robot;
};

void Board::print_step_map(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (floor[i][j].kind == '1'){
                std::cout << std::setw(3) << 'x';
            }
            else {
                std::cout << std::setw(3) << floor[i][j].steps;
            }
        } std::cout << std::endl;
    }
}

void Board::print_wrt_step_map(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (floor[i][j].kind == '1'){
                std::cout << std::setw(3) << 'x';
            }
            else {
                std::cout << std::setw(3) << floor[i][j].step_wrt_ldc;
            }
        } std::cout << std::endl;
    }
}

void Board::print_neighbor_map(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (floor[i][j].kind == '1'){
                std::cout << std::setw(3) << 'x';
            }
            else {
                std::cout << std::setw(3) << floor[i][j].neighbor;
            }
        } std::cout << std::endl;
    }
}


#endif