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

using namespace std;

class Item {
private:
    string item_name;
    string descrip;
    string type;
    int weight;
    int damage;
    int armor;
    
public:
    Item();
    Item(string, string, string, int, int, int);
    void setName(string);
    void setDescrip(string);
    void setType(string);
    void setWeight(int);
    void setDamage(int);
    void setArmor(int);
    string getName();
    string getDescrip();
    string getType();
    int getWeight();
    int getDamage();
    int getArmor();
};

#endif	/* ITEM_H */

