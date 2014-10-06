/* 
 * File:   Item.h
 * Author: James Sharman
 *
 * Created on 17 June 2014, 1:51 PM
 */

#ifndef ITEM_H
#define	ITEM_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:
    string item_name;
    string descrip;
    string type;
    int weight;
    int damage;
    int armor;
    int amount;
    int equipped;
    int item_index;
    int searchable;
    vector<Item> item_vec;
    
public:
    Item();
    Item(int, string, string, string, int, int, int, int, int);
    void setName(string);
    void setDescrip(string);
    void setType(string);
    void setWeight(int);
    void setDamage(int);
    void setArmor(int);
    void setAmount(int);
    void setEquipped(int);
    void setIndex(int);
    void setSearchable(int);
    void setItemInv(vector<Item>);
    string getName();
    string getDescrip();
    string getType();
    int getWeight();
    int getDamage();
    int getArmor();
    int getAmount();
    int getEquipped();
    int getIndex();
    int getSearchable();
    vector<Item> getItemInv();
};

#endif	/* ITEM_H */

