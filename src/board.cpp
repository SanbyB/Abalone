#include <iostream>
#include "../include/board.h"

Board::Board(int bs){
    boardSize = bs;
    // set up hexagonal board
    /**
                (1,1) (1,2) (1,3) (1,4) (1,5) 
                (2,1) (2,2) (2,3) (2,4) (2,5) (2,6) 
            (3,1) (3,2) (3,3) (3,4) (3,5) (3,6) (3,7) 
        (4,1) (4,2) (4,3) (4,4) (4,5) (4,6) (4,7) (4,8) 
    (5,1) (5,2) (5,3) (5,4) (5,5) (5,6) (5,7) (5,8) (5,9) 
        (6,2) (6,3) (6,4) (6,5) (6,6) (6,7) (6,8) (6,9) 
            (7,3) (7,4) (7,5) (7,6) (7,7) (7,8) (7,9) 
                (8,4) (8,5) (8,6) (8,7) (8,8) (8,9) 
                (9,5) (9,6) (9,7) (9,8) (9,9)
    */
    for(int i = 0; i <= boardSize; i++){
        for(int j = 0; j <= boardSize; j++){
            int value = 0;
                if(i == 0 || j == 0 || i == boardSize || j == boardSize || abs(i - j) == int(boardSize / 2)){ value = 5; }
            if(i < (int(boardSize / 2) + 1)){
                if(j >= (int(boardSize / 2) + 1) + i){
                    continue;
                }
                Cell cell = Cell(i, j, value);
                board[i][j] = cell;
            }
            else{
                if(j <= i - (int(boardSize / 2) + 1)){
                    continue;
                }
                Cell cell = Cell(i, j, value);
                board[i][j] = cell;
            }
        }
    }
}

void Board::init(){
    // initialise the board with the pieces
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

int Board::move(int colour, int dir, int row1, int col1, int row2, int col2, int row3, int col3){
    // check colour is a piece
    if(colour != 1 && colour != 2){ return 1; }
    // if not moving the correct piece return 1
    if(board.at(row1).at(col1).value != colour){ return 1; }
    if(row2 != -1 && col2 != -1){
        if(board.at(row2).at(col2).value != colour){ return 1; }
    }
    if(row3 != -1 && col3 != -1){
        if(board.at(row3).at(col3).value != colour){ return 1; }
    }

    // convert direction into row and column movement
    int rowMove = 0;
    int colMove = 0;

    switch(dir){
    case 0:
        rowMove = 0;
        colMove = 1;
        break;
    case 1:
        rowMove = -1;
        colMove = 0;
        break;
    case 2:
        rowMove = -1;
        colMove = -1;
        break;
    case 3:
        rowMove = 0;
        colMove = -1;
        break;
    case 4:
        rowMove = 1;
        colMove = 0;
        break;
    case 5:
        rowMove = 1;
        colMove = 1;
        break;
    
    default:
        break;
    }

    // if just single piece move
    if(row2 == -1 || col2 == -1){
        // check the space to move to is free
        if(board.at(row1 + rowMove).at(col1 + colMove).value == 0){
            board.at(row1 + rowMove).at(col1 + colMove).value = colour;
            board.at(row1).at(col1).value = 0;
            return 0;
        }
        return 1;
    }
    // if 2 piece move
    if(row3 == -1 || col3 == -1){
        // check pieces are in a line
        int direction = 0;
        if(row1 - row2 == 0 && abs(col1 - col2) == 1){
            direction = 0;
        }
        else if(abs(row1 - row2) == 1 && col1 - col2 == 0){
            direction = 1;
        }
        else if(abs(row1 - row2) == 1 && row1 - row2 == col1 - col2){
            direction = 2;
        }
        // pieces aren't connected
        else{
            return 1;
        }
        // if direction of pieces aligns with direction of movement
        if(dir % 3 == direction){
            // piece 2 is the front piece
            if(row1 + rowMove == row2 && col1 + colMove == col2){
                return push(colour, rowMove, colMove, row2, col2, 2);
            }
            // piece 1 is the front piece
            else{
                return push(colour, rowMove, colMove, row1, col1, 2);
            }
        }
        // direction of pieces doesn't align with direction of movement
        else{
            // check space is free to move
            if(board.at(row1 + rowMove).at(col1 + colMove).value == 0
                && board.at(row2 + rowMove).at(col2 + colMove).value == 0){
                board.at(row1 + rowMove).at(col1 + colMove).value = colour;
                board.at(row1).at(col1).value = 0;
                board.at(row2 + rowMove).at(col2 + colMove).value = colour;
                board.at(row2).at(col2).value = 0;
                return 0;
            }
            return 1;
        }

    }
    // if 3 piece move
    if(row3 != -1 && col3 != -1){
        // check pieces are in a line
        int direction = 0;
        if(row1 - row2 == 0 && row1 - row3 == 0){
            direction = 0;
            if(!(abs(col1 - col2) == 1 || abs(col1 - col2) == 2)){
                return 1;
            }
            if(!(abs(col3 - col2) == 1 || abs(col3 - col2) == 2)){
                return 1;
            }
            if(!(abs(col3 - col1) == 1 || abs(col3 - col1) == 2)){
                return 1;
            }
        }
        else if(col1 - col2 == 0 && col1 - col3 == 0){
            direction = 1;
            if(!(abs(row1 - row2) == 1 || abs(row1 - row2) == 2)){
                return 1;
            }
            if(!(abs(row3 - row2) == 1 || abs(row3 - row2) == 2)){
                return 1;
            }
            if(!(abs(row3 - row1) == 1 || abs(row3 - row1) == 2)){
                return 1;
            }
        }
        else if(row1 - row2 == col1 - col2 && row1 - row3 == col1 - col3){
            direction = 2;
            if(!(abs(row1 - row2) == 1 || abs(row1 - row2) == 2)){
                return 1;
            }
            if(!(abs(row3 - row2) == 1 || abs(row3 - row2) == 2)){
                return 1;
            }
            if(!(abs(row3 - row1) == 1 || abs(row3 - row1) == 2)){
                return 1;
            }
        }
        // pieces aren't connected
        else{
            return 1;
        }
        // if direction of pieces aligns with direction of movement
        if(dir % 3 == direction){
            if((row3 + rowMove != row1 && row3 + rowMove != row2) || (col3 + colMove != col1 && col3 + colMove != col2)){
                return push(colour, rowMove, colMove, row3, col3, 3);
            }
            if((row2 + rowMove != row1 && row2 + rowMove != row3) || (col2 + colMove != col1 && col2 + colMove != col3)){
                return push(colour, rowMove, colMove, row2, col2, 3);
            }
            if((row1 + rowMove != row3 && row1 + rowMove != row2) || (col1 + colMove != col3 && col1 + colMove != col2)){
                return push(colour, rowMove, colMove, row1, col1, 3);
            }
        }
        // direction of pieces doesn't align with direction of movement
        else{
            // check space is free to move
            if(board.at(row1 + rowMove).at(col1 + colMove).value == 0
                && board.at(row2 + rowMove).at(col2 + colMove).value == 0
                && board.at(row3 + rowMove).at(col3 + colMove).value == 0){
                board.at(row1 + rowMove).at(col1 + colMove).value = colour;
                board.at(row1).at(col1).value = 0;
                board.at(row2 + rowMove).at(col2 + colMove).value = colour;
                board.at(row2).at(col2).value = 0;
                board.at(row3 + rowMove).at(col3 + colMove).value = colour;
                board.at(row3).at(col3).value = 0;
                return 0;
            }
            return 1;
        }

    }



    return 0;
}


int Board::push(int colour, int rowMove, int colMove, int row, int col, int numPieces){
    int antiColour = colour == 1 ? 2 : 1;

    // if nothing in front of the pieces
    if(board.at(row + rowMove).at(col + colMove).value == 0){
        board.at(row - rowMove * (numPieces - 1)).at(col - colMove * (numPieces - 1)).value = 0;
        board.at(row + rowMove).at(col + colMove).value = colour;
        return 0;
    }
    // if opposing piece in front of pieces
    if(board.at(row + rowMove).at(col + colMove).value == antiColour){
        if(numPieces == 2){
            if(board.at(row + rowMove + rowMove).at(col + colMove + colMove).value == 0){
                board.at(row + rowMove + rowMove).at(col + colMove + colMove).value = antiColour;
                board.at(row - rowMove).at(col - colMove).value = 0;
                board.at(row + rowMove).at(col + colMove).value = colour;
                return 0;
            }
            if(board.at(row + rowMove + rowMove).at(col + colMove + colMove).value == 5){
                board.at(row - rowMove).at(col - colMove).value = 0;
                board.at(row + rowMove).at(col + colMove).value = colour;
                return 0;
            }
        }
        else if(numPieces == 3){
            if(board.at(row + rowMove + rowMove).at(col + colMove + colMove).value == 0){
                board.at(row + rowMove + rowMove).at(col + colMove + colMove).value = antiColour;
                board.at(row - rowMove - rowMove).at(col - colMove - colMove).value = 0;
                board.at(row + rowMove).at(col + colMove).value = colour;
                return 0;
            }
            if(board.at(row + rowMove + rowMove).at(col + colMove + colMove).value == 5){
                board.at(row - rowMove - rowMove).at(col - colMove - colMove).value = 0;
                board.at(row + rowMove).at(col + colMove).value = colour;
                return 0;
            }
            if(board.at(row + rowMove + rowMove).at(col + colMove + colMove).value == antiColour){
                if(board.at(row + rowMove * 3).at(col + colMove * 3).value == 0){
                    board.at(row + rowMove * 3).at(col + colMove * 3).value = antiColour;
                    board.at(row - rowMove - rowMove).at(col - colMove - colMove).value = 0;
                    board.at(row + rowMove).at(col + colMove).value = colour;
                    return 0;
                }
                if(board.at(row + rowMove * 3).at(col + colMove * 3).value == 5){
                    board.at(row - rowMove - rowMove).at(col - colMove - colMove).value = 0;
                    board.at(row + rowMove).at(col + colMove).value = colour;
                    return 0;
                }
            }
        }
        
    }
    return 1;
}


void Board::print(){
    int prev_i = -1;
    for(auto row : board){
        for(auto c : row.second){
            Cell cell = c.second;
            if(cell.coordinate_i != prev_i){
                std::cout << "\n";
                for(int i = 0; i < abs(int(boardSize / 2) - cell.coordinate_i); i++){
                    std::cout << " ";
                }
            }
            prev_i = cell.coordinate_i;
            std::cout << cell.value << " ";
        }
    }
    std::cout << "\n\n";
}
        