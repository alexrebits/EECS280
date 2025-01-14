// stats.cpp
#include "stats.hpp"
#include <cassert>
#include <vector>
#include <algorithm> // sort
#include <cmath> // sqrt, modf

using namespace std;

//EFFECTS: returns the count (sample size) of the numbers in v
// remember to cast from size_t to integer unless this is auto-casted
int count(vector<double> v) {
    return v.size();
}

//REQUIRES: v is not empty
//EFFECTS: returns the sum of the numbers in v
double sum(vector<double> v) {
    double s = 0.0;
    for (size_t i = 0; i< v.size(); ++i){
        s += v[i];
    }
  return s;
}

//REQUIRES: v is not empty
//EFFECTS: returns the arithmetic mean of the numbers in v
double mean(vector<double> v) {
    return (sum(v))/(count(v));
}

//REQUIRES: v is not empty
//EFFECTS: returns the median of the numbers in v
//IMPLIMENTATION: squentially sort the vector by swapping elements until it is sorted from low to high, check even/odd, for even take mean of two center values
double median(vector<double> v) {
    std::sort(v.begin(),v.end());
    
    if(v.size() % 2 ==1){
        int index = size(v)/2;
        return v[index];
    }
    else if(v.size() % 2 == 0){
        int i1 = size(v)/2 -1;
        int i2 = size(v)/2;
        return (v[i1]+v[i2])/2;
    }
    else{ //just in case c++ works differently than i thought
        assert(false);
    }
    
}
//REQUIRES: v is not empty
//EFFECTS: returns the min number in v
double min(vector<double> v) {
  double m = v[0];
  for (size_t i = 1; i<size(v); ++i){ //also check if starting at element 2 is ok since v[0] is starting point
    if(m > v[i]){
        m = v[i];
    }
  }
  return m;
}

//REQUIRES: v is not empty
//EFFECTS: returns the max number in v
double max(vector<double> v) {
  double m = v[0];
  for(size_t i = 1; i<size(v); ++i){ //see line 32 comment
    if(m<v[i]){
        m=v[i];
    }
  }
  return m;
}

//REQUIRES: v contains at least 2 elements
//EFFECTS: returns the corrected sample standard deviation of the numbers in v
double stdev(vector<double> v) {
  double sum = 0.0;
  double n = 1.0/(count(v) -1);
  for(size_t i = 0; i<v.size(); i++){
    sum += (v[i] - mean(v)) *(v[i] - mean(v));
  }
  return sqrt(n * sum);
}

//REQUIRES: v is not empty
//          p is between 0 and 1, inclusive
//EFFECTS: returns the percentile p of the numbers in v like Microsoft Excel.
//  Refer to the project spec for the formula to use.
//  NOTE: the definition in the spec uses indexing from 1.  You will need to
//  adapt it to use indexing from 0.
double percentile(vector<double> v, double p) {
  std::sort(v.begin(), v.end());
  double rank = p*(count(v)-1.0);
  int k = rank;
  double d = rank - k;
   if(k+1 == count(v)){
     return max(v);
   }
  else{
    return v[k] + d*(v[k+1] - v[k]);
  }
}
//REQUIRES: v and filter have the same number of elements
//EFFECTS: returns a new, filtered version of v containing the elements (and
//         only those elements) at v[x] where filter[x] is equal to target,
//         in the same order as they originally appear in v.
//         Note: For this function, compare values to the criteria using ==.
vector<double> filter(vector<double> v,
                      vector<double> criteria,
                      double target) {
  vector<double> temp ={};
 for(size_t i = 0; i<count(criteria); i++){
  if(criteria[i] == target){  //this doesn't work because of floating point stuff, ask how to resolve
    temp.push_back(v[i]);
  }
 }
 return temp;
}
