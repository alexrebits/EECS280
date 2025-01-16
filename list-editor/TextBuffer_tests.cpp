#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_backward){
    TextBuffer buffer;
    buffer.insert('a');
    buffer.insert('b');
    buffer.insert('c');
    buffer.insert('\n');
    buffer.insert('A');
    buffer.insert('B');
    ASSERT_EQUAL(buffer.get_column(),2);
    ASSERT_EQUAL(buffer.get_index(),6);
    buffer.backward();
    ASSERT_EQUAL(buffer.get_column(),1);
    ASSERT_EQUAL(buffer.get_index(),5);
    buffer.backward();
    buffer.backward();
    ASSERT_EQUAL(buffer.get_column(),3);
    ASSERT_EQUAL(buffer.get_row(),1);
    ASSERT_EQUAL(buffer.get_index(),3);
}

TEST_MAIN()
