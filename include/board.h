#include <vector>
#include <map>

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
        Board(int bs = 10);

        std::map<int, std::map<int, Cell>> board = {};
        int boardSize;


        void init();

        /**
         * checks if move is valid, if it is then
         * the move will be completed and the func will return 0
         * else the move will not be complete and will return 1
         * 
         * colour is the number of the player whose turn it is
         * row1, col2 is the row and column of the first piece selected to move
         * row2, col2, row3, col3 are respectfully the rows and columns 
         * of the 2nd and 3rd pieces to move
         * dir is the direction 0-5 the pieces are to move in
         * 0 being to the right, then increasing numbers go anti clockwise
         * 
         */ 
        
        int move(int colour, int dir, int row1, int col1, int row2 = -1, int col2 = -1, int row3 = -1, int col3 = -1);

        void print();

    private:
        
        int push(int colour, int rowMove, int colMove, int row, int col, int numPieces);

};