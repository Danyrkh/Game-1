/*!
    \file
    \brief File with the implementation of all classes
 */
#include "Classes.hpp"

/*!
    Creature's destructor
 */
Creature::~Creature() {}

/*!
    Sets the monster's attack
    \param[in] _attack Monster's attack
    \warning The function is hidden and its use in the program is undesirable, as it can lead to incorrect operation of the entire program.
 */
void Monster::SetAttack(int _attack) {}

/*!
    Sets the monster's defend
    \param[in] _defend Monster's defend
    \warning The function is hidden and its use in the program is undesirable, as it can lead to incorrect operation of the entire program.
 */
void Monster::SetDefend(int _defend) {}

/*!
    Moster's object constructor
    \param[in] _attack Monster's attack values
    \param[in] _defend Monster's defend values
 */
Monster::Monster(int _attack, int _defend) { 
    attack = _attack;
    defend = _defend;
}

/*!
    Has no parameters
    \return Monster's attack value
 */
int Monster::GetAttack() const { 
    return attack;
}

/*!
    Has no parameters
    \return Monster's defend value
 */
int Monster::GetDefend() const { 
    return defend;
}

/*!
    Has no parameters
    \return Monster's health value
 */
int Monster::GetHealth() const { 
    return (hp < 0) ? 0 : hp;
}

/*!
    Has no parameters
    \return Monster's maximum damage value
 */
int Monster::GetDamage() const { 
    return damage;
}

/*!
    Has no parameters
    \return Monster's name
 */
std::string Monster::GetName() const { 
    return name;
}

/*!
    Sets the monster's health value
    \param[in] _hp Monster's health value
 */
void Monster::SetHealth(int _hp) { 
    hp = (_hp < 0) ? 0 : _hp;
}

/*!
    Sets the monster's maximum damage value
    \param[in] _damage Monster's maximum damage value
 */
void Monster::SetDamage(int _damage) { 
    damage = (_damage < 0) ? 0 : _damage;
}

/*!
    Sets the monster's name
    \param[in] s Monster's name
 */
void Monster::SetName(const std::string &s) { 
    name = s;
}

/*!
    Simulates a monster attack
    \param[in] obj Attacked object
 */
void Monster::Attack(Creature *obj) { 
    int old_hp = obj->GetHealth();
    modifier = GetAttack() - obj->GetDefend() + 1;
    if (modifier <= 0) {
        modifier = 1;
    }
    if (GetDamage() == 0) {
        SetDamage(modifier);
    }
    for (;modifier != 0; modifier--) {
        int num = GetRandomNumber();
        if (num == 5 || num == 6) {
            std::cout << GetName() << " swings to hit..." << std::endl;
            gen = GetRandomNumber(M, GetDamage());
            obj->SetHealth(obj->GetHealth() - gen);
            break;
        }
    }
    if (old_hp == obj->GetHealth()) {
        std::cout << GetName() << " missed! You are lucky!" << std::endl;
    }
    else {
        if (gen == GetDamage()) {
            std::cout << GetName() << " delivered his most powerful blow! He managed to take away " << gen << " units of health" << std::endl;
            std::cout << "The hero " << obj->GetName() << " has a hard fate..." << std::endl;
        }
        else {
            std::cout << GetName() << " hit! He managed to take away " << gen << " units of health" << std::endl;
            std::cout << "Hero " << obj->GetName() << " have " << obj->GetHealth() << " lives left" << std::endl;
        }
    }
}

/*!
    Player's constructor
 */
Player::Player() {}

/*!
    Player's destructor
 */
Player::~Player() { 
    delete PlayerConnection;
}

/*!
    Creates an object if there was none before
    \return Reference to an object
 */
Player *Player::GetPlayer() { 
    if (PlayerConnection == nullptr) {
        PlayerConnection = new Player();
    }
    return PlayerConnection;
}

/*!
    Checks if the object has already been created
    \return Reference to an object if the object has already been created. 0 otherwise
 */
Player *Player::CheckPlayer() { 
    return (PlayerConnection == nullptr) ? 0 : PlayerConnection;
}

/*!
    Has no parameters
    \return Player's attack value
 */
int Player::GetAttack() const { 
    return attack;
}

/*!
    Has no parameters
    \return Player's defend value
 */
int Player::GetDefend() const { 
    return defend;
}

/*!
    Has no parameters
    \return Player's health value
 */
int Player::GetHealth() const {
    return (hp < 0) ? 0 : hp;
}

/*!
    Has no parameters
    \return Player's maximum damage value
 */
int Player::GetDamage() const { 
    return damage;
}

/*!
    Has no parameters
    \return Player's name
 */
std::string Player::GetName() const { 
    return name;
}

/*!
    Sets the palyer's attack
    \param[in] _attack Player's attack
 */
void Player::SetAttack(int _attack) { 
    attack = _attack;
}

/*!
    Sets the player's defend
    \param[in] _defend Player's defend
 */
void Player::SetDefend(int _defend) { 
    defend = _defend;
}

/*!
    Sets the player's health value
    \param[in] _hp Player's health value
 */
void Player::SetHealth(int _hp) { 
    hp = (_hp < 0) ? 0 : _hp;
}

/*!
    Sets the player's maximum damage value
    \param[in] _damage Player's maximum damage value
 */
void Player::SetDamage(int _damage) { 
    damage = (_damage < 0) ? 0 : _damage;
}

/*!
    Sets the player's name
    \param[in] s Player's name
 */
void Player::SetName(const std::string &s) { 
    name = s;
}

/*!
    Restores the player's health by 50% of the maximum level
    \param[in] max_player_hp Maximum player's health points
 */
void Player::Regeneration(int max_player_hp) { 
    if (counter_reg != 3) {
        hp += max_player_hp / 2;
        if (hp > max_player_hp) {
            hp -= (hp - max_player_hp);
        }
        counter_reg++;
        std::cout << "First aid kit used. " << 3 - counter_reg <<" left" << std::endl;
        std::cout << GetName() << " have " << GetHealth() << std::endl;
    }
    else {
        std::cout << "First aid kits are over!" << std::endl;
    }
}

/*!
    Simulates a player attack
    \param[in] obj Attacked object
 */
void Player::Attack(Creature *obj) { 
    int old_hp = obj->GetHealth();
    modifier = GetAttack() - obj->GetDefend() + 1;
    if (modifier <= 0) {
        modifier = 1;
    }
    if (old_hp == 0) {
        obj->SetHealth(modifier);
        old_hp = obj->GetHealth();
    }
    for (;modifier != 0; modifier--) {
        int num = GetRandomNumber();
        if (num == 5 || num == 6) {
            std::cout << GetName() << " swings to hit..." << std::endl;
            gen = GetRandomNumber(M, GetDamage());
            obj->SetHealth(obj->GetHealth() - gen);
            break;
        }
    }
    if (old_hp == obj->GetHealth()) {
        std::cout << GetName() << " missed! How is this possible?!" << std::endl;
    }
    else {
        if (gen == GetDamage()) {
            std::cout << GetName() << " delivered his most powerful blow! He managed to take away " << gen << " units of health" << std::endl;
            std::cout << "The monster " << obj->GetName() << " has a hard fate..." << std::endl;
        }
        else {
            std::cout << GetName() << " hit! He managed to take away " << gen << " units of health" << std::endl;
            std::cout << "Monster " << obj->GetName() << " have " << obj->GetHealth() << " lives left" << std::endl;
        }
    }
}

Player *Player::PlayerConnection = nullptr; ///< Initialization of an internal static variable
