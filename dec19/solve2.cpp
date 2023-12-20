#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

using namespace std;

typedef unordered_map<char,pair<int,int>> WF; 

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

  vector<pair<string,WF>> wfs;
  WF start;
  start['x'] = make_pair(1,4000);
  start['m'] = make_pair(1,4000);
  start['a'] = make_pair(1,4000);
  start['s'] = make_pair(1,4000);
  
  wfs.push_back(make_pair("in",start));

  long result =0;

  while(!wfs.empty()){
    auto wf = wfs.back();
    wfs.pop_back();
    if(wf.first=="A"){

      long temp = 1;
      for(auto w : wf.second){
        temp = temp * (w.second.second-w.second.first+1);
      }
      result += temp;
    }

    for(tuple<char,bool,int,string> r : allrules[wf.first]){
      if(get<0>(r)=='-'){
        wf.first = get<3>(r);
        wfs.push_back(wf);
        break;
      }
      auto range = wf.second[get<0>(r)];
      if(get<1>(r)){
        if(range.second < get<2>(r)){
          wf.first = get<3>(r);
          wfs.push_back(wf);
          break;
        }else if(range.first < get<2>(r)){

          WF newwf = wf.second;
          newwf[get<0>(r)] = make_pair(range.first,get<2>(r)-1);
          wfs.push_back(make_pair(get<3>(r),newwf));
          wf.second[get<0>(r)].first = get<2>(r);
        }
      }else if(!get<1>(r)){
        if(range.first > get<2>(r)){
          wf.first = get<3>(r);
          wfs.push_back(wf);
          break;
        }
        else if(range.second > get<2>(r)){

          WF newwf = wf.second;
          newwf[get<0>(r)] = make_pair(get<2>(r)+1,range.second);
          wfs.push_back(make_pair(get<3>(r),newwf));
          wf.second[get<0>(r)].second = get<2>(r);
        }
      } 
      
    }

  }

  cout << "THE RESULT IS: "<<result << endl;


}