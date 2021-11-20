#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <tuple>
using namespace std;

// ALGORITHM VERIFY
void verifyLampLogClock(int events[10][10], int n, int m);
bool check_pairs(int events[10][10], int n, int m, int i, int j);
void checkevents(int events[10][10], int n, int m);
void eventToArray();

string abc[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
string arr_LV[10][10] = {};
typedef vector<tuple<int, int, int>>event;

event send;
event receive;

int main() {
    
    ifstream inFile;
    string input; // holds input file's data
    int events[10][10]; // matrix holding given input events
    int n = 0;
    int m = 0;
    int mLast = 0;
    int temp;

    inFile.open("inputv.txt");
    if(!inFile) {
        cout << "Unable to open file.";
        exit(1);
    }

    // read data from file into events matrix and changes the ASCII to a int
    while(getline(inFile, input)){
        for(int i = 0; i < input.length(); i++) {
            if(isdigit(input[i])) {
                temp = (int)input[i];
                temp = temp - 48;
                events[n][m++] = temp;
            }
        }
        n++;
        mLast = m;
        m = 0;
    }
    m = mLast;

    verifyLampLogClock(events, n, m);
    eventToArray();
    checkevents(events, n, m);
    
    for(int d = 0; d < n;d++){
        for(int e = 0; e < m;e++){
            cout << arr_LV[d][e]<< " ";
            }
        cout<<endl;
    }
    return 0;
}

//Checks each cell to see if it's 1 less than the other cells and updates the Recieve tuple and its coordinates
void verifyLampLogClock(int events[10][10], int n, int m) {
    bool pair;
    for (int i=0; i < n; i++){
        int prev = 0;
        for(int j = 0; j < m; j++){
            if (events[i][j] - prev > 1){
                receive.push_back({events[i][j], i, j});
            }
            pair = check_pairs(events, n, m, i, j);
            if(pair == true){break;}
            prev = events[i][j];
        }
    }
    if(receive.size() != send.size()){
        cout<< "INCORRECT" <<endl;
        exit(0);
    }
}
//checks for the Send tuple and adds the tuple to its coordinates
bool check_pairs(int events[10][10], int n, int m, int i, int j){
    bool pair = false;
    for(int l = 0; l < n; l++){
        if(l != i){
            for(int k = 0; k < m; k++){
                if(events[l][k] > 1 && events[l][k] == events[i][j] - 1){
                    pair = true;
                    send.push_back({events[l][k], l, k});
                    break;
                }
            }
        if (pair == true){
            return true;
            break;}
        }
    }
    return false;
}

//Changes the tuples and it's coordinates, sorts them and concatinates the r or s + their corrosponding number and adds them to the arr_LV
void eventToArray(){
    sort(receive.begin(), receive.end());
    sort(send.begin(), send.end());
    int col = 0;
    int row = 0;
    for(int l = 0; l < send.size(); l++){
        row = get<1>(receive.at(l));
        col = get<2>(receive.at(l));
        arr_LV[row][col] = "r" + to_string(l+1);
        row = get<1>(send.at(l));
        col = get<2>(send.at(l));
        arr_LV[row][col] = "s" + to_string(l+1);
    }
}

//Goes through all the empty spots and changes 0 to "NULL" and puts in the alphabet
void checkevents(int events[10][10],int n,int m){
    int counter = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j< m; j++){
            if(events[i][j]== 0){
                arr_LV[i][j] = "NULL";
            }
            if(arr_LV[i][j].empty()){
                arr_LV[i][j] = abc[counter++];
            }
        }
    }
}
