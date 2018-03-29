// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// game.cpp

using namespace std;
#include<iostream>
#include<fstream>
#include"game.h"

Game::Game(){
	currentDepth = 0;
	currentPosition = 0;
}

Game::~Game(){

}

// Sets the player to the given hero.
void Game::setPlayer(Hero newPlayer){
	player = newPlayer;
}

// Returns the player.
Hero Game::getPlayer(){
	return player;
}

// Generates an array of rooms in order to create a new floor.
void Game::generateFloor(){
	string roomName;
	// Depending on the current depth level, changes the room's name for theme purposes.
	if(currentDepth == 0){
		roomName = "Lizardman Dungeon";
	}
	if(currentDepth == 1){
		roomName = "Clown Emporium";
	}
	if(currentDepth >= 2){
		roomName = "Rat House";
	}
	for(int i = 0; i < 6; i++){	// Creates new rooms and adds them to the array.
		Room newRoom(roomName, currentDepth);
		roomLayout[i] = newRoom;
	}
	roomLayout[5].setLocked(true);	// Locks the last room.
}

// Returns the current position of the player.
int Game::getPosition(){
	return currentPosition;
}

// Sets the current position of the player.
void Game::setPosition(int n){
	currentPosition = n;
}

// Gets the room at the given position.
Room Game::getRoomLayout(int position){
	return roomLayout[position];
}

// Gets the current depth level.
int Game::getDepth(){
	return currentDepth;
}

// Sets the current depth level.
void Game::setDepth(int n){
	currentDepth = n;
}
