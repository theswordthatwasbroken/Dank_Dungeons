/* 
 * File:   Inventory.h
 * Author: James Sharman
 *
 * Created on 28 July 2014, 1:53 PM
 */

#ifndef INVENTORY_H
#define	INVENTORY_H
//#include "Room.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Inventory {
public:
    Inventory();
    Inventory(vector<Item>);
    void showInventoryItems(PlayerCharacter);
    void addItem(int, int, int, vector<Item>);
    void dropItem(int);
    void setInvVector(vector<Item>);
    void setTotalDamage(int);
    void setTotalArmor(int);
    int getTotalDamage();
    int getTotalArmor();
    vector<Item> getInvVector();
    int checkInvForItem(string);
    string toLowerCase(string);
    int total_armor;
    int total_damage;
    
private:
    vector<Item> inventory_vec;
};

#endif	/* INVENTORY_H */

