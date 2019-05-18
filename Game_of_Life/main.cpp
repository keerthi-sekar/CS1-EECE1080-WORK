/*
 * EECE1080C Spring, 2019 Project 2 Final Submission:
 * -> Conway's Game of Life
 *
 * Filename:  main.cpp
 * Description:
 * This program is the basic concept of Conway's Game of Life. The alterations we made to the game are: allowing the user to select the amount
 * of generations printed, the file content that the program reads, and the parameters of determining which cell is dead or alive.
 * ------------------------------------------------------------------------------
 * |PLEASE USE OUR SAMPLE INPUT (settings.txt) OR USE SAME FORMAT. ~ Thank you. |
 * |                                                                            |
 * | settings.txt format:                                                       |
 * |  - Each row is a coordinate (x,y) for an alive of the cell                 |
 * ------------------------------------------------------------------------------
 *  Version:   1.0
 *  Finished:  04/25/2019 7:47:00PM
 *  Revision:  none
 *  Compiler:  MinGW
 *
 *  Developers:
 *      - Keerthi Sekar - sekarku@mail.uc.edu
 *      - Sarah George - georges6@mail.uc.edu
 *
 * Developer comments:
 * Developer 1 (Keerthi Sekar):
 * Tasks:
 * Main Menu set up (Menu and case structure), modes (determineisAlive1 and 2), Grid Class skeleton, and allowing user to quit whenever
 * they feel like.
 *
 * Learned from experience:
 * How to combine another person's code and ideas into mine. It was interesting to tackle the challenges of combining both of our ideas.
 * I also got a better understanding/practice of when to use classes to solve certain problems.
 *
 * Developer 2 (Sarah George):
 * Tasks:
 * Coord class, member functions determineisAlive, copy, Update, getLive, breakupstring, and updating board in main.
 * Learned from experience:
 *  How to effectively collaborate with another individual on a task and combine ideas. I have gained a better understanding of how to
 * implement object-oriented programming using classes. It was interesting to tackle the challenge of using File I/O, combining both developer's
 * ideas, and adding our own creativity to the game.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <vector>
#include <unistd.h>

using namespace std;

const int W =10, H = 10;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/* Class Name: Coord
 *
 * Description:
 * This sets the x and y variable from the file into the board
 */
class Coord{
public:
    Coord(){
        x = 0;
        y = 0;
    }

    Coord(int in_x, int in_y){
        x = in_x;
        y = in_y;
    }

    void setX(int in_x){
        x = in_x;
    }

    void setY(int in_y){
        y = in_y;
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }



private:
    int x,y;
};


/* Class Name: Grid
 *
 * Description:
 * Updates the population/board
 */
class Grid{
    public:
    Grid(){
        board[W][H] = false; //initialize everything to be dead
    }

    /* Member Function Name: getLive
     *
     * Description:
     * Reads file and sets the intial alive cells onto the board.
     *
     * Parameters:
     * none
     *
     * return value:
     * none - void function
     */
    void getLive(){

        infile.open("settings.txt");

        while(getline(infile,line)){
            stringstream ss(line);

            string xx,yy;

            getline(ss,xx, ' ');
            getline(ss,yy, ' ');

            x = stoi(xx);
            y = stoi(yy);

            Coord C1(x,y);
            board[C1.getX()][C1.getY()] = true;
        }
    }
    /* Member Function Name: Copy
     *
     * Description:
     * Copies previous generation into board 2
     *
     * Parameters:
     * bool board[W+1][H+1] and bool boardTwo[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void Copy(bool board[W+1][H+1], bool boardTwo[W+1][H+1]){  //copies board

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                boardTwo[i][j] = board[i][j];
            }
        }
    }
    /* Member Function Name: determineIsAlive
     *
     * Description:
     * Setting 1 - determines which cells are alive and marks rest as dead
     *
     * Parameters:
     * bool board[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void determineIsAlive(bool board[W+1][H+1]){  //calculates number of neighboring cells and determines if cell is alive
        bool boardTwo[W+1][H+1] = {};
        Copy(board,boardTwo);

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                int neighbors = 0;

                //neighbors = board[i - 1][j - 1] + board[i - 1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1];
                for(int m = -1; m < 2; m++){
                    for(int n = -1; n < 2; n++){
                        if(!(m ==0 && n == 0)){
                            if(boardTwo[i+m][j+n]){
                                neighbors++;
                            }
                        }
                    }
                }

                if(neighbors < 2 || neighbors > 3){
                    board[i][j] = false; //cell dies
                }
                else if(neighbors == 3){
                    board[i][j] = true;  //birth of new cell
                }
            }
        }
    }
    /* Member Function Name: determineIsAlive1
     *
     * Description:
     * Setting 2 - determines which cells are alive and marks rest as dead
     *
     * Parameters:
     * bool board[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void determineIsAlive1(bool board[W+1][H+1]){  //calculates number of neighboring cells and determines if cell is alive
        bool boardTwo[W+1][H+1] = {};
        Copy(board,boardTwo);

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                int neighbors = 0;

                //neighbors = board[i - 1][j - 1] + board[i - 1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1];
                for(int m = -1; m < 2; m++){
                    for(int n = -1; n < 2; n++){
                        if(!(m ==0 && n == 0)){
                            if(boardTwo[i+m][j+n]){
                                neighbors++;
                            }
                        }
                    }
                }

                if(neighbors < 3 || neighbors > 4){
                    board[i][j] = false; //cell dies
                }
                else if(neighbors == 2){
                    board[i][j] = true;  //birth of new cell
                }
            }
        }
    }
    /* Member Function Name: determineIsAlive2
     *
     * Description:
     * Setting 3 - determines which cells are alive and marks rest as dead
     *
     * Parameters:
     * bool board[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void determineIsAlive2(bool board[W+1][H+1]){  //calculates number of neighboring cells and determines if cell is alive
        bool boardTwo[W+1][H+1] = {};
        Copy(board,boardTwo);

        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                int neighbors = 0;

                //neighbors = board[i - 1][j - 1] + board[i - 1][j] + board[i - 1][j + 1] + board[i][j - 1] + board[i][j + 1] + board[i + 1][j - 1] + board[i + 1][j] + board[i + 1][j + 1];
                for(int m = -1; m < 2; m++){
                    for(int n = -1; n < 2; n++){
                        if(!(m ==0 && n == 0)){
                            if(boardTwo[i+m][j+n]){
                                neighbors++;
                            }
                        }
                    }
                }

                if(neighbors < 4 || neighbors > 5){
                    board[i][j] = false; //cell dies
                }
                else if(neighbors == 4){
                    board[i][j] = true;  //birth of new cell
                }
            }
        }
    }
    /* Member Function Name: Update
     *
     * Description:
     * Updates bool board to current status of each cell
     *
     * Parameters:
     * bool board[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void Update(bool board[W+1][H+1]){
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                cout << board[i][j];

            }
            cout << endl;
        }
    }
    /* Member Function Name: PrintBoard
     *
     * Description:
     * Translates bool to char board and prints out current population
     *
     * Parameters:
     * bool board[W+1][H+1]
     *
     * return value:
     * none - void function
     */
    void PrintBoard(bool board[W+1][H+1]){
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){

                if(board[i][j] == true){

                    cout << "O";
                }
                else{
                    cout << "*";
                }
                if(j == H-1){ //bounds
                    cout << endl;
                }
            }
        }
    }

    private:
        bool board[W][H];
        int x,y;
        ifstream infile;
        string line;
};

/* Function Name: displayInit
 *
 * Description:
 * Displays instructions
 *
 * Parameters:
 * none
 *
 * return value:
 * none - void function
 */
void displayInit(){
    cout << "                                 CONWAY'S GAME OF LIFE" << endl;
    cout << "Rules: " << endl;
    cout << "At each step in time, the following transitions occur:\n"
            "\n"
            "Any live cell with fewer than neighbor setting selected dies, as if by underpopulation.\n"
            "Any live cell with range of the neighbor setting selected lives on to the next generation.\n"
            "Any live cell with more than the neighbor setting selected dies, as if by overpopulation.\n"
            "Any dead cell with exactly the neighbor parameter selected becomes a live cell, as if by reproduction." << endl;
    cout << endl;
    cout << "Living cells are represented by O" << endl;
    cout << "Dead cells are represented by * " << endl;
    cout << endl;
}

/* Function Name: Menu
 *
 * Description:
 * Main menu for user to naviagate
 *
 * Parameters:
 * none
 *
 * return value:
 * none - void function
 */

int Menu(){
    unsigned int choice;
    system("CLS");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "Welcome to Conways Game of Life\n" << endl;
    cout << "Type a number to begin: " << endl;
    cout << "(1) START GAME " << endl;
    cout << "(2) INSTRUCTIONS " << endl;
    cout << "(0) EXIT" << endl;
    cout << "Your choice: ";
    cin >> choice;
    return choice;
}

/* Function Name: mode
 *
 * Description:
 * Displays instructions for user to select a setting
 *
 * Parameters:
 * none
 *
 * return value:
 * none - void function
 */
char mode(){
    char setting;
    system("CLS");
    SetConsoleTextAttribute(hConsole, 10);
    cout << "Select a setting - the rules are slightly different for each one\n" << endl;
    cout << "Type a letter to begin: " << endl;
    cout << "(a) Setting 1 - normal" << endl;
    cout << "(b) Setting 2 - neighbors = 2 is alive " << endl;
    cout << "(c) Setting 3 - neighbors = 4 is alive" << endl;
    cout << "Your choice: ";
    cin >> setting;
    return setting;
}

/* Function Name: breakupstring
 *
 * Description:
 * converts file content to vector double to manipulate in board
 *
 * Parameters:
 * string str
 *
 * return value:
 * vector<double>
 */

vector<double> breakupstring(string str){ //breaks up coordinates in line in text file
    vector<double> numdata;
    stringstream ss;
    ss << str;

    while(!ss.eof()){
        double temp;
        ss >> temp;
        numdata.push_back(temp);
    }

    return numdata;
}

int main(){
    char proceed;
    char getChoice;
    bool board[W+1][H+1];
    int option;
    int x,y;
    unsigned int gens;
    Grid G;

    vector<double> coords;

    string line;
    ifstream infile;

    option = Menu();
    getChoice = mode();
    switch(option){
        case 1:
            //Start of the Game
            system("CLS");

            cout << "How many generations do you want to create: " << endl;
            cin >> gens;
            switch(getChoice){
                case 'a':
                    //Setting 1: Normal
                    G.getLive();
                    G.determineIsAlive(board);
                    G.PrintBoard(board);
                    proceed = 'y';
                break;
                case 'b':
                    //Setting 2
                    G.getLive();
                    G.determineIsAlive1(board);
                    G.PrintBoard(board);
                    proceed = 'y';
                break;
                case 'c':
                    //Setting 3
                    G.getLive();
                    G.determineIsAlive2(board);
                    G.PrintBoard(board);
                    proceed = 'y';
                break;
                default:
                    //Re-enter choice as user put invalid choice
                    cout << "Please re-enter a choice." << endl;
                    cin >> getChoice;
            }

        break;
        case 2:
            //Instructions and then segways into the game
            system("CLS");
            SetConsoleTextAttribute(hConsole, 15);
            displayInit();

            cout << "How many generations do you want to create: " << endl;
            cin >> gens;

            cout << endl;
            proceed = 'y';
        break;
        case 0:
            //Exits program
            exit(0);
        default:
            //asks user again since an invalid choice was selected
            cout << "Please re-enter a choice." << endl;
            cin >> option;
    }

    while(proceed == 'y' && gens > 0){
        cout << "Type y to continue (n to exit): " << endl;
        cin >> proceed;
        //prints updated generations
        SetConsoleTextAttribute(hConsole, 11);
        system("CLS");
        G.PrintBoard(board);
        G.determineIsAlive(board);
        usleep(1000005);
        gens--;
        system("CLS");

    }

    cout << "Game over!" << endl;

    return 0;
}
