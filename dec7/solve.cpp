#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <tuple>


using namespace std;

int determineScore(string hand){

  map<char,int> count;

  for(char h: hand){
    if(count.find(h)!=count.end()){
      count[h] += 1;
    }else{
      count[h] =1;
    }
  }

  if(count.size()==1){
    //5 of a kind
    return 7;
  }else if(count.size()==2){
    if(count.begin()->second==2 || count.begin()->second==3){
      //full house
      return 5;
    }else{
      //four of a kind
      return 6;
    }
  }else if(count.size()==3){
    //two pairs or three of a kind
    if(count.begin()->second==2){
      return 3;
    }else if(count.begin()->second==3){
      return 4;
    }else if((++count.begin())->second==2){
      return 3;
    }else{
      return 4;
    }
  }else if(count.size()==4){
    //one pair 
    return 2;
  }else if(count.size()==5){
    //high card
    return 1;
  }
  //oh no
  cout << "OH NO"<<endl;
  return -1000000;
}
map<char,int> letters;
int compareCard(char left, char right){
  if(left==right){
    return 0;
  }
  if(isdigit(left)){
    if(isdigit(right)){
      if(int(left)>int(right)){
        return 1;
      }else{
        return -1;
      }
    }else{
      return -1;
    }
  }else{
    if(isdigit(right)){
      return 1;
    }else{
      if(letters[left] > letters[right]){
        return 1;
      }else{
        return -1;
      }
    }
  }
}


bool compare(tuple<string,int> left,tuple<string,int> right){
  int sleft = determineScore(get<0>(left));
  int sright = determineScore(get<0>(right));
  if(sleft == sright){
    //go through cards
    for(int i=0;i<5;i++){
      int comparison = compareCard(get<0>(left)[i],get<0>(right)[i]);
      if(comparison==0){
        continue;
      }else{
        if(comparison==1){
          return true;
        }else{
          return false;
        }
      }
    }
  }else{
    return (sleft>sright);

  }
}

int main(int argc, char **argv) {
  letters['A'] = 5;
  letters['K'] = 4;
  letters['Q'] = 3;
  letters['J']= 2;
  letters['T']=1;


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
  vector<tuple<string,int>> cards;

  while (std::getline(input, line)){
    //do stuff
    vector<string> temp;
    boost::split(temp, line, boost::is_any_of(" "));
    cards.push_back(make_tuple(temp[0], stoi(temp[1])));
  }
  sort(cards.begin(),cards.end(),compare);

  long result = 0;
  for(int i =0;i<cards.size();i++){
    result += get<1>(cards[i])*(cards.size()-i);
  }
  cout << "THE RESULT IS: "<<result<<endl;

}