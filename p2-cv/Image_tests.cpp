#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----

//default init initialization with w x h in header
TEST(test_init){
  Image img;
  Pixel p;
  p.r =0;
  p.g =0;
  p.b =0;
  Image_init(&img, 3,3);
  ASSERT_EQUAL(Image_get_pixel(&img,1,1).r,p.r);
}
// //tests the initialization using istreams or ifstreams or istringstreams
TEST(test_init_streams){
  Image img;
  string input =
  "P3\n3 3\n255\n255 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 \n";
  istringstream is(input);
  ostringstream os;
  Image_init(&img,is);
  Image_print(&img,os);
  string actual = os.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, input);
}
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}
//thoroughly tests the print function
TEST(test_print_thorough){

}
//test dimensions for both kinds of init functions
TEST(test_dimensions){
  Image img;
  Image i;
  Image_init(&img, 3,3);
  Image_init(&i, 2,7);
  ASSERT_EQUAL(Image_width(&img),3);
  ASSERT_EQUAL(Image_height(&img),3);
  ASSERT_EQUAL(Image_width(&i),2);
  ASSERT_EQUAL(Image_height(&i),7);

  //here do equivalent istream init tests
}

TEST(test_get_pixel_comprehensive){
  Image img;
  Image i;
  Pixel p;
  Image_init(&img,3,4);
  Image_init(&i,1,1);
  ASSERT_EQUAL(Image_get_pixel(&img,2,2).b,Image_get_pixel(&i,0,0).b);
  p.r = 1;
  p.b = 1;
  p.g = 1;
  Image_fill(&img,p);
  ASSERT_EQUAL(Image_get_pixel(&img,3,2).r,p.r);
  ASSERT_EQUAL(Image_get_pixel(&img,0,0).b,p.b);
  ASSERT_EQUAL(Image_get_pixel(&img,0,2).g,p.g);
  ASSERT_EQUAL(Image_get_pixel(&img,3,2).r,p.r);
  ASSERT_EQUAL(Image_get_pixel(&img,1,1).b,p.b);
}

TEST(test_set_pixel_basic){

}

TEST(test_fill){

}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
