#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.14159265359;

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
        bool operator==(Point &rhs) {
            return (rhs.x == x && rhs.y == y);
        }

    private:
        int x,y;
};

class Circle{

    // cin implementation for Point class
    friend istream & operator>>(istream &input, Circle &C ){
        input >> C.center >> C.p1;
        return input;
    }

    friend ostream & operator<<(ostream &output, Circle &C ){
        output << "Point 1: " << C.center << endl
               << "Point 2: " << C.p1 << endl
               << "Radius: " << C.radius() << endl
               << "Diameter: " << C.diameter() << endl
               << "Area: " << C.area() << endl
               << "Circumference: " << C.circumference() << endl;
        return output;
    }

    public:
    //default constructor
    Circle(){
        Point center(0,0);
        Point p1(0,0);
    }
    //overriding constructor
    Circle(const Point &u_center, const Point &u_p1): center(u_center), p1(u_p1){}

    void setCircle(Point &u_center, Point &u_p1){
        center = u_center;
        p1 = u_p1;
    }
    Point getcenter(){
        return center;
    }
    Point getp1(){
        return p1;
    }

    bool circleTest(){
        bool ctest;
        if((center.getX() == p1.getX()) &&(center.getY() == p1.getY())){
            ctest = false;
        }else{
            ctest = true;
        }
        return ctest;
    }
    double radius(){
        double cradius, x_sq, y_sq;
        if(circleTest() == false){
            cout << "You can't make a circle" << endl;
            cout << "Everything will now be outputted as 0" << endl;
        }else{
            x_sq = pow((p1.getX()-center.getX()), 2);
            y_sq = pow((p1.getY()-center.getY()), 2);
            cradius = sqrt(pow(x_sq,2)+pow(y_sq,2));
        }
        return cradius;
    }
    double diameter(){
        if(circleTest() == false){
            return 0.0;
        }else{
            return 2.0*radius();
        }
    }
    double area(){
        double carea;
        if(circleTest() == false){
            carea = 0.0;
        }else{
        carea = pow(radius(),2)*PI;
        }
        return carea;
    }
    double circumference(){
        if(circleTest() == false){
            return 0.0;
        }else{
        return diameter()*PI;
        }
    }
    bool cmpf(double firstFloat, double secondFloat, double epsilonV = 0.000006){
            return (fabs(firstFloat - secondFloat) < epsilonV);
    }
    private:
        Point center, p1;
};

int main()
{
    Circle c1;
    Circle c2;

    cout << "Input 2 sets of coordinates for circle 1: ";
    cin >> c1;
    cout << c1;

    cout << "Input 2 sets of coordinates for circle 2: ";
    cin >> c2;
    cout << c2;

    return 0;
}
