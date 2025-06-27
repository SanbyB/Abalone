#include <iostream>
#include <vector>


int sign(double num){
    if(num > 0){
        return 1;
    }
    if(num < 0){
        return -1;
    }
    return 0;
}

class Board{
    public:
        std::vector<std::vector<int>> board = {
                  {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0}
        };

        void init(){
            board = {
                      {1, 1, 0, 2, 2},
                    {1, 1, 1, 2, 2, 2},
                   {0, 1, 1, 0, 2, 2, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 2, 2, 0, 1, 1, 0},
                    {2, 2, 2, 1, 1, 1},
                      {2, 2, 0, 1, 1}
            };
        }

        /**
         * make a move
         * colour is the colour being moved, either 1, or 2
         * x1, y1 are the rows and columns of the board of the first piece to be moved
         * x2, y2 are the rows and columns of the board of the first piece to be moved
         * direction is a value 0-5 that the piece(s) move in 0 being East, and numbers incrementing anticlockwise
         * 
         * return 0 if successful move and 1 if not
         */
        int move(int colour, int x1, int y1, int x2, int y2, int direction){
            // check positions x1, y1 and x2, y2 are on the board
            if(x1 < 0 || x1 > 8 || x2 < 0 || x2 > 8){
                return 1;
            }
            if(y1 < 0 || y2 < 0 || y1 > 8 - abs(4 - x1) || y2 > 8 - abs(4 - x2)){
                return 1;
            }

            // check end colours are correct
            if(board.at(y1).at(x1) != colour || board.at(y2).at(x2) != colour){
                return 1;
            }


            // check positions x1, y1 and x2, y2 lie on a straight line no more than 3 spaces apart
            int numPieces = 0;
            int dir = -1;
            // single piece
            if(x1 == x2 && y1 == y2){
                numPieces = 1;
                dir = 0;
            }
            // on same horizontal line
            else if(y1 == y2 && abs(x1 - x2) < 3){
                numPieces = abs(x1 - x2) + 1;
                dir = 0;
                // check colour of middle
                if(abs(x1 - x2) == 2){
                    if(board.at(y1).at(x2 + sign(x1 - x2)) != colour){
                        return 1;
                    }
                }
            }
            // 2 pieces
            else if(abs(y1 - y2) == 1){
                if(x1 == x2){
                    numPieces = 2;
                    if(std::max(y1, y2) < 5){
                        dir = 1;
                    }
                    else{
                        dir = 2;
                    }
                }
                else if(std::max(y1, y2) < 5 && sign(y1 - y2) * (x1 - x2) == 1){
                    numPieces = 2;
                    dir = 2;
                }
                else if(std::max(y1, y2) >= 5 && sign(y1 - y2) * (x1 - x2) == -1){
                    numPieces = 2;
                    dir = 1;
                }
            }
            // 3 pieces
            else if(abs(y1 - y2) == 2){
                if(x1 == x2){
                    numPieces = 2;
                    if(std::max(y1, y2) < 5){
                        dir = 1;
                    }
                    else{
                        dir = 2;
                    }
                }
                else if(std::max(y1, y2) < 5 && sign(y1 - y2) * (x1 - x2) == 1){
                    numPieces = 2;
                    dir = 2;
                }
                else if(std::max(y1, y2) >= 5 && sign(y1 - y2) * (x1 - x2) == -1){
                    numPieces = 2;
                    dir = 1;
                }
            }
            

            
            return 0;
        }

        void print(){
            for(int i = 0; i < board.size(); i++){
                int spaces = abs(4 - i);
                for(int space = 0; space < spaces; space++){
                    std::cout << " ";
                }
                for(int j : board.at(i)){
                    std::cout << j << " ";
                }
                std::cout << "\n";
            }
        }

};

int main(){
    
    Board board = Board();
    board.init();
    board.print();

    return 0;
}