/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.hpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

const double epsilon = 0.00001;

static bool almost_equal(double x, double y) {
  return abs(x - y) < epsilon;
}
vector<double> small_data{1,2,3};
vector<double> large_data{1,2,3,4,5,6,7,100,2300,50105105,0,10,11, 12, 1,11,1};
vector<double> e{0};
void test_sum_small_data_set();
void test_sum_large_data_set();

void test_count_empty();
void test_count_three();
void test_count_large();

void test_mean_small_data_set();
void test_mean_large_data_set();

void test_median_one();
void test_median_odd();
void test_median_even();
void test_median_large_data_set();

void test_min_small_data_set();
void test_min_large_data_set();

void test_max_small_data_set();
void test_max_large_data_set();

void test_stdev_small_data_set();
void test_stdev_large_data_set();
void test_stdev_zeros();
void test_stdev_no_dev();
// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  test_sum_large_data_set();
  test_sum_small_data_set();
 test_sum_large_data_set();

 test_count_empty();
 test_count_three();
 test_count_large();

 test_mean_small_data_set();
 //test_mean_large_data_set();

 test_median_one();
 test_median_odd();
 test_median_even();
 test_median_large_data_set();

 test_min_small_data_set();
 test_min_large_data_set();

 test_max_small_data_set();
 test_max_large_data_set();

 test_stdev_small_data_set();
 //test_stdev_large_data_set();
 test_stdev_zeros();
 test_stdev_no_dev();
  // Call your test functions here
  cout << "PASS!" << endl;
  return 0;
}

void test_sum_small_data_set() {

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(almost_equal(sum(data),6));

}

void test_sum_large_data_set(){
  assert(almost_equal(sum(large_data), 50107579));
}

void test_count_empty(){
  assert(count(e) == 1);
}
void test_count_three(){
  assert(count(small_data)==3);
}
  
void test_count_large(){
  assert(count(large_data)==17);
}

void test_mean_small_data_set(){
  assert(mean(small_data) == 2);
}
// void test_mean_large_data_set(){
//   assert(mean(large_data)==)                      !!!
// }

void test_median_one(){
  vector<double> data{1};
  assert(median(data) == 1);
}
void test_median_odd(){
  assert(median(small_data)==2);
}
void test_median_even(){
  vector<double> data{1,2,3,4};
  assert(almost_equal(median(data),2.5));
}
  
void test_median_large_data_set(){
  assert(median(large_data) == 6);
}

void test_min_small_data_set(){
  assert(min(small_data) ==1);
}
void test_min_large_data_set(){
  assert(min(large_data)==0);
}

void test_max_small_data_set(){
  assert(max(small_data)==3);
}
void test_max_large_data_set(){
  assert(max(large_data)==50105105.0);
}

void test_stdev_small_data_set(){
  assert(stdev(small_data) == 1);
}
void test_stdev_large_data_set();
void test_stdev_zeros(){
  vector<double> data{0,0,0};
  assert(stdev(data) ==0);
}
void test_stdev_no_dev(){
  vector<double> data{10,10,10};
  assert(stdev(data) ==0);
}
// Add the test function implementations here.
