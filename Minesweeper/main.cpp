/*
 * EECE1080C Spring, 2019 Project 1 Final Submission:
 * -> Minesweeper
 *
 * Filename:  main.cpp
 * Description:
 * This program is the basic concept of minesweeper. In order to win the game, you must reveal all the squares that DO NOT
 * contain a mine, whether you flag them or not is a matter of personal preference. If a mine is revealed, the player loses.
 * To select boxes, type coordinates. There are 3 levels: Beginner (9x9), Intermediate (16x16), and Advanced (24x24).
 * If the user wants a challenge, they can try custom as they can set their own board.
 *
 *  Version:  1.0
 *  Finished:  03/13/2019 01:45 PM
 *  Revision:  none
 *  Compiler:  MinGW
 *
 *  Developers:
 *      - Keerthi Sekar - sekarku@mail.uc.edu
 *      - Siddharth Barve - barvesh@mail.uc.edu
 *
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * | Notes:                                                                                                                                 |
 * | Submitted Final Project Code on 3/13/19 - so did not need Milestone #2.                                                                |
 * | For Warnings - My partner (Siddharth) used Visual Studio and I used QTCreator. When we compiled each other's code together on his      |
 * | laptop we received no warnings but when we compiled it onto my computer, I received 110 warnings from QTCreator.                       |
 * -----------------------------------------------------------------------------------------------------------------------------------------
 * Developer comments:
 * Developer 1 (Keerthi Sekar):
 * Tasks:
 * Display Instructions, Difficulty, set-up back end board, reset board, print board, randomize mines, timer,
 * and added user-friendly aspects to game (like allowing player to quit at any point of the game)
 *
 * Learned from experience:
 * How to combine another person's code and ideas into mine. It was interesting to tackle the challenges of combining both of our ideas.
 * I also got a better understanding/practice of how to implement a 2D vector.
 *
 * Developer 2 (Siddharth Barve):
 * Tasks:
 * Setting Console text colors/features (using windows.h), data structure for coordinates, print board, mine location,
 * space/number display, and timer
 *
 * Learned from experience:
 * The intricacies of formatting using hConsole - adding color and highlighting, as well as, seeing how different compilers give different warnings.
 * (I used Visual Studio, while she used QTCreator.)
 */

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct coordinates {
    int xval;
    int yval;
};

//Prototypes of Functions
void DisplayInstructions();
unsigned int Level();
void PrintBoard(vector<vector<char>> vals);
void PrintBoard(int xval, int yval, vector<vector<char>> vals);
void ResetBoards(vector<vector<char>> &userboardvals, vector<vector<char>>&boardvals);
void GenerateMines(int x, int y, int mines, vector<vector<char>> &boardvals, vector<coordinates> &minelocations);
void GenerateMineCounts(vector<vector<char>> &boardvals, vector<coordinates> minelocations);
void FindBlanks(int x, int y, vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations);
void SelectSpace(int x, int y, int sel, vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations);
bool Selection(vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations);
void EndGame(int x, int y, vector<vector<char>>&userboardvals, vector<vector<char>>boardvals, vector<coordinates> minelocations);
int CountSpacesLeft(vector<vector<char>>userboardvals);
unsigned int MainMenu();


int main() {
    srand(unsigned(time(nullptr)));
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, nullptr);

    unsigned int row = 0;
    unsigned int col = 0;
    int x;
    int y;
    unsigned int mines = 0;
    unsigned int option;
    unsigned int diff;

    vector<vector<char>> userboardvals;
    vector<vector<char>> boardvals;
    vector<coordinates> minelocations;

    do {
        do {
            option = MainMenu();
            if (option == 0) {
                exit(0);
            }
        } while (option != 0 && option != 1 && option != 2);
        if (option == 2) {
            DisplayInstructions();
        }
        else {
            do {
                diff = Level();
            } while (diff != 0 && diff != 1 && diff != 2 && diff != 3 && diff != 4);
            if (diff == 1) {
                row = 9;
                col = 9;
                mines = 10;
            }
            else if (diff == 2) {
                row = 16;
                col = 16;
                mines = 40;
            }
            else if (diff == 3) {
                row = 16;
                col = 30;
                mines = 99;
            }
            else if (diff == 4) {
                do {
                    do {
                        system("CLS");
                        cout << "Enter Number of Rows: ";
                        cin >> row;

                        cout << "\nEnter Number of Columns: ";
                        cin >> col;
                    } while (row > 50 || col > 50 || (row*col) < 16);

                    cout << "\nEnter Number of Mines: ";
                    cin >> mines;

                    cout << "\n \n";
                } while (mines > (row*col / 2));
            }
            else if (diff == 0) {
                exit(0);
            }
            system("CLS");
            userboardvals.resize(row, vector<char>(col));
            boardvals.resize(row, vector<char>(col));
            minelocations.resize(mines);

            ResetBoards(userboardvals, boardvals);
            do {
                system("CLS");

                PrintBoard(userboardvals);

                cout << "\n \nSelect Space in Row Col format (ex. (5,3) => 5 3) \n \n   To exit select (0,0)-> 0 0 \n \n";
                cin >> x;
                cin >> y;
                if (x == 0 && y == 0) {
                    exit(0);
                }
            } while (x<0 || y<0 || unsigned(x)>userboardvals.size() || unsigned(y)>userboardvals.size());
            GenerateMines(x, y, mines, boardvals, minelocations);
            GenerateMineCounts(boardvals, minelocations);

            SelectSpace(x, y, 1, userboardvals, boardvals, minelocations);
            clock_t StartTime = clock();
            bool win = Selection(userboardvals, boardvals, minelocations);
            clock_t EndTime = clock();
            if (win) {
                EndGame(0, 0, userboardvals, boardvals, minelocations);
                SetConsoleTextAttribute(hConsole, 10);
                cout << "\nYOU WON! \n \n";
                cout << "Time: " << (EndTime - StartTime) / static_cast<double>(CLOCKS_PER_SEC) << " seconds";
                SetConsoleTextAttribute(hConsole, 8);
            }
            else {
                SetConsoleTextAttribute(hConsole, 12);
                cout << "\nYOU LOST \n \n ";
                SetConsoleTextAttribute(hConsole, 8);
            }
            cout << "\n";
            system("PAUSE");

        }
    } while (option != 0);
}
/* Function Name: MainMenu
 *
 * Function Description:
 * This function solves the user-friendliness of the game. It allows the user to choose to read instructions if needed or start game.
 *
 * Parameters:
 * none
 *
 * return value:
 * none - void function
 */
unsigned int MainMenu() {
    unsigned int sel;
    system("CLS");
    cout << "MINESWEEPER" << endl;
    cout << "\n \n";
    cout << "(1) START GAME " << endl;
    cout << "(2) INSTRUCTIONS" << endl;
    cout << "(0) EXIT GAME" << endl;
    cin >> sel;
    return sel;

}

/* Function Name: DisplayInstructions
 *
 * Function Description:
 * This function explains the game instructions to user. This also helps with the user-friendly aspect of the code.
 *
 * Parameters:
 * none
 *
 * return value:
 * none - void function
 */

void DisplayInstructions() {
    system("CLS");
    cout << "INSTRUCTIONS: \n \n";
    cout << "- You are presented with a board of squares. Some squares contain mines (bombs), others don't. "
            "If you click on a square containing a bomb, you lose. If you manage to select and reveal all the squares \n  "
            "(without revealing on any bombs) you win." << endl;
    cout << "- Revealing a square which doesn't have a bomb reveals the number of neighbouring squares containing bombs. "
            "Use this information plus some guess work to avoid the bombs." << endl;
    cout << "- To select a square, type in the coordinates of the square in Row Col format (ex. (5,3)-> 5 3). "
            "To mark a square you think is a bomb, select the square and select the 'Mark Space' option. \n \n";
    cout << "- A squares 'neighbours' are the squares adjacent above, below, left, right, and all 4 diagonals."
            "Squares on the sides of the board or in a corner have fewer neighbors. The board does not wrap around the edges." << endl;
    cout << "- If you open a square with 0 neighboring bombs, all its neighbors will automatically open."
            " This can cause a large area to automatically open. \n";
    cout << "- To remove a bomb marker from a square, select the square then select 'Unmark Space'." << endl;
    cout << "- The first square you open is never a bomb. \n";
    cout << "- If you mark a bomb incorrectly, you will have to correct the mistake before you can win. "
            "Incorrect bomb marking doesn't kill you, but it can lead to mistakes which do." << endl;
    cout << "- You don't have to mark all the bombs to win; you just need to open all non-bomb squares. \n \n";
    cout << "- To exit game select (0,0) (type in 0 0). \n \n";
    cout << "LEVEL:  ROWS:  COLUMNS:  MINES:" << endl;
    cout << "Beginner       9        9       10  " << endl;
    cout << "Intermediate  16       16       40   \n";
    cout << "Expert        16       30       99   \n";
    cout << "Custom* \n \n";
    cout << "*Mines cannot make up more than 50% of the squares on the board \n \n \n";
    system("PAUSE");
}

/* Function Name: Level
 *
 * Function Description:
 * This function allows user to select a level. This also helps with the user-friendly aspect of the code.
 *
 * Parameters:
 * none
 *
 * return value:
 * diff - level user chooses
 */

unsigned int Level() {
    unsigned int diff;
    system("CLS");
    cout << "    LEVEL:  ROWS:  COLUMNS:  MINES: \n";
    cout << "(1) Beginner       9        9       10   \n";
    cout << "(2) Intermediate  16       16       40   \n";
    cout << "(3) Expert        16       30       99   \n";
    cout << "(4) Custom* \n";
    cout << "(0) Exit \n \n";
    cout << "*Mines cannot make up more than 50% of the squares on the board \n \n";
    cout << "Please select level: ";
    cin >> diff;
    return diff;
}

/* Function Name: PrintBoard
 *
 * Function Description:
 * This function allows the user to see their moves only. This solves the way to show user just their moves in the game and not reveal the other
 * aspects to the game (the backend).
 *
 * Parameters:
 * vector<vector<char>> vals parameter allows you to pass in a specific board.
 *
 * return value:
 * none - void function
 */

void PrintBoard(vector<vector<char>> vals) {
    int x;
    int y;
    for (unsigned int r = 0; r < (vals.size() + 1) * 2; r++) {
        for (unsigned int c = 0; c < (vals[0].size() + 1) * 2; c++) {
            SetConsoleTextAttribute(hConsole, 8);
            y = (c - 1) / 2 + 1;
            x = (r - 1) / 2 + 1;
            if (r == 0) {
                if (c == 0) {
                    cout << "   ";
                }
                else if ((c - 1) % 2 == 0) {
                    cout << " ";
                }
                else {
                    SetConsoleTextAttribute(hConsole, 15);
                    if (y < 10) {
                        cout << "  " << y;
                    }
                    else {
                        cout << " " << y;
                    }
                    SetConsoleTextAttribute(hConsole, 8);
                }
            }
            else {
                if (c == 0) {
                    if ((r - 1) % 2 == 0) {
                        cout << "   ";
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 15);
                        if (x < 10) {
                            cout << "  " << x;
                        }
                        else {
                            cout << " " << x;
                        }
                        SetConsoleTextAttribute(hConsole, 8);
                    }
                }
                else if ((r - 1) % 2 == 0) {
                    if ((c - 1) % 2 == 0) {
                        cout << "-";
                    }
                    else {
                        cout << "---";
                    }
                }
                else {
                    if ((c - 1) % 2 == 0) {
                        cout << "|";
                    }
                    else {
                        cout << " ";

                        if ((vals[x - 1][y - 1]) == '1')
                            SetConsoleTextAttribute(hConsole, 11);
                        else if ((vals[x - 1][y - 1]) == '2')
                            SetConsoleTextAttribute(hConsole, 9);
                        else if ((vals[x - 1][y - 1]) == '3')
                            SetConsoleTextAttribute(hConsole, 10);
                        else if ((vals[x - 1][y - 1]) == '4')
                            SetConsoleTextAttribute(hConsole, 14);
                        else if ((vals[x - 1][y - 1]) == '5')
                            SetConsoleTextAttribute(hConsole, 6);
                        else if ((vals[x - 1][y - 1]) == '6')
                            SetConsoleTextAttribute(hConsole, 12);
                        else if ((vals[x - 1][y - 1]) == '7')
                            SetConsoleTextAttribute(hConsole, 13);
                        else if ((vals[x - 1][y - 1]) == '8')
                            SetConsoleTextAttribute(hConsole, 5);
                        else if ((vals[x - 1][y - 1]) == 'X')
                            SetConsoleTextAttribute(hConsole, 64);
                        else if ((vals[x - 1][y - 1]) == 'b')
                            SetConsoleTextAttribute(hConsole, 96);


                        cout << (vals[x - 1][y - 1]);
                        SetConsoleTextAttribute(hConsole, 8);
                        cout << " ";
                    }
                }
            }

        }
        cout << '\n';
    }
}

/* Function Name: PrintBoard
 *
 * Function Description:
 * This function allows the user to see their moves only. This solves the way to show user just their moves in the game and not reveal the other
 * aspects to the game (the backend).
 *
 * Parameters:
 * int xval - calling from the data structure on the top
 * int yval - calling from the data structure on the top
 * vector<vector<char>> vals - pass in a specific board (userboardvals or boardvals)
 *
 * return value:
 * none - void function
 */

void PrintBoard(int xval, int yval, vector<vector<char>> vals) {
    int x;
    int y;
    for (unsigned int r = 0; r < (vals.size() + 1) * 2; r++) {
        for (unsigned int c = 0; c < (vals[0].size() + 1) * 2; c++) {
            SetConsoleTextAttribute(hConsole, 8);
            y = (c - 1) / 2 + 1;
            x = (r - 1) / 2 + 1;
            if (r == 0) {
                if (c == 0) {
                    cout << "   ";
                }
                else if ((c - 1) % 2 == 0) {
                    cout << " ";
                }
                else {
                    SetConsoleTextAttribute(hConsole, 15);
                    if (y < 10) {
                        cout << "  " << y;
                    }
                    else {
                        cout << " " << y;
                    }
                    SetConsoleTextAttribute(hConsole, 8);
                }
            }
            else {
                if (c == 0) {
                    if ((r - 1) % 2 == 0) {
                        cout << "   ";
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 15);
                        if (x < 10) {
                            cout << "  " << x;
                        }
                        else {
                            cout << " " << x;
                        }
                        SetConsoleTextAttribute(hConsole, 8);
                    }
                }
                else if ((r - 1) % 2 == 0) {
                    if ((c - 1) % 2 == 0) {
                        cout << "-";
                    }
                    else {
                        cout << "---";
                    }
                }
                else {
                    if ((c - 1) % 2 == 0) {
                        cout << "|";
                    }
                    else {
                        cout << " ";

                        if ((vals[x - 1][y - 1]) == '1')
                            SetConsoleTextAttribute(hConsole, 11);
                        else if ((vals[x - 1][y - 1]) == '2')
                            SetConsoleTextAttribute(hConsole, 9);
                        else if ((vals[x - 1][y - 1]) == '3')
                            SetConsoleTextAttribute(hConsole, 10);
                        else if ((vals[x - 1][y - 1]) == '4')
                            SetConsoleTextAttribute(hConsole, 14);
                        else if ((vals[x - 1][y - 1]) == '5')
                            SetConsoleTextAttribute(hConsole, 6);
                        else if ((vals[x - 1][y - 1]) == '6')
                            SetConsoleTextAttribute(hConsole, 12);
                        else if ((vals[x - 1][y - 1]) == '7')
                            SetConsoleTextAttribute(hConsole, 13);
                        else if ((vals[x - 1][y - 1]) == '8')
                            SetConsoleTextAttribute(hConsole, 5);
                        else if ((vals[x - 1][y - 1]) == 'X')
                            if (xval == 0 && yval == 0) {
                                SetConsoleTextAttribute(hConsole, 44);
                            }
                            else {
                                SetConsoleTextAttribute(hConsole, 64);
                            }
                        else if ((vals[x - 1][y - 1]) == 'b')
                            if (xval == 0 && yval == 0) {
                                vals[x - 1][y - 1] = 'X';
                                SetConsoleTextAttribute(hConsole, 44);
                            }
                            else {
                                SetConsoleTextAttribute(hConsole, 96);
                            }

                        if (x == xval && y == yval) {
                            if (vals[x - 1][y - 1] != 'X') {
                                SetConsoleTextAttribute(hConsole, 112);
                            }
                        }

                        cout << (vals[x - 1][y - 1]);
                        SetConsoleTextAttribute(hConsole, 8);
                        cout << " ";
                    }
                }
            }

        }
        cout << '\n';
    }
    if (xval != 0 && yval != 0) {
        SetConsoleTextAttribute(hConsole, 15);
        cout << "( " << xval << " , " << yval << " ) \n";
    }
    SetConsoleTextAttribute(hConsole, 8);
}

/* Function Name: ResetBoards
 *
 * Function Description:
 * This function solves setting the boards to the settings/properties the user selects
 *
 * Parameters:
 * vector<vector<char>> &userboardvals - passes by reference so the vector can automatically change when function is called
 * vector<vector<char>>&boardvals - same as userboardvals, reset the vector that has all the key items of the game
 * (user doesn't see boardvals)
 *
 * return value:
 * none - void function
 */

void ResetBoards(vector<vector<char>> &userboardvals, vector<vector<char>>&boardvals) {
    for (unsigned int x = 0; x < userboardvals.size(); x++) {
        for (unsigned int y = 0; y < userboardvals[0].size(); y++) {
            userboardvals[x][y] = '*';
            boardvals[x][y] = ' ';
        }
    }
}

/* Function Name: GenerateMines
*
* Function Description:
* This function solves the randomizing of locations for the mines in the board. It takes into consideration the outer edges
* and prevents it from overriding other mines.
*
* Parameters:
* int x - passes x coordinate from vectors
* int y - passes y coordinate from vectors
* int mines - passes the mine count user chose (Based on level)
* vector<vector<char>> &boardvals - updates and passes back-end board
* vector<coordinates> &minelocations - updates and passes vector with minelocation
*
* return value:
* none - void function
*/

void GenerateMines(int x, int y, int mines, vector<vector<char>> &boardvals, vector<coordinates> &minelocations) {
    int xcoor;
    int ycoor;
    int ylbound, yubound, xlbound, xubound;

    bool validspace = 1;

    ylbound = -1;
    yubound = 1;
    xlbound = -1;
    xubound = 1;

    if ((x - 1) == 0) {
        xlbound = 0;
    }
    else {
        xlbound = -1;
    }

    if ((x - 1) == boardvals.size() - 1) {
        xubound = 0;
    }
    else {
        xubound = 1;
    }

    if ((y - 1) == 0) {
        ylbound = 0;
    }
    else {
        ylbound = -1;
    }

    if ((y - 1) == boardvals[0].size() - 1) {
        yubound = 0;
    }
    else {
        yubound = 1;
    }

    vector<coordinates> spaces(9);
    int i = 0;
    for (int ix = xlbound; ix <= xubound; ix++) {
        for (int iy = ylbound; iy <= yubound; iy++) {
            spaces[i].xval = x + ix;
            spaces[i].yval = y + iy;
            i++;
        }
    }

    for (int i = 0; i < mines; i++) {
        do {
            validspace = 1;
            xcoor = rand() % (boardvals.size());
            ycoor = rand() % (boardvals[0].size());

            for (int n = 0; n < 9; n++) {
                if (xcoor == spaces[n].xval - 1 && ycoor == spaces[n].yval - 1) {
                    validspace = 0;
                }
            }

            if (boardvals[xcoor][ycoor] != ' ') {
                validspace = 0;
            }
        } while (validspace == 0);
        boardvals[xcoor][ycoor] = 'X';
        minelocations[i].xval = xcoor;
        minelocations[i].yval = ycoor;
    }
}

/* Function Name: GenerateMineCounts
*
* Function Description:
* This function solves the part of displaying the amount of mines around a user's selected location.
*
* Parameters:
* vector<vector<char>> &boardvals - to update/pass the backend board
* vector<coordinates> minelocations - to ensure the coordinates of the mines
*
* return value:
* none - void function
*/

void GenerateMineCounts(vector<vector<char>> &boardvals, vector<coordinates> minelocations) {
    int lbound, rbound, tbound, bbound;
    lbound = -1;
    rbound = 1;
    tbound = -1;
    bbound = 1;
    for (unsigned int i = 0; i < minelocations.size(); i++) {

        if (minelocations[i].xval == 0) {
            lbound = 0;
        }
        else {
            lbound = -1;
        }

        if (minelocations[i].xval == boardvals.size() - 1) {
            rbound = 0;
        }
        else {
            rbound = 1;
        }

        if (minelocations[i].yval == 0) {
            tbound = 0;
        }
        else {
            tbound = -1;
        }

        if (minelocations[i].yval == boardvals[0].size() - 1) {
            bbound = 0;
        }
        else {
            bbound = 1;
        }

        for (int ix = lbound; ix <= rbound; ix++) {
            for (int iy = tbound; iy <= bbound; iy++) {
                if (boardvals[minelocations[i].xval + ix][minelocations[i].yval + iy] == ' ') {
                    boardvals[minelocations[i].xval + ix][minelocations[i].yval + iy] = '1';
                }
                else if (boardvals[minelocations[i].xval + ix][minelocations[i].yval + iy] != 'X') {
                    boardvals[minelocations[i].xval + ix][minelocations[i].yval + iy] = boardvals[minelocations[i].xval + ix][minelocations[i].yval + iy] + 1;
                }
            }
        }


    }
}

/* Function Name: FindBlanks
 *
 * Function Description:
 * This function solves what to display to user if there is no mines near it
 * and ensures that the logic stays within the bounds of the grid.
 *
 * Parameters:
 * int x - x coordinate based on userboard vector grid
 * int y - y coordinate based on userboard vector grid
 * vector<vector<char>> &userboardvals - user's board
 * vector<vector<char>> boardvals - back-end board
 * vector<coordinates> minelocations - coordinates of the mines placement
 *
 * return value:
 * none - void function
 */

void FindBlanks(int x, int y, vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations) {
    int ylbound, yubound, xlbound, xubound;
    ylbound = -1;
    yubound = 1;
    xlbound = -1;
    xubound = 1;
    if ((x - 1) == 0) {
        xlbound = 0;
    }
    else {
        xlbound = -1;
    }

    if ((x - 1) == boardvals.size() - 1) {
        xubound = 0;
    }
    else {
        xubound = 1;
    }

    if ((y - 1) == 0) {
        ylbound = 0;
    }
    else {
        ylbound = -1;
    }

    if ((y - 1) == boardvals[0].size() - 1) {
        yubound = 0;
    }
    else {
        yubound = 1;
    }

    for (int ix = xlbound; ix <= xubound; ix++) {
        for (int iy = ylbound; iy <= yubound; iy++) {
            if ((ix != 0 || iy != 0) && userboardvals[x + ix - 1][y + iy - 1] != ' ') {
                SelectSpace(x + ix, y + iy, 1, userboardvals, boardvals, minelocations);
            }

        }
    }



}

/* Function Name: SelectSpace
*
* Function Description:
* This function solves what the next steps are after the user decides whether to mark it, reveal it, or choose another space.
*
* Parameters:
* int x - x-coordinate
* int y - y-coordinate
* int sel - passes user's selection
* vector<vector<char>> &userboardvals - passes user's board
* vector<vector<char>> boardvals - passes backend board
* vector<coordinates> minelocations - passes coordinates of mines
*
* return value:
* none - void function
*/

void SelectSpace(int x, int y, int sel, vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations) {
    vector<coordinates> blanks;
    if (sel == 1) {
        userboardvals[x - 1][y - 1] = boardvals[x - 1][y - 1];
        if (boardvals[x - 1][y - 1] == ' ') {
            FindBlanks(x, y, userboardvals, boardvals, minelocations);
        }
        if (boardvals[x - 1][y - 1] == 'X') {
            EndGame(x, y, userboardvals, boardvals, minelocations);
        }
    }
    else if (sel == 2) {
        if (userboardvals[x - 1][y - 1] == 'b') {
            userboardvals[x - 1][y - 1] = '*';
        }
        else {
            userboardvals[x - 1][y - 1] = 'b';
        }
    }
}

/* Function Name: Selection
 *
 * Function Description:
 * This function solves what to display after the user decides whether to mark it, reveal it, or choose another space.
 *
 * Parameters:
 * vector<vector<char>> &userboardvals - update users board
 * vector<vector<char>> boardvals - do the same to the back-end board
 * vector<coordinates> minelocations - pass the locations of the mines
 *
 * return value:
 * choice of marking the space or selecting a different space
 */

bool Selection(vector<vector<char>> &userboardvals, vector<vector<char>> boardvals, vector<coordinates> minelocations) {
    int sel;
    int x;
    int y;
    bool gameend = 0;
    bool win = 0;
    do {
        do {
            do {
                system("CLS");
                PrintBoard(userboardvals);

                cout << "\n \nSelect Space in Row Col format (ex. (5,3) => 5 3) \n \n   To exit select (0,0)-> 0 0 \n \n";
                cin >> x;
                cin >> y;
                if (x == 0 && y == 0) {
                    exit(0);
                }
            } while ((x < 0 || y < 0) || unsigned(x) > userboardvals.size() || unsigned(y) > userboardvals[0].size() || (userboardvals[x - 1][y - 1] != '*' && userboardvals[x - 1][y - 1] != 'b'));
            do {
                system("CLS");
                PrintBoard(x, y, userboardvals);
                cout << "\n \n(1): Reveal Space \n";
                if (userboardvals[x - 1][y - 1] == '*') {
                    cout << "(2): Mark Space \n";
                }
                else {
                    cout << "(2): Unmark Space \n";
                }
                cout << "(0): Select Different Space \n \n";

                cin >> sel;
            } while (sel != 0 && sel != 1 && sel != 2);
        } while (sel == 0);
        system("CLS");
        SelectSpace(x, y, sel, userboardvals, boardvals, minelocations);
        if (unsigned(CountSpacesLeft(userboardvals)) <= minelocations.size()) {
            gameend = 1;
            win = 1;
        }
        if (boardvals[x - 1][y - 1] == 'X' && sel == 1) {
            gameend = 1;
            win = 0;
        }
    } while (!gameend);

    return win;
}

/* Function Name: EndGame
*
* Function Description:
* This function solves checking if user's coordinates match a mine's coordinates
*
* Parameters:
* int x - x coordinate in the board
* int y - y value of the board
* vector<vector<char>> &userboardvals - update the user board
* vector<vector<char>> boardvals - use backend board values
* vector<coordinates> minelocations - use mine coordinates to check with the back-end board
*
* return value:
* none - void function
*/

void EndGame(int x, int y, vector<vector<char>>&userboardvals, vector<vector<char>>boardvals, vector<coordinates> minelocations) {

    for (unsigned int i = 0; i < minelocations.size(); i++) {
        userboardvals[minelocations[i].xval][minelocations[i].yval] = boardvals[minelocations[i].xval][minelocations[i].yval];
    }
    system("CLS");
    PrintBoard(x, y, userboardvals);
}

/* Function Name: CountSpacesLeft
 *
 * Function Description:
 * This function solves the number of spaces left. This is to check if the user filled the board
 *
 * Parameters:
 * vector<vector<char>> userboardvals - user board
 *
 * return value:
 * The number of spaces that haven't been revealed yet
 */

int CountSpacesLeft(vector<vector<char>>userboardvals) {
    int space = 0;
    for (unsigned int x = 0; x < userboardvals.size(); x++) {
        for (unsigned int y = 0; y < userboardvals[0].size(); y++) {
            if (userboardvals[x][y] == '*' || userboardvals[x][y] == 'b') {
                space++;
            }
        }
    }
    return space;
}
