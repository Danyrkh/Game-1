/*!
    \file
    \brief Header file with description of all classes
    \warning It's strongly not recommended to change the value of M. If it happens and the program can be executed incorrectly, then the developer's protection will work and the value of M will be taken equal to 0
 */
#ifndef Classes_hpp
#define Classes_hpp

#include <iostream>
#include "GetRandomNumber.hpp"
#define M 0

/*!
    \brief Abstract base class
 
    The class contains a set of pure virtual functions and fields inherited by derived classes
 */
class Creature {
protected:
    std::string name; ///< Character's name
    int attack = 0; ///< Character attack
    int defend = 0; ///< Character defend
    int hp = 0; ///< Character health points
    int damage = 0; ///< Character's maximum damage
    int modifier = 0; ///< Attack modifier
    int gen = 0; ///< The actual value of the character's damage calculated at the moment of impact
    
public:
    virtual void Attack(Creature* obj) = 0;
    
    virtual int GetAttack() const = 0;
    
    virtual int GetDefend() const = 0;
    
    virtual int GetHealth() const = 0;
    
    virtual int GetDamage() const = 0;
    
    virtual std::string GetName() const = 0;
    
    virtual void SetAttack(int _attack) = 0;
    
    virtual void SetDefend(int _defend) = 0;
    
    virtual void SetHealth(int _hp) = 0;
    
    virtual void SetDamage(int _damage) = 0;
    
    virtual void SetName(const std::string& s) = 0;
    
    virtual ~Creature();
    
};

/*!
    \brief Derived class Monster
 
    The class contains the overridden functions of the base class
 */
class Monster: public Creature {
private:
    void SetAttack(int _attack) override;
    
    void SetDefend(int _defend) override;
    
public:
    Monster(int _attack, int _defend);

    int GetAttack() const override;
    
    int GetDefend() const override;
    
    int GetHealth() const override;
    
    int GetDamage() const override;
    
    std::string GetName() const override;
    
    void SetHealth(int _hp) override;
    
    void SetDamage(int _damage) override;
    
    void SetName(const std::string& s) override;
    
    void Attack(Creature* obj) override;
    
};

/*!
    \brief Derived class Player
 
    it's singleton class. The class contains the overridden functions of the base class and can only have one single player object
 */
class Player: public Creature {
private:
    Player();
    ~Player();
    
    static Player* PlayerConnection; ///< Static internal variable that holds a single instance of a class
    int counter_reg = 0; ///< Counter of first aid kits used
    
    Player(Player const&) = delete; ///< Prohibit copy operator
    Player& operator= (Player const&) = delete; ///< Prohibit assignment operator
    
public:
    static Player* GetPlayer();
    
    static Player* CheckPlayer();
    
    int GetAttack() const override;
    
    int GetDefend() const override;
    
    int GetHealth() const override;
    
    int GetDamage() const override;
    
    std::string GetName() const override;
    
    void SetAttack(int _attack) override;
    
    void SetDefend(int _defend) override;
    
    void SetHealth(int _hp) override;
    
    void SetDamage(int _damage) override;
    
    void SetName(const std::string& s) override;
    
    void Regeneration(int max_player_hp);
    
    void Attack(Creature* obj) override;
    
};

#endif /* Classes_hpp */
