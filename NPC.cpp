/* 
 * File:   NPC.cpp
 * Author: James Sharman
 * 
 * Created on 25 August 2014, 9:41 AM
 */

#include "NPC.h"

using namespace std;

NPC::NPC() {
}

NPC::NPC(string name, int hp, int amr, Inventory npc_inv, int hostile) {
    setName(name);
    setHP(hp);
    setAmr(amr);
    setInv(npc_inv);
    setHostile(hostile);
}

void NPC::setName(string name) {
    npc_name = name;
}

void NPC::setHP(int hp) {
    npc_hp = hp;
}

void NPC::setAmr(int amr) {
    npc_amr = amr;
}

void NPC::setInv(Inventory npc_inven) {
    npc_inv = npc_inven;
}

void NPC::setHostile(int hostile_flag) {
    hostile = hostile_flag;
}

string NPC::getName() {
    return npc_name;
}

int NPC::getHP() {
    return npc_hp;
}

int NPC::getAmr() {
    return npc_amr;
}

Inventory NPC::getInv() {
    return npc_inv;
}

int NPC::getHostile() {
    return hostile;
}