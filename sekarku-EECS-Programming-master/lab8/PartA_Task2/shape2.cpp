/*
 * =====================================================================================
 *
 *       Filename:  shape2.cpp
 *
 *    Description:  Complete Point (Part A) Code
 *
 *      Version:  1.0
 *      Created:  03/27/2019  11:52AM
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

class RectPrism{
public:
    //default
    RectPrism(){
        l = 0;
        h = 0;
        w = 0;
    }
    //overriding constructor
    RectPrism(double const &u_l, double const &u_h, double const &u_w){
        l = u_l;
        h = u_h;
        w = u_w;
    }
    //volume
    double Volume(){
        return l*w*h;
    }
    //surface area
    double SA(){
        return (2*w*l) + (2*l*h) + (2*h*w);
    }
    void display(){
        cout << "Surface Area: " << SA() << endl;
        cout << "Volume: " << Volume() << endl;
    }

private:
    double l;
    double h;
    double w;
};



int main()
{
    RectPrism prism1;
    RectPrism prism2(2.5,4.7,6);
    RectPrism prism3(11,13.5,15);

    cout << "First: " << endl;
    prism1.display();
    cout << "Second: " << endl;
    prism2.display();
    cout << "Third: " << endl;
    prism3.display();

    return 0;
}
