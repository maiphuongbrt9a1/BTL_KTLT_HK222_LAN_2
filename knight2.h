#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV, PALADIN_SHIELD, 
                LANCELOT_SPEAR, GUINEVERE_HAIR, EXCALIBUR_SWORD, NULL_ITEM};

class BaseItem;
class BaseKnight;
class BaseOpponent {
    public:
    BaseOpponent() {};
    ~BaseOpponent() {};
};

class MadBear : public BaseOpponent {
    protected:
    // xac dinh cac thong so cho tung muc tieu
    // gom tien, levelo, basedamage
};
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
protected:
    int numbers;
    BaseKnight* knight;
    BaseItem * head_item;
    BaseItem* tail_item;
};

class DragonKnight_Bag : public BaseBag {
    public:
    DragonKnight_Bag() {};
    DragonKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote);
    ~DragonKnight_Bag() {};
};
class LancelotKnight_Bag : public BaseBag {
    public:
    LancelotKnight_Bag(){};
    LancelotKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote);
    ~LancelotKnight_Bag(){};
};
class PaladinKnight_Bag : public BaseBag {
    public:
    PaladinKnight_Bag(){};
    PaladinKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote);
    ~PaladinKnight_Bag(){};
};
class NormalKnight_Bag : public BaseBag {
    public:
    NormalKnight_Bag(){};
    NormalKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote);
    ~NormalKnight_Bag(){};
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
    KnightType get_knightType() {return this->knightType;};

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

    BaseKnight** get_knights_arr () {return this->knights_arr;};
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
    
    void set_next_item (BaseItem* item) {this->next = item;};
    BaseItem* get_next_item() {return this->next;};
    
    void set_item_type(ItemType itemType) {this->item = itemType;};
    ItemType get_item_type () {return this->item;};
    
    BaseItem () {
        this->item = NULL_ITEM;
        this->next = 0;
    };

    ~BaseItem() {};
protected:
    ItemType item;
    BaseItem* next;
};

class Antidote : public BaseItem {
    public:
    Antidote() {
        this->item = NULL_ITEM;
        this->next = 0;
    };

    Antidote(ItemType itemType = NULL_ITEM, BaseItem* nextItem = 0) {
        this->item = itemType;
        this->next = nextItem;
    };

    ~Antidote() {};
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );

};
class PhoenixDownI : public BaseItem {
    public:
    PhoenixDownI(){
        this->item = NULL_ITEM;
        this->next = 0;
    };
    PhoenixDownI(ItemType itemType = NULL_ITEM, BaseItem* nextItem = 0) {
        this->item = itemType;
        this->next = nextItem;
    };
    ~PhoenixDownI(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownII : public BaseItem {
    public:
    PhoenixDownII(){
        this->item = NULL_ITEM;
        this->next = 0;
    };

    PhoenixDownII(ItemType itemType = NULL_ITEM, BaseItem* nextItem = 0) {
        this->item = itemType;
        this->next = nextItem;
    };
    ~PhoenixDownII(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIII : public BaseItem {
    public:
    PhoenixDownIII(){
        this->item = NULL_ITEM;
        this->next = 0;
    };

    PhoenixDownIII(ItemType itemType = NULL_ITEM, BaseItem* nextItem = 0) {
        this->item = itemType;
        this->next = nextItem;
    };
    ~PhoenixDownIII(){};;
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight );
};
class PhoenixDownIV : public BaseItem {
    public:
    PhoenixDownIV(){
        this->item = NULL_ITEM;
        this->next = 0;
    };

    PhoenixDownIV(ItemType itemType = NULL_ITEM, BaseItem* nextItem = 0) {
        this->item = itemType;
        this->next = nextItem;
    };
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
    ~KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__