#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {ANTIDOTE = 0, PHOENIXDOWN, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV, PALADIN_SHIELD, 
                LANCELOT_SPEAR, GUINEVERE_HAIR, EXCALIBUR_SWORD, NULL_ITEM};

class BaseItem;
class BaseBag;
class BaseKnight;
class BaseOpponent;
class ArmyKnights;

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
    bool died;

public:
    BaseKnight() {};
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    virtual bool fight (BaseOpponent* opponent) = 0;
    string toString() const;
    
    bool is_paladin(int HP) const;
    bool is_lancelot(int HP) const;
    bool is_dragon_knight(int HP) const;
    KnightType get_knightType() {return this->knightType;};

    int get_gil() const {return this->gil;};
    void set_gil(int gil) {
        if (gil > 999) this->gil = 999;
        else this->gil = gil;};

    int get_hp() const {return this->hp;};
    void set_hp(int hp, int maxhp) {
        if (hp <= maxhp) {this->hp = hp;}
        else this->hp = maxhp;
    };

    int get_maxhp() const {return this->maxhp;};

    void set_level(int level) {
        if (level > 10) this->level = 10;
        else this->level = level;};
    int get_level() const {return this->level;};

    int get_antidote() const {return this->antidote;};
    void set_antidote(int i) {
        if (i <= 5) this->antidote = i;
        else this->antidote = 5;};

    BaseBag* get_bag() {return this->bag;};

    void revival(BaseKnight* lastKnight); 
    ~BaseKnight() {};
};

class PaladinKnight : public BaseKnight {
    public:
    PaladinKnight() {};
    bool fight (BaseOpponent* opponent);
    ~PaladinKnight() {delete this->bag;};
};

class LancelotKnight : public BaseKnight {
    public:
    LancelotKnight() {};
    bool fight (BaseOpponent* opponent);
    ~LancelotKnight() {delete this->bag;};
};

class DragonKnight : public BaseKnight {
    public:
    DragonKnight() {};
    bool fight (BaseOpponent* opponent);
    ~DragonKnight() {delete this->bag;};
};

class NormalKnight : public BaseKnight {
    public:
    NormalKnight() {};
    bool fight (BaseOpponent* opponent);
    ~NormalKnight() {delete this->bag;};
};

class BaseOpponent {
public:
    virtual int get_event_id () = 0;
    virtual int get_levelO () = 0;
    virtual int get_baseDamage () = 0;
    virtual int get_gil () = 0;
    virtual int get_event_index () = 0;

    BaseOpponent() {};
    ~BaseOpponent() {};
    
protected:
    int levelO;
    int baseDamage;
    int i;
    int id_event;
    int gil;
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

    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    
    ~MadBear() {};    
// protected:
//     int levelO;
//     int baseDamage;
//     int i;
//     int id_event;
//     int gil;
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
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~Bandit() {};
// protected:
//     int levelO;
//     int baseDamage;
//     int i;
//     int id_event;
//     int gil;
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
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~LordLupin() {};
// protected:
//     int levelO;
//     int baseDamage;
//     int i;
//     int id_event;
//     int gil;
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
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~Elf() {};

// protected:
//     int levelO;
//     int baseDamage;
//     int i;
//     int id_event;
//     int gil;
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
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~Troll() {};
// protected:
//     int levelO;
//     int baseDamage;
//     int i;
//     int id_event;
//     int gil;
};

class Tornbery : public BaseOpponent {
public:
    Tornbery() {};
    Tornbery(int i, int id_event) {
        this->i = i;
        this->id_event = id_event;
        this->levelO = (this->i + this->id_event) % 10 + 1;
    };
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~Tornbery() {};

// protected:
//     int levelO;
//     int i;
//     int id_event;
//     // bool poisoned;
};

class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards() {};
    QueenOfCards(int i, int id_event, BaseKnight* lastKnight);
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~QueenOfCards() {};

// protected:
//     int levelO;
//     int i;
//     int id_event;
//     int gil;
//     int prize_money;
};


class NinaDeRings : public BaseOpponent {
public:
    NinaDeRings() {};
    NinaDeRings(int event_id, BaseKnight* lastKnight);
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
    ~NinaDeRings() {};
};
class DurianGarden : public BaseOpponent {
public:
    DurianGarden() {};
    DurianGarden(int event_id, BaseKnight* lastKnight);
    ~DurianGarden() {};
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
};

class OmegaWeapon : public BaseOpponent {
public:
    OmegaWeapon(){};
    OmegaWeapon(int event_id, BaseKnight* lastKnight, ArmyKnights* army);
    ~OmegaWeapon(){};
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
};

class Hades : public BaseOpponent {
    Hades(){};
    Hades(int event_id, BaseKnight* lastKnight, ArmyKnights* army);
    ~Hades(){}; 
    int get_event_id () {return this->id_event;};
    int get_levelO () {return this->levelO;};
    int get_baseDamage () {return this->baseDamage;};
    int get_gil () {return this->gil;};
    int get_event_index () {return this->i;};
};

class BaseBag {
public:
    BaseBag() {};
    ~BaseBag() {};
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    
    BaseKnight* get_knight_name () {return this->knight;};
    BaseItem* get_head_item() {return this->head_item;};
    void set_head_item (BaseItem* ptr_head_item) {this->head_item = ptr_head_item;};
    void set_tail_item (BaseItem* ptr_tail_item) {this->tail_item = ptr_tail_item;};
    void set_knight_name (BaseKnight* knight) {this->knight = knight;};
    int get_number_items() {return this->numbers;};
    void set_number_items(int i) {this->numbers = i;};
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
    void set_PaladinShield(bool flag) {this->paladin_shield = flag;};
    bool hasLancelotSpear() const;
    void set_LancelotSpear(bool flag) {this->lancelot_spear = flag;};
    bool hasGuinevereHair() const;
    void set_GuinevereHair(bool flag) {this->guinevere_hair = flag;};
    bool hasExcaliburSword() const;
    void set_ExcaliburSword(bool flag) {this->excalibur_sword = flag;};

    void printInfo() const;
    void printResult(bool win) const;
    BaseKnight* getKnight(int i) {return this->knights_arr[i];};
    BaseKnight** get_knights_arr () {return this->knights_arr;};

    void set_omega_weapon_flag(bool flag) {this->omega_weapon_flag = flag;};
    bool get_omega_weapon_flag() const {return this->omega_weapon_flag;};
    
    void set_hades_flag(bool flag) {this->hades = flag;};
    bool get_hades_flag() const {return this->hades;};
private:
    BaseKnight** knights_arr;
    BaseKnight* ptr_lastKnight;
    string file_armyknights;
    int number_knights;
    bool paladin_shield;
    bool lancelot_spear;
    bool guinevere_hair;
    bool excalibur_sword;
    bool omega_weapon_flag;
    bool hades;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    
    void set_next_item (BaseItem* item) {this->next = item;};
    BaseItem* get_next_item() {return this->next;};
    
    void set_item(BaseItem* item) {this->item = item;};
    BaseItem* get_item () {return this->item;};

    void set_item_type(ItemType itemType) {this->item_type = itemType;};
    ItemType get_item_type () {return this->item_type;};
    
    BaseItem () {
        this->item = 0;
        this->next = 0;
        this->item_type = NULL_ITEM;
    };

    ~BaseItem() {};
protected:
    BaseItem* item;
    BaseItem* next;
    ItemType item_type;
};

class Antidote : public BaseItem {
    public:
    Antidote(){
        this->item = 0;
        this->next = 0;
        this->item_type = ANTIDOTE;
    };
    ~Antidote() {};
    bool canUse ( BaseKnight * knight );
    void use ( BaseKnight * knight ){};

};
class PhoenixDownI : public BaseItem {
    public:
    PhoenixDownI(){
        this->item = 0;
        this->next = 0;
        this->item_type = PHOENIXDOWNI;
    };
    ~PhoenixDownI(){};
    bool canUse ( BaseKnight * knight ){};
    void use ( BaseKnight * knight ){};
};
class PhoenixDownII : public BaseItem {
    public:
    PhoenixDownII(){
        this->item = 0;
        this->next = 0;
        this->item_type = PHOENIXDOWNII;
    };
    ~PhoenixDownII(){};
    bool canUse ( BaseKnight * knight ){};
    void use ( BaseKnight * knight ){};
};
class PhoenixDownIII : public BaseItem {
    public:
    PhoenixDownIII(){
        this->item = 0;
        this->next = 0;
        this->item_type = PHOENIXDOWNIII;
    };
    ~PhoenixDownIII(){};
    bool canUse ( BaseKnight * knight ){};
    void use ( BaseKnight * knight ){};
};
class PhoenixDownIV : public BaseItem {
    public:
    PhoenixDownIV(){
        this->item = 0;
        this->next = 0;
        this->item_type = PHOENIXDOWNIV;
    };
    ~PhoenixDownIV(){};
    bool canUse ( BaseKnight * knight ){};
    void use ( BaseKnight * knight ){};
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