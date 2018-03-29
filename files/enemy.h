// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// enemy.h

using namespace std;
#include<iostream>
#include"hero.h"

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy{
public:
	// Constructors
	Enemy(string, string);
	Enemy();
	~Enemy();

	// Getters & Setters
	string getName();
	void setName(string);
	void setAttack(int);
	int getHealth();
	void setHealth(int);
	int getMaxHealth();
	void setMaxHealth(int);
	void setDrops(string*);
	string getDrops();
	void setDropChance(float*);
	float getDropChance();
	string getType();
	int getAttackPower();

	// Methods
	void getStats(string);
	void attack();
	void takeDamage(int);
	Hero dropItem(Hero);

private:
	string name;
	string type;
	int attackPower;
	int health;
	int maxHealth;
	string drops[5];
	float dropChance[5];
	int dropsSize;
};



#endif /* ENEMY_H_ */
