#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h> 
#include <map>
using namespace std;


bool isAdjacent(tuple<int,int> left, int rightx, int righty){
  int leftx = get<0>(left);
  int lefty = get<1>(left);
  //cout << leftx << ","<<lefty << " - "<<rightx<<","<<righty <<endl;

  if(abs(leftx-rightx) + abs(lefty-righty)<=1 ){
    return true;
  }else if(abs(leftx-rightx) + abs(lefty-righty)==2 && leftx!=rightx && lefty!=righty){
    return true;
  }
  return false;

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
  vector<vector<char>> parsed;
  map< tuple<int,int>, int > gears;

  int row =0;
  while (std::getline(input, line)){
    //do stuff
    vector<char> results;
    int col = 0;
    for(char l : line){
      results.push_back(l);
      
      if(l=='*'){
        gears[make_pair(col,row)] = 0;
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
    tuple<int,int> adjTo;
    bool add = false;
    for (int x=0;x<parsed[0].size();x++){
      if(isdigit(parsed[y][x])){
        num+=parsed[y][x];
        for(auto gear:gears){
          if(isAdjacent(get<0>(gear),x,y)){
            cout << "was ajacent"<<endl;
            adjTo = get<0>(gear);
            add=true;
          }
        }
        
      }else{
        if(!num.empty()){
          if(add){
            if(gears[adjTo] != 0){
              cout <<"adding this to res: " <<stoi(num) << "*"<<gears[adjTo]<< endl;
              result += stoi(num)*gears[adjTo];
            }else{
              gears[adjTo] = stoi(num);
            }
            
          }
          
        }
        num = "";
        add= false;
      }
    }


    if(!num.empty()){
          if(add){
            if(gears[adjTo] != 0){
              cout <<"Adding this to res: " <<stoi(num) << "*"<<gears[adjTo]<< endl;
              result += stoi(num)*gears[adjTo];
            }else{
              gears[adjTo] = stoi(num);
            }
            
          }
          
        }

  }

  cout << "THE RESULT IS: "<<result << endl;


}