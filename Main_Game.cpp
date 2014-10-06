/* 
 * File:   Main_Game.cpp
 * Author: James Sharman
 * 
 * Created on 29 July 2014, 9:32 AM
 */

#include "Main_Game.h"
#include "NPC.h"
#include <ctime>
#include <locale>

Inventory pc_inventory;
vector<Room> room_vec;
vector<Item> item_vec;
vector<vector<int> > inventory_vec;
vector<int> invitem_vec;
vector<string> journal_vec;
vector<string> j_vec;
vector<NPC> npc_vec;
string room_name;
string room_descrip;

void Main_Game::startGame() {
    showMainMenu();
}

vector<Item> Main_Game::getVector() {
    return item_vec;
}

void Main_Game::showMainMenu() {
    string player_input;
    cout << "Dank Dungeons of Dreethrift v1.0" << endl;
    cout << "---------------------------" << endl;
    cout << "a. New Game" << endl;
    cout << "b. Quit" << endl;
    cout << "[input: a or b]" << endl;
    cin.clear();
    cin.sync();
    getline(cin, player_input);
    
    if (player_input == "a") {
        room_vec.clear();
        item_vec.clear();
        inventory_vec.clear();
        journal_vec.clear();
        npc_vec.clear();
        loadAssets("items.txt", "Items");
        loadAssets("searchable_items.txt","Searchable Items");
        loadAssets("npcs.txt", "NPCs");
        loadAssets("rooms.txt", "Rooms");
        loadAssets("room_exits.txt", "Room Exits");
        loadAssets("room_items.txt", "Room Items");
        loadAssets("room_npcs.txt", "Room NPCs");
        loadAssets("pc_inventory.txt", "PC Inventory");
        loadAssets("journal.txt", "Journal");
        pc_inventory = Inventory(inventory_vec);
        
        cout << endl;
        cout << "Welcome to character creation. Woo!" << endl;
        cout << "Please enter your character's name: " << endl;
        cin.clear();
        cin.sync();
        getline(cin, player_input);
        game_pc = PlayerCharacter(player_input, 15, 15, 15, 15, 20, 0);
        cout << endl;
        cout << "Welcome to the game!" << endl;
        cout << "Want to know what's going on? The journal might help." << endl;
        cout << "For actual help, type 'help'." << endl;
        showRoomDesc();
        showGameMenu();
    } else if (player_input == "b") {
        cout << "Goodbye." << endl;
        cout << "Game over." << endl;
        exit(0);
    } else {
        showMainMenu();
    }
}

PlayerCharacter Main_Game::getGamePC() {
    return game_pc;
}

void Main_Game::showGameMenu() {
    int i;
    int pc_current_room = game_pc.getCurrentRoom();
    string player_input;
    vector<string> input_vector;
    cout << "-------------------" << endl;
    cout << "inv | char | journ | go | examine | get | help | quit" << endl;
    cout << "input: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, player_input);
    
    stringstream is(player_input);
    string word;
    int number_of_words = 0;
    while (is >> word) {
        input_vector.push_back(word);
        number_of_words++;
    }
    cout << endl;
    
    if (number_of_words == 1) {
        string word1;
        word1 = input_vector[0];
        if (word1 == "inv") {
            showInventoryMenu(1);
        } else if (word1 == "quit") {
            cout << "Exit" << endl;
            showMainMenu();
        } else if (word1 == "examine") {
            showRoomDesc();
        } else if (word1 == "go" || word1 == "get") {
            cout << "error: input incomplete. Format: " << word1 << " [object]" << endl;
        } else if (word1 == "char") {
            cout << "name: " << game_pc.getName() << endl;
            cout << "STR | AGI | INT | CHR" << endl;
            cout << game_pc.getStr() << "  | ";
            cout << game_pc.getAgi() << "  | ";
            cout << game_pc.getInt() << "  | ";
            cout << game_pc.getChr() << endl;
            cout << "HP: " << game_pc.getHP() << endl;
            cout << "AMR: " << pc_inventory.getTotalArmor() << endl;
            cout << "DMG: " << pc_inventory.getTotalDamage() << endl;
        } else if (word1 == "journ" || word1 == "journal") {
            i = 0;
            int journal_count = journal_vec.size();
            while (i < journal_count) {
                cout << journal_vec[i] << endl;
                i++;
            }
        } else if (word1 == "help") {
            cout << "The objective of the game is to find a horse and leave." << endl;
            cout << "available commands:" << endl;
            cout << "inv -- opens inventory" << endl;
            cout << "char -- shows character info" << endl;
            cout << "journ[al] -- shows journal entries" << endl;
            cout << "go [room exit] -- move to another room" << endl;
            cout << "examine [object in room] -- shows name and description of item. The command on it's own will show the room description." << endl;
            cout << "get [object in room] -- if appropriate, adds item to inventory" << endl;
            cout << "help -- help!" << endl;
            cout << "quit -- back to main menu" << endl;
        } else {
            cout << "error: invalid input." << endl;
        }
        
    } else if (number_of_words == 2) {
        string word1;
        string word2;
        string word_input;
        int vec_size;
        word1 = input_vector[0];
        word2 = input_vector[1];
        word_input = toLowerCase(word2);
        if (word1 == "examine") {
            i = 0;
            string item_name;
            int item_found = 0;
            vector<int> ri_vec;
            ri_vec = room_vec[pc_current_room].getRoomItems();
            vec_size = ri_vec.size();
            while (i < vec_size) {
                item_name = item_vec[ri_vec[i]].getName();
                item_name = toLowerCase(item_name);
                if (item_name == word_input) {
                    examineObject(word2);
                    item_found = 1;
                }
                i++;
            }

            if (item_found == 0) {
                cout << "error: invalid object." << endl;
            }
            
        } else if (word1 == "go") {
            i = 0;
            pc_current_room = game_pc.getCurrentRoom();
            int room_found = 0;
            int room_index = 0;
            vector<int> re_vec;
            re_vec.clear();
            re_vec = room_vec[pc_current_room].getRoomExits();
            vec_size = re_vec.size();
            string room_exit;
            while (i < vec_size) {
                room_exit = room_vec[re_vec[i]].getName();
                room_exit = toLowerCase(room_exit);
                if (room_exit == word_input) {
                    room_found = 1;
                    room_index = re_vec[i];
                    string rname = room_vec[pc_current_room].getName();
                    rname = toLowerCase(rname);
                    if (rname == "path" && room_exit == "north") {
                        int inv_check = pc_inventory.checkInvForItem("Horse");
                        if (inv_check == 1) {
                            cout << "You get on your horse and ride north." << endl;
                            cout << "Adventure and package delivery awaits!" << endl;
                            cout << endl;
                            cout << "[FIREWORKS] [DANCE MUSIC]" << endl;
                            cout << "Congrats! You finished the game. Thanks for playing. :-)" << endl;
                            cout << "Feedback/ hate mail/ book recommendations can be sent here:" << endl;
                            cout << "theswordthatwasbroken@hotmail.com" << endl;
                            cout << endl;
                            showMainMenu();
                            
                        } else {
                            cout << "Nope. You can't leave until you've found a horse." << endl;
                            cout << "It's way too far to walk." << endl;
                            break;
                        }
                    }
                    if (rname == "pub" && room_exit == "cellar") {
                        int inv_check = pc_inventory.checkInvForItem("Cellar_Key");
                        if (inv_check == 1) {
                            changeRoom(room_index);
                        } else {
                            cout << "CLINK! The cellar's mad locked, yo." << endl;
                            cout << "Find a key! *Your finely honed courier senses tell you it's in the pub, upstairs.*" << endl;
                            break;
                        }
                    }
                    changeRoom(room_index);
                    break;
                }
                i++;
            }
            
            if (room_found == 0) {
                cout << "error: invalid room." << endl;
            }
            
        } else if (word1 == "get") {
            i = 0;
            int item_found = 0;
            int item_index;
            int room_index = game_pc.getCurrentRoom();
            vector<int> ri_vec = room_vec[room_index].getRoomItems();
            int ri_count = ri_vec.size();
            string item_name;
            while (i < ri_count) {
                item_index = ri_vec[i];
                item_name = item_vec[item_index].getName();
                item_name = toLowerCase(item_name);
                if (item_name == word_input) {
                    item_found = 1;
                    int item_weight = item_vec[item_index].getWeight();
                    if (item_weight > 100) {
                        cout << "SPLINK! This is way to heavy and/or big to take with you." << endl;
                    } else {
                        cout << "You put the the item in your inventory." << endl;
                        pc_inventory.addItem(item_index, 1, 0, item_vec);
                        ri_vec.erase(ri_vec.begin() + i);
                        room_vec[room_index].setRoomItems(ri_vec);
                    }
                    break;
                }
                i++;
            }
            
            if (item_found == 0) {
                cout << "Error: object not found." << endl;
            }
            
        } else {
            cout << "error: invalid input." << endl;
        }
        
    } else {
        cout << "error: invalid input." << endl;
    }
    
    showGameMenu();
}

void Main_Game::showInventoryMenu(int show_items) {
    int i;
    inventory_vec = pc_inventory.getInvVector();
    int ivec_size = inventory_vec.size();
    int item_index;
    int show_items_flag = 0;
    string player_input;
    cout << endl;
    cout << "Inventory" << endl;
    
    if (show_items == 1) {
        pc_inventory.showInventoryItems(game_pc);
    }
    
    cout << "-------------" << endl;
    cout << "list | examine | drop | equip | unequip | help | exit" << endl;
    cout << "input: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, player_input);
    vector<string> input_vector;
    
    stringstream is(player_input);
    string word;
    int number_of_words = 0;
    while (is >> word) {
        input_vector.push_back(word);
        number_of_words++;
    }
    
    if (number_of_words > 0) {
        string word1 = input_vector[0];
        
        if (number_of_words == 1) {
            if (word1 == "examine" || word1 == "drop" || word1 == "equip" || word1 == "unequip") {
                cout << word1 << " what? " << endl;
                
            } else if (word1 == "exit") {
                cout << endl;
                showGameMenu();
                
            } else if (word1 == "list") {
                pc_inventory.showInventoryItems(game_pc);
                
            } else if (word1 == "help") {
                cout << "available commands:" << endl;
                cout << "list -- shows inventory items, hp, amr and dmg" << endl;
                cout << "examine [object in inventory] -- shows item name, description and stats" << endl;
                cout << "drop [object in inventory] -- removes item from inventory, puts item in current room" << endl;
                cout << "equip [object in inventory] -- equips unequipped armor or weapon" << endl;
                cout << "unequip [object in inventory] -- unequips equipped armor or weapon" << endl;
                cout << "help -- help!" << endl;
                cout << "exit-- exits inventory, returns to game." << endl;
            } else {
                cout << "error: input incorrect" << endl;
            }

        } else if (number_of_words > 1) {
            string word2 = input_vector[1];
            i = 0;
            int item_found = 0;
            while (i < ivec_size) {
                inventory_vec = pc_inventory.getInvVector();
                item_index = inventory_vec[i].getIndex();
                int equipped = inventory_vec[i].getEquipped();
                string word_input = toLowerCase(word2);
                string inv_item = toLowerCase(item_vec[item_index].getName());
                
                if (inv_item == word_input) {
                    item_found = 1;
                    if (word1 == "examine") {
                        examineObject(word2);
                        break;
                        
                    } else if (word1 == "drop") {
                        cout << "Item dropped on the ground." << endl;
                        pc_inventory.dropItem(i);
                        vector<int> ri_vec;
                        int item_index = inventory_vec[i].getIndex();
                        int room_index = game_pc.getCurrentRoom();
                        ri_vec = room_vec[room_index].getRoomItems();
                        ri_vec.push_back(item_index);
                        room_vec[room_index].setRoomItems(ri_vec);
                        break;
                        
                    } else if (word1 == "equip") {
                        if (equipped == 1) {
                            cout << "error: item already equipped." << endl;
                        } else {
                            if (inventory_vec[i].getType() == "melee") {
                                int a = 0;
                                while (a < inventory_vec.size()) {
                                    if (inventory_vec[a].getType() == "melee" && inventory_vec[a].getEquipped() == 1) {
                                        cout << inventory_vec[a].getName() << " unequipped." << endl;
                                        inventory_vec[a].setEquipped(0);
                                        pc_inventory.setInvVector(inventory_vec);
                                    }
                                    a++;
                                }
                                cout << inventory_vec[i].getName() << " equipped." << endl;
                                inventory_vec[i].setEquipped(1);
                                pc_inventory.setInvVector(inventory_vec);
                            } else if (inventory_vec[i].getType() == "armor") {
                                inventory_vec[i].setEquipped(1);
                                pc_inventory.setInvVector(inventory_vec);
                                cout << inventory_vec[i].getName() << " equipped." << endl;
                            } else {
                                cout << "error: item not equippable." << endl;
                            }
                        }
                        
                    } else if (word1 == "unequip") {
                        if (equipped == 0) {
                            cout << "error: item already unequipped." << endl;
                        } else {
                            inventory_vec[i].setEquipped(0);
                            pc_inventory.setInvVector(inventory_vec);
                            cout << inventory_vec[i].getName() << " unequipped." << endl;
                            
                        }
                    }
                }
                i++;
            }
            
            if (item_found == 0) {
                cout << "error: item not found." << endl;
            }
        }   
    }
    showInventoryMenu(show_items_flag);
}

void Main_Game::showCombatMenu() {
    string player_input;
    int number_of_words = 0;
    int combat_over = 0;
    int npcs_alive = 0;
    vector<string> input_vector;
    int i = 0;
    int wpn_equipped = 0;
    vector<Item> pc_inv = pc_inventory.getInvVector();
    while (i < pc_inv.size()) {
        if (pc_inv[i].getType() == "melee" && pc_inv[i].getEquipped() == 1) {
            wpn_equipped = pc_inv[i].getIndex();
        }
        i++;
    }
    
    cout << "Hostile creatures here: " << endl;
    int room_index = game_pc.getCurrentRoom();
    vector<NPC> rnpc_vec = room_vec[room_index].getRoomNPCs();
    i = 0;
    while (i < rnpc_vec.size()) {
        cout << i << ". " << rnpc_vec[i].getName();
        int npc_hp = rnpc_vec[i].getHP();
        if (npc_hp < 1) {
            cout << " | [DEAD]" << endl;
        } else {
            npcs_alive = 1;
            cout << " | HP: " << rnpc_vec[i].getHP();
            cout << " AMR: " << rnpc_vec[i].getAmr() << endl;
        }
        i++;
    }
    
    if (npcs_alive == 0) {
        cout << endl;
        cout << "You have driven your enemies before you and heard the lamentations of thier women. They're all dead." << endl;
        cout << "Combat's over." << endl;
        rnpc_vec.clear();
        room_vec[room_index].setRoomNPCs(rnpc_vec);
        return;
    }
    
    cout << endl;
    cout << "-------------" << endl;
    cout << "weapon equipped: " << item_vec[wpn_equipped].getName() << " | dmg: " << item_vec[wpn_equipped].getDamage() << endl;
    cout << "ARMOR: " << pc_inventory.getTotalArmor() << endl;
    cout << "HP: " << game_pc.getHP() << endl;
    cout << "attack | inv | run | help" << endl;
    cout << "input: " << endl;
    cin.clear();
    cin.sync();
    getline(cin, player_input);
    stringstream is(player_input);
    string word;
    while (is >> word) {
        input_vector.push_back(word);
        number_of_words++;
    }
    
    if (number_of_words == 1) {
        string word1 = input_vector[0];
        if (word1 == "help") {
            cout << "Combat! How does it work?" << endl;
            cout << "Combat roll is 0-10." << endl;
            cout << "A hit is made on 1- 10 minus opponent's armor value." << endl;
            cout << "Example: opponent has 4 armor. A hit would be a roll of 1-6, while a miss would be 0 or 7-10. Easy." << endl;
            cout << "Also, it doesn't matter if your HP drops below zero- you're actually an immortal vampire." << endl;
            cout << "available commands:" << endl;
            cout << "attack [number] -- attacks specified NPC with equipped weapon." << endl;
            cout << "inv -- shows items currently in inventory." << endl;
            cout << "run -- in theory, ends combat. In practice, doesn't do anything. It's a feature." << endl;
            cout << "help -- HELP!" << endl;
            
        } else if (word1 == "attack" || word1 == "equip") {
            cout << "error: input incomplete." << endl;
            
        } else if (word1 == "inv") {
            pc_inventory.showInventoryItems(game_pc);
            
        } else if (word1 == "run") {
            cout << endl;
            cout << "CLANG! You can't run." << endl;
            cout << endl;
        }
        
    } else if (number_of_words == 2) {
        string word1 = input_vector[0];
        string word2 = input_vector[1];
        
        if (word1 == "attack") {
            locale loc;
            int npc_count = rnpc_vec.size();
            if (isdigit(word2[0], loc) && word2.length() == 1 && stoi(word2) <= npc_count) {
                int npc_index = stoi(word2);
                if (rnpc_vec[npc_index].getHP() > 0) {
                    int npc_armor = rnpc_vec[npc_index].getAmr();
                    int npc_hp = rnpc_vec[npc_index].getHP();
                    int attack_result = attackRoll(npc_armor);
                    cout << endl;
                    cout << "You attack the " << rnpc_vec[npc_index].getName() << "." << endl;
                    if (attack_result == 1) {
                        int wpn_damage = item_vec[wpn_equipped].getDamage();
                        cout << "WACK! You hit the bad guy." << endl;
                        cout << "You did " << wpn_damage << " damage." << endl;
                        cout << endl;
                        npc_hp = npc_hp - wpn_damage;
                        rnpc_vec[npc_index].setHP(npc_hp);
                        room_vec[room_index].setRoomNPCs(rnpc_vec);
                    } else {
                        cout << "ARGH! You missed the bad guy." << endl;
                        cout << endl;
                    }

                    cout << "The bad guys attack!" << endl;
                    cout << "press any key to continue: " << endl;
                    cin.clear();
                    cin.sync();
                    getline(cin, player_input);

                    i = 0;
                    while (i < rnpc_vec.size()) {
                        if (rnpc_vec[i].getHP() > 0) {
                            cout << "You are being attacked by: " << rnpc_vec[i].getName() << endl;
                            int pc_armor = pc_inventory.getTotalArmor();
                            int pc_hp = game_pc.getHP();
                            attack_result = attackRoll(pc_armor);
                            if (attack_result == 1) {
                                Inventory npc_inv = rnpc_vec[i].getInv();
                                int npc_damage = npc_inv.getTotalDamage();
                                cout << "THUNK! The bad guy hit you. Ouch." << endl;
                                cout << "He did " << npc_damage << " damage to you." << endl;
                                cout << "You have " << pc_hp - npc_damage << " HP left." << endl;
                                cout << endl;
                                game_pc.setHP(pc_hp - npc_damage);
                            } else {
                                cout << "WHOOSH! The bad guy missed you." << endl;
                                cout << endl;
                            }
                            cout << "press any key to continue: " << endl;
                            cin.clear();
                            cin.sync();
                            getline(cin, player_input);
                        }
                        i++;
                    }
                } else {
                    cout << endl;
                    cout << "He is dead, Jim." << endl;
                }
            } else {
               cout << "error: input incorrect." << endl;
            }
        } else {
            cout << "error: input incorrect." << endl;
        }
    }
    
    if (combat_over == 0) {
        showCombatMenu();
    } else {
        cout << endl;
    }
}

int Main_Game::attackRoll(int target_armor) {
    int hit_max = 10 - target_armor;
    int miss_min = 10 - target_armor + 1;
    srand(time(NULL));
    int attack_roll =  rand() %10;
    cout << "Attack roll: " << attack_roll <<  "   [1 - " << hit_max << " = hit, " << miss_min << "+ or 0 = miss]" << endl;
    if (attack_roll < hit_max && attack_roll > 0) {
        return 1;
    } else {
        return 0;
    }
}

void Main_Game::changeRoom(int room_index) {
    game_pc.setCurrentRoom(room_index);
    showRoomDesc();
}

string Main_Game::toLowerCase(string text_string) {
    transform(text_string.begin(), text_string.end(), text_string.begin(), ::tolower);
    return text_string;
}

void Main_Game::examineObject(string item) {
    int a = 0;
    string item_param = item;
    item_param = toLowerCase(item_param);
    int item_found = 0;
    while (a < item_vec.size()) {
        string item_name;
        item_name = item_vec[a].getName();
        item_name = toLowerCase(item_name);
        if (item_name == item_param) {
            item_found = 1;
            int searchable = item_vec[a].getSearchable();
            cout << endl;
            cout << item_vec[a].getName() << endl;
            cout << item_vec[a].getDescrip() << endl;
            string item_type = item_vec[a].getType();
            if (item_type == "armor") {
                cout << "Armor: " << item_vec[a].getArmor() << endl;
            } else if (item_type == "melee") {
                cout << "Damage: " << item_vec[a].getDamage() << endl;
            }
            cout << "Weight: " << item_vec[a].getWeight() << endl;
            if (searchable == 1) {
                cout << endl;
                vector<Item> item_inv_vec = item_vec[a].getItemInv();
                cout << "There is something here. You search the object and find:" << endl;
                int x = 0;
                while (x < item_inv_vec.size()) {
                    cout << item_inv_vec[x].getName() << endl;
                    int item_index = item_inv_vec[x].getIndex();
                    pc_inventory.addItem(item_index, 1, 0, item_vec);
                    inventory_vec = pc_inventory.getInvVector();
                    x++;
                }
                item_vec[a].setSearchable(0);
                cout << "You put the items in your inventory." << endl;
            }
            break;
        }
        a++;
    }
}

void Main_Game::showRoomDesc() {
    cout << endl;
    int pc_current_room = game_pc.getCurrentRoom();
    cout << room_vec[pc_current_room].getName() << endl;
    cout << room_vec[pc_current_room].getDescrip() << endl;
    int i = 0;
    int vec_size = 0;
    vector<int> ri_vec = room_vec[pc_current_room].getRoomItems();
    vector<int> re_vec = room_vec[pc_current_room].getRoomExits();
    vector<NPC> rnpc_vec = room_vec[pc_current_room].getRoomNPCs();
    cout << "Things here: ";
    vec_size = ri_vec.size();
    while (i < vec_size) {
        cout << item_vec[ri_vec[i]].getName() << "  "; 
        i++;
    }
    cout << endl;
    
    i = 0;
    cout << "Room exits: ";
    vec_size = re_vec.size();
    while (i < vec_size) {
        cout << room_vec[re_vec[i]].getName() << "  ";
        i++;
    }
    cout << endl;
    
    i = 0;
    vec_size = rnpc_vec.size();
    if (vec_size > 0) {
        cout << endl;
        cout << "Gird your loins and into battle! You are being attacked!" << endl;
        showCombatMenu();
    }
}

void Main_Game::loadAssets(string fname, string assetType) {
    int i;
    fname = "content/" + fname;
    ifstream aStream;
    string line;
    aStream.open(fname.c_str());
    int line_count = 0;;
    
    vector<string> asset_vec;
    if (aStream.is_open()) {
        while (getline(aStream,line)) {
            string input = line;
            istringstream ss(input);
            string token;
            int asset_count = 0;
            asset_vec.clear();
            
            char delim;
            if (assetType == "Journal") {
                delim = '\n';
            } else {
                delim = ',';
            }
            
            while(getline(ss, token, delim)) {
                ostringstream convert;
                convert << token;
                token = convert.str();
                asset_vec.push_back(token);
                asset_count++;
            }
            
            if (assetType == "Rooms") {
                Room new_room;
                new_room = Room(asset_vec[0], asset_vec[1]);
                room_vec.push_back(new_room);
            
            } else if (assetType == "Room Exits") {
                i = 1;
                vector<int> rexit_vec;
                string room_name = asset_vec[0];
                int room_index = getRoomIndex(room_name);
                while (i < asset_count) {
                    int exit_index = stoi(asset_vec[i]);
                    rexit_vec.push_back(exit_index);
                    i++;
                }
                room_vec[room_index].setRoomExits(rexit_vec);
            
            } else if (assetType == "Room Items") {
                i = 1;
                int item_index;
                string room_name = asset_vec[0];
                int room_index = getRoomIndex(room_name);
                vector<int> ritem_vec;
                while (i < asset_count) {
                    item_index = stoi(asset_vec[i]);
                    ritem_vec.push_back(item_index);
                    i++;
                }
                room_vec[room_index].setRoomItems(ritem_vec);
            
            } else if (assetType == "Room NPCs") {
                string room_name = asset_vec[0];
                int room_index = getRoomIndex(room_name);
                int npc_index;
                vector<NPC> rnpc_vec;
                i = 1;
                while (i < asset_count) {
                    NPC room_npc;
                    npc_index = stoi(asset_vec[i]);
                    room_npc = npc_vec[npc_index];
                    rnpc_vec.push_back(room_npc);
                    i++;
                }
                room_vec[room_index].setRoomNPCs(rnpc_vec);
                
            } else if (assetType == "Items") {
                Item new_item;
                int ivec_count = item_vec.size();
                int damage;
                int armor;
                int weight;
                damage = stoi(asset_vec[3]);
                armor = stoi(asset_vec[4]);
                weight = stoi(asset_vec[5]);
                int amount = 1;
                int equipped = 0;
                new_item = Item(ivec_count, asset_vec[0], asset_vec[1], asset_vec[2], damage, armor, weight, amount, equipped);
                item_vec.push_back(new_item);
                
            } else if (assetType == "Searchable Items") {
                string source_item_name = asset_vec[0];
                int source_item_index = getItemIndex(source_item_name);
                vector<Item> item_store_vec;
                int item_index;
                int i = 1;
                while (i < asset_count) {
                    item_index = stoi(asset_vec[i]);
                    Item store_item = item_vec[item_index];
                    item_store_vec.push_back(store_item);
                    i++;
                }
                item_vec[source_item_index].setSearchable(1);
                item_vec[source_item_index].setItemInv(item_store_vec);
                
            } else if (assetType == "PC Inventory") {
                int ivec_size = inventory_vec.size();
                int item_index;
                int amount;
                int equipped;
                item_index = stoi(asset_vec[0]);
                amount = stoi(asset_vec[1]);
                equipped = stoi(asset_vec[2]);
                inventory_vec.push_back(item_vec[item_index]);
                inventory_vec[ivec_size].setAmount(amount);
                inventory_vec[ivec_size].setEquipped(equipped);
                
            } else if (assetType == "Journal") {
                journal_vec.push_back(asset_vec[0]);
            
            } else if (assetType == "NPCs") {
                string npc_name;
                int npc_hp;
                int npc_amr;
                Inventory npc_inv;
                int npc_hostile;
                NPC new_npc;
                vector<Item> npc_item_vec;
                npc_name = asset_vec[0];
                npc_hp = stoi(asset_vec[1]);
                npc_amr = stoi(asset_vec[2]);
                npc_hostile = stoi(asset_vec[3]);
                npc_item_vec.push_back(item_vec[10]);
                npc_item_vec.push_back(item_vec[11]);
                npc_item_vec.push_back(item_vec[5]);
                npc_item_vec.push_back(item_vec[8]);
                npc_item_vec[1].setEquipped(1);
                npc_inv = Inventory(npc_item_vec);
                new_npc = NPC(npc_name, npc_hp, npc_amr, npc_inv, npc_hostile);
                npc_vec.push_back(new_npc);
            }
            line_count++;
        }
        aStream.close();
    }
}

int Main_Game::getItemIndex(string item_name) {
    int i = 0;
    int item_index = 0;
    while (i < item_vec.size()) {
        if (item_name == item_vec[i].getName()) {
            item_index = i;
        }
        i++;
    }
    return item_index;
}

int Main_Game::getRoomIndex(string room_name) {
    int i = 0;
    int room_index = 0;
    while (i < room_vec.size()) {
        if (room_name == room_vec[i].getName()) {
            room_index = i;
        }
        i++;
    }
    return room_index;
}





int Main_Game::getPCDamage() {
    int ivec_size = inventory_vec.size();
    int i = 0;
    int item_index;
    int str_bonus;
    string item_type;
    int pc_damage = 0;
    while (i < ivec_size) {
        item_index = inventory_vec[i].getIndex();
        item_type = item_vec[item_index].getType();
        if (item_type == "melee") {
            int wpn_damage;
            wpn_damage = item_vec[item_index].getDamage();
            pc_damage = pc_damage + wpn_damage;
        }
        i++;
    }
    str_bonus = game_pc.getStrBonus();
    pc_damage = pc_damage + str_bonus;
    return pc_damage;
}