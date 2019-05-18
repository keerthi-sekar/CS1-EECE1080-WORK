/*
 * =====================================================================================
 *
 *       Filename:  shape1.cpp
 *
 *    Description:  Complete Point (Part A) Code
 *
 *      Version:  1.0
 *      Created:  03/27/2019  11:50 AM
 *      Revision:  none
 *      Compiler:  MINGW
 *
 *      Author:  Keerthi Sekar
 *      Organization: EECE1080C
 *
 * =====================================================================================
 */

#include <iostream>
#include <cmath>
using namespace std;

class Cube{
public:
    //default
    Cube(){
        edge = 0;
    }
    //overriding constructor
    Cube(double const u_edge){
        edge = u_edge;
    }
    //volume
    double Vol(){
        return pow(edge, 3);
    }
    //surface area
    double SA(){
       return 6*pow(edge, 2);
    }
    void display(){
        cout << "Surface Area: " << SA() << endl;
        cout << "Volume: " << Vol() << endl;
    }

private:
    double edge;
};


int main()
{
    Cube c1;
    Cube c2(2);
    Cube c3(8.73);

    cout << "Cube 1" << endl;
    c1.display();
    cout << "Cube 2" << endl;
    c2.display();
    cout << "Cube 3" << endl;
    c3.display();

    return 0;
}
