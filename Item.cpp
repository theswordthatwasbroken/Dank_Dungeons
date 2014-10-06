/* 
 * File:   Item.cpp
 * Author: James Sharman
 * 
 * Created on 17 June 2014, 1:51 PM
 */

#include "Item.h"

using namespace std;

Item::Item() {
}

Item::Item(int i_index, string item_name, string descrip, string type, int weight, int damage, int armor, int amount, int equipped) {
    setName(item_name);
    setDescrip(descrip);
    setType(type);
    setWeight(weight);
    setDamage(damage);
    setArmor(armor);
    setAmount(amount);
    setEquipped(equipped);
    setIndex(i_index);
    setSearchable(0);
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

void Item::setAmount(int num) {
    amount = num;
}

void Item::setEquipped(int equip) {
    equipped = equip;
}

void Item::setIndex(int i_index) {
    item_index = i_index;
}

void Item::setSearchable(int search_flag) {
    searchable = search_flag;
}

void Item::setItemInv(vector<Item> i_vec) {
    item_vec = i_vec;
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

int Item::getAmount() {
    return amount;
}

int Item::getEquipped() {
    return equipped;
}

int Item::getIndex() {
    return item_index;
}

int Item::getSearchable() {
    return searchable;
}

vector<Item> Item::getItemInv() {
    return item_vec;
}