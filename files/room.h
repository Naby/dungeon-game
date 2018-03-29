// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// room.h

using namespace std;
#include<iostream>
#include"enemy.h"

#ifndef ROOM_H_
#define ROOM_H_

class Room{
public:
	// Constructors
	Room();
	Room(string, int);
	~Room();

	// Getters/Setters
	string getName();
	void setName(string);
	int getDepth();
	void setDepth(int);
	void setLocked(bool);
	bool getLocked();
	int getEnemySize();
	void setEnemySize(int);
	Enemy getEnemy(int);

	// Methods
	void spawnEnemy(string, string);	// Creates an enemy in the room.
	void enterRoom();

private:
	string name;
	int depth;	// Rooms will spawn more enemies as the depth increases
	bool locked;	// If it is locked, the player will need to find a key from an enemy before being able to unlock it.
	Enemy enemies[5];
	int enemySize;
};



#endif /* ROOM_H_ */
