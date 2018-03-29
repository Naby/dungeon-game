// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// game.h

using namespace std;
#include<iostream>
#include"hero.h"
#include"room.h"
#include"enemy.h"

#ifndef GAME_H_
#define GAME_H_

class Game{
public:
	// Constructors
	Game();
	~Game();

	// Getters & Setters
	void setPlayer(Hero);
	Hero getPlayer();
	int getDepth();
	void setDepth(int);
	int getPosition();
	void setPosition(int);
	void setRoomLayout();
	Room getRoomLayout(int);

	// Methods
	void generateFloor();

private:
	Hero player;
	int currentDepth;
	int currentPosition;
	Room roomLayout[6];
};



#endif /* GAME_H_ */
