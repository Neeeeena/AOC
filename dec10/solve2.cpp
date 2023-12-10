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

double polygonArea(double X[], double Y[], int n)
{
    // Initialize area
    double area = 0.0;
 
    // Calculate value of shoelace formula
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (X[j] + X[i]) * (Y[j] - Y[i]);
        j = i;  // j is previous vertex to i
    }
 
    // Return absolute value
    return abs(area / 2.0);
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

  
  vector<pair<pair<int,int>,vector<pair<int,int>>>> next;
  vector<pair<int,int>> empty;
  next.push_back(make_pair(start,empty));

  unordered_set<pair<int,int>,hashFunction> seen;
  vector<pair<int,int>> largest;
  pair<int,int> hasLargest;
  while(!next.empty()){
    auto pr = next.back();
    next.pop_back();
    pair<int,int> ele = pr.first;
    seen.insert(ele);
    if(ele.second >= pipes.size() || ele.first >= pipes[0].size()){
      continue;
    }
    if(pr.second.size()>largest.size()){
      largest = pr.second;
      hasLargest = pr.first;
    }
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

        vector<pair<int,int>> prevs;
        prevs = pr.second;
        prevs.push_back(ele);

        next.push_back(make_pair(t,prevs));
      }
    }
  }
  largest.push_back(hasLargest);


  double x[largest.size()];
  double y[largest.size()];

  for(int i =0;i<largest.size();i++){
    x[i] = largest[i].first;
    y[i] = largest[i].second;
  }
  double pa = polygonArea(x,y,largest.size());
  double b = pa+1-(largest.size()/2);
  cout << "THE RESULT IS: "<<b<<endl;
}