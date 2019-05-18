#include <iostream>

using namespace std;

int whichQuadrant(double a, double b){
    int w;
    if (a > 0 && b > 0){
        w = 1;
    } else if(a < 0 && b > 0){
        w = 2;
    } else if(a < 0 && b < 0){
        w = 3;
    }else if(a > 0 && b < 0){
        w = 4;
    }else if ((a == 0.0 && b < 0.0) || (a == 0.0 && b > 0.0)) {
        w = 'Y';
    }else if((b == 0.0 && a < 0.0) || (b == 0.0 && a > 0.0)){
        w = 'X';
    }else if (a == 0.0 && b ==0.0) {
        w = 'C';
    }
    return w;
}

string message(int q) {
    string msg;
    if(q == 'C') msg = "On Center";
    if(q == 'X') msg = "On XAxis";
    if(q == 'Y') msg = "On YAxis";
    if(q ==  1)  msg = "Q1";
    if(q ==  2)  msg = "Q2";
    if(q ==  3)  msg = "Q3";
    if(q ==  4)  msg = "Q4";
    return msg;
}

int main() { // No need to change main()
    double  x = 0;
    double y = 0;

    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be On Center" << endl;

    x = 0;
    y = 4.8;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be YAxis" << endl;

    y = 0;
    x = 4.8;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be XAxis" << endl;

    x = 4.8;
    y = 4.8;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be On Q1" << endl;

    x = -7;
    y = -4.8;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be On Q3" << endl;

    x = 7;
    y = -3;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be On Q4" << endl;

    x = -9;
    y = 8;
    cout << "For XY Pair: " << x << "," << y << " function returns: "
         <<  message(whichQuadrant(x,y))
         << " should be On Q2" << endl;

    return 0;
}
