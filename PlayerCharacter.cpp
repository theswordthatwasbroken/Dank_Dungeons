/* 
 * File:   PlayerCharacter.cpp
 * Author: James Sharman
 * 
 * Created on 17 June 2014, 11:22 AM
 */

#include "PlayerCharacter.h"

using namespace std;

PlayerCharacter::PlayerCharacter() {
}

PlayerCharacter::PlayerCharacter(string pc_name, int str, int agi, int intel, int chr, int hp, int current_room) {
    setName(pc_name);
    setStr(str);
    setAgi(agi);
    setInt(intel);
    setChr(chr);
    setHP(hp);
    setCurrentRoom(current_room);
}

void PlayerCharacter::setName(string name) {
    pc_name = name;
}

void PlayerCharacter::setStr(int str) {
    pc_strength = str;
}

void PlayerCharacter::setAgi(int agi) {
    pc_agility = agi;
}

void PlayerCharacter::setInt(int intel) {
    pc_intelligence = intel;
}

void PlayerCharacter::setChr(int chr) {
    pc_charisma = chr;
}

void PlayerCharacter::setHP(int hp) {
    pc_hp = hp;
}

void PlayerCharacter::setCurrentRoom(int room_index) {
    pc_current_room = room_index;
}

string PlayerCharacter::getName() {
    return pc_name;
}

int PlayerCharacter::getStr() {
    return pc_strength;
}

int PlayerCharacter::getStrBonus() {
    pc_strbonus = pc_strength / 5;
    return pc_strbonus;
}

int PlayerCharacter::getAgi() {
    return pc_agility;
}

int PlayerCharacter::getAgiBonus() {
    pc_agibonus = pc_agility / 3;
    return pc_agibonus;
}

int PlayerCharacter::getInt() {
    return pc_intelligence;
}

int PlayerCharacter::getChr() {
    return pc_charisma;
}

int PlayerCharacter::getHP() {
    return pc_hp;
}

int PlayerCharacter::getCurrentRoom() {
    return pc_current_room;
}