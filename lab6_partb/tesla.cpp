#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;

const int ROW_SIZE = 15;
const int COL_SIZE = 15;

//Output rules for the user
void rules(){
    cout << "How to play:" << endl;
    cout <<
            "You walk into Elon's house to find his roadster! Try to navigate through his house without waking him up!"
            "If you wake him up the first time, he move to another location and it will be denoted as the lowercase letter e."
            "If you run into him again, you will automatically lose! Make sure you don't go near him."
            "Hints will be given on the bottom. Warmer = close to the raodster and colder = away from the roadster."
            "If you find his pinto or yugo, then you automatically lose (aka Starman). "
            "You can leave the game at any time. Best of luck!"
            << endl
            << endl;
}

//initialize board
void initBoard(char board[ROW_SIZE][COL_SIZE], char fill_char) {
    for(int r = 0; r < ROW_SIZE; r++) {
         for(int c  = 0; c < COL_SIZE; c++) {
              board[r][c] = fill_char;
         }
    }
}

//display user's position and board
void displayboard(char board[ROW_SIZE][COL_SIZE]){
    for(int r = 0; r < ROW_SIZE; r++) {
         for(int c  = 0; c < COL_SIZE; c++) {
              cout << board[r][c];
         }
         cout << endl;
    }
}

//randomize funcction for all the coordinates
int randomize(){
    int randomval;
    randomval = rand() % 15;

    return randomval;
}

//Loop to check if user still wants to play game
bool playGame(bool play){
    bool begin = true;

    if(play == 'y'){
        begin = true;
    }else{
        begin = false;
    }

    return begin;
}

//Waking up Elon
void wakeElon(int ecol, int erow, int ucol, int urow, char board[ROW_SIZE][COL_SIZE]){
    if(erow == (urow + 4) || erow == (urow - 4) || ecol == (ucol + 4) || ecol == (ucol - 4)){
        cout << "Elon's awake!" << endl;
        board[erow][ecol] = 'E'; // place elon musk
        displayboard(board);
    }
}

//hints about being near the roadster
void hint(int roadcol, int roadrow, int ucol, int urow){
    if(roadrow <= (urow + 4) || roadrow <= (urow - 4) || roadcol <= (ucol + 4) || roadcol <= (ucol - 4)){
        cout << "Warmer" << endl;
    }else{
        cout << "Colder" << endl;
    }
}

//randomize Elon after running into him the first time
bool randElon(int ecol, int erow, int urow, int ucol, int pcol, int prow, int yrow, int ycol, int roadcol, int roadrow, char board[ROW_SIZE][COL_SIZE], bool loser){
    int life = 2;
    do{
        erow = randomize();
        ecol = randomize();
    }while(((ecol == ucol) && (erow == urow))||((ecol == pcol) && (erow == prow)) || ((erow == yrow) && (ecol == ycol)) || ((ecol == roadcol) && (erow == roadrow)));
    board[erow][ecol] = 'e';
    displayboard(board);
    life -= 1;
    if(life == 0){
        loser = true;
    }
    return loser;
}

int main()
{
    char board[ROW_SIZE][COL_SIZE];
    char move, play;
    bool begin, loser, loss;
    int urow, ucol;
    int prow, pcol;
    int yrow, ycol;
    int roadrow, roadcol;
    int erow, ecol;
    int turn;

    //initialize
    initBoard(board, '*');
    srand(static_cast<unsigned int>(time(nullptr)));
    begin = true;
    loser = false;
    loss = false;
    turn = 0;

    //randomize everyone's position
    urow = randomize();
    ucol = randomize();

    //to prevent overlap in coordinate points
    do{
        prow = randomize();
        pcol = randomize();
    }while((pcol == ucol) && (prow == urow));

    do{
        yrow = randomize();
        ycol = randomize();
    }while(((ycol == ucol) && (yrow == urow))||((ycol == pcol) && (yrow == prow)));

    do{
        roadrow = randomize();
        roadcol = randomize();
    }while(((roadcol == ucol) && (roadrow == urow))||((roadcol == pcol) && (roadrow == prow)) || ((roadrow == yrow) && (roadcol == ycol)));

    do{
        erow = randomize();
        ecol = randomize();
    }while(((ecol == ucol) && (erow == urow))||((ecol == pcol) && (erow == prow)) || ((erow == yrow) && (ecol == ycol)) || ((ecol == roadcol) && (erow == roadrow)));

    //board[prow][pcol] = 'P';       // pinto pos
    //board[yrow][ycol] = 'Y';       //yugo pos
    //board[roadrow][roadcol] = 'R'; //roadster pos
    board[urow][ucol] = 'U';         //place user
    //board[erow][ecol] = 'E';       //elon musk pos

    rules(); // Show user the rules of the game
    displayboard(board);           //display's board for user to see


    while(begin == true){
        cout << "Would you like to play? y/n" << endl;
        cin >> play;
        if(play != 'y'){
            break;
        }
        cout << "Which direction do you want to go? w, a, s, d" << endl;
        cin >> move;

        //To move north
         if(move == 'w'){
             if((board[urow-1][ucol] == '*') && (board[urow-1][ucol] != 'E') && (board[urow-1][ucol] != 'P') && (board[urow-1][ucol] != 'Y') && (board[urow-1][ucol] != 'R')){
                 char temp = '*';
                 temp = board[urow-1][ucol];
                 board[urow-1][ucol] = 'U';
                 board[urow][ucol] = temp;
                 urow = urow - 1;
                 turn += 1;
                 displayboard(board);
                 hint(roadcol, roadrow, ucol, urow);
                 wakeElon(ecol, erow, ucol, urow, board);
             }else{
                 if(board[urow-1][ucol] == 'P'){
                     cout << "You chose the Pinto, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow-1][ucol] == 'Y'){
                     cout << "You chose the Yugo, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow-1][ucol] == 'E'){
                     cout << "You woke Elon! Next time he finds you, it's game over." << endl;
                     board[erow][ecol] = 'E';
                     loss = randElon(ecol, erow, urow, ucol, pcol, prow, yrow, ycol, roadcol,roadrow,board, loser);
                     if(loss == true){
                         cout << "Starman - You lose!" << endl;
                         break;
                     }
                 }
                 if(board[urow-1][ucol] == 'R'){
                     cout << "Congrats! You escaped." << endl;
                     cout << "It took you " << turn << " turns." << endl;
                     break;
                 }
             }
          //To move south
          }else if(move == 's'){
             if((board[urow+1][ucol] == '*') && (board[urow+1][ucol] != 'E') && (board[urow+1][ucol] != 'P') && (board[urow+1][ucol] != 'Y') && (board[urow-1][ucol] != 'R')){
                 char temp = '*';
                 temp = board[urow+1][ucol];
                 board[urow+1][ucol] = 'U';
                 board[urow][ucol] = temp;
                 urow = urow + 1;
                 turn += 1;
                 displayboard(board);
                 hint(roadcol, roadrow, ucol, urow);
                 wakeElon(ecol, erow, ucol, urow, board);
             }else{
                 if(board[urow+1][ucol] == 'P'){
                     cout << "You chose the Pinto, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow+1][ucol] == 'Y'){
                     cout << "You chose the Yugo, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow+1][ucol] == 'E'){
                     cout << "You woke Elon! Next time he finds you, it's game over." << endl;
                     board[erow][ecol] = 'E';
                     loss = randElon(ecol, erow, urow, ucol, pcol, prow, yrow, ycol, roadcol,roadrow,board, loser);
                     if(loss == true){
                         cout << "Starman - You lose!" << endl;
                         break;
                     }
                 }
                 if(board[urow+1][ucol] == 'R'){
                     cout << "Congrats! You escaped." << endl;
                     cout << "It took you " << turn << " turns." << endl;
                     break;
                 }
             }
          //to move west
          }else if(move == 'a'){
             if((board[urow][ucol-1] == '*') && (board[urow][ucol-1] != 'E') && (board[urow][ucol-1] != 'P') && (board[urow][ucol-1] != 'Y') && (board[urow-1][ucol] != 'R')){
                 char temp = '*';
                 temp = board[urow][ucol-1];
                 board[urow][ucol-1] = 'U';
                 board[urow][ucol] = temp;
                 ucol = ucol - 1;
                 turn += 1;
                 displayboard(board);
                 hint(roadcol, roadrow, ucol, urow);
                 wakeElon(ecol, erow, ucol, urow, board);
             }else{
                 if(board[urow][ucol-1] == 'P'){
                     cout << "You chose the Pinto, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow][ucol-1] == 'Y'){
                     cout << "You chose the Yugo, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow][ucol-1] == 'E'){
                     cout << "You woke Elon! Next time he finds you, it's game over." << endl;
                     board[erow][ecol] = 'E';
                     loss = randElon(ecol, erow, urow, ucol, pcol, prow, yrow, ycol, roadcol,roadrow,board, loser);
                     if(loss == true){
                         cout << "Starman - You lose!" << endl;
                         break;
                     }
                 }
                 if(board[urow][ucol-1] == 'R'){
                     cout << "Congrats! You escaped." << endl;
                     cout << "It took you " << turn << " turns." << endl;
                     break;
                 }
             }
          //to move east
          }else if(move == 'd'){
             if((board[urow][ucol+1] == '*') && (board[urow][ucol+1] != 'E') && (board[urow][ucol+1] != 'P') && (board[urow][ucol+1] != 'Y') && (board[urow-1][ucol] != 'R')){
                 char temp = '*';
                 temp = board[urow][ucol+1];
                 board[urow][ucol+1] = 'U';
                 board[urow][ucol] = temp;
                 ucol = ucol + 1;
                 turn += 1;
                 displayboard(board);
                 hint(roadcol, roadrow, ucol, urow);
                 wakeElon(ecol, erow, ucol, urow, board);
             }else{
                 if(board[urow][ucol+1] == 'P'){
                     cout << "You chose the Pinto, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow][ucol+1] == 'Y'){
                     cout << "You chose the Yugo, wrong car buddy. Game Over!" << endl;
                     break;
                 }
                 if(board[urow][ucol+1] == 'E'){
                     cout << "You woke Elon! Next time he finds you, it's game over." << endl;
                     board[erow][ecol] = 'E';
                     loss = randElon(ecol, erow, urow, ucol, pcol, prow, yrow, ycol, roadcol,roadrow,board, loser);
                     if(loss == true){
                         cout << "Starman - You lose!" << endl;
                         break;
                     }
                 }
                 if(board[urow][ucol+1] == 'R'){
                     cout << "Congrats! You escaped." << endl;
                     break;
                 }
             }
          }
       }

    cout << "End of Game! Exiting..." << endl;

}

