#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323846; //M_PI isn't compatible with cmath

double currentamp(double w, double L, double C, double R, double E0){
    //Solve for A in most equations
    double amp;
    amp = (w*E0)/sqrt(pow((L*w*w)-(1/C),2) + (R*R)*(w*w));
    return amp;
}

double phase(double L, double w, double R, double C){
    //returns phase angle for all equations
    double pAngle;
    pAngle = atan(((L*w)/R) - (1/(R*C*w)));
    return pAngle;
}

double totalCurrent(double w, double L, double C, double R, double t, double E0){
    double I;
    I = currentamp(w,L,C,R,E0)*(sin((w*t)-phase(L,w,R,C)));
    return I;
}

double totalVR(double w, double L, double C, double R, double E0, double t){
    double Vr;
    Vr = R*currentamp(w,L,C,R,E0)*sin((w*t)-phase(L,w,R,C));
    return Vr;
}

double totalVL(double w, double L, double C, double R, double E0, double t){
    double Vl;
    Vl = L*w*currentamp(w,L,C,R,E0)*cos((w*t) -phase(L,w,R,C));
    return Vl;
}

double totalVC(double w, double L, double C, double R, double E0, double t){
    double Vc;
    Vc = -1*(currentamp(w,L,C,R,E0)/(C*w))*cos((w*t) - phase(L,w,R,C));
    return Vc;
}

double appliedV(double w, double E0, double t){
    double V;
    V = E0*sin(w*t);
    return V;
}

double vDiff(double w, double L, double C, double R, double E0, double t){
   double vDiff;
    vDiff = appliedV(w, E0, t) - (totalVR(w,L,C,R,E0,t) + totalVL(w,L,C,R,E0,t) + totalVC(w,L,C,R,E0,t));
    return vDiff;
}
int main(){
    double w, f, E0, R, L, C, T, AV;
    int nstep;
    int j = 0;

    //input statements for user
    cout << "f: " << endl;
    cin >> f;
    cout << "E0: " << endl;
    cin >> E0;
    cout << "R: " << endl;
    cin >> R;
    cout << "L: " << endl;
    cin >> L;
    cout << "C: " << endl;
    cin >> C;
    cout << "nstep: " << endl;
    cin >> nstep;

    w = 2*PI*f;
    T = 2*(1/f);

    //Output format
    cout << "Calculated A = " << currentamp(w,L,C,R,E0) << endl;
    cout << "Calculated Phase Angle = " << (180/PI)*phase(L,w,R,C) << endl;

    cout
            << setw(10) << "Iter"
            << setw(10) << "Time"
            << setw(10) << "AV"
            << setw(10) << "I"
            << setw(10) << "VR"
            << setw(10) << "VL"
            << setw(10) << "VC"
            << setw(10) << "VT"
            << setw(10) << "Vdiff"
            << endl;

    // loops follows Figure 3 example on google doc
    for(double i = 0; i < T; i+= 0.001){

        cout << setw(10) << j << " ";
        cout << setw(10) << i << " ";
        cout << setw(10) << fixed << setprecision(5) << appliedV(w, E0, i);
        cout << setw(10) << fixed << setprecision(8) << totalCurrent(w,L,C,R,E0,i);
        cout << setw(10) << fixed << setprecision(5) << totalVR(w,L,C,R,E0,i);
        cout << setw(10) << fixed << setprecision(5) << totalVL(w,L,C,R,E0,i);
        cout << setw(10) << fixed << setprecision(5) << totalVC(w,L,C,R,E0,i);
        cout << setw(10) << fixed << setprecision(5) << appliedV(w, E0, i);
        cout << setw(10) << fixed << setprecision(5) << vDiff(w, L, C, R, E0, i) << endl;

        j += 1;

    }

}


