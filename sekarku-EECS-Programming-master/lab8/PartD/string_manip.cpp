/*
 * =====================================================================================
 *
 *       Filename:  string_manip.cpp
 *
 *    Description:  Complete String (Part D) Code
 *
 *      Version:  1.0
 *      Created:  03/27/2019  12:20 AM
 *      Revision:  none
 *      Compiler:  MINGW
 *
 *      Author:  Keerthi Sekar
 *      Organization: EECE1080C
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class stringManip {
    public:
        stringManip();
        stringManip(string input);
        string retrieve();
        void setString(string input);
        void chop();
        void padString(int n);
        void center(int length);
        void truncate(int n);
        void removeNonAlpha();
        void convertToUpperCase();
        void convertToLowerCase();
    private:
        string tobeEdited;
};

// Default Constructor
stringManip::stringManip(){
    tobeEdited = "";
}

// Overloaded Constructor
stringManip::stringManip(string in_string){
    tobeEdited = in_string;
}
//set function
void stringManip::setString(string input){
    tobeEdited = input;
}

// retrieve function (like get function)
string stringManip::retrieve(){
    return tobeEdited;
}

//chop() function
void stringManip::chop(){
    if(tobeEdited == ""){
        tobeEdited = "";
    }else{
      for(int j = 0; j < tobeEdited.size(); j++){
            if(tobeEdited[j] == ' '){
                tobeEdited.erase(j,1);
            }
       }
    }
}
// padString() function
void stringManip::padString(int n){
    if(tobeEdited.size() < (static_cast<unsigned long long>(n))){
        for(unsigned long long i = tobeEdited.size(); i < static_cast<unsigned long long>(n);i++){
            tobeEdited += " ";
        }
    }else{
        cout << tobeEdited;
    }
}
//center function
void stringManip::center(int length){
    int am_space;
    chop();
    am_space = length - tobeEdited.size();

    for(int k = 0; k < (am_space/2); k++){
        tobeEdited.insert(k, " ");
    }
    for(int l = 0; l < ((am_space/2)+1); l++){
        tobeEdited += " ";
    }
}
//truncate function
void stringManip::truncate(int n){
    if(tobeEdited.size() > n){
        while(tobeEdited.size() > n){
            tobeEdited.pop_back();
        }
    }
}
//removeNonAlpha function
void stringManip::removeNonAlpha(){
    string new_s;
    if(tobeEdited == ""){
        tobeEdited = new_s;
    }else{
        for(int i = 0; i < tobeEdited.size(); i++){
            if((!isalpha(tobeEdited[i]))||(tobeEdited[i] == ' ')){
               tobeEdited.erase(i,1);
            }
            if(tobeEdited[i] == '!'){
                tobeEdited.erase(i,1);
            }
        }
    }
}
//convert to uppercase
void stringManip::convertToUpperCase(){
    cout << "<";
    for(int k = 0; k < tobeEdited.size(); k++){
        putchar(toupper(tobeEdited[k]));
        tobeEdited[k] = toupper(tobeEdited[k]); // modify tobeEdited
    }
    cout << ">";
}
//convert to lowercase
void stringManip::convertToLowerCase(){
    cout << "<";
    for(int k = 0; k < tobeEdited.size(); k++){
        putchar(tolower(tobeEdited[k]));
        tobeEdited[k] = tolower(tobeEdited[k]); // modify tobeEdited
    }
    cout << ">";
}
int main(){
    //When testing each function - test one at a time
    stringManip S1;
    stringManip S2(" xyz ");
    stringManip S3("kEeRtHi");
    stringManip S4("test1ing");

    cout << S2.retrieve() << endl;
    S2.chop();
    cout << "<" << S2.retrieve() << ">" << endl;

    cout << S2.retrieve() << endl;
    S2.center(20);
    cout << "<" << S2.retrieve() << ">" << endl;

    cout << S2.retrieve() << endl;
    S2.padString(15);
    cout << "<" << S2.retrieve() << ">" << endl;

    cout << S2.retrieve() << endl;
    S2.truncate(1);
    cout << "<" << S2.retrieve() << ">" << endl;

    cout << S4.retrieve() << endl;
    S4.removeNonAlpha();
    cout << "<" << S4.retrieve() << ">" << endl;

    cout << S3.retrieve() << endl;
    S3.convertToUpperCase();


    cout << S3.retrieve() << endl;
    S3.convertToLowerCase();


    return 0;
}
