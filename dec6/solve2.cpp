#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {

  long times = 51926890;
  long distance = 222203111261225;
  


  long lb = 0;

    for(int j=1;j<=times;j++){
      long c = (times-j)*(j);
      if(c>distance){
        lb = j;
        break;
      }
    }
long ub = 0;
    for(int j=times;j>=0;j--){
      long c = (times-j)*(j);
      if(c>distance){
        ub = j;
        break;
      }
    }
  


  cout << "THE RESULT IS: "<<ub-lb+1<<endl;



}