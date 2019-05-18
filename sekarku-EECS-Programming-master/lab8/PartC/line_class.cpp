/*
 * =====================================================================================
 *
 *       Filename:  line_class.cpp
 *
 *    Description:  Complete Line (Part C) Code
 *
 *      Version:  1.0
 *      Created:  03/27/2019  11:58 AM
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
#include <cmath>

using namespace std;

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
        Point(){
            x = 0;
            y = 0;
        }
        Point(const int &in_x, const int &in_y): x(in_x), y(in_y){}

        void setPoints(int &in_x, int &in_y){
            x = in_x;
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

class Line {
    // implement cout for Line classes objects
    friend ostream & operator<<(ostream &output, const Line &L ){
        output << "Point 1: " << L.P1 << endl << "Point 2: " << L.P2;
        return output;
    }

    // implement cin for Line classes objects
    friend istream & operator>>( istream &input, Line &L ){
        input >> L.P1 >> L.P2;
        return input;
    }

public:
    Line(){
      Point P1(0,0);
      Point P2(0,0);
    }
    Line(Point &u_P1, Point &u_P2){
        P1 = u_P1;
        P2 = u_P2;
    }
    void setData(Point &u_P1, Point &u_P2){
        P1 = u_P1;
        P2 = u_P2;
    }
    Point getP1(){
        return P1;
    }
    Point getP2(){
        return P2;
    }
    //calculates slope
    double slope(){
        double slope;
        if (cmpf ( static_cast<double>(P1.getX())  , static_cast<double>(P2.getX())) ) {
            slope = 0.0;
        } else{
            slope = (P2.getY() - P1.getY())/ (P2.getX() - P1.getX());
        }
        return slope;
    }
    //calculates length of 2 lines
    double distance(){
        return pow(pow((P2.getX() - P1.getX()), 2) + pow((P2.getY() - P1.getY()), 2), 1/2);
    }
    double yint(){
        return P1.getY() - (slope()* P1.getX());
    }

    //Test if vertical or horizontal (combined into 1 function)
    void test(){
        if(P1.getY() == P2.getY()){
            cout << "Line is horizontal" << endl;
        }else if(P1.getX() == P2.getX()){
            cout << "Line is vertical" << endl;
        }else{
            cout << "Line may be diagonal since it's not vertical or horizontal" << endl;
        }
    }
    //displays data
    void display(){
        cout << "Slope: " << slope() << endl;
        cout << "Length: " << distance() << endl;
        cout << "Y-int: " << yint() << endl;
        test();

    }
    //after input of L2 outputs if lines are parallel
    void parallel(Line L1, Line L2){
        if(L1.slope() == L2.slope()){
            cout << "Lines are parallel" << endl;
        }else{
            cout << "Lines aren't parallel" << endl;
        }
    }
    //allows to compare 2 double values
    bool cmpf(double firstFloat, double secondFloat, double epsilonV = 0.000006)
    {
        return (fabs(firstFloat - secondFloat) < epsilonV);
    }
private:
    Point P1, P2;
};


int main(){
    Line L0;
    Line L1;
    Line L2;
    cout << "L0: should have all zeros for values" << endl;
    cout << L0 << endl;
    L0.display();

    cout << "Enter Two Points For Line1: ";
    cin >> L1;
    cout << L1 << endl;


    cout << "L1 Data: "<< endl;
    L1.display();

    cout << "Enter Two Points For Line2: ";
    cin >> L2;
    cout << L2 << endl;

    cout << "L2 Data: "<< endl;
    L2.display();
    L2.parallel(L1, L2);

    return 0;
}
