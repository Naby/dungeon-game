// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// hero.h

using namespace std;
#include<iostream>

#ifndef HERO_H_
#define HERO_H_

class Hero{
public:
	// Constructors
	Hero(string, string);
	Hero();
	~Hero();

	// Getters and Setters
	string getName();
	string getJob();
	int getHealth();
	void setHealth(int);
	int getMaxHealth();
	void setMaxHealth(int);
	int getMana();
	void setMana(int);
	int getMaxMana();
	void setMaxMana(int);
	string getSkills(int);
	void setSkills(string, int);
	int getSkillsSize();
	void setSkillsSize(int);
	int getSkillCost(int);
	int getInventorySize();
	void setInventorySize(int);
	string getInventory(int);
	void setInventory(string, int);
	void setInventoryQuantity(int, int);
	int getInventoryQuantity(int);
	void setAttackModifier(int);
	int getAttackModifier();

	// Methods
	void createJob(string);
	void displayInventory();
	int getItemPosition(string);
	int getSkillPosition(string);
	void displaySkills();

private:
	string name;
	string job;
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int attackModifier;
	string skills[5];
	int skillsSize;
	int skillsCost[5];
	string inventory[5];
	int inventoryQuantity[5];
	int inventorySize;
};



#endif /* HERO_H_ */
