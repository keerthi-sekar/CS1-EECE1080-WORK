#include <iostream>

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
        bool operator==(Point &rhs) {
            return (rhs.x == x && rhs.y == y);
        }

    private:
        int x,y;
};

class Quad{
        friend istream & operator>>(istream &input, Quad &Q ){
               input >> Q.p1 >> Q.p2 >> Q.p3 >> Q.p4;
               return input;
           }

        friend ostream & operator<<(ostream &output, Quad &Q ){
               output << "Point 1: " << Q.p1 << endl
                      << "Point 2: " << Q.p2 << endl
                      << "Point 3: " << Q.p3 << endl
                      << "Point 4: " << Q.p4 << endl
                      << "Is it a Quadrilateral? (No = 0; Yes = 1) " << Q.quadtest() << endl
                      << "Area: " << Q.area() << endl;

               return output;
           }
public:
    Quad(){
        Point p1(0,0);
        Point p2(0,0);
        Point p3(0,0);
        Point p4(0,0);
    }
    Quad(const Point &u_1, const Point &u_2, const Point &u_3, const Point &u_4): p1(u_1), p2(u_2), p3(u_3), p4(u_4){}

    void setData(Point &u_1, Point &u_2, Point &u_3, Point &u_4){
        p1 = u_1;
        p2 = u_2;
        p3 = u_3;
        p4 = u_4;
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
    Point getp4(){
        return p4;
    }
    bool quadtest(){
        double t1, t2, t3, t4;
        t1 = p1.getX()*(p2.getY()-p3.getY()) + p2.getX()*(p3.getY()-p1.getY())+ p3.getX()*(p1.getY()-p2.getY());
        t2 = p2.getX()*(p3.getY()-p4.getY()) + p3.getX()*(p4.getY()-p2.getY()) + p4.getX()*(p2.getY() - p3.getY());
        t3 = p1.getX()*(p3.getY()-p4.getY())+ p3.getX()*(p4.getY()-p1.getY()) + p4.getX()*(p3.getY()-p1.getY());
        t4 = p1.getX()*(p2.getY()-p4.getY())+ p2.getX()*(p4.getY()-p1.getY()) + p4.getX()*(p1.getY()-p2.getY());
        if(cmpf(t1,0) || cmpf(t2,0) || cmpf(t3,0) || cmpf(t4,0)){
            return false;
        }else{
            return true;
        }
    }
    double area(){
        double a1, a;
        a1 = abs((p1.getX()*p2.getY())+(p2.getX()*p3.getY()) + (p3.getX()*p4.getY())+(p4.getX()*p1.getY())-(p2.getX()*p1.getY())-(p3.getX()*p2.getY())-(p4.getX()*p3.getY())-(p1.getX()*p4.getY()));
        a = 0.5*a1;
        return a;
    }
    bool cmpf(double firstFloat, double secondFloat, double epsilonV = 0.000006){
            return (fabs(firstFloat - secondFloat) < epsilonV);
    }
private:
    Point p1, p2, p3, p4;
};

int main()
{
    Quad q1;
    Quad q2;

    cout << "Q1: " << endl;
    cin >> q1;
    cout << q1;

    cout << "Q2: " << endl;
    cin >> q2;
    cout << q2;

    return 0;
}
