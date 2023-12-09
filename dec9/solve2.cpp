#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

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

    vector<string> sn;
    boost::split(sn, line,boost::is_any_of(" "));
    vector<int> series;
    for(auto s : sn){
      series.push_back(stoi(s));
    }
    vector<vector<int>> grid;
    grid.push_back(series);
    bool done=false;
    while(!done){
      vector<int> nextSeries;
      for(int i=0;i<grid.back().size()-1;i++){
        nextSeries.push_back(grid.back()[i+1]-grid.back()[i]);
      }
      grid.push_back(nextSeries);

      if(accumulate(nextSeries.begin(), nextSeries.end(), 0)==0){
        done = true;
      }
    }

    grid.back().insert(grid.back().begin(),0);

    for(int i = grid.size()-2;i>=0;i--){
      grid[i].insert(grid[i].begin(), grid[i].front()-grid[i+1].front());
    }

    result += grid[0].front();
  }

  cout << "THE RESULT IS: "<<result << endl;
}