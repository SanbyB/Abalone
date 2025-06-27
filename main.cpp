#include <iostream>
#include <vector>
#include <map>


int sign(double num){
    if(num > 0){
        return 1;
    }
    if(num < 0){
        return -1;
    }
    return 0;
}

class Cell{
    public:
        Cell(){};
        Cell(int ci, int cj, int v){
            coordinate_i = ci;
            coordinate_j = cj;
            value = v;
        }
        int coordinate_i = 0;
        int coordinate_j = 0;
        int value = 0;
};

class Board{
    public:
        Board(){
            int index = 0;
            for(int i = 1; i <= 9; i++){
                for(int j = 1; j <= 9; j++){
                    if(i < 5){
                        if(j >= 5 + i){
                            continue;
                        }
                        Cell cell = Cell(i, j, 0);
                        board[i][j] = cell;
                    }
                    else{
                        if(j <= i - 5){
                            continue;
                        }
                        Cell cell = Cell(i, j, 0);
                        board[i][j] = cell;
                    }
                }
            }
        }

        std::map<int, std::map<int, Cell>> board = {};


        void init(){
            board.at(1).at(1).value = 1;
            board.at(1).at(2).value = 1;
            board.at(2).at(1).value = 1;
            board.at(2).at(2).value = 1;
            board.at(2).at(3).value = 1;
            board.at(3).at(2).value = 1;
            board.at(3).at(3).value = 1;

            board.at(1).at(4).value = 2;
            board.at(1).at(5).value = 2;
            board.at(2).at(4).value = 2;
            board.at(2).at(5).value = 2;
            board.at(2).at(6).value = 2;
            board.at(3).at(5).value = 2;
            board.at(3).at(6).value = 2;

            board.at(7).at(7).value = 1;
            board.at(7).at(8).value = 1;
            board.at(8).at(7).value = 1;
            board.at(8).at(8).value = 1;
            board.at(8).at(9).value = 1;
            board.at(9).at(8).value = 1;
            board.at(9).at(9).value = 1;

            board.at(7).at(4).value = 2;
            board.at(7).at(5).value = 2;
            board.at(8).at(4).value = 2;
            board.at(8).at(5).value = 2;
            board.at(8).at(6).value = 2;
            board.at(9).at(5).value = 2;
            board.at(9).at(6).value = 2;
        }

        int move(int colour, int row1, int col1, int dir, int row2 = -1, int col2 = -1, int row3 = -1, int col3 = -1){
            return 0;
        }


        void print(){
            int prev_i = 0;
            for(auto row : board){
                for(auto c : row.second){
                    Cell cell = c.second;
                    if(cell.coordinate_i != prev_i){
                        std::cout << "\n";
                        for(int i = 0; i < abs(5 - cell.coordinate_i); i++){
                            std::cout << " ";
                        }
                    }
                    prev_i = cell.coordinate_i;
                    std::cout << cell.value << " ";
                }
            }
            std::cout << "\n\n";
        }
        
};

int main(){
    
    Board board = Board();
    board.init();
    board.print();

    return 0;
}