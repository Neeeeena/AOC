#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

vector<string> adv_tokenizer(string s, char del)
{
    stringstream ss(s);
    string word;
    vector<string> output;
    while (!ss.eof()) {
        getline(ss, word, del);
        if(!word.empty()){
          output.push_back(word);
        }
        
    }
    return output;
}

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
  //red, green, blue
  vector<int> max = {12,13,14};
  int result = 0;

  while (std::getline(input, line)){
    bool invalid = false;
    cout << line << endl;
    int maxr = 0;
    int maxg = 0;
    int maxb = 0;

    //Parse this
    //Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    int id = stoi(line.substr(line.find("Game ")+5, (line.find(":")-line.find(" "))-1 ));
    cout << "ID: " <<id << endl;
    vector<string> sets = adv_tokenizer(line.substr(line.find(":")+1), ';');
    for(string set: sets){
      vector<string> draws = adv_tokenizer(set,',');
      for(string draw : draws){
        vector<string> pair = adv_tokenizer(draw,' ');

        if(pair[1].find("red") !=string::npos){
          if(stoi(pair[0])>maxr){
            maxr = stoi(pair[0]);
          }

        }else if(pair[1].find("green")!= string::npos){
          if(stoi(pair[0])>maxg){
            maxg = stoi(pair[0]);
          }
        }else if(pair[1].find("blue")!=string::npos){
          if(stoi(pair[0])>maxb){
            maxb = stoi(pair[0]);
          }
        }
      }
    }
    result += maxr*maxb*maxg;

  }
  cout << "THIS IS THE RESULT: "<<result << endl;


}