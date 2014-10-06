/* 
 * File:   PlayerCharacter.h
 * Author: James Sharman
 *
 * Created on 17 June 2014, 11:22 AM
 */

#ifndef PLAYERCHARACTER_H
#define	PLAYERCHARACTER_H
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class PlayerCharacter {
private:
    string pc_name;
    int pc_strength;
    int pc_agility;
    int pc_intelligence;
    int pc_charisma;
    int pc_hp;
    int pc_armor;
    int pc_strbonus;
    int pc_agibonus;
    int pc_current_room;

public:
    PlayerCharacter();
    PlayerCharacter(string, int, int, int, int, int, int);
    void setName(string);
    void setStr(int);
    void setAgi(int);
    void setInt(int);
    void setChr(int);
    void setHP(int);
    void setCurrentRoom(int room_index);
    string getName();
    int getStr();
    int getAgi();
    int getInt();
    int getChr();
    int getHP();
    int getStrBonus();
    int getAgiBonus();
    int getCurrentRoom();
};

#endif	/* PLAYERCHARACTER_H */

