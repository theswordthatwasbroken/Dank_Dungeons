/* 
 * File:   NPC.h
 * Author: James Sharman
 *
 * Created on 25 August 2014, 9:41 AM
 */

#ifndef NPC_H
#define	NPC_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "Inventory.h"

using namespace std;

class NPC {
public:
    NPC();
    NPC(string, int, int, Inventory, int);
    void setName(string);
    void setHP(int);
    void setAmr(int);
    void setInv(Inventory);
    void setHostile(int);
    string getName();
    int getHP();
    int getAmr();
    Inventory getInv();
    int getHostile();
private:
    string npc_name;
    int npc_hp;
    int npc_amr;
    Inventory npc_inv;
    int hostile;
};

#endif	/* NPC_H */

