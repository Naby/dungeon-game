// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// room.cpp

using namespace std;
#include<iostream>
#include<fstream>
#include"room.h"
#include"hero.h"

Room::Room(){

}

Room::~Room(){

}

Room::Room(string newName, int newDepth){
	name = newName;
	depth = newDepth;
	locked = false;
	enemySize = 0;
}

// Returns the room's name.
string Room::getName(){
	return name;
}

// Sets the room's name.
void Room::setName(string newName){
	name = newName;
}

// Returns the room's depth.
int Room::getDepth(){
	return depth;
}

// Sets the room's depth.
void Room::setDepth(int n){
	depth = n;
}

// Sets whether the room is locked or not.
void Room::setLocked(bool isLocked){
	locked = isLocked;
}

// Returns whether the room is locked or not.
bool Room::getLocked(){
	return locked;
}

// Spawns a new enemy inside of the room.
void Room::spawnEnemy(string newName, string newType){
	Enemy enemyOne(newName, newType);
	enemies[enemySize] = enemyOne;	// Adds the enemy to the list of current enemies in the room.
	enemySize++;
}

// Returns the size of the enemies array.
int Room::getEnemySize(){
	return enemySize;
}

// Sets the size of the enemies array.
void Room::setEnemySize(int n){
	enemySize = n;
}

// Enters the room, spawning enemies based off of the current depth level.
void Room::enterRoom(){
	string newName;
	string newType;
	if(depth == 0){
		newName = "Dark Lizardman";
		newType = "lizardman";
	}
	if(depth == 1){
		newName = "Neighborhood Clown";
		newType = "clown";
	}
	if(depth >= 2){
		newName = "Collective Mass of 500 Rats";
		newType = "rat";
	}
	spawnEnemy(newName, newType);
}

// Returns the enemy at the given position of the enemies array.
Enemy Room::getEnemy(int position){
	return enemies[position];
}
