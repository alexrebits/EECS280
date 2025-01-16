#include "Map.hpp"
#include "unit_test_framework.hpp"
#include <string>

TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(test_empty){
    Map<std::string,int> count;
    ASSERT_TRUE(count.empty());
    count["Apple"];
    ASSERT_FALSE(count.empty());
    count.insert({"Apples",1});
    ASSERT_FALSE(count.empty());
}
TEST(test_size){
    Map<std::string,int> count;
    ASSERT_EQUAL(count.size(), 0);
    count["Apple"];
    ASSERT_EQUAL(count.size(), 1);
    count.insert({"Apples",1});
    ASSERT_EQUAL(count.size(), 2);
    count["Apple"] = 10;
    ASSERT_EQUAL(count.size(),2);
}
TEST(test_find){
    Map<std::string, double> average;
    ASSERT_EQUAL(average.find("Weight"),average.end());
    average["Weight"] = 0.0;
    ASSERT_EQUAL(average.find("Weight"),average.begin());
    average["Weight"] = 10;
    ASSERT_EQUAL(average.find("Weight"),average.begin());
    ASSERT_EQUAL(++average.find("Weight"),average.end());
    average["Size"] = 2;
    ASSERT_EQUAL(average.find("Size"),average.begin());
    ASSERT_EQUAL(++average.find("Size"),average.find("Weight"));
}
TEST(test_operator){
    Map<int,int> vector;
    vector[1] = 3;
    vector[0] = 5;
    vector[3] = 4;
    vector[2] = 2;
    ASSERT_EQUAL(vector[1],3);
    ASSERT_EQUAL(vector[3],4);
    ASSERT_EQUAL(vector.size(),4);
    vector[3] = 27;
    ASSERT_EQUAL(vector.size(),4);
}


TEST_MAIN()
