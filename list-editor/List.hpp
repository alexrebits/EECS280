#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public: 
  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return !(first);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const{
    return listSize;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    return last->datum;
  }

  //MODIFIES: increments listSize, adjusts first, 
  //changes the prev of the new second element
  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *data = new Node;
    data->datum = datum;
    data->next = first;
    data->prev = nullptr;
    if(listSize >0){
      first->prev = data;
    }
    else{last = data;}
    first = data;
    listSize++;
  }

  //MODIFIES: increments listSize
  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *data = new Node;
    data->datum = datum;
    data->next = nullptr;
    data->prev = last;
    if(listSize >0){
      last->next = data;
    }
    else{first = data;}
    last = data;
    listSize++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list  
  void pop_front(){
    assert(!empty());
    Node *temp = first;
    first = first->next;
    if(listSize >1){ first->prev = nullptr;}
    else{last = nullptr;}
    delete temp; //make sure this cleans up everything???
    listSize--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    assert(!empty());
    Node *temp = last;
    last = last->prev;
    if(listSize>1){last->next = nullptr;} 
    else{first = nullptr;}
    delete temp;
    listSize--;
  }

  //MODIFIES: may invalidate list iterators, listSize = 0
  //EFFECTS:  removes all items from the list
  void clear(){
    while(!empty()){
      pop_front();
    }
    assert(listSize == 0);
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  //default ctor
  List() : first(nullptr), last(nullptr){}
  //dtor
  ~List() { //is this enough?
    clear();
  }
  //copy ctor
  List(const List &other) : first(nullptr), last(nullptr) {copy_all(other);}

  //overloaded assignment operator 
  List &operator=(const List &other){
    if(this == &other) {return *this;}
    clear();
    copy_all(other);
    return *this;
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    for(auto ptr = other.begin(); ptr != other.end(); ptr++){
      push_back(*ptr);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  size_t listSize = 0;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr){}

    //copy ctor
    Iterator(const Iterator &input) : list_ptr(input.list_ptr), node_ptr(input.node_ptr){}

    //overloaded assignment operator 
    Iterator &operator=(const Iterator &rhs){
      if(*this == rhs){return *this;}
      list_ptr = rhs.list_ptr;
      node_ptr = rhs.node_ptr;
      return *this;
    }
    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    //no destructor???


    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    T & operator*() const{
      assert(node_ptr);
      return (node_ptr->datum);
    }
    Iterator &operator++(){
      assert(list_ptr);
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }
    Iterator operator++(int /*fill*/){ //postfix ++ 
      Iterator copy = *this;
      operator++();
      return copy;
    } 
    bool operator==(const Iterator &other) const{
      if(!list_ptr && !other.list_ptr){ //both lists are nullptrs
        if(!node_ptr && !other.node_ptr){
          return true; // default initialized 
        }
        assert(false); //check if they don't have lists and have equal nodeptrs??
      }
      else if(!(list_ptr || other.list_ptr)){ 
        //one list is a nullptr,so comparing an end itor to a default
        return false;
      }
      else if(list_ptr==other.list_ptr){ //same list
        if(node_ptr == other.node_ptr){
          return true;
        }
        return false;
      }
      assert(false); //undefined behavior is assert okay??
    }
    bool operator!=(const Iterator &it) const{
      return !operator==(it);
    }
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal            CHECK
    // - a default-constructed iterator must compare unequal to an       CHECK 
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must        CHECK
    //   compare equal
    // - two iterators to different locations in the same list must      CHECK
    //   compare unequal
    // - comparing iterators obtained from different lists results in    CHECK
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.



    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class List;
    friend class TextBuffer;

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np){}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const{ //what about deleting this??
    Iterator temp =  Iterator(this,first);
    return temp;
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    Iterator final = Iterator(this,nullptr);
    return final;
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i){
    assert(i.node_ptr);
    if(i == begin()){
      i++;
      pop_front();
    }
    else if(i == --end()){
      i++;
      pop_back();
    }
    else{ 
      auto temp = i;
      ((i.node_ptr)->prev)->next = (i.node_ptr)->next;
      ((i.node_ptr)->next)->prev = (i.node_ptr)->prev;
      i++;
      delete temp.node_ptr; //how to clean up this node???!!
      listSize--;
    }
    return i;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum){ //check for beginning and end ?!?!!?
    if(i == begin()){
      push_front(datum);
      i--;
    } 
    else if(i == end()){
      push_back(datum);
      i--;
    }
    else{
      Node *temp = new Node;
      temp->datum = datum;
      temp->next = i.node_ptr;
      temp->prev = (i.node_ptr)->prev;
      (temp->prev)->next = temp;
      (temp->next)->prev = temp;
      i--;
      listSize++;
    }
    return i;
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
