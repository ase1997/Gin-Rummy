/*
	ECGR 2104 - 01
	Dr. Arun Ravindran
	
	Final Project - Gin Rummy
	
	Dmitri Gutuleac
	Khoa Do
	Shanle Yao
	Kyle Marks
*/


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm> 
#include <ctime>
#include <cstdlib>



#include "Player.h" //Header file for the Player Class.
#include "Card.h" //Header file for Card Class.

using namespace std;




//GLOBAL VARIABLES AND VECTORS
void setupCards();
void shuffleCards();
void makeHand(int num, int player); //make hand: num = number of cards, player = for which player? 1 = Player 1, 2 = Player 2
void numInStack();
void makeDiscard(); //Creates the discard pile
//void startGame(); //Initiates the game
void displayCards();
void playerChoice();
void discardCard();
void GameTimeP1();
void GameTimeP2();
void cpMove();
void displayResult();
void checkGame();

//int turnCounter = 1; //This will be available to all functions within main.cpp.
//Convention: Odd numbers = Player 1  goes. Even Numbers: Player 2 goes.




Player p1; //Human Player
Player p2; //Computer Player


Card H1, H2, H3, H4, H5, H6, H7, H8, H9, H10, H11, H12, H13,
      D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13,
      C1, C2, C3, C4, C5, C6, C7, C8, C9,C10, C11, C12, C13,
	  S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13;

vector <Card> cards; //The 52 cards in the deck. Original Vector. This vector does not get modified. The definition of a deck. 
vector <Card> stack; //The 52 playing cards. Players pull/place cards from/to here. This is the playing deck of cards. 
vector <Card> discard; //Discard Pile of the game.

//END OF GLOBAL VARIABLES AND VECTORS


int main ()
{

			setupCards();   //Go ahead and initialize the cards and store them in the vector 'cards' which won't be touched.
	        stack=cards;    //Make a copy of the vector above. This vector of cards will be used to play the game. 
	        shuffleCards(); //Shuffle the cards.
	        numInStack();
		    makeHand(10,1);
	        makeHand(10,2);
  cout << "Welcome to Gin Rummy!" << endl << endl;
  cout << "Press 1 to START" << endl << "Press 2 to EXIT \n\n";
  cout << ">> ";
    int f;
    cin >> f;
    cin.ignore();   
    
    while (f != 2)
	{
			
			
			
			GameTimeP1();
	        //displayCards();
	        
	      //  p1.showCards();
			playerChoice();
	        makeDiscard();
	        discardCard();
			
			GameTimeP2();
			// cp's decision to choose a card either in stack or discard pile
			// by generating radondom function (ex: generate an int from 1-2)
			// 1: cp chooses from stack, 2: cp chooses from discard pile
			// same method makes cp randomly pick a card in deadwoods and discard that card
			cpMove(); 
			checkGame();

			
	// only P1 has privilege to end game by hitting GIN
    cin.ignore();   
	}
		

 		if (f == 2)
		{
			// after game ends, display both P1's and cp's hand 
		
			//calculate points based on deadwoods and dispay winner
			displayResult();
	            cout << "Bye!" << endl;
	            return 0;
	    }
}

//setupCards() initializes all the cards and populates them in the array.
//This array is then copied to the 'stack' array where the cards
//of the game will be dealt from. The original array will remain untouched.

void setupCards()
{
//Hearts from cards[0]-cards[12]
cards.push_back(H1);
cards.push_back(H2);
cards.push_back(H3);
cards.push_back(H4);
cards.push_back(H5);
cards.push_back(H6);
cards.push_back(H7);
cards.push_back(H8);
cards.push_back(H9);
cards.push_back(H10);
cards.push_back(H11);
cards.push_back(H12);
cards.push_back(H13);
//Diamonds from cards[13]-cards[25]
cards.push_back(D1);
cards.push_back(D2);
cards.push_back(D3);
cards.push_back(D4);
cards.push_back(D5);
cards.push_back(D6);
cards.push_back(D7);
cards.push_back(D8);
cards.push_back(D9);
cards.push_back(D10);
cards.push_back(D11);
cards.push_back(D12);
cards.push_back(D13);
//Clubs from cards[26]-cards[38]
cards.push_back(C1);
cards.push_back(C2);
cards.push_back(C3);
cards.push_back(C4);
cards.push_back(C5);
cards.push_back(C6);
cards.push_back(C7);
cards.push_back(C8);
cards.push_back(C9);
cards.push_back(C10);
cards.push_back(C11);
cards.push_back(C12);
cards.push_back(C13);
//Spades from cards[39]-cards[51]
cards.push_back(S1);
cards.push_back(S2);
cards.push_back(S3);
cards.push_back(S4);
cards.push_back(S5);
cards.push_back(S6);
cards.push_back(S7);
cards.push_back(S8);
cards.push_back(S9);
cards.push_back(S10);
cards.push_back(S11);
cards.push_back(S12);
cards.push_back(S13);


for (int i = 0; i <= 12; i++) //For Suit of Hearts
{
cards[i].suit = "Hearts";
cards[i].index = (i+1);

if (i == 0)
{
	cards[i].face = "A";
	cards[i].points = 1;
}
else if (i == 10)
{
	cards[i].face = "J";
	cards[i].points = 10;

}
else if (i == 11)
{
	cards[i].face = "Q";
	cards[i].points = 10;
}
else if (i == 12)
{
	cards[i].face = "K";
	cards[i].points = 10;
}
else
{
	cards[i].points= i+1;
	cards[i].face= to_string(i+1);
}
}

for (int i = 13; i <= 25; i++) // For suit Diamonds
{
cards[i].suit = "Diamonds";
cards[i].index = (i-12);

if (i == 13)
{
	cards[i].face = "A";
	cards[i].points = 1;
}
else if (i == 23)
{
	cards[i].face = "J";
	cards[i].points = 10;

}
else if (i == 24)
{
	cards[i].face = "Q";
	cards[i].points = 10;
}
else if (i == 25)
{
	cards[i].face = "K";
	cards[i].points = 10;
}

else
{
	cards[i].points= i-12;
	cards[i].face= to_string(i-12);
}
}

for (int i = 26; i <= 38; i++) // For suit Clubs
{
cards[i].suit = "Clubs";
cards[i].index = (i-25);

if (i == 26)
{
	cards[i].face = "A";
	cards[i].points = 1;
}
else if (i == 36)
{
	cards[i].face = "J";
	cards[i].points = 10;

}
else if (i == 37)
{
	cards[i].face = "Q";
	cards[i].points = 10;
}
else if (i == 38)
{
	cards[i].face = "K";
	cards[i].points = 10;
}

else
{
	cards[i].points= i-25;
	cards[i].face= to_string(i-25);
}
}

for (int i = 39; i <= 51; i++) // For suit Spades
{
cards[i].suit = "Spades";
cards[i].index = (i-38);

if (i == 39)
{
	cards[i].face = "A";
	cards[i].points = 1;
}
else if (i == 49)
{
	cards[i].face = "J";
	cards[i].points = 10;

}
else if (i == 50)
{
	cards[i].face = "Q";
	cards[i].points = 10;
}
else if (i == 51)
{
	cards[i].face = "K";
	cards[i].points = 10;
}
else
{
	cards[i].points= i-38;
	cards[i].face= to_string(i-38);
}
}





}
	
//Shuffles the 'stack' deck of cards. The origianl 'cards' 
//vector is untouched. 
void shuffleCards(){

		srand(time(NULL));
		random_shuffle(stack.begin(),stack.end());
		
}



// makeHand' runs initially to create two sets of hands for the two players.
//This function is only ran once initially in the beginning of the program. 
//Num = number of cards that need to be removed from the stack
//player = the player for which the hand is being created for. 
void makeHand(int num, int player){

//If passed value for 'player' = 1:
if (player == 1){

vector<Card> hnd1(stack.begin(), stack.begin() + (num));
stack.erase(stack.begin(), stack.begin() + (num));

p1.hand = hnd1;

hnd1.clear();

}

//If passed value for 'player' = 2:
else if (player == 2){
vector<Card> hnd2(stack.begin(), stack.begin() + (num));
stack.erase(stack.begin(), stack.begin() + (num));

p2.hand = hnd2;
hnd2.clear();
}

}

void makeDiscard() //Creates the discard pile
{
    vector<Card> disc(stack.begin(), stack.begin() + 1);
    stack.erase(stack.begin(), stack.begin() + 1);
    discard = disc;
    disc.clear();
    
}

//numInStack checks to see how many cards are remaining in the stack.
void numInStack(){
	
	cout << "Cards remaining in the stack: " << stack.size() << endl;
}





//Where the game is actually going to be played.



void GameTimeP1(){
	
    p1.findMelds();
    makeDiscard();
    displayCards();
    
}

void GameTimeP2(){
	
    p2.findMelds();

}



void checkGame(){
		
	 if (p1.playerScore() == 0)
    {
    	//the user has reached GIN
    	cout << "GIN!!!" << endl;
    	
    	cout << "Player 1 Has Won The Game!" << endl;
    	
    	
    	cout << "Player 1 Cards listed below: " << endl;
    	p1.showCards();
    	
    	cout << "Player 2 Cards listed below: " << endl;
    	p2.showCards();
    	
    	exit(0);
	}
    
        if (p2.playerScore() == 0)
    {
    	//the user has reached GIN
    	cout << "GIN!!!" << endl;
    	
    	cout << "Player 2 Has Won The Game!" << endl;
    	
    	
    	cout << "Player 2 Cards listed below: " << endl;
    	p1.showCards();
    	
    	cout << "Player 1 Cards listed below: " << endl;
    	p2.showCards();
    	
    	exit(0);
	}
	
		if (stack.size() <= 2){
			cout << "Cards in stack have ran out. Player 1 and Player 2 are tied." << endl;
			exit (0);
		}
}


void displayCards()
{
      
    if(discard.size() == 0){
        cout << "Discard Pile is Empty" << endl;
        cout << "----------------------------------" << endl;
    }
    else{
        cout << endl << "Discard Pile: " << discard.back().face <<" " << discard.back().suit << endl;
        cout << "----------------------------------" << endl;
    }
}



void playerChoice()
{
 string plyrChoice;	//Stores the player’s option of stock or discard

	bool choice = false;

	while(choice == false){		//Runs until the player enters a valid response
	    cout << "Pull from stock pile or discard pile." << endl;
	    cout << "Input('stock' or 'discard'): ";
	    cin >> plyrChoice;		//Player will enter whether they pull from the stock or discard pile
	
    //If the player enters “stock”, they will pull the card on top of the stock pile    
    if (plyrChoice == "stock" || plyrChoice == "Stock" || plyrChoice == "STOCK"){
        p1.hand.push_back(stack.back());
        stack.pop_back();
        
        p1.findMelds();
        displayCards();
        
	    choice = true;			//11Player has entered a valid response
	    break;
    }
	    
    //If the player enters “discard”, they will pull the card on top of the discard pile
    else if (plyrChoice == "discard" || plyrChoice == "Discard" || plyrChoice == "DISCARD"){
        p1.hand.push_back(discard.back());
        discard.pop_back();
        p1.findMelds();        
        displayCards();
	    choice = true;			//Player has entered a valid response
	    break;
	}
	
    //If the player inputs an incorrect value, they will be prompted to input again    
    else {
	        cout << "Please input a correct statement stock/discard" << endl << endl;
	     }
	}   
}


//Getting rid of a card.
void discardCard()
{
     cout << "Input the number of the card you would like to discard." << endl;
     int i;
     bool response = false;
     while(response == false)
     {
         cin >> i;
         if(i <= 11)
         {
            discard.push_back(p1.hand[i-1]);
            p1.hand.erase(p1.hand.begin()+i-1);
            displayCards();
            response = true;
         }
         else
         {
             cout << "Please input a valid response." << endl;
             cout << "----------------------------------" << endl;
             cout << "Input the number of the card you would like to discard." << endl;
         }
     }
}


void cpMove()
{
	unsigned seed = time(0);
	srand(seed);
	 int plyrChoice = (rand() % (2 - 1 + 1)) + 1; //generate a number from 1 to 2

	bool choice = false;

/*	while(choice == false){		//Runs until the player enters a valid response
	    cout << "Pull from stock pile or discard pile." << endl;
	    cout << "Input('stock' or 'discard'): ";
	    cin >> plyrChoice;*/		//Player will enter whether they pull from the stock or discard pile
	
    //If the player enters “stock”, they will pull the card on top of the stock pile    
    if (plyrChoice == 1){
        p2.hand.push_back(stack.back());
        stack.pop_back();
        
       // displayCards();
        
	    choice = true;			//11Player has entered a valid response
	   // break;
    }
	    
    //If the player enters “discard”, they will pull the card on top of the discard pile
    else if (plyrChoice == 2){
        p2.hand.push_back(discard.back());
        discard.pop_back();
        displayCards();
	    choice = true;			//Player has entered a valid response
	    //break;
	}
	
    //If the player inputs an incorrect value, they will be prompted to input again    
   /* else {
	        cout << "Please input a correct statement stock/discard" << endl << endl;
	     }
	}  */ 
	
	
	vector<Card> disc(stack.begin(), stack.begin() + 1);
    stack.erase(stack.begin(), stack.begin() + 1);
    discard = disc;
    disc.clear();
    
    int plyrChoice1 = (rand() % (11 - 1 + 1)) + 1; //generate a number from 1 to 11
    
     bool response = false;
     while(response == false)
     {
         if(plyrChoice1 <= 11)
         {
         	
            discard.push_back(p2.hand[plyrChoice1-1]);
            p2.hand.erase(p2.hand.begin()+plyrChoice1-1);
           // displayCards();
            response = true;
         }
	}
}

void displayResult()
{
	cout <<"PLAYER 1 HAND" << endl;
	p1.showCards();
	
	cout <<" \n\n\n PLAYER 2 HAND" << endl;
	p2.showCards();
	
}







