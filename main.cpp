/* 
 * File:   main.cpp
 * Author: James Sharman
 *
 * Created on 16 June 2014, 10:47 AM
 */

/*string input = line;
istringstream ss(input);
string token;

while(getline(ss, token, ',')) {
    cout << token << endl;
}*/

#include <cstdlib>
#include <string>
#include "Main_Game.h"
using namespace std;
/*
 * 
 */
int main() {
    int myvar = 25;
    cout << &myvar << endl;;
    cout << myvar << endl;
    Main_Game main_game;
    main_game.startGame();
    return 0;
}
