#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

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

    private:
        Point center, p1;
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
                  << "Triangle? (0 = false; 1 = true) " << T.triTest() << endl
                  << "Area: " << T.area() << endl
                  << "Perimeter: " << T.perimeter() << endl
                  << "Is it equilateral? (0 = false; 1 = true) " << T.equil() << endl;
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

vector<double> breakupstring(string str){
    vector<double> numdata;
    stringstream ss;
    ss << str;

    while(!ss.eof()){
        double temp;
        ss >> temp;
        numdata.push_back(temp);
    }

    return numdata;
}

int main()
{
    ifstream infile;
    ofstream outfile("shapes-info.txt");
    infile.open("shapes.txt");
    vector<double> numbers;
    string instuff;

    while(getline(infile, instuff)){
        numbers = breakupstring(instuff);
        outfile << instuff << endl;
        if(numbers.size()%2 != 0){
            outfile << "Insufficient coordinate input!!" << endl;
            outfile << "-----------------------------" << endl;
        }else{
            if(numbers.size() == 4){
                outfile << "Sufficient coordinate input" << endl;
                Point p1(numbers.at(0), numbers.at(1));
                Point p2(numbers.at(2), numbers.at(3));
                Circle c1(p1, p2);
                if(!c1.circleTest()){
                    outfile << "You can't make a circle with these points." << endl;
                }else{
                    outfile << "This is a Circle" << endl;
                }
                outfile << c1 << endl;

            }else if(numbers.size() == 6){
                outfile << "Sufficient coordinate input" << endl;
                outfile << "This is a Triangle" << endl;
                Point p1(numbers.at(0), numbers.at(1));
                Point p2(numbers.at(2), numbers.at(3));
                Point p3(numbers.at(4), numbers.at(5));
                Triangle t1(p1, p2, p3);
                outfile << t1 << endl;
            }else if(numbers.size() == 8){
                outfile << "Sufficient coordinate input" << endl;
                outfile << "This is a Quadrilateral" << endl;
                Point p1(numbers.at(0), numbers.at(1));
                Point p2(numbers.at(2), numbers.at(3));
                Point p3(numbers.at(4), numbers.at(5));
                Point p4(numbers.at(6), numbers.at(7));
                Quad q1(p1, p2, p3, p4);
                outfile << q1 << endl;
            }
        }
    }

    infile.close();
    outfile.close();

    return 0;
}
