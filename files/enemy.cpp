// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// enemy.cpp

using namespace std;
#include<iostream>
#include<fstream>
#include"enemy.h"

Enemy::Enemy(string newName, string newType){
	name = newName;
	type = newType;
	attackPower = 0;
	dropsSize = 0;
	for(int i = 0; i < 5; i++){
		drops[i] = "";
		dropChance[i] = 0;
	}
	getStats(newType + ".txt");	// Adds the file extension to the end of the job name to form the actual filename.
}

Enemy::Enemy(){

}

Enemy::~Enemy(){

}

// Returns the enemy's name.
string Enemy::getName(){
	return name;
}

// Sets the enemy's name.
void Enemy::setName(string n){
	name = n;
}

// Returns the enemy's health.
int Enemy::getHealth(){
	return health;
}

// Sets the enemy's health.
void Enemy::setHealth(int n){
	if(n <= maxHealth){	// Health cannot be greater than the max.
		if(n < 0){	// Health cannot be less than zero, so sets it to 0.
			health = 0;
		}
		else{
			health = n;
		}
	}
	else{
		health = maxHealth;	// If it is greater than the max, sets it equal to the max.
	}
}

// Gets the enemy's max health.
int Enemy::getMaxHealth(){
	return maxHealth;
}

// Gets the enemy's type.
string Enemy::getType(){
	return type;
}

// Gets the enemy's attack.
int Enemy::getAttackPower(){
	return attackPower;
}

// Drops items into the player's inventory.
Hero Enemy::dropItem(Hero player){
	// Stores the dropped items to show the player what dropped.
	string droppedItems[4];
	int droppedItemsSize = 0;
	for(int i = 0; i < 3; i++){	// Initializes the droppedItems array.
		droppedItems[i] = "";
	}
	for(int i = 0; i < dropsSize; i++){	// Loops for each of the enemy's possible drops.
		bool proceed = true;	// Flags whether the player already has a key so that they don't have more than one. There should only be one key on each floor.
		float randomChoice = ((int)(rand() % 99));	// Generates a random number between 0 and 99.
		randomChoice = randomChoice / 100;	// Divides the number by 100 so that it's between 0.00 and 0.99.
		if(player.getItemPosition(drops[i]) > -1 && drops[i] == "key"){	// If the drop is a key, and the player has or has had a key before, proceeds.
			if(player.getInventoryQuantity(player.getItemPosition(drops[i])) > 0){	// If the player currently has more than zero keys in their inventory, flags proceed to false.
				proceed = false;	// Prevents the player from getting more than one key by stopping its chances of dropping.
			}
		}
		// If the random number is less than or equal to the drop chance, proceeds to drop it. (25% chance a number between 0 and 1 will be below 0.25)
		if(dropChance[i] >= randomChoice && proceed == true){
			droppedItems[droppedItemsSize] = drops[i];	// Stores the drop in the droppedItems array.
			int found = 0;	// Stores whether the player already has that item in their inventory.
			for(int a = 0; a < player.getInventorySize(); a++){	// Searches the player's inventory.
	    		if(droppedItems[droppedItemsSize] == player.getInventory(a) && found == 0){	// Checks to see if the item is found in the inventory.
	    			player.setInventoryQuantity(player.getInventoryQuantity(a) + 1, i);	// Increases the quantity of the item by one.
	    			found = 1;	// Flags that the item has been found in the inventory.
	    		}
			}
			if(found == 0){	// If the item is not yet in the inventory, adds it.
				player.setInventory(drops[i], player.getInventorySize());	// Adds the item to the inventory.
				player.setInventoryQuantity(1, player.getInventorySize());	// Sets the quantity of the new item to 1.
				player.setInventorySize(player.getInventorySize() + 1);	// Increases the inventory size, as a new item was just added.
			}
			droppedItemsSize++;	// Because an item was dropped, increments droppedItemsSize.
		}
	}
	if(droppedItemsSize > 0){	// If the enemy drops something, start the "dropped" sentence.
		cout << name << " has dropped";
	}
	for(int b = 0; b < droppedItemsSize; b++){	// Loops through every dropped item.
		// Changes the name from the actual item's name to words for increased readability.
		if(droppedItems[b] == "hpot"){
			droppedItems[b] = "health potion";
		}
		if(droppedItems[b] == "mpot"){
			droppedItems[b] = "mana potion";
		}
		if(droppedItems[b] == "horn"){
			droppedItems[b] = "spooky clown flower horn";
		}
		// If there is more than one item in the list, and it is the last item, ends the sentence with "and".
		if(b == droppedItemsSize - 1 && droppedItemsSize > 1){
			cout << " and a " << droppedItems[b] << "." << endl;
		}
		else{
			if(b == droppedItemsSize - 1 && droppedItemsSize == 1){	// If there is one item in the list, displays the item with a period after it.
				cout << " a " << droppedItems[b] << "." << endl;
			}
			else{	// If there is more than one item in the list, and it is not the last item, adds a comma after the item, as there are more items to come.
				cout << " a " << droppedItems[b] << ",";
			}
		}
	}
	return player;
}

// Reads in all of the parameters for the chosen enemy, and sets the data members to reflect it.
// ==== File Layout ====
// MAXHP:<int>
// ATTACK-POWER:<int>
// <drop1>*<dropchance>,<drop2>*<dropchance>,<drop3>*<dropchance>
void Enemy::getStats(string filename){
	ifstream dataFile(filename, ios::in);
	string line;
	int lineNumber = 0;	// Records the current line, as different job data is on different lines,
	while(dataFile){	// Parses through each line of the file.
		getline(dataFile, line);
		if(line != ""){	// If the line is not empty, proceeds.
			if(lineNumber == 2){	// Reads the third line of data.
				int lastPosition = 0;
				for(int i = 0; i < line.length(); i++){
					if(line[i] == '*'){	// Separator character between drop and drop chance.
						drops[dropsSize] = line.substr(lastPosition, i - lastPosition);	// Drop is everything before the asterisk.
						i++;	// i is incremented in order to put it at the position after the asterisk (the first digit of the drop chance).
						lastPosition = i;	// lastPosition is recorded to document the start of the drop chance value.
						// Increments i until it is no longer a number.
						while((line[i] >= '0' && line[i] <= '9') || line[i] == '.'){
							i++;	// When the loop exits, the last number will be one position before i.
						}
						// Drop chance is set to everything after the asterisk and before the next non-digit character.
						dropChance[dropsSize] = stof(line.substr(lastPosition, i - lastPosition));
						dropsSize++;	// dropsSize is incremented in order to place the next skill in the next value of the array.
						lastPosition = i + 1;	// Sets the last position to the space after the comma (the comma comes after the last drop's drop chance).
						i++;	// Increments i, as the next character is just a comma.
					}
				}
			}
			if(lineNumber == 1){	// Reads the second line of data.
				// Checks for a colon, then sets attackPower to the integer value of everything after the colon.
				for(int i = 0; i < line.length(); i++){
					if(line[i] == ':'){
						attackPower = stoi(line.substr(i+1, line.length()));
					}
				}
			}
			if(lineNumber == 0){	// Reads the first line of data.
				// Checks for a colon, then sets maxHealth to the integer value of everything after the colon.
				for(int i = 0; i < line.length(); i++){
					if(line[i] == ':'){
						maxHealth = stoi(line.substr(i+1, line.length()));
						health = maxHealth;
					}
				}
			}
		lineNumber++;	// Increments lineNumber in order to change the function depending on which line is being parsed.
		}
	}
	// Test code to ensure the file was read correctly
	/* cout << name << " " << type << endl;
	cout << maxHealth << " " << health << endl;
	cout << attackPower << endl;
	for(int i = 0; i < 5; i++){
		cout << drops[i] << " " << dropChance[i] << " || ";
	}
	cout << endl; */
}
