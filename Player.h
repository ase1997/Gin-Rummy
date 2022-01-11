#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include<iostream>
#include <string>
#include <algorithm>
#include "Card.h"

//--------------Beginning of Program----------------------
using namespace std;
void sortIndex(vector<Card>& deck); //This will sort the user's hand by index value of card
void sortSuit(vector<Card>& deck); //This will sort the user's hand by suit.
void findSets(vector<Card>& deck); //This finds all the Melds that exist in the player's hand.
void findRuns(vector<Card>&deck);
void removeMelds(vector<Card> &deck);
void removeWood(vector<Card> &deck);
void printCards(vector<Card>&deck); //Prints all the necessary card information from a passed vector of CARD-type objects.
int cardPoints(vector<Card>&deck); //Fucntion accepts vector of cards and determines the total points of the given vector.


class Player{

	public:
		void showCards(); //Shows the player's card.
		int playerScore();	//Holds the player's deadwood score.
		void findMelds(); //Will find all the melds of the player's hand
		vector<Card> hand; //The player's cards
		void displayMelds(); //This will COUT all of the user's meld's in a section of its own.
		void displayDeadwood(); //'                             deadwood        ' in a section of its own.
  		void setProperties(vector<Card> &deck); //sets the card properties that are later used to determine whether a ccard belongs to a meld.

};


int Player::playerScore(){
	
	int k = 0;
	for (int i=0; i<hand.size();i++){
		if(hand[i].type == 2){
			k = k+hand[i].points;
			
		}
	}
	
	return k;
}


void Player::setProperties(vector<Card> &deck){

	int i = 0;
	while (i<deck.size()){

		string cFace = deck[i].face;
		string cSuit = deck[i].suit;
		int cIndex = deck[i].index;
		int cPoints = deck[i].points;
		int cType = deck[i].type;

		for (int j=0; j<hand.size(); j++)
		{

		if (hand[j].type !=0){}

		if ((hand[j].face == cFace) && (hand[j].suit == cSuit) && (hand[j].index == cIndex)){
			hand[j].type = cType;
		}

		}

		i++;
	}
		}

//shows deadwood cards of the player
void Player::displayDeadwood(){
	vector<Card>vec_DEAD;
	int i = 0;
while (i<hand.size()){
	if (hand[i].type == 2){
		
		vec_DEAD.push_back(hand[i]);
	//	cout << hand[i].face << "-"<< hand[i].suit << "   "<<endl;
	}
	i++;
}
	sortSuit(vec_DEAD);
	
	if (vec_DEAD.size() == 0){
		cout << "\n\nNo DEADWOOD REMAINING\n" << endl;
	}
	
	else {
	cout << "\n\n\nYour Deadwood Pile"<<endl;
	cout << "-------------------" <<endl;

	for (int m = 0; m<vec_DEAD.size(); m++){
		cout << vec_DEAD[m].face << "-" << vec_DEAD[m].suit << "  " << endl;
		}
		

	}
	}



//shows the Melds of the play'ers hand.
void Player::displayMelds(){
vector<Card>vec_MELDS;
int i = 0;
while (i<hand.size()){
	if (hand[i].type == 1){
		vec_MELDS.push_back(hand[i]);
		cout << hand[i].face << "-"<< hand[i].suit << "   "<<endl;
	}
	i++;
}

		sortIndex(vec_MELDS);
		if (vec_MELDS.size() == 0){
			cout << "\n\nYou have no melds at this time." << endl;
		}
		
		else{

		cout << "\n\n\nYour Melds Pile"<<endl;
		cout << "---------------" << endl;
		for (int m = 0; m<vec_MELDS.size(); m++)
		{
			cout << vec_MELDS[m].face << "-" << vec_MELDS[m].suit << endl;

   			

		}
		
	}
}






//ssindex is a comparator that sorts the array based on the card's index.
bool sindex(const Card &c1, const Card & c2)
{

if (c1.index < c2.index) return true;
if (c2.index < c1.index) return false;

if (c1.suit < c2.suit) return true;
if (c2.suit < c1.suit) return false;


}


//ssuit is a comparator that sorts the array based on the card's suit.
bool ssuit(const Card &c1, const Card & c2)
{
if (c1.suit < c2.suit) return true;
if (c2.suit < c1.suit) return false;

if (c1.index < c2.index) return true;
if (c2.index < c1.index) return false;
}



//Sort players cards by index.
void sortIndex(vector<Card>&deck){

sort(deck.begin(), deck.end(), sindex);

}

//Sort players cards by index.
void sortSuit(vector<Card>&deck){

sort(deck.begin(), deck.end(), ssuit);

}


void Player::showCards(){
	cout << "----------------------------------" << endl;
	cout << "--------Deadwood Score: " << playerScore() << endl;
    cout << "--------Hand is listed below ";
    cout << "\n----------------------------------" << endl;
    sortSuit(hand);
    for (int i = 0; i<hand.size(); i++){
    cout << "["<< i+1 <<"]-------->" <<" " << hand[i].face << " " << hand[i].suit << endl;
    }
	}


void Player::findMelds(){
//Resetting the 'card.type' attribute to 0 for every card in the deck to perform the meld algorithm.
for (int i = 0; i<hand.size(); i++){
	hand[i].type = 0;
}




////////STARTING SETS////////////
vector<Card> tempSHand = hand;
vector<Card> tempRHand = hand;

sortIndex(tempSHand); 					//Sort the temporary hand  by index to check for sets.
findSets(tempSHand); 					//Passed by reference and modifies the 'card.type' attribute to determine deadwood or meld.
vector<Card> tempSWood = tempSHand;
removeMelds(tempSWood);
vector<Card> tempSet = tempSHand;
removeWood(tempSet);

//////////DONE WITH SETS///////////


//////STARTING RUNS/////////////////


sortSuit(tempRHand);        //Sort the tepmorary hand by suit to check for runs.
findRuns(tempRHand);			//Passed by reference and modifies the 'card.type' attribute to determine deadwood or meld.

vector<Card> tempRWood = tempRHand;


removeMelds(tempRWood);
vector<Card> tempRun = tempRHand;
removeWood(tempRun);

int totalDeadwood = cardPoints(hand);

int sDWpnts = cardPoints(tempSWood); //How much deadwood a SET config. would leave
int rDWpnts = cardPoints(tempRWood); //How much deadwood a RUN config would leave.

// cout << "Total Dead Wood: " << totalDeadwood << endl;
// cout << "Set Dead Wood: " << sDWpnts << endl;
// cout << "Run Dead Wood: " << rDWpnts << endl;

int sPnts = cardPoints(tempSet);
int rPnts = cardPoints(tempRun);


if (sDWpnts < rDWpnts){


	setProperties(tempSet);//If set has leess deadwood, take its deadwood and run it to find any runs.
	sortSuit(tempSWood);
	findRuns(tempSWood);
	setProperties(tempSWood);
}

else{


	setProperties(tempRun);
	sortIndex(tempRWood);
	findSets(tempRWood);
	setProperties(tempRWood);

	}

Player::displayMelds();
Player::displayDeadwood();




}




int cardPoints(vector<Card> &deck){
	int i = 0;
	int k = 0;
	while (i<deck.size()){
		k = deck[i].points + k;
		i++;
	}

	return k;
}

//Remove the 'set' elements from the array.
void removeMelds(vector<Card>&deck){

	if (deck.empty()==false){
		for(int i = deck.size()-1; i>=0; i=i-1){
			if(deck[i].type == 1){
				deck.erase(deck.begin() + i);
			}
		}
	}


}
//Remove the 'deadwood' of 'set' meld from the array.
void removeWood(vector<Card> &deck){
		if (deck.empty()==false){
		for(int i = deck.size()-1; i>=0; i=i-1){
			if(deck[i].type == 2){
				deck.erase(deck.begin() + i);
			}
		}
	}

}





void findSets(vector<Card> &deck){
	int i = 0; //The card we're comparing everything too.

//	Card* deck[i],deck[i+1],deck[i+2],deck[i+3]; //Initialize the four cards we'll be workin with.

	while (i<=deck.size()-3){ //If there are at least 4 cards remaining.
		//cout << "Currently looking at card # " << i+1 << endl;
		//cout << "At least four cards remaining \n";

		if (deck[i].index == deck[i+1].index){
		//	cout << "First two match, checking third one \n";

			 if (deck[i+1].index == deck[i+2].index){
			//	cout << "Third one matches, checking fourth one \n";
			 	//deck[i+1].index == deck[i+2].index == | deck[i].index [SET OF 3] Check if card 4 is equal.
				 if (deck[i+2].index == deck[i+3].index){
				 //	cout << "Fourth one matches, storing in SET vector \n";

					deck[i].type = 1;
					deck[i+1].type = 1;
					deck[i+2].type = 1;
					deck[i+3].type = 1;



				 	i=i+4;

			 		//deck[i+2].index == deck[i+3].index == deck[i+1].index == deck[i].index ALL FOUR CARDS ARE EQUAL [SET OF 4]

				 	//All four cards matched.


				 }

				 else{

			//	 	cout << "Fourth card doesn't match. Storing only 3 cards into the SET vector\n";

				 	//Only cards 1 and 2 and 3 matched. = SET OF 3. -> MELD
					deck[i].type = 1;
					deck[i+1].type = 1;
					deck[i+2].type = 1;

				 	i=i+3;
				 }
			 }
			 else{

			 	//Only cards 1 and 2 matched. SET of 2 = no set. -> move to deadwood.
			 //	cout << "Third card doesn't match. Store 2 cards into the sWood vector \n";
				deck[i].type = 2;
				deck[i+1].type = 2;


			 	i=i+2;

			 }
		}
		else{
			//Cards 1 and 2 don't match. -> Deadwood -> Move to next index.
		//	cout << "This card doesn't match the next card. Store it in sWood vector \n";
			deck[i].type = 2;

			i++;
		}

		}

		if (i>=deck.size()-4){ //There are less than 4 cards remaining in the vector.

		//	cout << "***There are less than four cards remaining*** \n";

			int numLeft = (deck.size()-i); //How many cards remain for us to check?
			switch(numLeft){
				case 1: //1 card left
	//			cout << "*One card remains \n";

					deck[i].type = 2;

	//				cout << "Storing remaining card in sWood vector\n";
					break;
				case 2: //2 cards left
	//			cout << "*Two cards remain \n";
					deck[i].type = 2;

					deck[i+1].type = 2;

	//			cout << "Storing two remaining cards into sWood vector \n";

					break;
				case 3: //3 cards left
	//			cout << "*Three cards remain \n";

					if (deck[i].index == deck[i+1].index == deck[i+2].index){

	//					cout << "All three cards are equal. Storing in SET vector. \n";
						//Cards are a set of 3

						deck[i].type = 1;
						deck[i+1].type = 1;
						deck[i+2].type = 1;
					}

					else{
	//					cout <<"Three cards don't match. Storing in sWood vector \n";
						//All three cards are deadwood.
						deck[i].type = 2;
						deck[i+1].type = 2;
						deck[i+2].type = 2;
						break;
					} //end of switch cases
				 //end of else statement





						}
					}

}



void findRuns(vector<Card> &deck){

	sortSuit(deck);
	int i = 0; //The card we're comparing everything too.
	while (i<=deck.size()-3){ //If there are at least 4 cards remaining.
		// cout << "Currently looking at card # " << i+1 << endl;
		// cout << "At least four cards remaining \n";

		if ((deck[i].index == (deck[i+1].index -1)) && (deck[i].suit == deck[i+1].suit)){

			// cout << "First two match, checking third one \n";

			 if ((deck[i+1].index == (deck[i+2].index -1)) && (deck[i+1].suit == deck[i+2].suit)){
				// cout << "Third one matches, checking fourth one \n";
			 	//deck[i+1].index == deck[i+2].index == | deck[i].index [SET OF 3] Check if card 4 is equal.
			 if ((deck[i+2].index == (deck[i+4].index -1)) && (deck[i+2].suit == deck[i+4].suit)){
				 	// cout << "Fourth one matches, storing in SET vector \n";
				 	deck[i].type=1;
				 	deck[i+1].type=1;
				 	deck[i+2].type=1;
				 	deck[i+3].type=1;

				 	i=i+4;

			 		//deck[i+2].index == deck[i+4].index == deck[i+1].index == deck[i].index ALL FOUR CARDS ARE EQUAL [SET OF 4]

				 	//All four cards matched.


				 }

				 else{

				 	// cout << "Fourth card doesn't match. Storing only 3 cards into the SET vector\n";

				 	//Only cards 1 and 2 and 3 matched. = SET OF 3. -> MELD

					deck[i].type = 1;
					deck[i+1].type = 1;
					deck[i+2].type = 1;

				 	i=i+3;
				 }
			 }
			 else{

			 	//Only cards 1 and 2 matched. SET of 2 = no set. -> move to deadwood.
			 	// cout << "Third card doesn't match. Store 2 cards into the sWood vector \n";
				deck[i].type = 2;
				deck[i+1].type = 2;
			 	i=i+2;

			 }
		}
		else{
			//Cards 1 and 2 don't match. -> Deadwood -> Move to next index.
			// cout << "This card doesn't match the next card. Store it in sWood vector \n";
			deck[i].type = 2;
			i++;
		}

		}

		if (i>=deck.size()-4){ //There are less than 4 cards remaining in the vector.

			// cout << "***There are less than four cards remaining*** \n";

			int numLeft = (deck.size()-i); //How many cards remain for us to check?
			switch(numLeft){
				case 1: //1 card left
				// cout << "*One card remains \n";


					deck[i].type = 2;

					// cout << "Storing remaining card in sWood vector\n";
					break;
				case 2: //2 cards left
				// cout << "*Two cards remain \n";
					deck[i].type = 2;
					deck[i+1].type = 2;


				// cout << "Storing two remaining cards into sWood vector \n";

					break;

				case 3: //3 cards left

					// cout << "*Three cards remain \n";
					deck[i] = deck[i];
					deck[i+1] = deck[i+1];
					deck[i+2] = deck[i+2];


					int c1Index = (deck[i].index);
					int c2Index = (deck[i+1].index)-1;
					int c3Index = (deck[i+2].index)-2;

					string c1Suit = deck[i].suit;
					string c2Suit = deck[i+1].suit;
					string c3Suit = deck[i+2].suit;

					if (c1Index == c2Index == c3Index){ //Indexes Match

							if ((c1Suit.compare(c2Suit)) && (c1Suit.compare(c3Suit))){ //Suits Match
								// cout << "All three cards are equal. Storing in SET vector. \n";
								//Cards are a set of 3
								deck[i].type = 1;
								deck[i+1].type = 1;
								deck[i+2].type = 1;}


							else{//The suits don't match
								// cout <<"Three cards don't match. Storing in sWood vector \n";
								//All three cards are deadwood.

								deck[i].type = 2;
								deck[i+1].type = 2;
								deck[i+2].type = 2;

								}
							}


					 else{
						// cout <<"Three cards don't match. Storing in sWood vector \n";
						//All three cards are deadwood.
							deck[i].type = 2;
							deck[i+1].type = 2;
							deck[i+2].type = 2;


						break;
						} //end of switch cases
					}



							}
							}



//Prints absoluately all the details regarding the vector of cards passed to the function.
void printCards(vector<Card>&deck){
	int i = 0;
	while (i<deck.size()){

		cout << "|Index: " <<  deck[i].index << " |Face: " << deck[i].face << "|Suit: " << deck[i].suit << endl;
		cout << "|Points: " << deck[i].points << "===|Type===: " << deck[i].type << endl <<endl;
		i++;
	}


}




#endif

