#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

//randomize data
int randomize(int userlimit){
    int randVal;
    randVal = rand() % (userlimit + 1); // a number from 1-user range
    return randVal;

}

//to run counter
void storeval(vector <int> &val, int sample, int upperlimit){
    int randomval;
    val.resize(upperlimit+1);

    for(int i = 0; i < sample; ++i){
        randomval = randomize(upperlimit);
        val[randomval] += 1;
    }


}

//find min value
int Min_val(vector <int> &val){
  int min = val[0];

  for(int i = 0; i < val.size(); i++){
        if(val[i] < min){
            min = val[i];
        }
    }

  return min;

}

//find max value
int Max_val(vector <int> &val){
    int max = val[0];

    for(int i = 0; i < val.size(); i++){
          if(val[i] > max){
              max = val[i];
          }
      }

    return max;
}

//calculate the sum
int Sum_val(vector <int> &val){
    int sum = 0;

    for(int i = 0; i < val.size(); i++){
        sum = sum + val[i];
    }

    return sum;
}

//calculate the mean
double Mean_val(vector<int> &val, int sum, int upperlimit){
    double mean;
    sum = Sum_val(val);

    mean = static_cast<double> (sum)/static_cast<double>((upperlimit+1));

    return mean;

}

//Outputs historgram
void displayv(int upperlimit, vector <int> &val, int sample){
    int max;
    int freq;
    int scale;

    storeval(val, sample, upperlimit);
    //set sections
    cout
                << setw(10) << "Index"
                << setw(10) << "Frequency"
                << setw(5) << "Bar"
                << endl;

    //Index
    for(int i = 1; i < upperlimit+1; i++){
        cout << setw(10) << i << " ";

        //Frequency
        cout << setw(10) << val[i] << " ";

        //Bar
        max = Max_val(val);
        scale = max/60;
        freq = val[i];
        for(int l = 0; l < (freq/scale); l++){
            cout << "*";
        }
        cout << endl;
    }

    cout << "Scale is " << scale << " per *" << endl;
}

int main()
{
    int upperlimit, samplesize;
    int min, max, sum;
    double mean;
    vector <int> val;
    srand(static_cast<unsigned int>(time(nullptr))); // Seed random number

    cout << "What would you like to be your upper limit?" << endl;
    cin >> upperlimit; // Tells user range

    //check that it doesn't exceed 100
    if(upperlimit > 100){
        cout << "Can't exceed 100, input again" << endl;
        cin >> upperlimit;
    }

    cout << "How many samples?" << endl;
    cin >> samplesize;

    //check if it is at least 10,000
    while (samplesize < 10000){
        cout << "Need at least 10,000 samples, sorry!" << endl;
        cin >> samplesize;
    }

    //Output histogram and statistics
    displayv(upperlimit, val, samplesize);
    min = Min_val(val);
    max = Max_val(val);
    sum = Sum_val(val);
    mean = Mean_val(val, sum, upperlimit);

    cout << "Range is from 1 to " << upperlimit << endl;
    cout << "Mean: " << mean << endl;
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;

}
