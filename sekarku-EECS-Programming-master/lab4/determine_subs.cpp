#include <iostream>

using namespace std;

string determineSubstance(double check){
    string boiling;
    if((check >= 95) && (check < 105)){
          boiling = "Water";
    }else if((check >= 339.15) && (check < 374.85)){
          boiling = "Mercury";
    }else if((check >= 1127.65) && (check < 1246.35)){
          boiling = "Copper";
    }else if((check >= 2083.35) && (check < 2302.65)){
        boiling = "Silver";
    }else if ((check >= 2527) && (check < 2793)) {
        boiling = "Gold";
    }else{
        boiling = "Unknown";
    }
    return boiling;
}

int main() {  //NO NEED TO CHANGE THIS
    double bp = 100;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Water" << endl;
    bp = 350;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Mecury" << endl;
    bp = 2100;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Silver" << endl;
    bp = 1100;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Unknown" << endl;
    bp = 1150;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Copper" << endl;
    bp = 2600;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Gold" << endl;
    bp = 11000;
    cout << "Substance function returns: " << determineSubstance(bp)
         << " for a temperature of " << bp << " Should be Known" << endl;
    return 0;
}
