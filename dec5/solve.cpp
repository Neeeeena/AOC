#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <map>
#include <tuple>

using namespace std;


long doMap(vector<tuple<long,long,long>> mapping, long key){

  //find key
  for(long i = 0;i<mapping.size();i++){
    if(key >= get<0>(mapping[i]) && (i==mapping.size()-1 ||  key < get<0>(mapping[i+1]) ) ){
          //do next or this

        //-1 to include element
        if( get<0>(mapping[i])+get<2>(mapping[i])-1 >= key ){
          return get<1>(mapping[i])+(key-get<0>(mapping[i]));
        }else{
          //not in this case
          return key;
        }
      }
    
  }
  return key;
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
  vector<vector<tuple<long,long,long>>> mappings;
  vector<long> seeds;
  long mapIndex = -1;
  while (std::getline(input, line)){
    if(line.empty()){
      continue;
    }
    //do stuff
    //get seeds
    if(line.find("seeds:")!=string::npos){
      vector<string> stringseeds;
      boost::split(stringseeds, line.substr(line.find("seeds:")+6), boost::is_any_of(" "));
      for(string s:stringseeds){
        if(s!=""){
          seeds.push_back(stol(s));
        }
      }
    }
    else if(line.find("map:")!=string::npos){
      mapIndex+=1;
      vector<tuple<long,long,long>> m;
      mappings.push_back(m);
    }else{
      vector<string> values;
      boost::split(values, line, boost::is_any_of(" "));

      mappings[mapIndex].push_back(make_tuple(stol(values[1]),stol(values[0]),stol(values[2])));
    }
    
    

  }

  //sort!
  for(auto &v:mappings){
    sort(v.begin(),v.end());
  }



  vector<long> results;
  for(auto s:seeds){
    long c = s;
    for(auto m: mappings){
      c=  doMap(m,c);
    }
    results.push_back(c);
    
  }

  cout << "RESULT IS: " << *min_element(results.begin(),results.end()) << endl;

}