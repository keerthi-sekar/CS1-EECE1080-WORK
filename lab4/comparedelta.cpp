#include <iostream>
#include <cmath>

using namespace std;

bool compareDelta(double num1, double num2, double delta){
    double difference;
    bool test = false;
    difference = fabs(num1 - num2);
    if(difference <= delta){
        test = true;
    }
    return test;
}

int main() {

    double Number1 = 1.205;
    double Number2 = 1.305;
    double Delta = 0.100;

    cout << "CompareDelta() Number1: " << Number1 << " Number2: " << Number2 << " Delta " << Delta << " returned: "
         << compareDelta(Number1, Number2, Delta) << " should be 1 " << endl;
    Number1 = 1;
    Number2 = 2;
    cout << "CompareDelta() Number1: " << Number1 << " Number2: " << Number2 << " Delta " << Delta << " returned: "
         << compareDelta(Number1, Number2, Delta) << " should be 0 " << endl;
    Number1 = 2;
    Number2 = 4;
    Delta = 2.5;
    cout << "CompareDelta() Number1: " << Number1 << " Number2: " << Number2 << " Delta " << Delta << " returned: "
         << compareDelta(Number1, Number2, Delta) << " should be 1 " << endl;
    Number1 = 1.3058;
    Number2 = 1.3059;
    Delta   = 0.00001;
    cout << "CompareDelta() Number1: " << Number1 << " Number2: " << Number2 << " Delta " << Delta << " returned: "
         << compareDelta(Number1, Number2, Delta) << " should be 0 " << endl;

   return 0;
}
