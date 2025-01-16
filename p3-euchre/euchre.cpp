#include <iostream>
#include <fstream>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"
#include <cassert>
using namespace std;

class Game {
 public:
  Game(vector<Player*> players,Pack pack,bool shuf)
    : players(players), pack(pack), shuf(shuf){
      //do i have to check for invariants?
    }; //ctor
  void play(){ //call this while points < needed points to win
    play_hand();
  } //play hands
  int getPoints(int index){
    assert(index == 0 || index==1);
    return points.at(index);
  }


 private:
  vector<Player*> players;
  vector<int> tricksWon = vector(4,0);
  vector<int> points = vector(2,0);  
  Pack pack;
  int numDealer = 0; 
  int numLeader= 0;
  int numTrumper;
  int numHand = 0;
  Card up;
  Suit up_suit;
  bool shuf;
  
  // ...

  void shuffle(){
    pack.Pack::shuffle();
  }
  // 
  //MODIFIES: players (hands), the pack, up
  //EFFECTS: deals 5 cards to each player,sets the value of up, the suit of up_suit
  void deal(){ 
    cout<<*players.at(numDealer) << " deals"<<endl;
    for(int i = 0; i<4; i+=2){
        for(int j = 0; j<3; j++){
            players.at((numDealer + +1+i)%4)->add_card(pack.Pack::deal_one()); 
        }
        for(int k = 0; k<2; k++){
            players.at((numDealer + 2 + i) %4)->add_card(pack.Pack::deal_one());
        }
    }
    for(int i = 0; i<4; i+=2){
        for(int j = 0; j<2; j++){
            players.at((numDealer + i + 1)%4)->add_card(pack.Pack::deal_one()); 
        }
        for(int k = 0; k<3; k++){
            players.at((numDealer + 2 + i)%4)->add_card(pack.Pack::deal_one());
        }
    }
    Card u = pack.deal_one(); 
    up = u; 
    up_suit = up.get_suit();
    cout<< up << " turned up"<<endl;
  }
  //
  //MODIFIES: up_suit, changes the hand of the trump maker, numTrumper
  //EFFECTS: makes trump and keeps track of who made trump.

  
  void make_trump(){
    numLeader = numDealer +1;
    int i = numLeader;
    bool madeTrump = players.at((i)%4)->make_trump(up,(i)%4==numDealer,1,up_suit);

    while(!madeTrump && i<=numLeader +2){
      cout<<*players.at((i)%4)<<" passes"<<endl;
      i++;
      madeTrump = players.at((i)%4)->make_trump(up,(i)%4==numDealer,1,up_suit);
    }
    if(!madeTrump){
      cout<<*players.at((i)%4)<< " passes"<<endl;
      if(i==numLeader+3){//round two
        i=numLeader;
        madeTrump = players.at((i)%4)->make_trump(up,(i)%4==numDealer,2,up_suit);
        while(!madeTrump && i<=numLeader+2){
            cout<<*players.at((i)%4)<< " passes"<<endl;
            i++;
            madeTrump = 
            players.at((i)%4)->make_trump(up,(i)%4==numDealer,2,up_suit);
        }
        cout <<*players.at((i)%4) << " orders up " << up_suit << "\n" <<endl;
        numTrumper = (i)%4;
      }
    }
    else{ //round 1 selection 
        
        numTrumper = i%4;
        cout <<*players.at(numTrumper) << " orders up " << up_suit << "\n" <<endl;
        players.at(numDealer)->add_and_discard(up);
    }
    
  }
//
//MODIFIES: numLeader, tricksWon, players hands
//EFFECTS: each player plays one card and a winner is decided
  void play_trick(){ 
    vector<Card> trick(4);
    Card t = players.at(numLeader%4)->lead_card(up_suit);
    trick.at(numLeader%4) = t; //leads trick
    cout<<trick.at(numLeader%4) << " led by " << *players.at(numLeader%4)<<endl;
    for(int i = 1 +numLeader; i<4 +numLeader; i++){ //plays the other cards
        Card l = players.at(i%4)->play_card(t,up_suit);
        trick.at(i%4) = l;
        // cout<<up_suit<<endl;
        cout<<trick.at(i%4)<< " played by " <<*players.at(i%4)<<endl;
    }
    int maxInd = numLeader%4;
    
    Card *max = &trick.at(maxInd); //finding max
    for(size_t j = numLeader+1; j<numLeader+4; j++){
        if(Card_less(*max,trick.at(j%4),trick.at(numLeader%4),up_suit)){
            max = &trick.at(j%4);
            maxInd = j%4;
        }
    }
    tricksWon.at(maxInd)++;
    numLeader = maxInd;
    cout << *players.at(maxInd)<< " takes the trick"<<"\n"<<endl;
  }

  void add_up_score(){

    int team0 = tricksWon.at(0) + tricksWon.at(2);
    int team1 = tricksWon.at(1) + tricksWon.at(3);

    if(team0>team1){ //team0 won!
    cout<<*players.at(0) << " and "<<*players.at(2) <<" win the hand"<<endl;
      if(numTrumper%2 ==0){ //team0 took trump and won
        points.at(0)++;
        if(team0==5){ //march!
          points.at(0)++;
          cout<< "march!" <<endl;
        }
      }
      else{ //team1 took trump and lost; euchred!
        points.at(0)+=2;
        cout<< "euchred!"<<endl;
      }
    }
    else{ //team1 won!
      cout<<*players.at(1) << " and "<<*players.at(3) <<" win the hand"<<endl;
      // assert(team1>team0);
      if(numTrumper%2==1){ //team1 took trump
        points.at(1)++;
        if(team1==5){ //march!
          points.at(1)++;
          cout<< "march!" <<endl;
        }
      }
      else{ //team 0 took trump and lost, euchred!
        points.at(1)+=2;
        cout<< "euchred!"<<endl;
      }
    }
    cout<<*players.at(0)<<" and "<<*players.at(2)<<
    " have "<<points.at(0)<<" points"<<endl;
    cout<<*players.at(1)<<" and "<<*players.at(3)<<
    " have "<<points.at(1)<<" points\n"<<endl;
    tricksWon = vector(4,0);
  }
  //
  //MODIFIES: points, etc?
  //EFFECTS: plays one hand of euchre and adds up points
  void play_hand(){//shuffle, deal, make trump, play 5 tricks, score.
    if(shuf){
      shuffle();
    }
    else{
    pack.reset();
    }
    cout<< "Hand " << numHand << endl;
    deal();
    make_trump();
    numLeader = numDealer+1;
    for(int i = 0; i<5; i++){ //plays 5 tricks
        play_trick();

    }
    //scoring element
    add_up_score();
    numHand++;
    numDealer = (numDealer+1)%4;
  }
  
};
int main(int argc, char **argv) {
  if(argc !=12){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
  }
  string winPointsTemp = argv[3];
  int winPoints = stoi(winPointsTemp);
  if(!(winPoints >=1 && winPoints <=100)){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
  }
  string shuf = argv[2];
  if(shuf != "shuffle" && shuf != "noshuffle"){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
  }
  string types;
  for(int i = 5; i <=11; i+=2){
    types = argv[i];
    if(types != "Simple" && types != "Human"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
    }
  }

  string filename = argv[1];
  ifstream fin(filename);
  Pack pack(fin);
  if(!fin.is_open()){
    cout << "Error opening " << filename << endl;
    return -1;
  }

  for(int i = 0; i <argc; i++){
    cout <<argv[i] << " ";
  }
  cout<<endl;

  //make a vector of players
  vector<Player*> p;
  for(int i = 4; i <=11; i+=2){
    p.push_back(Player_factory(argv[i],argv[i+1]));
  }
  //make the pack file in to a pack
  

  //amount of points needed to win
  //winPoints
  //make a game with these details
  Game game(p,pack,shuf=="shuffle");

  while((winPoints > game.getPoints(0) && winPoints>game.getPoints(1))
  ||game.getPoints(1)== game.getPoints(0)){//in case of tie??
    game.play();
  }
  if(game.getPoints(0)>game.getPoints(1)){
    cout<<*p.at(0)<<" and "<<*p.at(2)<< " win!"<<endl;
  }
  else{
    cout<<*p.at(1)<<" and "<<*p.at(3)<< " win!"<<endl;
  }

  for (size_t i = 0; i < p.size(); ++i) { //delete all players
  delete p[i];
  }
}

