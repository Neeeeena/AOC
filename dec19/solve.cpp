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
  unordered_map<string,vector<tuple<char,bool,int,string>>> allrules;
  vector<unordered_map<char,int>> workflows;
  while (std::getline(input, line)){
    if(line[0]=='{'){
      vector<string> ind;
      unordered_map<char,int> tw;
      boost::split(ind,line.substr(1,line.size()-2),boost::is_any_of(","));
      for(auto in : ind){
        tw[in[0]]=stoi(in.substr(2));
      }
      workflows.push_back(tw);
    }
    else if(line==""){
      continue;
    }
    else{
      vector<string> parts;
      boost::split(parts,line,boost::is_any_of("{}"));
      vector<string> temp;
      boost::split(temp,parts[1],boost::is_any_of(","));
      vector<tuple<char,bool,int,string>> rules;
      for(auto r : temp){
        if(r.find(":")!=string::npos){
          vector<string> t;
          boost::split(t,r,boost::is_any_of(":"));
          rules.push_back(make_tuple(
            t[0][0],
            t[0][1]=='<',
            stoi(t[0].substr(2)),
            t[1]
          ));
        }else{
          rules.push_back(make_tuple('-',false,0,r));
        }
      }
      allrules[parts[0]]=rules;
    }
    //do stuff
  }

  int result =0;
  for(auto w : workflows){

    string rule = "in";
    while(rule!="R" && rule!="A"){
      for(tuple<char,bool,int,string> r : allrules[rule]){

        if(get<0>(r)=='-'){
          rule = get<3>(r);

          break;
        }
        else if((get<1>(r)&& w[get<0>(r)]<get<2>(r)) || (!get<1>(r)&& w[get<0>(r)]>get<2>(r)) ){
          rule = get<3>(r);

          break;
        }
      }
    }
    if(rule=="A"){

      for(auto k : w){
        result += k.second;
      }
    }
  }
  cout << "THE RESULT IS: "<<result << endl;


}