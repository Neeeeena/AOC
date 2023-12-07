#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>
#include <tuple>
#include <string>

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
    if(count.begin()->second==2){
      return 3;
    }else if(count.begin()->second==3){
      return 4;
    }else if((++count.begin())->second==2){
      return 3;
    }else{
      return 4;
    }
    //two pairs or three of a kind
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
  if(letters[left] > letters[right]){
        return 1;
      }else{
        return -1;
      }
}

string makeWin(string hand){
  map<char,int> count;

  if(hand.find('J')==string::npos){
    return hand;
  }
  for(char h: hand){
    if(count.find(h)!=count.end()){
      count[h] += 1;
    }else{
      count[h] =1;
    }
  }

  //find largest count not J
  int largest =0;
  char bestChar;
  for(auto c : count){
    if(c.first!='J'){
      if(c.second>largest){
        bestChar = c.first;
        largest = c.second;
      }else if(c.second==largest){
        //is this a better character?
        int compar = compareCard(c.first,bestChar);
        if(compar==1){
          bestChar = c.first;
          largest = c.second;
        }
        
      }
    }
  }
  return boost::replace_all_copy(hand,"J",string(1,bestChar));

}

bool compare(tuple<string,int,string> left,tuple<string,int,string> right){
  int sleft = determineScore(get<0>(left));

  int sright = determineScore(get<0>(right));

  if(sleft == sright){
    //go through cards
    for(int i=0;i<5;i++){
      int comparison = compareCard(get<2>(left)[i],get<2>(right)[i]);
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

  letters['A'] = 13;
  letters['K'] = 12;
  letters['Q'] = 11;
  letters['J']= 1;
  letters['T']=10;
  letters['2']=2;
  letters['3']=3;
  letters['4']=4;
  letters['5']=5;
  letters['6']=6;
  letters['7']=7;
  letters['8']=8;
  letters['9']=9;


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
  vector<tuple<string,int,string>> cards;

  while (std::getline(input, line)){
    //do stuff
    vector<string> temp;
    boost::split(temp, line, boost::is_any_of(" "));
    string goodHand = makeWin(temp[0]);
    cards.push_back(make_tuple(goodHand, stoi(temp[1]),temp[0]));
  }
  


  sort(cards.begin(),cards.end(),compare);

  long result = 0;
  for(int i =0;i<cards.size();i++){
    result += get<1>(cards[i])*(cards.size()-i);
  }
  cout << "THE RESULT IS: "<<result<<endl;

}