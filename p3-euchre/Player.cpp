#include "Player.hpp"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>


class SimplePlayer: public Player   {
    public: 
        SimplePlayer(const std::string name)
        :n(name) {}

        //EFFECTS returns player's name
        const std::string & get_name() const override{
            return n;
        }

        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c) override{
            
            hand.push_back(c);
        }

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
                int round, Suit &order_up_suit) const override{
            int count = 0;

            if(round == 1){
                for(size_t i = 0; i<hand.size(); i++){
                    if(hand[i].is_face_or_ace() && 
                    hand[i].get_suit(upcard.get_suit()) == upcard.get_suit()){
                        count++;
                    }
                }
                if(count >1){
                    order_up_suit = upcard.get_suit();
                    return true;
                }
                else{ return false; }
            }
            
            if (round == 2 && is_dealer){
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            if(round == 2 && !is_dealer){
                for(int i = 0; i<hand.size();i++){
                    if(hand[i].is_face_or_ace() && 
                    hand[i].get_suit(Suit_next(upcard.get_suit())) 
                    == Suit_next(upcard.get_suit())){
                        count++;
                    }
                }
                if(count >=1){
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
            }
            return false;
         }

        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard) override{
            
            Card *low = &hand[0];
            int index = 0;
            for(size_t i = 1; i<hand.size(); i++){
                if(Card_less(hand[i],*low,upcard.get_suit())){
                low = &hand[i];
                index = i;
                }
            }
            if(!Card_less(upcard,*low, upcard.get_suit())){
                hand.erase(hand.begin()+index);
                add_card(upcard);               
            }
            
        }
        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump) override{
            int index;
            Card *temp = &hand[0];
            std::vector<Card> ytrump = {};
            std::vector<Card> ntrump = {};
            for(size_t i = 0; i<hand.size(); i++){
                if(hand[i].get_suit(trump) != trump){
                    ntrump.push_back(hand[i]);
                }
                else {
                    ytrump.push_back(hand[i]);
                }
            }
            if(!ntrump.empty()){
                Card *max = &ntrump[0];
                for(size_t i= 0; i<ntrump.size();i++){
                    if(Card_less(*max, ntrump[i],trump)){
                        max = &ntrump[i];
                    }
                }   
                temp = max;
                for(size_t i = 0; i<hand.size(); i++){
                    if(*temp == hand[i]){
                        index = i;
                    }
                }
                hand.erase(hand.begin()+index);
                return *temp;
            }
            else{
                Card *max = &ytrump[0];
                for(size_t i= 0; i<ytrump.size();i++){
                    if(Card_less(*max, ytrump[i],trump)){
                        max = &ytrump[i];
                    }
                }   
                temp = max;
                for(size_t i = 0; i<hand.size(); i++){
                    if(*temp == hand[i]){
                        index = i;
                    }
                }
                hand.erase(hand.begin()+index);
                return *temp;
            }
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump) override{ 
            int index; 
            Card *temp;
            std::vector<Card> yled = {};
            std::vector<Card> nled = {};
            for(size_t i = 0; i<hand.size();i++){
                if(hand[i].get_suit(trump) == led_card.get_suit(trump)){
                    yled.push_back(hand[i]);
                }
                else{
                    nled.push_back(hand[i]);
                }
            }
            if(!yled.empty()){
                Card *max = &yled[0];
                for(size_t i = 0; i<yled.size(); i++){
                    if(Card_less(*max,yled[i],led_card,trump)){
                        max = &yled[i];
                    }
                }
                temp = max;
                for(size_t i = 0; i<hand.size(); i++){
                    if(*temp == hand[i]){
                        index = i;
                    }
                }
                hand.erase(hand.begin()+index);
                return *temp;
            }
            else{
                Card *min = &nled[0];
                for(size_t i = 1; i<nled.size(); i++){
                    if(Card_less(nled[i],*min,led_card,trump)){
                        min = &nled[i];
                    }
                }
                temp = min; 
                for(size_t i = 0; i<hand.size(); i++){
                    if(*temp == hand[i]){
                        index = i;
                    }
                }
                hand.erase(hand.begin()+index);
                return *temp;
            }
            
        }
        private: 
            std::string n;
            std::vector<Card> hand;
};

class HumanPlayer: public Player{
    std::string n;
    std::vector<Card> hand;
    public:
        HumanPlayer(const std::string &name)
        :n(name) {}
         
        //EFFECTS returns player's name
        const std::string & get_name() const override{
            return n;
        }

        //REQUIRES player has less than MAX_HAND_SIZE cards
        //EFFECTS  adds Card c to Player's hand
        void add_card(const Card &c) override{
            hand.push_back(c);
            std::sort(hand.begin(),hand.end()); 
        }

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
                int round, Suit &order_up_suit) const override{
            print_hand();
            std::cout << "Human player " << n << ", please enter a suit, or \"pass\":\n";
            std::string decision;
            std::cin >> decision;

            if (decision != "pass") {
                order_up_suit = string_to_suit(decision);
                return true;
            }
         
         return false;
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard) override{
            print_hand();
            std::cout << "Discard upcard: [-1]\n";
            std::cout << "Human player " << n << ", please select a card to discard:\n";
            std::string index;
            std::cin >> index;
            if(stoi(index) != -1){
                hand.erase(hand.begin()+stoi(index));
                add_card(upcard);
            }
        }
        //REQUIRES Player has at least one card
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(Suit trump) override{
            print_hand();
            std::cout << "Human player " << n << ", please select a card:\n";
            std::string input;
            std::cin >> input;
            Card temp = hand.at(stoi(input));
            hand.erase(hand.begin()+stoi(input));
            return temp;

        }

        //REQUIRES Player has at least one card
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, Suit trump) override{
            //can we assume they won't cheat?
            print_hand();
            std::cout << "Human player " << n << ", please select a card:\n";
            std::string input;
            std::cin >> input;
            Card temp = hand.at(stoi(input));
            hand.erase(hand.begin()+stoi(input));
            return temp;
        }
    private:
        void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            std::cout << "Human player " << n << "'s hand: "
                << "[" << i << "] " << hand[i] << "\n";
}

};
//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    // We need to check the value of strategy and return 
    // the corresponding player type.
    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    // Repeat for each other type of Player
    if(strategy == "Human"){
        return new HumanPlayer(name);
    }
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}
//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}