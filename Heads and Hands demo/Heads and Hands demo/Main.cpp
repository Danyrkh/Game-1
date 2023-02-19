/*!
    \file
    \brief Creation of characters and their interaction
    \author Daniil Remennykh -//- danielerkh@gmail.com
 
    In the main function, there is an interaction with the user: character creation and game simulation
 */
#include <string>
#include <vector>
#include <limits>
#include "Classes.hpp"
#include "GetRandomNumber.hpp"
#include "FilteredInput.hpp"
using namespace std;
 
int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    vector<Monster> vec;
    string hero, name, command, aggressor, ans;
    int attack, defend, player_damage, player_health, max_monsters_attack = 0, min_monster_defend = 20, counter = 0;
    Player* player_obj = nullptr;
    
    while(1) {
        counter++;
        cout << "Which character do you want to create? Enter: Monster or Player?" << endl;
        
        FilteredInput(hero);
        while (hero != "Monster" && hero != "Player") {
            cout << "Oops... You entered the wrong character name. Try again!" << endl;
            FilteredInput(hero);
        }
        if (Player::CheckPlayer() != 0 && hero == "Player") {
            cout << "The player has already been created!" << endl;
            counter--;
            continue;
        }

        cout << "Enter character name" << endl;
        FilteredInput(name);
        
        cout << "Enter attack and defense parameters for the character separated by a space. Parameters have a range from 1 to 20" << endl;
        cin >> attack >> defend;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (attack < 1 || attack > 20 || defend < 1 || defend > 20) {
            cout << "Oops... You entered the wrong attack and defense parameters. Try again!" << endl;
            cin >> attack >> defend;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        if (hero == "Monster") {
            Monster monster_obj(attack, defend);
            monster_obj.SetName(name);
            vec.push_back(monster_obj);
            if (vec.back().GetAttack() > max_monsters_attack) {
                max_monsters_attack = vec.back().GetAttack();
            }
            if (vec.back().GetDefend() < min_monster_defend) {
                min_monster_defend = vec.back().GetDefend();
            }
            cout << "Monster " << vec.back().GetName() << " created!" << endl;
        }
        else {
            if (Player::CheckPlayer() == 0) {
                player_obj = Player::GetPlayer();
                player_obj->SetAttack(attack);
                player_obj->SetDefend(defend);
                player_obj->SetName(name);
                cout << "Player " << player_obj->GetName() << " сreated!" << endl;
            }
        }
        
        cout << "What's next? You can add more characters or start attacking. Enter: Add or Attack" << endl;
        FilteredInput(command);
        while (command != "Add" && command != "Attack") {
            cout << "Oops... You entered the incorrect command. Try again!" << endl;
            FilteredInput(command);
        }
        if (command == "Add") {
            cout << "Add more characters!" << endl;
            continue;
        } else if (counter == 1) {
            cout << "Too few characters. Add more!" << endl;
            continue;
        }
        else if (player_obj == nullptr) {
            cout << "Add Player!" << endl;
            continue;
        }
        else if (command == "Attack") {
            player_health = max_monsters_attack - player_obj->GetDefend() + 1;
            if (player_health <= 0) {
                player_health = 1;
            }
            player_obj->SetHealth(player_health);
            player_damage = player_obj->GetAttack() - min_monster_defend + 1;
            if (player_damage <= 0) {
                player_damage = 1;
            }
            player_obj->SetDamage(player_damage);
            break;
        }
    }
     
    cout << "So you have hero " << player_obj->GetName() << " and " << vec.size() << " monsters" << endl;
    cout << "Hero " << player_obj->GetName() << " came to the lair of monsters to give them a fight. What will happen next?" << endl;
    
    while(!vec.empty()) {
        cout << "Who will attack: the Monster or the Player? Enter: Monster or Player" << endl;
        FilteredInput(aggressor);
        while (aggressor != "Monster" && aggressor != "Player") {
            cout << "Oops... You entered the wrong character name. Try again!" << endl;
            FilteredInput(aggressor);
        }
        if (aggressor == "Monster") {
            cout << "Monster " << vec.back().GetName() << " are attacking!" << endl;
            vec.back().Attack(player_obj);
            if (player_obj->GetHealth() == 0) {
                cout << "You lose!" << endl;
                break;
            }
            else if (player_obj->GetHealth() < player_health) {
                cout << "Use first aid kit? Enter: Yes or No" << endl;
                FilteredInput(ans);
                while (ans != "Yes" && ans != "No") {
                    cout << "Oops... You entered the wrong command. Try again!" << endl;
                    FilteredInput(ans);
                }
                if (ans == "Yes") {
                    player_obj->Regeneration(player_health);
                }
            }
        }
        else {
            cout << player_obj->GetName() << " are attacking!" << endl;
            player_obj->Attack(&vec.back());
            if (vec.back().GetHealth() == 0) {
                cout << vec.back().GetName() << " is defeated" << endl;
                vec.pop_back();
                cout << "It's done! One of the monsters has been defeated. Let's go next!" << endl;
            }
        }
        if (vec.empty()) {
            cout << "Ou, all monsters defeated!" << endl;
            cout << "You Win!" << endl;
        }
        else {
            cout << "Next step. ";
        }
    }
    
    cout << "Game over" << endl;
}
