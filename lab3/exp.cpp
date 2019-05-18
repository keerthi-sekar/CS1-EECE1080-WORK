// Program: exp.cpp
// Description: Test and develop a version of the exp() function - main() has test
// code to check and see if this version of exp() function works properly.

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double factorial(int N) {
    double return_val = N;
    for(int i = N; i > 0; i--){
        return_val = N * factorial(N-1);
        if(N > 1){
            return_val = N * factorial(N-1);
        }
        else{
            return_val = 1;
        }

    return return_val;
    }
}

double E_to_X(double X) {
    double answer = 0;
    for(int j = 1; j <= 27; j++){
        answer += pow(X, j)/ factorial(j);
    }
   return answer+1;

}


int main() {

	cout << fixed << "E_to_X(0) is " << E_to_X(0) << " should be 1" << endl;
	cout << fixed << "E_to_X(1) is " << E_to_X(1) << " should be 2.718" << endl;
	cout << fixed << "E_to_X(2) is " << E_to_X(2) << " should be 7.38" << endl;
	cout << fixed << "E_to_X(5) is " << E_to_X(5) << " should be 120" << endl;
	cout << fixed << "E_to_X(10) is " << E_to_X(10) << " should be 22026" << endl;

	return 0;
}
