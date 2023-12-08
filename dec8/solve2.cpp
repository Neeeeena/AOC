#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

 map<string,tuple<string,string>> links;

tuple<long,string> goToZ(string instructions, long startStep, string start){

    string next = start;
    long steps = 0;
    long i = startStep;
    bool done = false;
    while(!done){
      char instruction = instructions[i%instructions.size()];
      if(instruction=='R'){
        next = get<1>(links[next]);
      }else{
        next = get<0>(links[next]);
      }
      steps += 1;
      i += 1;
      if(next[2]=='Z'){
        done = true;
      }
    }
    return make_tuple(steps,next);
  }

long getIndexOfSmallest(vector<long> v){
  long smallest = v[0];
  long smallestIndex = 0;
  for(long i=0;i<v.size();i++){
    if(v[i]<smallest){
      smallest = v[i];
      smallestIndex = i;
    }
  }
  return smallestIndex;
}

bool allEqual(vector<long> v){
  for(int i =0;i<v.size()-1;i++){
    if(v[i]!=v[i+1]){
      return false;
    }
  }
  return true;
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
  string instructions;
  getline(input, instructions);
  getline(input, line);
  
  
  vector<string> starts;
  vector<string> ends;
  while (std::getline(input, line)){

    string lhs = line.substr(0,3);
    string ll = line.substr(7,3);
    string rr = line.substr(12,3);

    links[lhs] = make_tuple(ll,rr);
    if(lhs[2]=='A'){
      starts.push_back(lhs);
    }
    if(lhs[2]=='Z'){
      ends.push_back(lhs);
    }
  }

  for(string end:ends){
    cout << end << endl;
  }


  vector<long> numberOfSteps;
  vector<string> zValues;

  for(int i =0;i<starts.size();i++){

    tuple<long,string> steps = goToZ(instructions,0,starts[i]);
    numberOfSteps.push_back(get<0>(steps));
    zValues.push_back(get<1>(steps));

  }
  map<string,tuple<long,string>> zTable;

  for(long i =0;i<instructions.size();i++){
    for(string z : ends){
      tuple<long,string> steps = goToZ(instructions,i,z);
      zTable[z+to_string(i)] = steps;
    }
  }


  long j = 0;
  while(!allEqual(numberOfSteps)){
    long smallestIndex = getIndexOfSmallest(numberOfSteps);
    string thisZ = zValues[smallestIndex];
    long thisInst = numberOfSteps[smallestIndex]%instructions.size();
    auto next = zTable[thisZ+to_string(thisInst)];
    numberOfSteps[smallestIndex] += get<0>(next);
    zValues[smallestIndex] = get<1>(next);

  }


  cout << "THE RESULT IS: "<< numberOfSteps[0]<<endl;

}