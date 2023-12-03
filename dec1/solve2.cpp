#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

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
  vector<string> char_digits = {"one","two","three","four","five","six","seven","eight","nine"};
  while (std::getline(input, line)){
    cout << line << endl;
    //do stuff
    int first_value = -1;
    int last_value = -1;
    int first_index = line.size();
    int last_index = -1;

    //cout << line << endl;
    for(int i=0;i<char_digits.size();i++){
      size_t s = line.find(char_digits[i]);
      
      if(s!= string::npos){
        //cout << "found: "<<char_digits[i]  << " at: "  << s<< endl;
        if(s < first_index){
          first_index = s;
          first_value = i+1;
        }
        //cout << "what is this: "<<last_index << " and "<<s <<endl;
      }


      s = line.rfind(char_digits[i]);
      
      if(s!= string::npos){
        //cout << "found: "<<char_digits[i]  << " at: "  << s<< endl;

        //cout << "what is this: "<<last_index << " and "<<s <<endl;
        if(last_index==-1 || s>last_index){
          last_index = s;
          last_value = i+1;
        }
      }
    }


    for(int j=0; j < line.size() ; j++){
      char l = line[j];
      if(isdigit(l)){
        if(j < first_index){
          first_index = j;
          first_value = int(l)-48;
          //cout << "CHANGED: "<< first_value<< endl;
        }
        if(last_index == -1 || j >last_index){
          last_index = j;
          last_value = int(l)-48;
          //cout << "CHANGED2: "<< last_value<< endl;
        }
      }
    }

    //cout << first_value << " at " <<first_index << " AND " << last_value << " at " << last_index << endl;
    cout << "THIS IS: "<<first_value*10 + last_value << endl;
    result += first_value*10 + last_value;

  }
  cout << "Result to 1: " <<result << endl;


}