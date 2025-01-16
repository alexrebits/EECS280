#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);  
}
TEST(test_empty){
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    list.pop_front();
    ASSERT_TRUE(list.empty());
    list.push_back(0);
    ASSERT_FALSE(list.empty());
    list.pop_back();
    ASSERT_TRUE(list.empty());

    list.push_front(1);
    list.push_front(1);
    list.push_front(1);
    list.push_front(1);
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_size){
    List<int> list;
    ASSERT_EQUAL(list.size(),0);
    list.push_back(1);
    list.push_back(1);
    list.push_back(1);
    ASSERT_EQUAL(list.size(),3);
    list.pop_back();
    ASSERT_EQUAL(list.size(),2);
    list.clear();
    ASSERT_EQUAL(list.size(),0);
}

TEST(test_front){
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(list.front(),1);
    list.push_back(2);
    ASSERT_EQUAL(list.front(),1);
    list.push_front(3);
    ASSERT_EQUAL(list.front(),3);
    list.pop_front();
    list.pop_front();
    ASSERT_EQUAL(list.front(),2);
}

TEST(test_back){
    List<int> list;
    list.push_front(5);
    ASSERT_EQUAL(list.back(),5);
    list.push_front(3);
    ASSERT_EQUAL(list.back(),5);
    list.push_back(2);
    ASSERT_EQUAL(list.back(),2);
    list.pop_back();
    list.pop_back();
    ASSERT_EQUAL(list.back(),3);
}

TEST(test_copy_ctor){
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int> b = a;
    ASSERT_EQUAL(a.front(),b.front());
    ASSERT_EQUAL(a.back(),b.back());
    a.pop_back();
    ASSERT_NOT_EQUAL(a.back(),b.back());
    b.pop_back();
    ASSERT_EQUAL(a.back(),b.back());
}

TEST(test_assignment){
    List<int> a;
    List<int> b;
    a.push_back(1);
    b.push_back(1);
    ASSERT_EQUAL(a.front(),b.front());
    a.push_back(4);
    a.push_front(3);
    ASSERT_NOT_EQUAL(a.front(),b.front());
    b = a;
    ASSERT_EQUAL(a.front(),b.front());
    ASSERT_EQUAL(a.back(),b.back());
    b=a;
    ASSERT_EQUAL(a.front(),b.front());
    ASSERT_EQUAL(a.back(),b.back());
    a = b;
    ASSERT_EQUAL(a.front(),b.front());
    ASSERT_EQUAL(a.back(),b.back());
}
TEST(test_assignment_same){
    List<int> a;
    List<int> b;
    a = a;
    
    ASSERT_TRUE(a.empty());
    ASSERT_TRUE(b.empty());
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    a = b;
    ASSERT_EQUAL(a.size(),3);
    ASSERT_EQUAL(a.front(),1);
    ASSERT_EQUAL(a.back(),3);
    ASSERT_EQUAL(*(++a.begin()),2);
    a = b;
    b = a;
    a = b;
    ASSERT_EQUAL(a.size(),3);
    ASSERT_EQUAL(a.front(),1);
    ASSERT_EQUAL(a.back(),3);
    ASSERT_EQUAL(*(++a.begin()),2);
    ASSERT_EQUAL(b.size(),3);
    ASSERT_EQUAL(b.front(),1);
    ASSERT_EQUAL(b.back(),3);
    ASSERT_EQUAL(*(++b.begin()),2);
    a = a;
    ASSERT_EQUAL(a.size(),3);
    ASSERT_EQUAL(a.front(),1);
    ASSERT_EQUAL(a.back(),3);
    ASSERT_EQUAL(*(++a.begin()),2);
}

TEST(test_assignment_edge){
    List<int> a;
    List<int> b;
    a.push_back(1);
    a = b;
    ASSERT_TRUE(a.empty());
    ASSERT_TRUE(b.empty());
    a.push_back(2);
    b = a;
    ASSERT_TRUE(b.size() == 1);
    ASSERT_TRUE(a.front() ==2);

}
TEST(test_assignment_edge_two){
    //test for copying from a big to a small, small to a big
    //empty to long, long to empty
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    List<int> b;
    b.push_back(4);
    b = a;
    ASSERT_EQUAL(b.size(),9);
    ASSERT_EQUAL(b.front(),1);
    ASSERT_EQUAL(b.back(),9);
    a.clear();
    a= b; 
    ASSERT_EQUAL(a.size(),b.size());
    ASSERT_EQUAL(a.front(),b.front());
    ASSERT_EQUAL(a.back(),b.back());
    ASSERT_EQUAL(*(++(++(++a.begin()))),
    *(++(++(++b.begin()))));
    a.clear();
    a.push_back(11);
    b = a;
    ASSERT_EQUAL(b.size(),1);
    ASSERT_EQUAL(b.front(),11);
    b.clear();
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
    a.push_back(8);
    a.push_back(9);
    a = b;
    ASSERT_TRUE(a.empty());
}
TEST(test_iterator_beginend){ 
    List<int> list;
    ASSERT_EQUAL(list.begin(),list.end());
    list.push_back(1);
    ASSERT_EQUAL((++list.begin()),list.end());
    ASSERT_NOT_EQUAL(list.begin(),list.end());
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQUAL((++(++(++list.begin()))),list.end());
    ASSERT_NOT_EQUAL(++list.begin(),list.end());
}
TEST(test_erase_middle_other){
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.erase(++a.begin());
    ASSERT_EQUAL(*(++a.begin()),3);
    ASSERT_EQUAL(*a.begin(),1);
}

// TEST(test_iterator_copy_ctor){

// }
// TEST(test_iterator_assignment){

// }

// TEST(test_iterator_operators){

// }

TEST(test_erase_beginend){
    List<int> a;
    a.push_back(1);
    ASSERT_EQUAL(a.end(),a.erase(a.begin()));
    ASSERT_TRUE(a.empty());
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQUAL(a.erase(--(a.end())),a.end());
    ASSERT_TRUE(a.size() ==2);
    ASSERT_EQUAL(a.erase(a.begin()),++a.begin());
    ASSERT_TRUE(a.size() ==1);
}
TEST(test_erase_middle){
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    ASSERT_EQUAL(a.erase(--a.end()),a.end());
    ASSERT_EQUAL(*(--a.end()),2);
    ASSERT_EQUAL(*a.begin(),1);
}

TEST(test_insert_beginend){
    List<int> a;
    a.insert(a.begin(),2);
    ASSERT_EQUAL(a.front(),2);
    ASSERT_EQUAL(a.front(),a.back());
    a.insert(a.begin(),1);
    ASSERT_EQUAL(*(a.begin()),1);
    ASSERT_EQUAL(*(--a.end()),2);
    ASSERT_TRUE(a.size()==2);
    a.insert(a.end(),3);
    ASSERT_EQUAL(*(--a.end()),3);
}

TEST(test_insert_middle){
    List<int> a;
    a.insert(a.begin(),3);
    a.insert(a.begin(),1);
    a.insert(++a.begin(),2);
    ASSERT_EQUAL(*(a.begin()),1);
    ASSERT_EQUAL(*(++a.begin()),2);
    ASSERT_EQUAL(*(++(++a.begin())),3);
    ASSERT_EQUAL(++(++(++a.begin())),a.end());
}
TEST_MAIN()
