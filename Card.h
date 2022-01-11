#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card
{
	public:
	string suit; //The cards' suit (Hearts, Diamonds, Spades, Clubs)
	int index;	//The index of the card. 1-13. 1st card = Ace, 13th card = King
	string face; //The face of the card. (e.g. 1, 2, A, K, Q, 10 ...etc.)
	int points;	 //How much points the card is worth in the game.
	int type;
	
	
	Card();
	
};

Card::Card(){

suit = "none";
index = 0;
face = "none";
face = "none";
points = 0;
type = 0; //val of 1 =  meldTEMP; val of 2 =  deadwoodTEMP;

}

#endif

