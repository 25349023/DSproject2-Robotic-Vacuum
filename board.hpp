#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <iomanip>

struct Cell {
    char kind;
    int steps;
    int neighbor;
    bool cleaned;

    Cell(): kind('1'), steps(0), neighbor(0), cleaned(false) {}

    bool isCharger() {
        return kind == 'R';
    }
};


class Robot;

class Board {
    int rows, cols;

public:
    Cell **floor; 

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

    void print_step_map(){
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

    void print_neighbor_map(){
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


    friend Robot;
};

#endif