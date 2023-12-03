#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h> 
using namespace std;

struct hashFunction 
{ 
  size_t operator()(const tuple<int ,  
                    int>&x) const
  { 
    return get<0>(x) ^ get<1>(x); 
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
  vector<vector<char>> parsed;

  unordered_set<tuple<int, int>, hashFunction > adjacent;
  int row =0;
  while (std::getline(input, line)){
    //do stuff
    vector<char> results;
    int col = 0;
    for(char l : line){
      results.push_back(l);
      if(!isdigit(l)&& l!='.'){
        adjacent.insert(make_tuple(col-1,row+1));
        adjacent.insert(make_tuple(col-1, row));
        adjacent.insert(make_tuple(col-1, row-1));
        adjacent.insert(make_tuple(col, row-1));
        adjacent.insert(make_tuple(col, row+1));
        adjacent.insert(make_tuple(col+1, row));
        adjacent.insert(make_tuple(col+1, row+1));
        adjacent.insert(make_tuple(col+1, row-1));
      }
      col+=1;
    }
    row+=1;
    parsed.push_back(results);
  }

   
  int result =0;
  for(int y=0;y<parsed.size();y++){
    int x = 0;
    string num = "";
    bool adj = false;
    for (int x=0;x<parsed[0].size();x++){
      if(isdigit(parsed[y][x])){
        num+=parsed[y][x];
        if(adjacent.find(make_tuple(x,y))!=adjacent.end()){
          adj = true;
        }
        
      }else{
        if(!num.empty()&&adj){
          cout <<"adding this to res: " <<stoi(num)<< endl;
          result += stoi(num);
        }
        num = "";
        adj= false;
      }
    }


    if(!num.empty()&&adj){
              cout <<"adding this to res: " <<stoi(num)<< endl;
              result += stoi(num);
            }

  }

  cout << "THE RESULT IS: "<<result << endl;


}