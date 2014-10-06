/* 
 * File:   Room.h
 * Author: James Sharman
 *
 * Created on 17 June 2014, 2:47 PM
 */

#ifndef ROOM_H
#define	ROOM_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "NPC.h"

using namespace std;

class Room {
private:
    string room_name;
    string room_descrip;
    vector<int> room_item_vec;
    vector<int> room_exit_vec;
    vector<NPC> room_npc_vec;
    
public:
    Room();
    //Room(string, string, vector<int>, vector<int>);
    Room(string, string);
    void showRoomDesc();
    void setName(string);
    void setDescrip(string);
    void setRoomItems(vector<int>);
    void setRoomExits(vector<int>);
    void setRoomNPCs(vector<NPC>);
    string getName();
    string getDescrip();
    vector<int> getRoomItems();
    vector<int> getRoomExits();
    vector<NPC> getRoomNPCs();
    int checkRoomForItem(int);
};

#endif	/* ROOM_H */

