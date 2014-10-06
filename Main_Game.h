/* 
 * File:   Main_Game.h
 * Author: James Sharman
 *
 * Created on 29 July 2014, 9:32 AM
 */

#ifndef MAIN_GAME_H
#define	MAIN_GAME_H
#include "PlayerCharacter.h"
#include "Item.h"
#include "Room.h"
#include "NPC.h"
#include "Inventory.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Main_Game {
public:
    void showMainMenu();
    void showGameMenu();
    void loadAssets(string, string);
    void startGame();
    void showRoomDesc();
    void changeRoom(int);
    void showInventoryMenu(int);
    void showCombatMenu();
    string toLowerCase(string);
    void examineObject(string);
    vector<Item> getVector();
    PlayerCharacter getGamePC();
    int getPCDamage();
    int getPCCurrentRoom();
    void setRoomItemVec(vector<vector<int> >);
    vector<vector<int> > getRoomItemVec();
    int getItemIndex(string);
    int getRoomIndex(string);
    int attackRoll(int);
    
    PlayerCharacter game_pc;
    string test_var;
    vector<Item> item_vec;
    vector<Item> inventory_vec;
    vector<int> invitem_vec;
private:

};

#endif	/* MAIN_GAME_H */