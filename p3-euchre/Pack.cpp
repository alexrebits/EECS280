#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <array> //check if i need all of these or what else i need

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(){
    next = 0;
    int i = 0;
    for(int s = SPADES; s<=DIAMONDS; s++){
        for(int r = NINE; r<=ACE; r++){
            Card temp(static_cast<Rank>(r),static_cast<Suit>(s)); 
            cards[i] = temp;
            i++;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
Pack::Pack(std::istream& pack_input){
    next = 0;
    string rank;
    string trash;
    string suit;
    int i =0;
    while(pack_input>>rank>>trash>>suit){
        Card temp(string_to_rank(rank),string_to_suit(suit));
        cards[i] = temp;
        i++;
    }
}

// REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    Card c = cards[next];
    next++;
    return c;
}


// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    array<Card,PACK_SIZE> temp; 
    for(int a = 0; a<7; a++){
        for(int f =0; f<PACK_SIZE/2; f++){ // first half of cards
        temp[(2*f)+1] = cards[f]; 
        }
        for(int s = PACK_SIZE/2; s<PACK_SIZE; s++){// second half of cards
            temp[2*(s-(PACK_SIZE/2))] = cards[s];
        }

        for(int i = 0; i<PACK_SIZE; i++){ //makes fills cards with the shuffled elements
            cards[i] = temp[i];
        }
    }
    reset();
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    return next==24;
}