#include <iostream>
#include <cmath>

using namespace std;

//Note to grader - program won't run unless it's names main.cpp (so didn't name it triangle.cpp)
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

class Triangle{
    friend istream & operator>>(istream &input, Triangle &T ){
           input >> T.p1 >> T.p2 >> T.p3;
           return input;
       }

       friend ostream & operator<<(ostream &output, Triangle &T ){
           output << "Point 1: " << T.p1 << endl
                  << "Point 2: " << T.p2 << endl
                  << "Point 3: " << T.p3 << endl
                  << "Triangle? (No = 0; Yes = 1) " << T.triTest() << endl
                  << "Area: " << T.area() << endl
                  << "Perimeter: " << T.perimeter() << endl
                  << "Is it equilateral? (No = 0; Yes = 1) " << T.equil() << endl;
           return output;
       }
public:
    Triangle(){
        Point p1(0, 0);
        Point p2(0, 0);
        Point p3(0, 0);
    }
    Triangle(const Point &u_p1, const Point &u_p2, const Point &u_p3): p1(u_p1), p2(u_p2), p3(u_p3){}

    void setTriangle(Point &u_p1, Point &u_p2, Point &u_p3){
        p1 = u_p1;
        p2 = u_p2;
        p3 = u_p3;
    }
    Point getp1(){
        return p1;
    }
    Point getp2(){
        return p2;
    }
    Point getp3(){
        return p3;
    }
    bool operator==(Triangle &rhs) {
        return (rhs.p1 == p1 && rhs.p2 == p2 && rhs.p3 == p3);
    }
    bool triTest(){
        int test;
        test = p1.getX()*(p2.getY()-p3.getY())+ p2.getX()*(p3.getY()-p1.getY()) + p3.getX()*(p1.getY()-p2.getY());
        if(test == 0){
            return false;
        }else{
            return true;
        }
    }

    double area(){
        double area, l1, l2, l3;
        if(triTest() == false){
            return 0.0;
        }else{
            l1 = sqrt(pow((p2.getX() - p1.getX()), 2) + pow((p2.getY() - p1.getY()), 2));
            l2 = sqrt(pow((p3.getX() - p2.getX()), 2) + pow((p3.getY() - p2.getY()), 2));
            l3 = sqrt(pow((p3.getX() - p1.getX()), 2) + pow((p3.getY() - p1.getY()), 2));
            area = sqrt(perimeter()*(perimeter()-l1)*(perimeter()-l2)*(perimeter()-l3));
            return area;
        }
    }

    double perimeter(){
        double l1, l2, l3, P;
        if(triTest() == false){
            return 0.0;
        }else{
            l1 = sqrt(pow((p2.getX() - p1.getX()), 2) + pow((p2.getY() - p1.getY()), 2));
            l2 = sqrt(pow((p3.getX() - p2.getX()), 2) + pow((p3.getY() - p2.getY()), 2));
            l3 = sqrt(pow((p3.getX() - p1.getX()), 2) + pow((p3.getY() - p1.getY()), 2));
            P = l1 + l2 + l3;
            return P;
        }

    }
    bool equil(){
        double l1, l2, l3;
        if(triTest() == false){
            return false;
        }else{
            l1 = sqrt(pow((p2.getX() - p1.getX()), 2) + pow((p2.getY() - p1.getY()), 2));
            l2 = sqrt(pow((p3.getX() - p2.getX()), 2) + pow((p3.getY() - p2.getY()), 2));
            l3 = sqrt(pow((p3.getX() - p1.getX()), 2) + pow((p3.getY() - p1.getY()), 2));
            if(l1 == l2 == l3){
                return true;
            }else{
                return false;
            }
        }

    }
    bool sameTri(Triangle t1, Triangle t2){
        if(t1==t2){
           return true;
        }else{
           return false;
        }
    }
private:
    Point p1, p2, p3;
};

int main()
{
    Triangle t1;
    Triangle t2;

    cout << "T1: " << endl;
    cin >> t1;
    cout << t1;

    cout << "T2: " << endl;
    cin >> t2;
    cout << t2;

    cout << "Are the triangles the same? (No = 0; Yes = 1) " << t2.sameTri(t1, t2);
    return 0;
}
