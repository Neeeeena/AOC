#include <fstream>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
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
    //Parse this
    //Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    int id = stoi(line.substr(line.find("Game ")+5, (line.find(":")-line.find(" "))-1 ));
    cout << "ID: " <<id << endl;
    vector<string> sets;
    boost::split(sets, line.substr(line.find(":")+1), boost::is_any_of(";"));
    for(string set: sets){
      vector<string> draws = adv_tokenizer(set,',');
      for(string draw : draws){
        vector<string> pair = adv_tokenizer(draw,' ');

        if(pair[1].find("red") !=string::npos){
          if(stoi(pair[0])>12){
            //this game is invalid!
            cout << id << " not valid " << pair[0] << " " << pair[1]<<" is too many R"<< endl;
            invalid = true;
          }
        }else if(pair[1].find("green")!= string::npos){
          if(stoi(pair[0])>13){
            //this game is invalid!
            cout << id << " not valid " << pair[0] << " " << pair[1]<<" is too many G"<< endl;
            invalid = true;
          }
        }else if(pair[1].find("blue")!=string::npos){
          if(stoi(pair[0])>14){
            //this game is invalid!
            cout << id << " not valid " << stoi(pair[0]) << " " << pair[1]<<" is too many B"<< endl;
            invalid = true;
          }
        }
      }
    }
    if(!invalid){
      result += id;
    }

  }
  cout << "THIS IS THE RESULT: "<<result << endl;


}