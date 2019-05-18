/*
 * =====================================================================================
 *
 *       Filename:  point_class.cpp 
 *
 *    Description:  Complete Point (Part B) Code
 * 
 *      Version:  1.0
 *      Created:  03/27/2019  11:54 AM
 *      Revision:  none
 *      Compiler:  MINGW
 *
 *      Author:  Keerthi Sekar
 *      Organization: EECE1080C  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Please complete this Point class.
// The cin/cout operators have been overloaded for you
class Point {

    // cout implementation for Point class
    friend ostream & operator<<(ostream &output, const Point &P ){
        output << "x: " << P.x << " y: " << P.y;
        return output;
    }

    // cin implementation for Point class
    friend istream & operator>>(istream &input, Point &P ){
        input >> P.x >> P.y;
        return input;
    }

public:
    //default
    Point(){
        x = 0;
        y = 0;
    }
    //overriding constructor
    Point(const int &in_x, const int &in_y): x(in_x), y(in_y){}

    //set function
    void setPoints(const int &in_x, const int &in_y){
        x = in_x;
        y = in_y;
    }
    //get functions
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }

private:
    int x,y;
};

int main(){
    Point P1;
    Point P2(7,6);
    cout << "Point P1 should have 0,0 as values" << endl;
    cout << P1 << endl;
    cout << "Point P2 should have 7,6 as values" << endl;
    cout << P2 << endl;

    cout << "Enter x and y points: ie 3 4 ";
    cin >> P1;
    cout << P1 << endl;

    return 0;
}
