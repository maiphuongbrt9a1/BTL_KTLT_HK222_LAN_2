#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV, PALADIN_SHIELD, 
                LANCELOT_SPEAR, GUINEVERE_HAIR, EXCALIBUR_SWORD};

class BaseItem;
class BaseKnight;
class BaseOpponent {
    public:
    BaseOpponent() {};
    ~BaseOpponent() {};
};

class MadBear : public BaseOpponent {};
class Bandit : public BaseOpponent {};
class LordLupin : public BaseOpponent {};
class Elf : public BaseOpponent {};
class Troll : public BaseOpponent {};
class Tornbery : public BaseOpponent {};
class QueenOfCards : public BaseOpponent {};
class NinaDeRings : public BaseOpponent {};
class DurianGarden : public BaseOpponent {};
class OmegaWeapon : public BaseOpponent {};
class Hades : public BaseOpponent {};

class BaseBag {
public:
    BaseBag() {};
    ~BaseBag() {};
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    BaseKnight* get_knight_name () {return this->knight;};
    void set_knight_name (BaseKnight* knight) {this->knight = knight;};
private:
    BaseKnight* knight;
};

class DragonKnight_Bag : public BaseBag {
    public:
    DragonKnight_Bag() {};
    ~DragonKnight_Bag() {};
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    private:
    BaseItem** item_arr;
};
class LancelotKnight_Bag : public BaseBag {
    public:
    LancelotKnight_Bag(){};
    ~LancelotKnight_Bag(){};
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
    
    private:
    BaseItem** item_arr;
};
class PaladinKnight_Bag : public BaseBag {
    public:
    PaladinKnight_Bag(){};
    ~PaladinKnight_Bag(){};
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    private:
    BaseItem** item_arr;
};
class NormalKnight_Bag : public BaseBag {
    public:
    NormalKnight_Bag(){};
    ~NormalKnight_Bag(){};
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;

    private:
    BaseItem** item_arr;
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    BaseKnight() {};
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    bool is_paladin(int HP) const;
    bool is_lancelot(int HP) const;
    bool is_dragon_knight(int HP) const;

    ~BaseKnight() {};
};

class PaladinKnight : public BaseKnight {
    public:
    PaladinKnight() {};
    ~PaladinKnight() {delete[] this->bag;};
};

class LancelotKnight : public BaseKnight {
    public:
    LancelotKnight() {};
    ~LancelotKnight() {delete[] this->bag;};
};

class DragonKnight : public BaseKnight {
    public:
    DragonKnight() {};
    ~DragonKnight() {delete[] this->bag;};
};

class NormalKnight : public BaseKnight {
    public:
    NormalKnight() {};
    ~NormalKnight() {delete[] this->bag;};
};

class Events {
public:
    Events() {};
    Events(const string & file_events) {
        this->file_events = file_events;

        ifstream myfile(file_events);
        if (myfile.is_open()) {
            int id = 0;
            myfile >> this->number_events;

            this->id_event_arr = new int [this->number_events];
            for (int i = 0; i < this->number_events; i++) {
                myfile >> id;
                id_event_arr[i] = id;
            }     

            myfile.close();       
        }
        else {
            cout << "ERROR: File events didn't open!\n"; 
        }
    };

    ~Events() {
        delete[] this->id_event_arr;
    }

    int count() const {return this->number_events;};
    
    int get(int i) const {
        return this->id_event_arr[i];
    };
private:
    string file_events;
    int number_events;
    int* id_event_arr;
};

class ArmyKnights {
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    BaseKnight* getKnight (int i) {return this->knights_arr[i];}
private:
    BaseKnight** knights_arr;
    BaseKnight* ptr_lastKnight;
    string file_armyknights;
    int number_knights;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    BaseItem () {};
    ~BaseItem() {};
};

class Antidote : public BaseItem {
    public:
    Antidote() {};
    ~Antidote() {};
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
    
    private:

};
class PhoenixDownI : public BaseItem {
    public:
    PhoenixDownI(){};
    ~PhoenixDownI(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownII : public BaseItem {
    public:
    PhoenixDownII(){};
    ~PhoenixDownII(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIII : public BaseItem {
    public:
    PhoenixDownIII(){};
    ~PhoenixDownIII(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIV : public BaseItem {
    public:
    PhoenixDownIV(){};
    ~PhoenixDownIV(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__