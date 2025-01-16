#include <cassert>
#include "Matrix.hpp"
// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  // assert(0 < width && 0 < height);
  mat->width = width;
  mat->height = height;
  mat->data.clear();

  for(int i = 0; i<width*height; i++){
    mat->data.push_back(0);
  }

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  
  os << Matrix_width(mat) << " " << Matrix_height(mat) << std::endl;
  for(int y = 0; y< Matrix_height(mat); y++){
    for(int x = 0; x< Matrix_width(mat); x++){
      os << *Matrix_at(mat,y,x) << " ";
    }
    os << std::endl;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  // assert(mat->width > 0);
  return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  //access the data point (integer) at column,row
  // assert(0 <= row && row < Matrix_height(mat));
  // assert(0 <= column);
  // assert(column < Matrix_width(mat));
  return &mat->data.at((row * mat->width) + column);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  //same as before but return a const pointer? or just a normal
  // pointer that automatically converts to const
  // assert(0 <= row && row < Matrix_height(mat));
  // assert(0 <= column && column < Matrix_width(mat));
  return &mat->data.at((row * mat->width) + column);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  //traverses the entire matrix, setting data = value at each iteration
  for(int y = 0; y< Matrix_height(mat); y++){
    for(int x = 0; x< Matrix_width(mat); x++){
        *Matrix_at(mat,y,x) = value;
    }
  }
  // for(int i = 0; i< Matrix_height(mat) * Matrix_width(mat); i++){
  //   int y = i / Matrix_width(mat);
  //   int x = i % Matrix_width(mat);
  //   *Matrix_at(mat,y,x) = value;
  // }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  //  Sets data = value at all edge spaces
  for(int y = 0; y< Matrix_height(mat); y++){
    for(int x = 0; x< Matrix_width(mat); x++){
      if(x == 0 || x == Matrix_width(mat) -1){
        *Matrix_at(mat,y,x) = value;
      }
      else if(y==0 || y == Matrix_height(mat) -1){
        *Matrix_at(mat,y,x) = value;
      }
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  //traverses entire matrix, storing a maximum value at the beginning 
  //and finding a possible maximum with every iteration
  int max = *Matrix_at(mat,0,0);
  for(int y = 0; y< Matrix_height(mat); y++){
    for(int x = 0; x< Matrix_width(mat); x++){
        if(max < *Matrix_at(mat,y,x)){
          max = *Matrix_at(mat,y,x);
        }
    }
  }
  return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  // assert(0 <= row && row < Matrix_height(mat));
  // assert(0 <= column_start && column_end <= Matrix_width(mat));
  // assert(column_start < column_end);
  int min = column_start;
    for(int x = column_start; x< column_end; x++){
        if(*Matrix_at(mat,row,min) > *Matrix_at(mat,row,x)){
          min = x;
        }
    }
    return min;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {

    int minv = *Matrix_at(mat,row, 
    Matrix_column_of_min_value_in_row(mat,row,column_start,column_end));
    return minv;
}
