/* 
 * File:   Item.cpp
 * Author: James Sharman
 * 
 * Created on 17 June 2014, 1:51 PM
 */

#include "Item.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Item::Item() {
}

Item::Item(string item_name, string descrip, string type, int weight, int damage, int armor) {
    setName(item_name);
    setDescrip(descrip);
    setType(type);
    setWeight(weight);
    setDamage(damage);
    setArmor(armor);
}

void Item::setName(string name) {
    item_name = name;
}

void Item::setDescrip(string descr) {
    descrip = descr;
}

void Item::setType(string item_type) {
    type = item_type;
}

void Item::setWeight(int weigh) {
    weight = weigh;
}

void Item::setDamage(int dmg) {
    damage = dmg;
}

void Item::setArmor(int amr) {
    armor = amr;
}

string Item::getName() {
    return item_name;
}

string Item::getDescrip() {
    return descrip;
}

string Item::getType() {
    return type;
}

int Item::getWeight() {
    return weight;
}

int Item::getDamage() {
    return damage;
}

int Item::getArmor() {
    return armor;
}