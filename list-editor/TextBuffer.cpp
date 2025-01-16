#include "TextBuffer.hpp"
#include <cassert>
#include <iostream>
    //EFFECTS: Computes the column of the cursor within the current row.
  //NOTE: This does not assume that the "column" member variable has
  //      a correct value (i.e. the row/column INVARIANT can be broken).
  int TextBuffer::compute_column() const{
    int count = 0;
    auto it = cursor;
    if(it == data.begin()){return count;}
    --it;
    for(; *it !='\n'; it--){
      if(it ==data.begin()){return count+1;}
      count++;
    }
    return count;
  }


  //EFFECTS: Creates an empty text buffer. Its cursor is at the past-the-end
  //         position, with row 1, column 0, and index 0.
  TextBuffer::TextBuffer() : data(), 
  cursor(data.end()),row(1), column(0), index(0){}

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position forward and returns true,
  //          unless the cursor is already at the past-the-end position,
  //          in which case this does nothing and returns false.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::forward(){
    if(is_at_end()){return false;}
    if(*cursor == '\n'){ //goes to next line
      column = 0;
      row++;
    }
    else{
      column++;
    }
    ++cursor;
    index++;
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position backward and returns true,
  //          unless the cursor is already at the first character in
  //          the buffer, in which case this does nothing and returns false.
  //HINT:     Implement and use the private compute_column() member
  //          function to compute the column when moving left from the
  //          beginning of a line to the end of the previous one.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::backward(){
    if(cursor == data.begin()){return false;}
    if(column == 0){
      if(row ==1){return false;}
      row--;
      cursor--;
      column = compute_column();
    }
    else{
      cursor--;
      column--;
    }
    index--;
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Inserts a character in the buffer before the cursor position.
  //          If the cursor is at the past-the-end position, this means the
  //          inserted character is the last character in the buffer.
  //          The cursor remains in the same place as before the insertion.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::insert(char c){ // double check this is all right
    if(is_at_end()){
      data.push_back(c);
    }
    else if(cursor == data.begin()){
      data.push_front(c);
    }
    else{ //in the middle somewhere
      cursor = ++data.insert(cursor,c); 
      //double check cursor location??
      //make tests for this specifically
    }
    if(c == '\n'){ 
      row++;
      column = 0;
    }
    else{ column++;}
    index++;
  }

  //MODIFIES: *this
  //EFFECTS:  Removes the character from the buffer that is at the cursor and
  //          returns true, unless the cursor is at the past-the-end position,
  //          in which case this does nothing and returns false.
  //          The cursor will now point to the character that was after the
  //          deleted character, or the past-the-end position if the deleted
  //          character was the last one in the buffer.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::remove(){ 
    if(is_at_end()){
      return false;
    }
    // if(column ==0){
    //   row--;
    //   column = compute_column();
    // }
    // else{
    //   column--;
    // }
    cursor = data.erase(cursor); //row, col, and index don't change??

    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the start of the current row (column 0).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_start(){ //is this right??
    int temp = row;
    while(column != 0){
      backward();
    }
    assert(temp == row);
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the end of the current row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_end(){ //double check???
    int temp = row;
    while(!is_at_end()){
      if(*cursor !='\n'){
        forward();
      }
      else{
        assert(temp == row);
        return;
      }
    }
    assert(temp == row);
  }

  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          if it exists. If the row does not have that many columns,
  //          moves to the end of the row (the newline character that
  //          ends the row, or the past-the-end position if the row is
  //          the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_column(int new_column){ 
    //double check conditionals??
    if(column == new_column){return;} //already at the right place
    else if(column>new_column){ //needs to move backwards
      while(column > new_column){
        backward();
      }
    }
    else{ // needs to move forward or to the end of the row
      while(column<new_column &&!is_at_end()){
        if(*cursor !='\n'){
          forward();
        }
        else{return;}
      }
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::up(){ 
    //should work, double check invariants and then check functions if it doesn't work??
    if(row ==1){return false;}
    int temp = column;
    move_to_row_start();
    backward();
    move_to_row_start();
    move_to_column(temp);
    return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer). Does
  //          nothing if the cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::down(){
    // auto it = cursor; 
    // for(;*it != '\n'; it++){ //returns false if in last row
    //   if(it == data.end()){
    //     return false;
    //   }
    // }
    // //not last row
    // int temp = column;
    // move_to_row_end();
    // forward();
    // move_to_column(temp);
    // return true;
    auto it = cursor;
    for(;it != data.end();++it){
      if(*it == '\n'){
        int temp = column;
        move_to_row_end();
        forward();
        move_to_column(temp);
        return true;
      }
    }
    return false;
  }

  //EFFECTS:  Returns whether the cursor is at the past-the-end position.
  bool TextBuffer::is_at_end() const{
    return cursor == data.end();
  }

  //REQUIRES: the cursor is not at the past-the-end position
  //EFFECTS:  Returns the character at the current cursor
  char TextBuffer::data_at_cursor() const{
    assert(!is_at_end());
    return *cursor;
  }

  //EFFECTS:  Returns the row of the character at the current cursor.
  int TextBuffer::get_row() const{
    return row;
  }

  //EFFECTS:  Returns the column of the character at the current cursor.
  int TextBuffer::get_column() const{
    return column;
  }

  //EFFECTS:  Returns the index of the character at the current cursor
  //          with respect to the entire contents. If the cursor is at
  //          the past-the-end position, returns size() as the index.
  int TextBuffer::get_index() const{
    int ind = index;
    if(is_at_end()){
        ind = size();
    }
    return ind;
  }

  //EFFECTS: Returns the number of characters in the buffer.
  int TextBuffer::size() const{ //if i use my own implementation 
    return data.size();
    // int i = 0;
    // for(auto it = data.begin(); it != data.end(); it++){
    //   i++;
    // }
    // return i;
  }

  //EFFECTS:  Returns the contents of the text buffer as a string.
  //HINT: Implement this using the string constructor that takes a
  //      begin and end iterator. You may use this implementation:
  //        return std::string(data.begin(), data.end());
  std::string TextBuffer::stringify() const{ //??
    return std::string(data.begin(),data.end());
  }

