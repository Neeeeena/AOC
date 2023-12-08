#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <tuple>

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
  string instructions;
  getline(input, instructions);
  getline(input, line);
  
  map<string,tuple<string,string>> links;

  while (std::getline(input, line)){

    string lhs = line.substr(0,3);
    string ll = line.substr(7,3);
    string rr = line.substr(12,3);

    links[lhs] = make_tuple(ll,rr);
  }
  string next = "AAA";
  int steps = 0;
  bool done = false;
  while(!done){
    char instruction = instructions[steps%instructions.size()];
    if(instruction=='R'){
      next = get<1>(links[next]);
    }else{
      next = get<0>(links[next]);
    }
    steps += 1;
    if(next=="ZZZ"){
      done = true;
    }
  }


  cout << "THE RESULT IS: "<<steps << endl;

}