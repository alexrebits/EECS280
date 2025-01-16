#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_shuffle_ctor){ //figure out the order of a shuffled deck
    Pack pack;
    pack.shuffle();
    Card first = pack.deal_one();
    ASSERT_EQUAL(KING,first.get_rank());
    ASSERT_EQUAL(CLUBS,first.get_suit());

    Card second = pack.deal_one();
    ASSERT_EQUAL(JACK,second.get_rank());
    ASSERT_EQUAL(HEARTS,second.get_suit());    

    Card third = pack.deal_one();
    ASSERT_EQUAL(NINE,third.get_rank());
    ASSERT_EQUAL(SPADES,third.get_suit());
    
    Card four = pack.deal_one();
    ASSERT_EQUAL(ACE,four.get_rank());
    ASSERT_EQUAL(CLUBS,four.get_suit());    
}

TEST(test_pack_empty){
    Pack pack;
    for(int i = 0; i<24; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
    pack.reset();
    ASSERT_FALSE(pack.empty());
    for(int i = 0; i<24; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}

TEST(test_fin_ctor){
    ifstream fin("pack1.in");
    Pack pack(fin);
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    Card third = pack.deal_one();
    Card fourth = pack.deal_one();
    
    ASSERT_EQUAL(first.get_rank(),ACE);
    ASSERT_EQUAL(first.get_suit(),DIAMONDS);
    ASSERT_EQUAL(second.get_rank(),TEN);
    ASSERT_EQUAL(second.get_suit(),CLUBS);
    ASSERT_EQUAL(third.get_rank(),NINE);
    ASSERT_EQUAL(third.get_suit(),SPADES);
    ASSERT_EQUAL(fourth.get_rank(),QUEEN);
    ASSERT_EQUAL(fourth.get_suit(),SPADES);
}
// Add more tests here

TEST_MAIN()
