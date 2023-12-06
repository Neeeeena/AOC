#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <set>
#include <math.h>
#include <map>
#include <bits/stdc++.h>

using namespace std;

set<int> convertToSet(vector<string> v)
{
    set<int> s;
 

    for (string x : v) {
        if(x==""){
          continue;
        }
        s.insert(stoi(x));
    }

    return s;
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
  int result = 0;

  vector<int> scores;

  while (std::getline(input, line)){
    vector<int> wonOnes;
    vector<string> parts;
    boost::split(parts, line.substr(line.find(":")+1), boost::is_any_of("|"));
    //good numbers
    vector<string> goodones;
    boost::split(goodones, parts[0], boost::is_any_of(" "));

    set<int> goodset = convertToSet(goodones);

    vector<string> chosenones;
    boost::split(chosenones, parts[1], boost::is_any_of(" "));

    for(string chosen : chosenones){
      if(chosen!=""){
        if(goodset.find(stoi(chosen))!=goodset.end()){
          wonOnes.push_back(stoi(chosen));
        }
      }
      
    }
    scores.push_back(wonOnes.size());

  }

  vector<int> wins(scores.size(), 1);
  //whatever works
  for(int i=0;i<scores.size();i++){
    for(int k=0;k<wins[i];k++){
      for(int j=0;j<scores[i];j++){
        wins[i+j+1] +=1;
      }
    }

  }

  cout << "THE RESULT IS: "<<accumulate(wins.begin(), wins.end(), 0)<<endl;


}