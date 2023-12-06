#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {

  vector<int> times = {51,92,68,90};
  vector<int> distance = {222,2031,1126,1225};
  

  vector<int> results;
  for(int i=0;i<times.size();i++){
    results.push_back(0);
    for(int j=1;j<=times[i];j++){
      int c = (times[i]-j)*(j);
      if(c>distance[i]){
        results[i]+= 1;
      }
    }
    cout << results[i]<<endl; 
  }

  int res = 1;

  for(int r : results){
    res = res*r;
  }

  cout << "THE RESULT IS: "<<res<<endl;



}