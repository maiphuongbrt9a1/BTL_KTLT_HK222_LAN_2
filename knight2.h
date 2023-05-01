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
public:
    MadBear() {};
    
    MadBear(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->gil = 100;
        this->baseDamage = 10;
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~MadBear() {};    
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
};
class Bandit : public BaseOpponent {
public:
    Bandit() {};
    Bandit(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->gil = 150;
        this->baseDamage = 15;
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~Bandit() {};
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
};

class LordLupin : public BaseOpponent {
public:
    LordLupin() {};
    LordLupin(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->gil = 450;
        this->baseDamage = 45;
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~LordLupin() {};
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
};

class Elf : public BaseOpponent {
public:
    Elf() {};
    Elf(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->gil = 750;
        this->baseDamage = 75;
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~Elf() {};
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
};

class Troll : public BaseOpponent {
public:
    Troll() {};
    Troll(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->gil = 800;
        this->baseDamage = 95;
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~Troll() {};
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
};

class Tornbery : public BaseOpponent {
public:
    Tornbery() {};
    Tornbery(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->levelO = (this->i + this->id_event) % 10 + 1;
    };
    ~Tornbery() {};
protected:
    int levelO;
    int i;
    int id_event;
    // bool poisoned;
};

class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards() {};
    QueenOfCards(int i, int id_event, BaseKnight* lastKnight) {
        this->i = i;
        this->id_event = id_event;
        this->prize_money = lastKnight->get_gil();
        this->levelO = (this->i + this->id_event) % 10 + 1;

    };
    ~QueenOfCards() {};
protected:
    int levelO;
    int i;
    int id_event;
    int prize_money;
};

class NinaDeRings : public BaseOpponent {
public:
    NinaDeRings() {};
    NinaDeRings(BaseKnight* lastKnight) {
        if (lastKnight->get_gil() >= 50) {
            int temp = lastKnight->get_maxhp() / 3;
            if (lastKnight->get_hp() < temp) {
                int new_gil = lastKnight->get_gil() - 50;
                int new_hp = lastKnight->get_hp() + (lastKnight->get_maxhp() / 5);
                lastKnight->set_gil(new_gil);
                lastKnight->set_hp(new_hp, lastKnight->get_maxhp());
            }
        }

    };
    ~NinaDeRings() {};
};
class DurianGarden : public BaseOpponent {
public:
    DurianGarden() {};
    DurianGarden(BaseKnight* lastKnight) {
        lastKnight->set_hp(lastKnight->get_maxhp(), lastKnight->get_maxhp());
    };
    ~DurianGarden() {};
};

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

    int get_gil() const {return this->gil;};
    void set_gil(int gil) {this->gil = gil;};
    int get_hp() const {return this->hp;};
    void set_hp(int hp, int maxhp) {
        if (hp <= maxhp) {this->hp = hp;}
        else this->hp = maxhp;
    };
    int get_maxhp() const {return this->maxhp;};
    int get_level() const {return this->level;};
    int get_antidote() const {return this->antidote;};
    void set_antidote(int i) {this->antidote = i;};
    BaseBag* get_bag() {return this->bag;};

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