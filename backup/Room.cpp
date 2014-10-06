/* 
 * File:   Room.cpp
 * Author: James Sharman
 * 
 * Created on 17 June 2014, 2:47 PM
 */

#include "Room.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Room::Room() {
}

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

string Room::getName() {
    return room_name;
}

string Room::getDescrip() {
    return room_descrip;
}