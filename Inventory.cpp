/* 
 * File:   Inventory.cpp
 * Author: James Sharman
 * 
 * Created on 28 July 2014, 1:53 PM
 */

#include "Inventory.h"

using namespace std;

Inventory::Inventory() {  
}

Inventory::Inventory(vector<Item> inv_vec) {
    setInvVector(inv_vec);
    setTotalArmor(0);
    setTotalDamage(0);
}

vector<Item> Inventory::getInvVector() {
    return inventory_vec;
}

void Inventory::setInvVector(vector<Item> inv_vec) {
    inventory_vec = inv_vec;
}

void Inventory::addItem(int item_index, int amount, int equipped, vector<Item> item_vec) {
    int a = 0;
    int item_found = 0;
    while (a < inventory_vec.size()) {
        if (inventory_vec[a].getIndex() == item_index) {
            item_found = 1;
            inventory_vec[a].setAmount(inventory_vec[a].getAmount() + 1);
            break;
        }
        a++;
    }
    if (item_found == 0) {
        Item inv_item = item_vec[item_index];
        inv_item.setAmount(amount);
        inv_item.setEquipped(equipped);
        inventory_vec.push_back(inv_item);   
    }
    setInvVector(inventory_vec);
}

void Inventory::dropItem(int inv_index) {
    int amount = inventory_vec[inv_index].getAmount();
    if (amount < 2) {
        inventory_vec.erase(inventory_vec.begin() + inv_index);
    } else if (amount > 1)  {
        inventory_vec[inv_index].setAmount(inventory_vec[inv_index].getAmount() - 1);
    }
}

void Inventory::showInventoryItems(PlayerCharacter game_pc) {
    cout << endl;
    cout << game_pc.getName() << endl;
    int item_amount;
    int item_equip;;
    int item_index;
    int item_weight;
    int total_weight = 0;
    string item_name;
    string item_type;
    int ivec_size = inventory_vec.size();
    int i = 0;
    
    cout << "-------------" << endl;
    cout << "You are carrying: " << endl;    
    i = 0;
    while (i < ivec_size) {
        item_index = inventory_vec[i].getIndex();
        item_equip = inventory_vec[i].getEquipped();
        item_type = inventory_vec[i].getType();
        item_weight = inventory_vec[i].getWeight();
        item_name = inventory_vec[i].getName();
        item_amount = inventory_vec[i].getAmount();
        total_weight = total_weight + item_weight;
        cout << inventory_vec[i].getName();
        
        if (item_equip == 1) {
            cout << " [equipped] ";
            if (item_type == "armor") {
                cout << "[amr +" << inventory_vec[i].getArmor() << "] ";
                
            } else if (item_type == "melee") {
                cout << "[dmg +" << inventory_vec[i].getDamage() << "] ";
            }
        }
        
        if (item_amount > 1) {
            cout << " [x" << inventory_vec[i].getAmount() << "]";
        }
        
        cout << endl;
        i++;
    }

    cout << "[items weight: " << total_weight << "]"  << endl;
    cout << "[armor: " << getTotalArmor() << "]" << endl;
    cout << "[damage: " << getTotalDamage() << "]" << endl;
    cout << "[hp: " << game_pc.getHP() << "]" << endl;
    cout << endl;
}

void Inventory::setTotalArmor(int amr) {
    total_armor = amr;
}

void Inventory::setTotalDamage(int dmg) {
    total_damage = dmg;
}

int Inventory::getTotalArmor() {
    int i = 0;
    int armor_count = 0;
    while (i < inventory_vec.size()) {
        if (inventory_vec[i].getType() == "armor" && inventory_vec[i].getEquipped() == 1) {
            armor_count = armor_count + inventory_vec[i].getArmor();
        }
        i++;
    }
    return armor_count;
}

int Inventory::getTotalDamage() {
    int i = 0;
    int damage_count = 0;
    int weapon_equipped = 0;
    while (i < inventory_vec.size()) {
        if (inventory_vec[i].getType() == "melee" && inventory_vec[i].getEquipped() == 1) {
            weapon_equipped = 1;
            damage_count = damage_count + inventory_vec[i].getDamage();
        }
        i++;
    }
    if (weapon_equipped == 0) {
        damage_count = 3;
    }
    return damage_count;
}

int Inventory::checkInvForItem(string item_name) {
    int i = 0;
    while (i < inventory_vec.size()) {
        string inv_name = inventory_vec[i].getName();
        inv_name = toLowerCase(inv_name);
        item_name = toLowerCase(item_name);
        if (inv_name == item_name) {
            return 1;
        }
        i++;
    }
    return 0;
}

string Inventory::toLowerCase(string text_string) {
    transform(text_string.begin(), text_string.end(), text_string.begin(), ::tolower);
    return text_string;
}