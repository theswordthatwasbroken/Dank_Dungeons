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

using namespace std;

class Room {
private:
    string room_name;
    string room_descrip;
    
public:
    Room();
    Room(string, string);
    void setName(string);
    void setDescrip(string);
    string getName();
    string getDescrip();
};

#endif	/* ROOM_H */

