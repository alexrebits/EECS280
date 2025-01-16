#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

//uses Matrix_init and checks that the first and last value are 0
TEST(test_init_catch_all){
  Matrix mat;
  Matrix_init(&mat, 5,3);
  ASSERT_EQUAL(*Matrix_at(&mat,0,0),0);
  ASSERT_EQUAL(*Matrix_at(&mat,2,4),0);
  ASSERT_EQUAL(*Matrix_at(&mat,0,4),0);
  ASSERT_EQUAL(*Matrix_at(&mat,1,0),0);
  ASSERT_EQUAL(*Matrix_at(&mat,2,0),0);
}

TEST(test_print){
  Matrix mat; 
  Matrix_init(&mat,5,3);
  *Matrix_at(&mat,1,2) = 10;
  ostringstream expected;
  expected << "5 3\n" << "0 0 0 0 0 \n" << "0 0 10 0 0 \n" << "0 0 0 0 0 \n";
  ostringstream actual;
  Matrix_print(&mat,actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_print_width){
  Matrix mat; 
  Matrix_init(&mat,10,1);
  *Matrix_at(&mat,0,5) = 2;
  ostringstream expected;
  expected << "10 1\n" << "0 0 0 0 0 2 0 0 0 0 \n";
  ostringstream actual;
  Matrix_print(&mat,actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_print_height){
  Matrix mat; 
  Matrix_init(&mat,1,10);
  *Matrix_at(&mat,4,0) = 2;
  ostringstream expected;
  expected << "1 10\n" << "0 \n" << "0 \n" << "0 \n"<< "0 \n"<< "2 \n"
  << "0 \n"<< "0 \n"<< "0 \n"<< "0 \n"<< "0 \n";
  ostringstream actual;
  Matrix_print(&mat,actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);

  *Matrix_at(&mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
//Tests width and height functions
TEST(test_dimensions){
  Matrix mat;
  Matrix_init(&mat,4,4);
  ASSERT_EQUAL(Matrix_width(&mat), 4);
  ASSERT_EQUAL(Matrix_height(&mat), 4);
  Matrix m;
  Matrix_init(&m, 5, 1);
  ASSERT_EQUAL(Matrix_width(&m), 5);
  ASSERT_EQUAL(Matrix_height(&m), 1); 
}
//fills a matrix with the value 3 and asserts that 1,1 is 3
TEST(test_at){
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat,3);
  ASSERT_EQUAL(*Matrix_at(&mat, 1,1), 3);
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 5;
  const int height = 3;
  const int value = 42;
  Matrix_init(&mat, 5, 3);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}
//fills a 1x1 matrix with 5 and asserts that the value at 0,0 is 5
TEST(test_fill_unit_matrix){
  Matrix mat; 
  Matrix_init(&mat, 1,1);
  Matrix_fill(&mat,5);
  ASSERT_EQUAL(*Matrix_at(&mat,0,0), 5);
}
//fills the border of a 5x5 matrix with 1, tests that the edges are 1 and the inside is 0
TEST(test_fill_border){
  Matrix mat;
  Matrix_init(&mat, 5,5);
  Matrix_fill_border(&mat,1);
  for(int r = 0; r<5; r++){
    for(int c = 0; c<5; c++){
      if(r == 0 || r == 4 || c == 0 || c == 4){
        ASSERT_EQUAL(*Matrix_at(&mat,r,c),1);
      }
      else{
        ASSERT_EQUAL(*Matrix_at(&mat,r,c), 0);
      }
    }
  }
}


//fills a 3x5 Matrix with 42 and makes one spot 43, checks that Matrix_max returns 43
TEST(test_max){
  Matrix mat;
  const int value = 42;
  Matrix_init(&mat, 5, 3);
  Matrix_fill(&mat, value);
  *Matrix_at(&mat, 2,2) = 43;
  ASSERT_EQUAL(Matrix_max(&mat),43);
}
//Edge case for Matrix_max
TEST(test_max_edge){
  Matrix mat;
  const int value = 42;
  Matrix_init(&mat, 5, 3);
  Matrix_fill(&mat, value);
  *Matrix_at(&mat, 2,4) = 43;
  ASSERT_EQUAL(Matrix_max(&mat),43);
}
//tests max value at 0,0
TEST(test_max_edge_zero){
  Matrix mat;
  const int value = 42;
  Matrix_init(&mat, 5, 3);
  Matrix_fill(&mat, value); 
  *Matrix_at(&mat, 0,0) = 43;
  ASSERT_EQUAL(Matrix_max(&mat),43);
}
TEST(test_max_false_index){
  Matrix mat;
  Matrix_init(&mat,3,3);
  Matrix_fill(&mat, -1);
  ASSERT_EQUAL(Matrix_max(&mat), -1);
}
TEST(test_min_col_in_row){
  Matrix mat;
  Matrix_init(&mat,3,10);
  Matrix_fill_border(&mat,2);
  *Matrix_at(&mat,4,1) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,1,0,3),1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,4,0,3),0);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,9,0,3),0);
}
TEST(test_min_col_in_row_range){
  Matrix mat;
  Matrix_init(&mat,5,10);
  Matrix_fill_border(&mat,1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,1,1,5),1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,0,2,5),2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,9,2,4),2);
  *Matrix_at(&mat,9,4) = 0;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,9,2,5),4);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,9,2,4),2);
}
TEST(test_col_min_in_row_unit){
  Matrix mat;
  Matrix_init(&mat,1,1);
  Matrix_fill(&mat,1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat,0,0,1),0);
}

TEST(test_min_in_row){
  Matrix mat;
  Matrix_init(&mat,3,10);
  Matrix_fill_border(&mat,2);
  *Matrix_at(&mat,4,1) = 3;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,1,0,3),0);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat,4,0,3),2);
}

TEST_MAIN() // Do NOT put a semicolon here
