/* 
 * File:   Room.cpp
 * Author: James Sharman
 * 
 * Created on 17 June 2014, 2:47 PM
 */

#include "Room.h"

using namespace std;

Room::Room() {
}

/*Room::Room(string roomName, string roomDescrip, vector<int> ri_vec, vector<int> re_vec) {
    setName(roomName);
    setDescrip(roomDescrip);
    setRoomItems(ri_vec);
    setRoomExits(re_vec);
}*/

Room::Room(string roomName, string roomDescrip) {
    setName(roomName);
    setDescrip(roomDescrip);
}

void Room::setName(string roomName) {
    room_name = roomName;
}

void Room::setDescrip(string roomDescrip) {
    room_descrip = roomDescrip;
}

void Room::setRoomItems(vector<int> ri_vec) {
    room_item_vec = ri_vec;
}

int Room::checkRoomForItem(int item_index) {
    vector<int> ri_vec = room_item_vec;
    int ri_count = ri_vec.size();
    int i = 0;
    
    while (i < ri_count) {
        if (ri_vec[i] == item_index) {
            return 1;
        }
        i++;
    }
    
    return 0;
}

void Room::setRoomExits(vector<int> re_vec) {
    room_exit_vec = re_vec;
}

void Room::setRoomNPCs(vector<NPC> npc_vec) {
    room_npc_vec = npc_vec;
}

string Room::getName() {
    return room_name;
}

string Room::getDescrip() {
    return room_descrip;
}

vector<int> Room::getRoomItems() {
    return room_item_vec;
}

vector<int> Room::getRoomExits() {
    return room_exit_vec;
}

vector<NPC> Room::getRoomNPCs() {
    return room_npc_vec;
}