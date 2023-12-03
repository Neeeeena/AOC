#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if (argc != 2){
    cerr << "Incorrect number of arguments!" << endl;
    return 1;
  }
  ifstream input(argv[1]);

  if (!input.is_open()) {
    cerr << "Can't open file!" << endl; 
    return 1;
  }

  string line;
  int result = 0;
  
  while (std::getline(input, line)){
    //do stuff
    vector<int> digits;
    for(char l : line){
      if(isdigit(l)){
        digits.push_back(int(l)-48);
        cout << l << " and "<< int(l)- 48 << endl;
      }
    }
    if(digits.size()==1){
      cout << digits[0]*10+digits[0] << endl;
      result += digits[0]*10+digits[0];
    }else{
      cout << digits[0]*10 + digits[digits.size()-1] << endl;
      result += digits[0]*10 + digits[digits.size()-1];
    }
  }
  cout << "Result to 1: " <<result << endl;


}