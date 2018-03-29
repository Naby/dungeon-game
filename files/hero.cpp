// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// hero.cpp

using namespace std;
#include<iostream>
#include<fstream>
#include"hero.h"

Hero::Hero(){

}

Hero::Hero(string newName, string newJob){
	name = newName;
	job = newJob;
	attackModifier = 0;
	skillsSize = 0;
	inventorySize = 0;
	// Initializes arrays.
	for(int i = 0; i < 5; i++){
		skills[i] = "";
		skillsCost[i] = 0;
		inventory[i] = "";
		inventoryQuantity[i] = 0;
	}
	createJob(newJob + ".txt");	// Adds the file extension to the end of the job name to form the actual filename.
}

Hero::~Hero(){

}

// Returns the hero's name.
string Hero::getName(){
	return name;
}

// Returns the hero's health.
int Hero::getHealth(){
	return health;
}

// Sets the hero's health.
void Hero::setHealth(int newHealth){
	if(newHealth > maxHealth){	// Current health cannot be greater than max health.
		health = maxHealth;
	}
	else{
		health = newHealth;
	}
	if(newHealth <= 0){	// When health reaches zero, the player dies and the game ends.
		health = 0;
	}
}

// Returns the hero's max health.
int Hero::getMaxHealth(){
	return maxHealth;
}

// Returns the hero's job.
string Hero::getJob(){
	return job;
}

// Sets the hero's max health.
void Hero::setMaxHealth(int newMax){
	if(newMax <= 0){	// Max health cannot be negative, so sets it to 1.
		maxHealth = 1;
		cout << "Maxhealth is wrong my guy";
	}
	else{
		maxHealth = newMax;
	}
}

// Returns the hero's mana.
int Hero::getMana(){
	return mana;
}

// Sets the hero's mana.
void Hero::setMana(int newMana){
	if(newMana <= maxMana){	// Mana cannot exceed its maximum, so sets it to the max.
		mana = newMana;
	}
	if(newMana < 0){	// Mana cannot be negative, so sets it to 0.
		mana = 0;
	}
}

// Returns the hero's max mana.
int Hero::getMaxMana(){
	return maxMana;
}

// Sets the hero's max mana.
void Hero::setMaxMana(int newMax){
	if(newMax <= 0){	// Checks if the mana is valid, as it cannot be 0 or less than 0.
		maxMana = 1;
		cout << "Maxmana is wrong my guy";
	}
	else{
		maxMana = newMax;
	}
}

// Returns the hero's attack.
int Hero::getAttackModifier(){
	return attackModifier;
}

// Sets the hero's attack.
void Hero::setAttackModifier(int newAttack){
	if(newAttack > 0){	// Checks if the attack is valid, as it cannot be 0 or less than 0.
		attackModifier = newAttack;
	}
	else{
		attackModifier = 1;
	}
}

// Returns the skill at the given position.
string Hero::getSkills(int position){
	if(position < skillsSize && position >= 0){	// checks to see if the position is valid.
		return skills[position];
	}
	else{
		return "";	// If the skill is not found, returns nothing.
	}
}

// Creates a new skill of given name at the given position.
void Hero::setSkills(string skill, int position){
	skills[position] = skill;
}

// Returns the mana cost of the skill at the given position.
int Hero::getSkillCost(int position){
	return skillsCost[position];
}

// Returns the item at the given position of the inventory.
string Hero::getInventory(int position){
	return inventory[position];
}

// Adds a new item to the given position of the inventory.
void Hero::setInventory(string item, int position){
	inventory[position] = item;
}

// Returns the size of the skills array.
int Hero::getSkillsSize(){
	return skillsSize;
}

// Sets the size of the skills array.
void Hero::setSkillsSize(int newSize){
	skillsSize = newSize;
}

// Returns the size of the inventory array.
int Hero::getInventorySize(){
	return inventorySize;
}

// Sets the size of the inventory array.
void Hero::setInventorySize(int newSize){
	inventorySize = newSize;
}

// Sets the quantity of the item at the given position in the inventoryQuantity array.
void Hero::setInventoryQuantity(int value, int position){
	inventoryQuantity[position] = value;
}

// Returns the quantity of the item at the given position in the inventoryQuantity array.
int Hero::getInventoryQuantity(int position){
	return inventoryQuantity[position];
}

// Displays the hero's current inventory to the user.
void Hero::displayInventory(){
	cout << name << "'s Inventory: " << endl;
	for(int i = 0; i < inventorySize; i++){	// Loops for every item in the inventory.
		cout << inventory[i] << " (" << inventoryQuantity[i] << " available) ";
		// Adds descriptions for each of the items depending on what the item is.
		if(inventory[i] == "hpot"){
			cout << "- restores 7 health." << endl;
		}
		if(inventory[i] == "mpot"){
			cout << "- restores 3 mana." << endl;
		}
		if(inventory[i] == "horn"){
			cout << "- a colorful clown horn. Use it to see what happens." << endl;
		}
		if(inventory[i] == "key"){
			cout << "- unlocks the door at the last room of the floor." << endl;
		}
	}
}

// Displays the hero's current skills to the user.
void Hero::displaySkills(){
	cout << name << "'s Skills: " << endl;
	for(int i = 0; i < skillsSize; i++){	// Loops for every skill in the skills array.
		cout << skills[i] << " (costs " << skillsCost[i] << " mana) ";
		// Adds descriptions for each of the skills depending on what the skill is.
		if(skills[i] == "berserk"){
			cout << "- screams very angrily and causes your attack power to permanently increase by one point." << endl;
		}
		if(skills[i] == "cleave"){
			cout << "- deals 3 damage." << endl;
		}
		if(skills[i] == "blaze"){
			cout << "- casts fire magic, dealing 5 damage." << endl;
		}
		if(skills[i] == "restore"){
			cout << "- restores 5 health." << endl;
		}
	}
}

// Returns the position in the inventory array of the given item.
int Hero::getItemPosition(string item){
	for(int i = 0; i < inventorySize; i++){
		if(inventory[i] == item){
			return i;
		}
	}
	return -1;	// If the item is not found, returns -1.
}

// Returns the position in the skills array of the given skill.
int Hero::getSkillPosition(string skill){
	for(int i = 0; i < skillsSize; i++){
		if(skills[i] == skill){
			return i;
		}
	}
	return -1;	// If the skill isn't found, returns -1.
}

// Reads in all of the parameters for the chosen class, and sets the data members in Hero to reflect it.
// ==== File Layout ====
// MAXHP:<int> MAXMP:<int>
// ATTACK-MODIFIER:<int>
// <skill1>*<manacost>,<skill2>*<manacost>,<skill3>*<manacost>
// <inventory1>*<quantity>,<inventory2>*<quantity>,<inventory3>*<quantity>
void Hero::createJob(string filename){
	ifstream dataFile(filename, ios::in);
	string line;
	int lineNumber = 0;	// Records the current line, as different job data is on different lines,
	while(dataFile){	// Parses through each line of the file.
		getline(dataFile, line);
		if(line != ""){	// If the line is not empty, proceeds.
			if(lineNumber == 3){	// Reads the fourth line of data.
				int lastPosition = 0;
				for(int i = 0; i < line.length(); i++){
					if(line[i] == '*'){	// Separator character between inventory item and quantity.
						inventory[inventorySize] = line.substr(lastPosition, i - lastPosition);	// Skill is everything before the asterisk.
						i++;	// i is incremented in order to put it at the position after the asterisk (the first digit of the mana cost).
						lastPosition = i;	// lastPosition is recorded to document the start of the mana cost value.
						// Increments i until it is no longer a number.
						while(line[i] >= '0' && line[i] <= '9'){
							i++;	// When the loop exits, the last number will be one position before i.
						}
						// Skill cost is set to everything after the asterisk and before the next non-digit character.
						inventoryQuantity[inventorySize] = stoi(line.substr(lastPosition, i - lastPosition));
						inventorySize++;	// skillsSize is incremented in order to place the next skill in the next value of the array.
						lastPosition = i + 1;	// Sets the last position to the space after the comma (the comma comes after the last skill's mana cost).
						i++;	// Increments i, as the next character is just a comma.
					}
				}
			}
			if(lineNumber == 2){	// Reads the third line of data.
				int lastPosition = 0;
				for(int i = 0; i < line.length(); i++){
					if(line[i] == '*'){	// Separator character between skill and mana cost.
						skills[skillsSize] = line.substr(lastPosition, i - lastPosition);	// Skill is everything before the asterisk.
						i++;	// i is incremented in order to put it at the position after the asterisk (the first digit of the mana cost).
						lastPosition = i;	// lastPosition is recorded to document the start of the mana cost value.
						// Increments i until it is no longer a number.
						while(line[i] >= '0' && line[i] <= '9'){
							i++;	// When the loop exits, the last number will be one position before i.
						}
						// Skill cost is set to everything after the asterisk and before the next non-digit character.
						skillsCost[skillsSize] = stoi(line.substr(lastPosition, i - lastPosition));
						skillsSize++;	// skillsSize is incremented in order to place the next skill in the next value of the array.
						lastPosition = i + 1;	// Sets the last position to the space after the comma (the comma comes after the last skill's mana cost).
						i++;	// Increments i, as the next character is just a comma.
					}
				}
			}
			if(lineNumber == 1){	// Reads the second line of data.
				// Checks for a colon, then sets attackModifier to the integer value of everything after the colon.
				for(int i = 0; i < line.length(); i++){
					if(line[i] == ':'){
						attackModifier = stoi(line.substr(i+1, line.length()));
					}
				}
			}
			if(lineNumber == 0){	// Reads the first line of data.
				// Loops two times in order to differentiate setting of the health and the mana.
				for(int z = 0; z < 2; z++){
					// Reads the max health from the file.
					int i = 0;	// i is the start point of the HP value.
					// Loops until it finds a number.
					while(line[i] <= '0' || line[i] >= '9'){
						i++;
					}
					line.erase(0, i);	// Erases everything up to the number.
					i = 0;	// Resets i to 0, as the start of the line had been erased.
					// Records the number of digits in the number by looping until a number isn't found.
					while(line[i] >= '0' && line[i] <= '9'){
						i++;	// When the loop exits, i will be the position after the last number.
					}
					// For the first loop around, sets the health.
					if(z == 0){
						maxHealth = stoi(line.substr(0, i));
						health = maxHealth;
						line.erase(0, i+1);	// Erases the numbers to prepare for the mana to be read in.
					}
					// For the second loop around, sets the mana.
					if(z == 1){
						maxMana = stoi(line.substr(0, i));
						mana = maxMana;
					}
				}
			}
		lineNumber++;	// Increments lineNumber in order to change the function depending on which line is being parsed.
		}
	}
	// Test code to ensure the file was read correctly
	/* cout << name << " " << job << endl;
	cout << maxHealth << " " << health << endl;
	cout << maxMana << " " << mana << endl;
	cout << attackModifier << endl;
	for(int i = 0; i < 5; i++){
		cout << skills[i] << " " << skillsCost[i] << " || ";
	}
	cout << endl;
	for(int i = 0; i < 5; i++){
		cout << inventory[i] << " " << inventoryQuantity[i] << " || ";
	}
	cout << endl; */
}
