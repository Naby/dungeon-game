// Author: Jeff Lucca
// Recitation: 209 Byrandurga Gopinath
//
// Assignment 8
// main.cpp

using namespace std;
#include<iostream>
#include<fstream>
#include"hero.h"
#include"game.h"
#include"enemy.h"
#include"room.h"

int main(){
	Game saveOne;
	cout << "You wake up to a sharp pain in your abdomen. Your memory is hazy and your vision is foggy. You concentrate for a second to remember who you are." << endl;
	string heroName;
	cout << "Please enter your name: ";
	getline(cin, heroName);
	string job = "";
	while(job != "warrior" && job != "mage"){	// Loops until a valid job is given.
		cout << "Please enter your job (warrior or mage): ";
		getline(cin, job);
		for(int i = 0; i < job.length(); i++){	// Converts the string to lowercase.
			job[i] = tolower(job[i]);
		}
		if(job != "warrior" && job != "mage"){
			cout << "Job not recognized. ";
		}
	}
	Hero heroOne = Hero(heroName, job);	// Creates the character based on the given name and job.
	saveOne.setPlayer(heroOne);
	cout << "After taking a moment to collect yourself, you look at your surroundings and find an overgrown lizard ready to poke you with a pointy stick a second time."
			" Realizing you are conscious, he scurries away to the next room in front of you. You follow." << endl;
	// Loops indefinitely until the game is over (the player's health reaches zero).
	while(saveOne.getPlayer().getHealth() > 0){
		saveOne.generateFloor();	// Generates the floor, creating 6 rooms and storing them in saveOne's roomLayout array.
		int snapshotDepth = saveOne.getDepth();	// Snapshots the depth in order to compare it if it ever changes.
		while(snapshotDepth == saveOne.getDepth()){	// Loops until the user enters a new depth.
			int a = 0;	// Stops the last room from being skipped when proceeding from the second-to-last room to the last room.
			string line = "";
			Room currentRoom = saveOne.getRoomLayout(saveOne.getPosition());	// Stores the current room as the current position in roomLayout. When the user moves forward/back, this makes a 'new' room.
			cout << "You enter room " << saveOne.getPosition() + 1 << " of the " << currentRoom.getName() << "." << endl;
			currentRoom.enterRoom();	// Spawns enemies based on the room that was entered.
			Enemy enemyOne = currentRoom.getEnemy(0);	// Sets enemyOne to the enemy that just spawned.
			cout << "You encounter a " << enemyOne.getName() << " with " << enemyOne.getHealth() << " health. He looks at you with his big " << enemyOne.getType() << " eyes.";
			if(currentRoom.getEnemySize() > 1){	// Unused, originally intended to have more than one enemy spawn at some point.
				cout << "He has " << currentRoom.getEnemySize() - 1 << " goons waiting behind him.";
			}
			cout << endl;
			while(currentRoom.getEnemySize() > 0){	// While there are still enemies in the room, loop the battle.
				string choice;
				int enemyDead = 0;	// Records whether the enemy dies during skill usage.
				while(choice != "a" && choice != "n" && enemyDead == 0){	// Loops until either the enemy dies, or the player finally chooses to attack or do nothing.
					cout << "What will you do? Input 'a' to attack, 'n' to do nothing, 's' to use a job skill (" << heroOne.getMana() << "/" << heroOne.getMaxMana() << " mana remaining), or 'i' to open the inventory." << endl;
					getline(cin, choice);
					if(choice != "a" && choice != "n" && choice != "i" && choice != "s"){	// Stops invalid inputs from losing the player their turn.
						cout << "That's not a valid action. Think very hard about what you are doing. ";
					}
					if(choice == "i"){	// Opens the inventory.
						while(choice != "b"){	// Loops until the user chooses to back, as they may want to use multiple items at once.
							heroOne.displayInventory();	// Displays the hero's current inventory.
							cout << "If you wish to use any of these items, enter the name. Otherwise, input 'b' to go back." << endl;
							getline(cin, choice);
							int position = heroOne.getItemPosition(choice);
							if(position >= 0 && choice != "b"){	// If the position of the item is -1, it doesn't exist, so it has to be >=0. If the user chooses to go back. skip this.
								if(heroOne.getInventoryQuantity(position) > 0){	// In order to use an item, the player needs to have more than zero of them.
									if(choice == "hpot"){	// Uses a health potion.
										heroOne.setHealth(heroOne.getHealth() + 7);	// Restores health by 7.
										heroOne.setInventoryQuantity(heroOne.getInventoryQuantity(position) - 1, position);	// Subtracts one from the health potions' quantity.
										cout << "7 health restored." << endl;
									}
									if(choice == "mpot"){	// Uses a mana potion.
										heroOne.setMana(heroOne.getMana() + 3);	// Restores mana by 3.
										heroOne.setInventoryQuantity(heroOne.getInventoryQuantity(position) - 1, position);	// Subtracts one from the mana potions' quantity.
										cout << "3 mana restored." << endl;
									}
									if(choice == "key"){	// Key will show up in the inventory so that the player knows they have one. However, it doesn't do anything.
										cout << "You can't use that item." << endl;
									}
									if(choice == "horn"){	// Uses a clown horn.
										cout << "You take out the clown horn and honk it. It makes a funny noise and the " << enemyOne.getName() << " laughs at you." << endl;
										heroOne.setInventoryQuantity(heroOne.getInventoryQuantity(position) - 1, position);	// Subtracts one from the horns' quantity.
									}
								}
								else{	// If the input passes the valid item test, but fails the next step, the quantity is 0, and as such, it can't be used because there aren't any.
									cout << "You don't have any left." << endl;
								}
							}
							else{
								if(choice != "b"){	// If the input fails the valid item test and isn't 'b', tells the user it wasn't found and loops back.
									cout << "You don't have any of those." << endl;
								}
							}
						}
					}
					if(choice == "s"){	// Opsn the skills menu.
						while(choice != "b"){	// Loops until the user chooses to go back, exiting the skills menu.
							heroOne.displaySkills();	// Displays the hero's current skills.
							cout << "If you wish to use any of these skills, enter the name. Otherwise, input 'b' to go back." << endl;
							getline(cin, choice);
							int position = heroOne.getSkillPosition(choice);
							if(position >= 0 && choice != "b"){	// If the position of the skill is -1, it doesn't exist, so it has to be >=0. If the user chooses to go back, skip this.
								if(heroOne.getSkillCost(position) <= heroOne.getMana()){	// Checks if the hero has enough mana to cast the skill. Current mana must be greater than the mana cost.
									if(choice == "berserk" && heroOne.getJob() == "warrior"){	// Uses berserk. Jobs have unique skills, so checks if it is a warrior using it.
										heroOne.setAttackModifier(heroOne.getAttackModifier() + 1);	// Attack modifier is increased by one when this skill is cast.
										cout << heroOne.getName() << "'s attack has been increased to " << heroOne.getAttackModifier() << "!" << endl;
										heroOne.setMana(heroOne.getMana() - heroOne.getSkillCost(position));	// Subtracts the mana cost from the user's mana.
										cout << "You have " << heroOne.getMana() << "/" << heroOne.getMaxMana() << " mana remaining." << endl;
									}
									if(choice == "cleave" && heroOne.getJob() == "warrior"){	// Uses cleave.
										enemyOne.setHealth(enemyOne.getHealth() - 3);	// Takes 3 health off of the enemy.
										cout << "Cleaved the " << enemyOne.getName() << " for 3 damage!";
										cout << " It has " << enemyOne.getHealth() << "/" << enemyOne.getMaxHealth() << " health remaining." << endl;
										if(enemyOne.getHealth() == 0){	// Because this skill can kill, it must check if the enemy dies from this.
											enemyDead = 1;	// If enemyDead = 1, it breaks the loop at the beginning (the choice the player makes to wait, attack, etc.), and skips to defeating the enemy.
										}
										heroOne.setMana(heroOne.getMana() - heroOne.getSkillCost(position));	// Subtracts the mana cost from the user's mana.
										cout << "You have " << heroOne.getMana() << "/" << heroOne.getMaxMana() << " mana remaining." << endl;
									}
									if(choice == "blaze" && heroOne.getJob() == "mage"){	// Uses blaze. Jobs have unique skills, so checks if it is a mage using it.
										enemyOne.setHealth(enemyOne.getHealth() - 5);	// Takes 5 health off of the enemy.
										cout << "Scorched the " << enemyOne.getName() << " for 5 damage!";
										cout << " It has " << enemyOne.getHealth() << "/" << enemyOne.getMaxHealth() << " health remaining." << endl;
										if(enemyOne.getHealth() == 0){	// Because this skill can kill, it msut check if the enemy dies from this.
											enemyDead = 1;	// If enemyDead = 1, it breaks the loop at the beginning (the choice the player makes to wait, attack, etc.), and skips to defeating the enemy.
										}
										heroOne.setMana(heroOne.getMana() - heroOne.getSkillCost(position));	// Subtracts the mana cost from the user's mana.
										cout << "You have " << heroOne.getMana() << "/" << heroOne.getMaxMana() << " mana remaining." << endl;
									}
									if(choice == "restore"  && heroOne.getJob() == "mage"){	// Uses restore.
										cout << "You wave your staff in circles, magically restoring 5 health." << endl;
										heroOne.setHealth(heroOne.getHealth() + 5);	// Restores the hero's health by 5.
										heroOne.setMana(heroOne.getMana() - heroOne.getSkillCost(position));	// Subtracts the mana cost from the user's mana.
										cout << "You have " << heroOne.getHealth() << "/" << heroOne.getMaxHealth() << " health remaining." << endl;
										cout << "You have " << heroOne.getMana() << "/" << heroOne.getMaxMana() << " mana remaining." << endl;
									}
								}
								else{	// If the input passes the valid skill check, but fails the next step, it is because the hero doesn't have the mana to cast it.
									cout << "You don't have enough mana to use " << choice << "." << endl;
								}
							}
							else{
								if(choice != "b"){	// If the input fails the valid skill check and isn't 'b', either they typed it wrong or it's a skill for another job.
									cout << "You can't use that skill, or it doesn't exist." << endl;
								}
							}
						}
					}
				}
				if(choice == "a"){	// If the user inputs a, they choose to attack.
					cout << "You hit the " << enemyOne.getType() << " for " << heroOne.getAttackModifier() << " damage! ";
					enemyOne.setHealth(enemyOne.getHealth() - heroOne.getAttackModifier());	// Subtracts the hero's damage from the enemy's health.
				}
				if(choice == "n"){	// If the user inputs n, they choose to do nothing. That is not a good idea. You can't do that in a real life battle. You'll die.
					cout << "You did nothing! I'm not sure why you did that. ";
				}
				if(enemyOne.getHealth() <= 0){	// Checks if the enemy is dead, right after the hero's attack. If the enemy has no health, breaks the combat loop.
					break;
				}
				if(currentRoom.getEnemySize() == 0){	// If there are no more enemies in the room, also breaks the combat loop.
					break;
				}
				cout << "The enemy " << enemyOne.getName() << " has " << enemyOne.getHealth() << "/" << enemyOne.getMaxHealth() << " health remaining." << endl;
				cout << "The " << enemyOne.getName() << " hits you for " << enemyOne.getAttackPower() << " damage! ";
				heroOne.setHealth(heroOne.getHealth() - enemyOne.getAttackPower());	// Subtracts the enemy's attack power from the hero's health
				if(heroOne.getHealth() <= 0){	// Checks to see if the user's health hits 0.
					cout << "You have 0/" << heroOne.getMaxHealth() << " health remaining." << endl;
					goto isDead;	// If health is 0, the game needs to end, so goes to the isDead flag at the bottom of the file.
				}
				cout << "You have " << heroOne.getHealth() << "/" << heroOne.getMaxHealth() << " health remaining." << endl;
			}
			cout << "You killed him. Wow." << endl;
			heroOne = enemyOne.dropItem(heroOne);	// When the enemy dies, drops items for the player. Overwrites the player with the exact copy of it that has the new drops in their inventory.
			cout << "The room is now clear of enemies. ";
			line = "";
			// After the room is cleared, the user needs to move forward a room or back a room in order to continue their journey.
			while(line != "f" && line != "b"){	// Loops until the user inputs a valid choice to go forward or back.
				cout << "Move forward one room ('f') or backwards one room ('b')?" << endl;
				getline(cin, line);
				if(line == "f"){	// Moves forward.
					if(saveOne.getPosition() == 5){	// If the position is 5, meaning the last room, progression is locked behind a key.
						cout << "The door in front of you is locked. You reach into your backpack for a key." << endl;
						if(heroOne.getItemPosition("key") > -1){	// If a key is not found, its position will be -1.
							if(heroOne.getInventoryQuantity(heroOne.getItemPosition("key")) > 0){	// If the user's key quantity is greater than 0, proceeds.
								currentRoom.setLocked(false);	// Unlocks the door.
								heroOne.setInventoryQuantity(0, heroOne.getItemPosition("key"));	// Removes the key from the user's inventory.
							}
						}
						if(currentRoom.getLocked() == false){	// If the door is unlocked by the player (it's locked by default), proceeds.
							cout << "You find a key and use it to unlock the door, unveiling a staircase winding even deeper underground. ";
						}
						else{	// If the room is locked, the user needs to find a key.
							cout << "You don't have a key. You decide to kill more enemies in order to scavenge one from them." << endl;
							cout << "You move back one room." << endl;
							saveOne.setPosition(saveOne.getPosition() - 1);	// Moves the player to the only option (back a room) in order to fight more enemies.
						}
					}
					else{
						saveOne.setPosition(saveOne.getPosition() + 1);	// If the position is not 5, goes forward a room.
						a = 1;	// Sets a to 1 in order to prevent thinking it's the last room moving down to the next depth, now that the position is 5.
					}
				}
				if(line == "b"){
					if(saveOne.getPosition() == 0){	// If the current position is the first room, it can't move backwards, so moves forwards.
						cout << "You are in the first room. You can't go backwards. Going forwards instead." << endl;
						saveOne.setPosition(saveOne.getPosition() + 1);	// Goes forwards a room.
					}
					else{
						saveOne.setPosition(saveOne.getPosition() - 1);	// Goes back a room.
					}
				}
				if(line != "f" && line != "b"){
					cout << "Command not recognized. ";
				}
			}
			if(saveOne.getPosition() == 5 && currentRoom.getLocked() == false && a == 0){	// If the room is unlocked, the position is the last room, and a == 0, proceeds.
				saveOne.setDepth(saveOne.getDepth() + 1);	// Increases the depth level. This causes the rooms to change spawned enemies.
				// Gives a themed message based on what enemies are on the next floor.
				if(saveOne.getDepth() == 1){
					cout << "As you descend down the steps, circus music and honking noises echo loudly across the walls." << endl;
					saveOne.setPosition(0);
				}
				if(saveOne.getDepth() == 2){
					cout << "As you descend down the steps, the stench of 1,000 rats assaults your nose." << endl;
					saveOne.setPosition(0);
				}
				if(saveOne.getDepth() > 2){
					cout << "You start heading down the steps but stop as you notice that everything seems the same as the last floor."
							" You ask yourself why you are still playing this game, but you head down anyway." << endl;
				}
			}
		}
	}
	isDead:	// If the player dies, goes to this flag and ends the game.
		cout << endl;
		cout << endl;
		cout << "You have been defeated." << endl;
		cout << "You have made it to depth " << saveOne.getDepth() << ", room " << saveOne.getPosition() + 1 << "! Congratulations.";

		return 0;
}

