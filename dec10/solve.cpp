#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

// Hash function  
struct hashFunction 
{ 
  size_t operator()(const pair<int ,  
                    int> &x) const
  { 
    return x.first ^ x.second; 
  } 
}; 




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
  vector<vector<char>> pipes;
  pair<int,int> start;
  int r=0;
  while (std::getline(input, line)){
    //do stuff
    vector<char> row;
    for(int c=0;c<line.size();c++){
      row.push_back(line[c]);
      if(line[c]=='S'){
        start = make_pair(c,r);
      }
    }
    pipes.push_back(row);
    r+=1;
  }

  
  vector<pair<pair<int,int>,int>> next;
  next.push_back(make_pair(start,0));

  unordered_set<pair<int,int>,hashFunction> seen;
  int largest = 0;
  while(!next.empty()){
    pair<pair<int,int>,int> pr = next.back();
    next.pop_back();
    pair<int,int> ele = pr.first;
    seen.insert(ele);
    if(ele.second >= pipes.size() || ele.first >= pipes[0].size()){
      continue;
    }
    largest = max(largest,pr.second);
    char pipe = pipes[ele.second][ele.first];

    vector<pair<int,int>> temp;
    if(pipe=='7'){
      temp.push_back(make_pair(ele.first-1,ele.second));
      temp.push_back(make_pair(ele.first,ele.second+1));
    }else if(pipe=='F'){
      temp.push_back(make_pair(ele.first+1,ele.second));
      temp.push_back(make_pair(ele.first,ele.second+1));
    }else if(pipe=='-'){
      temp.push_back(make_pair(ele.first+1,ele.second));
      temp.push_back(make_pair(ele.first-1,ele.second));
    }else if(pipe=='L'){
      temp.push_back(make_pair(ele.first+1,ele.second));
      temp.push_back(make_pair(ele.first,ele.second-1));
    }else if(pipe=='J'){
      temp.push_back(make_pair(ele.first-1,ele.second));
      temp.push_back(make_pair(ele.first,ele.second-1));
    }
    else if(pipe=='|'){
      temp.push_back(make_pair(ele.first,ele.second-1));
      temp.push_back(make_pair(ele.first,ele.second+1));
    }else if(pipe=='S'){
      temp.push_back(make_pair(ele.first,ele.second-1));
      temp.push_back(make_pair(ele.first,ele.second+1));
      temp.push_back(make_pair(ele.first-1,ele.second));
      temp.push_back(make_pair(ele.first+1,ele.second));
    }
    else{
      continue;
    }
    for(auto t : temp){
      if(seen.find(t)==seen.end()){
        next.push_back(make_pair(t,pr.second+1));
      }
    }
  }
  //for start node
  largest+=1;

  if(largest%2==1){
    cout << "THE RESULT IS: "<< largest/2+1 << endl;
  }else{
    cout << "THE RESULT IS: "<< largest/2 << endl;
  }
  

}