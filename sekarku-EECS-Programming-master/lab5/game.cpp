#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

//Game instructions for user
void GameInstr(){
    cout << "How to play:" << endl;
    cout << "First you choose a point value to match your rolls. Everytime you play, you will roll 3 times. You have to wage an amount from $1-$100 before you roll." << endl;
    cout << "If you win, you get the waged money added to your account. If you lose, it will be deducted!" << endl;
    cout << "You can exit at any point of the game. Be careful not to lose all of your money!" << endl;
    cout << "With that in mind, let's begin!" << endl;
    cout << endl;
}

int rollDie(){
    int randval;
    randval = (rand()%6) + 1; //random number from 1-6
    return randval;
}

//Plays one game and returns if win or loss after 3 rolls
bool playOneGame(int correctnum){
    bool win = false;
    int roll;

    //Roll 3 times per game
    for(int i = 1; i <= 3; i++){
        roll = rollDie();
        cout << "Roll " << i << ": " << roll << endl;
        if(roll == correctnum){
            i = 4; //to exit loop
            win = true;
        }else{
            win = false;
        }
    }

    return win;

}

//Checks after wage if user can continue
bool accountcheck(int wage, int accountnum){
    bool accountdone = false;

    if((accountnum - wage) < 0){
        cout << "Oh no! You don't have any more money!" << endl;
        accountdone = true;
    }else{
        accountdone = false;
    }

    return accountdone;
}

//outputs win statistics
void win_output(int win, int loss, int money){
    cout << endl;
    cout << "Win!" << endl;
    cout << "Win Count: " << win << endl;
    cout << "Loss Count: " << loss << endl;
    cout << "Current Account: $" << money;
}

//outputs loss statistics
void loss_output(int win, int loss, int money){
    cout << endl;
    cout << "Loss :(" << endl;
    cout << "Win Count: " << win << endl;
    cout << "Loss Count: " << loss << endl;
    cout << "Current Account: $" << money;
}

//Tells user final stats after playing
void final_output(int win, int loss, int money){
    int total;
    total = (win/(win+loss))*100;

    cout << endl;
    cout << "Thanks for playing!" << endl;
    cout << "Your final results: " << endl;
    cout << "Win Count: " << win << " And Loss Count: " << loss << endl;
    cout << "Percentage: " << total << "%" << endl;
    cout << "Final Account Balance: $" << money;
}


int main()
{
    int point;
    int win_count, loss_count, account, wage;
    bool play;
    char sPlayer;


    //initialized statements
    account = 100;
    win_count = 0;
    loss_count = 0;
    sPlayer = 'y';
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number

    GameInstr();

     while(sPlayer != 'n'){
         if((sPlayer = 'y') || (sPlayer = 'Y')){
             cout << "Enter your point value (1-6): ";  //base number to refer to for points
             cin >> point;
             cout << "Before we roll, how much do you want to wage? (0 to exit) " << endl;
             cin >> wage;
             if(wage == 0){
                 final_output(win_count, loss_count, account);
                 break;
             }else if ((wage > 0) && (wage <= 100)){
                 play = playOneGame(point);

                 if(play == true){
                        win_count += 1;
                        account += wage;
                        win_output(win_count, loss_count, account);
                        cout << "Would you like to roll? y/n" << endl;
                        cin >> sPlayer;

                 }else{
                       loss_count += 1;

                       //calls function to check if user has money to wage for next roll
                       if(accountcheck(wage, account)){
                           account = 0; //Since you can not end with negative money
                           final_output(win_count, loss_count, account);
                           break;
                       }else{
                            account -= wage;
                            loss_output(win_count, loss_count, account);
                            cout << "Would you like to roll? y/n" << endl;
                            cin >> sPlayer;
                       }
                 }
             }else{
                 cout << "Amount you want to wage doesn't exist, input from $1-$100" << endl;
             }
          }

    }

    final_output(win_count, loss_count, account);
    cout << endl;
    cout << "exiting now... Goodbye!" << endl;
    return 0;
}
