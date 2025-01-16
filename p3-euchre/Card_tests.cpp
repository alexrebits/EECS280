#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_card_ctor_default){
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_card_get_overloaded){
    Card a(KING,HEARTS);
    Card b(QUEEN,SPADES);
    Card c(JACK,HEARTS);
    Card d(JACK,DIAMONDS);
    Card e(JACK,CLUBS);
    Card f(JACK,SPADES);
    ASSERT_EQUAL(HEARTS, a.get_suit(DIAMONDS));
    ASSERT_EQUAL(SPADES, b.get_suit(CLUBS));
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, d.get_suit(HEARTS));
    ASSERT_EQUAL(SPADES,e.get_suit(SPADES));
    ASSERT_EQUAL(CLUBS, f.get_suit(CLUBS));
}
TEST(test_is_face){
    Card e(NINE, DIAMONDS);
    Card f(TEN, SPADES);
    Card a(JACK,HEARTS);
    Card b(QUEEN, DIAMONDS);
    Card c(KING,SPADES);
    Card d(ACE,CLUBS);
    ASSERT_TRUE(a.is_face_or_ace());
    ASSERT_TRUE(b.is_face_or_ace());
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(d.is_face_or_ace());
    ASSERT_FALSE(e.is_face_or_ace());
    ASSERT_FALSE(f.is_face_or_ace());
}
TEST(test_bower){
    Card a(JACK,DIAMONDS);
    Card b(JACK,HEARTS);
    Card c(JACK,CLUBS);
    Card d(JACK,SPADES);
    Card e(QUEEN,HEARTS);
    ASSERT_TRUE(a.is_right_bower(DIAMONDS));
    ASSERT_TRUE(a.is_left_bower(HEARTS));
    ASSERT_FALSE(a.is_left_bower(DIAMONDS));
    ASSERT_FALSE(a.is_right_bower(HEARTS));
    ASSERT_TRUE(b.is_left_bower(DIAMONDS));
    ASSERT_FALSE(c.is_right_bower(DIAMONDS));
    ASSERT_FALSE(d.is_left_bower(HEARTS));
    ASSERT_FALSE(e.is_right_bower(HEARTS)||e.is_left_bower(HEARTS));
}
TEST(test_is_trump){
    Card a(NINE, SPADES);
    Card b(TEN, DIAMONDS);
    Card c(JACK,DIAMONDS);
    Card d(QUEEN, HEARTS);
    Card e(KING,CLUBS);
    Card f(ACE,SPADES);
    ASSERT_TRUE(a.is_trump(SPADES));
    ASSERT_FALSE(b.is_trump(HEARTS));
    ASSERT_TRUE(c.is_trump(HEARTS) && c.is_trump(DIAMONDS));
    ASSERT_TRUE(d.is_trump(HEARTS));
    ASSERT_FALSE(e.is_trump(HEARTS));
    ASSERT_FALSE(f.is_trump(CLUBS));   
}
TEST(test_os_operator){
    string a = "Queen of Spades";
    string b = "Nine of Clubs";
    string c = "Jack of Diamonds";
    string d = "Ten of Hearts";
    Card a1(QUEEN,SPADES);
    Card b1(NINE,CLUBS);
    Card c1(JACK,DIAMONDS);
    Card d1(TEN,HEARTS);
    ostringstream oss;
    ostringstream oss1;
    ostringstream oss2;
    ostringstream oss3;
    oss << a1;
    ASSERT_EQUAL(oss.str(),a);

    oss1 << b1;
    ASSERT_EQUAL(oss1.str(),b);

    oss2 << c1;
    ASSERT_EQUAL(oss2.str(),c);

    oss3 << d1;
    ASSERT_EQUAL(oss3.str(),d);
}

TEST(test_is_operator){
    string a = "Queen of Spades";
    string b = "Nine of Clubs";
    string c = "Jack of Diamonds";
    string d = "Ten of Hearts";
    Card a1(QUEEN,SPADES);
    Card b1(NINE,CLUBS);
    Card c1(JACK,DIAMONDS);
    Card d1(TEN,HEARTS);
    Card a2;
    Card b2;
    Card c2;
    Card d2;
    istringstream iss(a);
    istringstream iss1(b);
    istringstream iss2(c);
    istringstream iss3(d);
    iss >> a2;
    iss1 >> b2;
    iss2 >> c2;
    iss3 >> d2;
    ASSERT_EQUAL(a1,a2);
    ASSERT_EQUAL(b1,b2);
    ASSERT_EQUAL(c1,c2);
    ASSERT_EQUAL(d1,d2);
}

TEST(test_equality_operators){
    Card a(NINE, SPADES);
    Card b(TEN, DIAMONDS);
    Card c(JACK,DIAMONDS);
    Card c1(JACK,DIAMONDS);
    Card d(QUEEN, HEARTS);
    Card e(KING,CLUBS);
    Card f(ACE,SPADES);
    Card g(ACE,SPADES);
    ASSERT_TRUE(c>b);
    ASSERT_TRUE(c>=c1);
    ASSERT_FALSE(b>e);
    ASSERT_TRUE(a<f);
    ASSERT_FALSE(f<d);
    ASSERT_TRUE(a<=b);
    ASSERT_TRUE(f==f);
    ASSERT_TRUE(e!=c);  
    ASSERT_TRUE(f==g);
    ASSERT_FALSE(e==c);
}

TEST(test_Suit_next){
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS),SPADES);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS),DIAMONDS);
}

TEST(test_Card_less){
    Card ns(NINE, SPADES);
    Card td(TEN, DIAMONDS);
    Card jd(JACK,DIAMONDS);
    Card jh(JACK,HEARTS);
    Card qh(QUEEN, HEARTS);
    Card kc(KING,CLUBS);
    Card as(ACE,SPADES);
    ASSERT_FALSE(Card_less(ns,ns,DIAMONDS));
    ASSERT_TRUE(Card_less(ns,td,DIAMONDS));
    ASSERT_TRUE(Card_less(td,ns,SPADES));
    ASSERT_FALSE(Card_less(qh,jd,SPADES));
    ASSERT_TRUE(Card_less(qh,jd,HEARTS));
    ASSERT_FALSE(Card_less(as,jd,CLUBS));
    ASSERT_TRUE(Card_less(jd,as,SPADES));
    ASSERT_TRUE(Card_less(as,jd,HEARTS));
    ASSERT_FALSE(Card_less(as,kc,HEARTS));
    ASSERT_TRUE(Card_less(jd,jh,HEARTS));
}

TEST(test_cl_led){
    Card a(NINE, SPADES);
    Card b(JACK,DIAMONDS);
    Card c(JACK,SPADES);
    Card d(JACK,HEARTS);
    Card e(KING,CLUBS);
    Card f(ACE,SPADES);
    Card g(ACE,HEARTS);
    ASSERT_TRUE(Card_less(a,b,e,CLUBS));
    ASSERT_TRUE(Card_less(b,a,f,CLUBS));
    ASSERT_TRUE(Card_less(b,d,e,HEARTS));
    ASSERT_TRUE(Card_less(b,d,g,SPADES));
    ASSERT_TRUE(Card_less(e,a,f,HEARTS));
    ASSERT_TRUE(Card_less(e,c,a,HEARTS));
}

TEST(test_specific){
    Card js(JACK,SPADES);
    Card as(ACE,SPADES);
    ASSERT_TRUE(Card_less(js,as,js,string_to_suit("Hearts")));
}

// Add more test cases here

TEST_MAIN()

// Card a(NINE, DIAMONDS);
//     Card b(TEN, SPADES);
//     Card c(JACK,HEARTS);
//     Card d(QUEEN, DIAMONDS);
//     Card e(KING,SPADES);
//     Card f(ACE,CLUBS);
