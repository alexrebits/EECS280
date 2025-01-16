#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_add_card){
    Player * john = Player_factory("John", "Simple");
    Card jack_spade(JACK,SPADES);
    Card led(ACE,HEARTS);
    john->add_card(jack_spade);
    ASSERT_TRUE(jack_spade == john->play_card(led, HEARTS));
    john->add_card(jack_spade);
    ASSERT_TRUE(jack_spade == john->play_card(led, DIAMONDS));

    delete john;
}

TEST(test_player_make_trump){ //goes through all cases
    Player * alex = Player_factory("Alex", "Simple");
    Player * kaustubh = Player_factory("Kaustubh" , "Simple");
    Card one(ACE,DIAMONDS);
    Card two(KING,SPADES);
    Card three(TEN,HEARTS);
    Card four(KING,DIAMONDS);
    Card five(JACK,CLUBS);
    Card up(QUEEN,DIAMONDS);
    Suit up_suit = string_to_suit("Spades");
    kaustubh->add_card(three);
    kaustubh->add_card(five);
    kaustubh->add_card(two);
    ASSERT_FALSE(kaustubh->make_trump(up,false,1,up_suit));
    ASSERT_EQUAL(up_suit,string_to_suit("Spades"));
    ASSERT_FALSE(kaustubh->make_trump(up,true,1,up_suit));
    ASSERT_EQUAL(up_suit,string_to_suit("Spades"));
    alex->add_card(one);
    alex->add_card(two);
    alex->add_card(three);
    alex->add_card(four);
    alex->add_card(five);
    ASSERT_TRUE(alex->make_trump(up,false,1,up_suit));
    ASSERT_EQUAL(up_suit, string_to_suit("Diamonds"));
    //second round
    ASSERT_TRUE(alex->make_trump(up,true,2,up_suit));
    ASSERT_EQUAL(up_suit, string_to_suit("Hearts"));
    up_suit = string_to_suit("Diamonds");
    ASSERT_FALSE(alex->make_trump(up,false,2,up_suit));
    ASSERT_EQUAL(up_suit,string_to_suit("Diamonds"));

    ASSERT_TRUE(alex->make_trump(three,false,2,up_suit));
    ASSERT_EQUAL(up_suit, string_to_suit("Diamonds"));
    ASSERT_FALSE(kaustubh->make_trump(three,true,1,up_suit));

    delete alex;
    delete kaustubh;
}

TEST(test_player_make_trump_bowers){
    Player * leah = Player_factory("Leah","Simple");
    Player * alex = Player_factory("Alex","Simple");
    Card bower1(JACK,HEARTS);
    Card bower2(JACK,DIAMONDS);
    Card up(NINE,DIAMONDS);
    Suit order_up = string_to_suit("Clubs");
    leah->add_card(bower1);
    alex->add_card(bower2);
    ASSERT_TRUE(leah->make_trump(up,true,2,order_up));
    ASSERT_EQUAL(order_up, string_to_suit("Hearts"));
    order_up = string_to_suit("Clubs");
    ASSERT_TRUE(leah->make_trump(up,false,2,order_up));
    ASSERT_EQUAL(order_up, string_to_suit("Hearts"));
    ASSERT_TRUE(alex->make_trump(up,false,2,order_up));
    order_up = string_to_suit("Clubs");
    leah->add_card(bower2);
    ASSERT_TRUE(leah->make_trump(up,true,1,order_up));
    ASSERT_EQUAL(order_up,string_to_suit("Diamonds"));
    order_up = string_to_suit("Clubs");
    ASSERT_TRUE(leah->make_trump(up,false,1,order_up));
    ASSERT_EQUAL(order_up,string_to_suit("Diamonds"));

    delete leah;
    delete alex;
}

TEST(test_player_add_discard){
    Player * alex = Player_factory("Alex","Simple");
    Player * kaustubh = Player_factory("Kaustubh", "Simple");
    Player * leah = Player_factory("Leah","Simple");
    Card nh(NINE,HEARTS);
    Card ts(TEN,SPADES);
    Card js(JACK,SPADES);
    Card kd(KING,DIAMONDS);
    Card qs(QUEEN,SPADES);
    Card bower1(JACK,HEARTS);
    Card bower2(JACK,DIAMONDS);

    Card up(QUEEN,HEARTS);
    Card up2(NINE,SPADES);
    
    alex->add_card(js);
    alex->add_and_discard(up);

    ASSERT_EQUAL(up,alex->play_card(up,up.get_suit()));

    leah->add_card(nh);
    leah->add_card(ts);
    leah->add_card(js);
    leah->add_card(kd);
    leah->add_card(qs);
    leah->add_and_discard(up);
    
    ASSERT_EQUAL(leah->play_card(up2,up2.get_suit()),js);
    ASSERT_EQUAL(leah->play_card(up2,up2.get_suit()),qs);
    ASSERT_EQUAL(leah->play_card(up2,up2.get_suit()),nh);   
    ASSERT_EQUAL(leah->play_card(up2,up2.get_suit()),up);
    ASSERT_EQUAL(leah->play_card(up2,up2.get_suit()),kd);

    kaustubh->add_card(bower1);
    kaustubh->add_card(bower2);

    ASSERT_EQUAL(kaustubh->play_card(up,up.get_suit()),bower1);
    ASSERT_EQUAL(kaustubh->play_card(up,up.get_suit()),bower2);
    delete alex;
    delete kaustubh;
    delete leah;
}

TEST(test_player_lead){
    Player * alex = Player_factory("Alex", "Simple");
    Player * kaustubh = Player_factory("Kaustubh" , "Simple");
    Card one(ACE,DIAMONDS);
    Card two(KING,SPADES);
    Card three(TEN,HEARTS);
    Card four(KING,DIAMONDS);
    Card five(JACK,CLUBS);
    alex->add_card(one);
    alex->add_card(two);
    alex->add_card(three);
    alex->add_card(four);
    alex->add_card(five);

    ASSERT_EQUAL(alex->lead_card(DIAMONDS),two);
    ASSERT_EQUAL(alex->lead_card(SPADES),one);
    ASSERT_EQUAL(alex->lead_card(HEARTS),four);
    ASSERT_EQUAL(alex->lead_card(CLUBS),three);
    ASSERT_EQUAL(alex->lead_card(CLUBS),five);
    kaustubh->add_card(one);
    kaustubh->add_card(four);
    ASSERT_EQUAL(kaustubh->lead_card(DIAMONDS),one);
    ASSERT_EQUAL(kaustubh->lead_card(SPADES),four);

    delete alex;
    delete kaustubh;
}
// Add more tests here
    // alex->add_card(one);
    // alex->add_card(two);
    // alex->add_card(three);
    // alex->add_card(four);
    // alex->add_card(five);
TEST_MAIN()
