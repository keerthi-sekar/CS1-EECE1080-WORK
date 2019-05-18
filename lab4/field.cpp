#include <iostream>
#include <cmath>

using namespace std;

const double Q = 0.000000001;
const double KE = 9000000000;

double Efield(double r, double a = 1);

double Efield(double radius, double a_value){
    double Er;

    if(radius < a_value){
        Er = (KE*Q*radius)/pow(a_value, 3);
        cout << "Efield: " << Er << endl;
    } else if(radius >= a_value){
        Er = (KE*Q)/pow(radius, 2);
        cout << "Efield: " << Er << endl;
    }

    return Er;
}

int main(){
    double r, a;

    cin >> r;
    cin >> a;

    cout << "Efield: " << Efield(r,a);
}
