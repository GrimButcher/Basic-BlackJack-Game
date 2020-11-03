#include <iostream>
#include<vector>
#include <algorithm>
#include<string>
#include<stdlib.h>
//cards in deck
std::vector<int> num_cards = {'2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};

//initializing functions
char rand_card();
int hand_val(std::vector<char> user_hand);
bool choice();

int main() {
	//setting up random value generator for rand_card function
	srand(time(NULL));

	bool end = false;
	int user_hand_val = 0;
	int computer_hand_val = 0;
	std::vector<char> dealer_hand;
	std::vector<char> user_hand;

	//greets and places first to cards in dealer and user
	std::cout<<"Welcome to Blackjack!!!\n";
	std::cout<<"Let's begin the game against the dealer!\n\n\n";
	for(int i = 0; i <= 1; i++){
		dealer_hand.push_back(rand_card());
		user_hand.push_back(rand_card());	
	}
	std::cout<<"This is the house hand: \n";
	std::cout<<dealer_hand[0]<<" and unknown!\n\n";
	std::cout<<"This is your hand: \n";
	std::cout<<"Card one: "<<user_hand[0]<<" Card two: "<<user_hand[1]<<"\n\n";
	
	/*asks user if they want more cards and gives if so,
	stops if user says so or if their hand val is greater than 21*/
	while(end == false && user_hand_val < 21){
		end = choice();
		if(end == false){
			user_hand.push_back(rand_card());
			for(auto c : user_hand)std::cout<<" "<<c;
			user_hand_val = hand_val(user_hand);
		}
	}
	//if the user busts shows that they lose
	if(user_hand_val > 21){
		std::cout<<"\nYou lose your bet.";
		exit(0);
	}
	//this is the computers hand that is being dealt with
	computer_hand_val = hand_val(dealer_hand);
	while(computer_hand_val < 18){
		dealer_hand.push_back(rand_card());
		computer_hand_val = hand_val(dealer_hand);
		std::cout<<"The dealer's hand ";
		for(auto c : dealer_hand)std::cout<<" "<<c;
		std::cout<<"\n\n";
	}
	//computer lose condition
	if(computer_hand_val > 21 || computer_hand_val < user_hand_val){
		std::cout<<"\nThe dealer loses, you gain money";
		exit(0);
	}//user win condition
	else{
		std::cout<<"\nThe dealer wins with: ";
		for(auto c : dealer_hand)std::cout<<c<<" ";
		std::cout<<" You lose your bet.";
	}
}
//generates random card
char rand_card(){
	int random_num = rand() % 12;
	return num_cards[random_num];
}

//counts the value of the cards
int hand_val(std::vector<char> user_hand){
	int sum = 0;
	for(char c : user_hand){
		if(isdigit(c))sum += ((int)c)-48;
		else if(isalpha(c) && c != 'A')sum+=10;
	}
	for(int d : user_hand)
		if(isalpha(d) && d == 'A')
			(sum + 11 > 21)?sum += 1:sum += 11;
	return sum;
}

//determines whether the user wants to continue or not
bool choice(){
	std::string choices;
	std::cout<<"\nDo you want a card? ";
	std::cin>>choices;
	std::transform(choices.begin(), choices.end(), choices.begin(), ::tolower);
	while(choices != "yes" && choices != "no"){
		std::cout<<"Pls input your card again.";
		std::cin>>choices;
		std::transform(choices.begin(), choices.end(), choices.begin(), ::tolower);
	}
	return choices == "no";
}

