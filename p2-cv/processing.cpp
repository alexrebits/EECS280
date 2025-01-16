#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  Matrix_init(energy,Image_width(img),Image_height(img));
 
  int max = squared_difference(Image_get_pixel(img,0,1),
                            Image_get_pixel(img,2,1))
  +squared_difference(Image_get_pixel(img,1,0),Image_get_pixel(img,3,0));
  for(int r = 1; r<Image_height(img)- 1; r++){ 
    for(int c = 1; c<Image_width(img)- 1;c++){ 
      //calculate energy and fill the inside of the energy matrix
      int vert = squared_difference(Image_get_pixel(img,r-1,c),
                            Image_get_pixel(img,r+1,c)); //n + s
      int horiz = squared_difference(Image_get_pixel(img,r,c-1),
                          Image_get_pixel(img,r,c+1)); // w + e
      *Matrix_at(energy,r,c) = vert + horiz; //fills r,c of energy
      if(max < vert+horiz){ //finds greatest energy
        max = vert + horiz; 
      }
    }
  }
  Matrix_fill_border(energy, max);
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));
  for(int i = 0; i<Matrix_width(cost); i++){ //initializes the cost matrix first row 
    *Matrix_at(cost,0,i) = *Matrix_at(energy, 0, i);
  }
  for(int r = 1; r<Matrix_height(energy); r++){ //traverses the other rows 
    *Matrix_at(cost,r,0) = *Matrix_at(energy, r, 0)
                      +Matrix_min_value_in_row(cost,r-1,0,2);

    for(int c =1; c<Matrix_width(energy)-1; c++){//traverses each column
      *Matrix_at(cost,r,c) =  *Matrix_at(energy,r,c)
                        +Matrix_min_value_in_row(cost,r-1,c-1,c+2);

    }
    *Matrix_at(cost,r,Matrix_width(cost)-1)=
    *Matrix_at(energy,r,Matrix_width(cost)-1)+
    Matrix_min_value_in_row(cost,r-1,Matrix_width(cost)-2,Matrix_width(cost));
  }
}
  


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  vector<int> seam(Matrix_height(cost), 0);
  
  seam[0] = Matrix_column_of_min_value_in_row(cost, 
            Matrix_height(cost)-1, 0, Matrix_width(cost)-1);

  for(int i = 1; i < Matrix_height(cost); i++){
    if(seam[i-1] == 0){
      seam[i] = Matrix_column_of_min_value_in_row(cost, 
                Matrix_height(cost)-1-i, 0, 2);
      
    }
    else if(seam[i-1] == Matrix_width(cost)-1){
      seam[i] = Matrix_column_of_min_value_in_row(cost, 
      Matrix_height(cost)-1-i, Matrix_width(cost)-2, Matrix_width(cost));

    }
    else{
      seam[i] = Matrix_column_of_min_value_in_row(cost, 
      Matrix_height(cost)-1-i, seam[i-1]-1,seam[i-1]+2);
    }
  }
  for(int i = 0; i<seam.size()/2; i++){
    int temp = seam[i];
    seam[i] = seam[seam.size()-1-i];
    seam[seam.size()-1-i] = temp;
  }
  return seam;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  Image temp;
  Image_init(&temp,Image_width(img)-1,Image_height(img));
  for(int r = 0; r<Image_height(img); r++){
    
    for(int c1 = 0; c1<seam[r]; c1++){
      Image_set_pixel(&temp,r,c1,Image_get_pixel(img,r,c1)); 
    }
    for(int c2 = seam[r] + 1; c2<Image_width(img); c2++){
      Image_set_pixel(&temp,r,c2-1,Image_get_pixel(img,r,c2));
    }
  }
  *img = temp;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  while(Image_width(img) != newWidth){
    Matrix energy;
    Matrix_init(&energy,Image_width(img),Image_height(img));
    Matrix cost;
    Matrix_init(&cost,Matrix_width(&energy),Matrix_height(&energy));
    vector<int> min;
    compute_energy_matrix(img,&energy);
    compute_vertical_cost_matrix(&energy,&cost);
    min = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img,min);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img,newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img,newWidth);
  seam_carve_height(img,newHeight);
}
