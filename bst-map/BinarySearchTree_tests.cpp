#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
using namespace std;

TEST(test_) {
    // Add your tests here
    ASSERT_TRUE(true);
}
TEST(test_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(),0);
    ASSERT_EQUAL(tree.height(),0);  
    ASSERT_TRUE(tree.check_sorting_invariant());
}
TEST(test_basic_tree){ //make another test for edge trees, like lines or really zig zaggy ones
//a false positive somewhere in here, double check spec
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_EQUAL(tree.size(),1);
    // ASSERT_EQUAL(++tree.begin(),tree.end()); //is this the error?
    tree.insert(3);
    tree.insert(7);
    ASSERT_FALSE(tree.empty());   
    ASSERT_EQUAL(tree.size(),3);
    ASSERT_EQUAL(tree.height(),2);  
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(12);
    ASSERT_EQUAL(tree.size(),4); 
    ASSERT_EQUAL(tree.height(),3);  
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(15);
    ASSERT_EQUAL(tree.size(),5);
    ASSERT_EQUAL(tree.height(),4);  
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(1);
    ASSERT_EQUAL(tree.size(),6);
    ASSERT_EQUAL(tree.height(),4);  
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "5 3 1 7 12 15 ");

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "1 3 5 7 12 15 ");
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_location_func){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.begin(),tree.end());
    ASSERT_EQUAL(tree.min_element(),tree.end());
    ASSERT_EQUAL(tree.begin(),tree.min_element());
    ASSERT_EQUAL(tree.begin(),tree.max_element());
    tree.insert(5);
    ASSERT_EQUAL(*(tree.begin()),5);
    ASSERT_EQUAL(tree.min_element(),tree.begin());
    ASSERT_EQUAL(tree.begin(),tree.min_element());
    ASSERT_NOT_EQUAL(tree.begin(),tree.end());
    tree.insert(4);
    ASSERT_EQUAL(tree.min_greater_than(5),tree.end());
    tree.insert(10);
    ASSERT_EQUAL(tree.min_greater_than(5),tree.max_element());
    tree.insert(15);
    ASSERT_EQUAL(tree.min_greater_than(10),tree.max_element());
    tree.insert(6);
    ASSERT_NOT_EQUAL(tree.min_greater_than(5),tree.max_element());
    ASSERT_EQUAL(*(tree.min_greater_than(5)),6);
    ASSERT_EQUAL(tree.min_element(),tree.begin());
    tree.insert(3);
    tree.insert(2);
    ASSERT_EQUAL(tree.min_greater_than(1),tree.min_element());
    ASSERT_EQUAL(tree.begin(),tree.min_element());
    tree.insert(1);
    ASSERT_EQUAL(*(tree.begin()),1);
    ASSERT_NOT_EQUAL(tree.begin(),tree.end());
    ASSERT_EQUAL(*(tree.min_element()),1);
    ASSERT_EQUAL(tree.size(),8);
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_min_element_stick){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(20);
    ASSERT_EQUAL(tree.min_element(),tree.begin());
    ASSERT_EQUAL(*(tree.min_element()),5);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.size(),3);
}

TEST(test_max_element_stick){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(20);
    ASSERT_EQUAL(*(tree.max_element()),20);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.size(),3);
}
TEST(test_copy_ctor){// test assoc impl methods 
    BinarySearchTree<int> cherry;
    BinarySearchTree<int> apple(cherry);
    ASSERT_TRUE(apple.empty());
    ASSERT_EQUAL(apple.size(),0);
    ASSERT_EQUAL(apple.height(),0); 
    apple.insert(6);
    apple.insert(4);
    apple.insert(9);
    apple.insert(5);
    apple.insert(2);
    apple.insert(13);
    ASSERT_TRUE(cherry.empty());
    ASSERT_FALSE(apple.empty());
    ASSERT_EQUAL(apple.size(),6);
    ASSERT_EQUAL(apple.height(),3);
    ASSERT_EQUAL(*(apple.begin()),2);
    ASSERT_EQUAL(*(++apple.min_greater_than(5)),9);
    BinarySearchTree<int> pineapple(apple);
    ASSERT_FALSE(pineapple.empty());
    ASSERT_EQUAL(pineapple.size(),6);
    ASSERT_EQUAL(pineapple.height(),3);
    ASSERT_EQUAL(*(pineapple.begin()),2);
    ASSERT_EQUAL(*(++pineapple.min_greater_than(5)),9);
}
TEST(test_assignment_ctor){// in terms of assoc impl methods
    BinarySearchTree<int> maple; 
    maple.insert(2);
    maple.insert(1);
    maple.insert(3);
    BinarySearchTree<int> oak; 
    oak = maple;
    ASSERT_EQUAL(maple.size(),oak.size());
    ASSERT_EQUAL(maple.height(),oak.height());
    ASSERT_EQUAL(*(maple.begin()),*(oak.begin()));
    ASSERT_EQUAL(*(++maple.begin()),*(++oak.begin()));
    ASSERT_EQUAL(*(maple.max_element()),*(oak.max_element()));
    ASSERT_TRUE(maple.check_sorting_invariant());
    ASSERT_TRUE(oak.check_sorting_invariant());
}

TEST(test_self_assignment){
    BinarySearchTree<int> pine;
    pine = pine; 
    ASSERT_TRUE(pine.empty());
    ASSERT_EQUAL(pine.size(),0);
    ASSERT_EQUAL(pine.height(),0);  
    ASSERT_TRUE(pine.check_sorting_invariant());
    pine.insert(5);
    pine.insert(3);
    pine.insert(8);
    pine.insert(10);
    ASSERT_EQUAL(pine.begin(),pine.min_element());
    ASSERT_EQUAL(*(pine.min_greater_than(5)),8);
    ASSERT_EQUAL(pine.size(),4);
    ASSERT_EQUAL(pine.height(),3);
    pine = pine;
    ASSERT_EQUAL(pine.begin(),pine.min_element());
    ASSERT_EQUAL(*(pine.min_greater_than(5)),8);
    ASSERT_EQUAL(pine.size(),4);
    ASSERT_EQUAL(pine.height(),3);
}
// TEST(test_iterator_increment){ //may not be necessary

// }
// TEST(test_min_greater_than_edge){ //figure out something

// }

TEST(test_find){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.find(1),tree.end());
    tree.insert(10);
    ASSERT_EQUAL(tree.find(1),tree.end());
    tree.insert(0);
    ASSERT_EQUAL(tree.find(1),tree.end());
    ASSERT_EQUAL(tree.find(10),tree.max_element());
    ASSERT_EQUAL(tree.find(0),tree.min_element());
    tree.insert(1);
    ASSERT_EQUAL(tree.find(1),tree.min_greater_than(0));
    tree.insert(15);
    tree.insert(7);
    tree.insert(3);
    ASSERT_EQUAL(tree.find(14),tree.end());
    ASSERT_EQUAL(tree.find(3),tree.min_greater_than(1));
    ASSERT_EQUAL(tree.find(7),++tree.min_greater_than(1));
    ASSERT_TRUE(tree.check_sorting_invariant());
    *(tree.find(10)) = 19;
    ASSERT_FALSE(tree.check_sorting_invariant());
    *(tree.find(19)) = 10;
    *(tree.find(15)) = 27;
    *(tree.find(10)) = 19;
    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_sorting_invariant){
    
}

TEST(test_traversals){
    
}
// TEST(test_insert){ // are there edge cases???

// }
TEST_MAIN()
