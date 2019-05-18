#include <iostream>
#include <cmath>
#include <string>
using namespace std;

const double TOLERANCE = 0.0001;

double f(double x0){
    double f0;
    f0 = (pow(x0,4)) + (2*pow(x0,3)) - (31*pow(x0,2)) - (32*x0) + 60;
    return f0;
}

double fprime(double x0){
    double f1;
    f1 = (4*pow(x0,3)) + (6*pow(x0,2)) - (62*x0) - 32;
    return f1;
}

double newtonRoot(double x1){
    double x0;
    do{
        x0 = x1;
        x1 = x0 - f(x0)/fprime(x0);
    }while(fabs(x1-x0) >= TOLERANCE);

    return x1;

    /*double answer = 0;
    answer = X - (f(X)/fprime(X));
    while(fabs(answer - X) > TOLERANCE){
        X = answer;
        answer = X - (f(X)/fprime(X));
    }
    return answer;
    */
}

int main(){
    double X;
    string a;
    //cout << "Enter initial Guess" << endl;
    cin >> X;
    //cout << newtonRoot(X) << endl;
    cout << "Enter Another Guess: y/n?" << endl;
    do{
        cin >> a;
        cin >> X;
        cout << "Root: " << newtonRoot(X) << endl;
    }while(a == "y");
    //cout << "Root: " << newtonRoot(X);
    return 0;
}
