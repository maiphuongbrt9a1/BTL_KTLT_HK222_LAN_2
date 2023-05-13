#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem* item) {
    if (item == nullptr) return false;
    if(this->head_item == 0) {
        this->numbers = 1;
        this->head_item = item;
        this->tail_item = this->head_item;
        this->head_item->set_next_item(0);
        return true;
    }
    else {
        if (
            (this->knight->get_knightType() == DRAGON && this->numbers <= 13 && item->get_item_type() != ANTIDOTE)
            || (this->knight->get_knightType() == LANCELOT && this->numbers <= 15)
            || (this->knight->get_knightType() == NORMAL && this->numbers <= 18)
            || (this->knight->get_knightType() == PALADIN)
            ) 
        {
            this->numbers++;
            item->set_next_item(this->head_item);
            this->head_item = item;
            return true;
        }
        else return false;
    }
};

BaseItem* BaseBag::get(ItemType itemType) {
    BaseItem* temp = this->head_item;
    while(temp) {
        if (itemType == ANTIDOTE && temp->get_item_type() == itemType) {
            return temp;
        }
        else if (itemType != ANTIDOTE && temp->get_item_type() != ANTIDOTE) {
            return temp;
        }
        
        temp = temp->get_next_item();
    }

    return nullptr;
};

string BaseBag::toString() const {
    string res = "Bag[count=";
    res += to_string(this->numbers);
    res += ";";

    BaseItem* temp = this->head_item;
    while (temp) {
        if (temp->get_item_type() == ANTIDOTE) 
            res += "Antidote,";
        else if (temp->get_item_type() == PHOENIXDOWNI) 
            res += "PhoenixI,";
        else if (temp->get_item_type() == PHOENIXDOWNII)
            res += "PhoenixII,";
        else if (temp->get_item_type() == PHOENIXDOWNIII) 
            res += "PhoenixIII,";
        else if (temp->get_item_type() == PHOENIXDOWNIV)
            res += "PhoenixIV,";
        else temp = temp->get_next_item();
    }

    res += "]";
    return res;
};
/* * * END implementation of class BaseBag * * */

DragonKnight_Bag::DragonKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (size_t i = 0; i < number_phoenixdownI; i++){
            BaseItem* newItem = new PhoenixDownI();
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote();
        this->insertFirst(newItem);
    }
};

LancelotKnight_Bag::LancelotKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (size_t i = 0; i < number_phoenixdownI; i++){
            BaseItem* newItem = new PhoenixDownI();
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote();
        this->insertFirst(newItem);
    }
};

PaladinKnight_Bag::PaladinKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (size_t i = 0; i < number_phoenixdownI; i++){
            BaseItem* newItem = new PhoenixDownI();
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote();
        this->insertFirst(newItem);
    }
};

NormalKnight_Bag::NormalKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (size_t i = 0; i < number_phoenixdownI; i++){
            BaseItem* newItem = new PhoenixDownI();
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote();
        this->insertFirst(newItem);
    }
};

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight * knight;
    BaseKnight* temp = new NormalKnight;

    if (temp->is_paladin(maxhp)) {
        knight = new PaladinKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->gil_changes = 0;
        knight->antidote = antidote;
        knight->bag = new PaladinKnight_Bag(knight, phoenixdownI, antidote);
        knight->died = false;
        knight->poisoned = false;
        knight->knightType = PALADIN;
    }
    else if (temp->is_lancelot(maxhp)) {
        knight = new LancelotKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->gil_changes = 0;
        knight->antidote = antidote;
        knight->died = false;
        knight->poisoned = false;
        knight->bag = new LancelotKnight_Bag(knight, phoenixdownI, antidote);
        knight->knightType = LANCELOT;
    }
    else if (temp->is_dragon_knight(maxhp)) {
        knight = new DragonKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->gil_changes = 0;
        knight->antidote = antidote;
        knight->bag = new DragonKnight_Bag(knight, phoenixdownI, antidote);
        knight->died = false;
        knight->poisoned = false;
        knight->knightType = DRAGON;
    }
    else {
        knight = new NormalKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->gil_changes = 0;
        knight->antidote = antidote;
        knight->died = false;
        knight->poisoned = false;
        knight->bag = new NormalKnight_Bag(knight, phoenixdownI, antidote);
        knight->knightType = NORMAL;
    }

    delete temp;
    return knight;

};

bool BaseKnight::is_paladin(int HP) const {
    if (HP == 1) return 0;
    else if (HP == 2) return 1;
    int flag = 1;
    for (int i = 2; i < sqrt(HP) + 2; i++) {
        if (HP % i == 0)
        {
            flag = 0;
            break;
        }
    }
    if (flag) return 1;
    else return 0;
};

bool BaseKnight::is_lancelot(int HP) const {
    if (HP == 888) return true;
    else return false;
};

bool BaseKnight::is_dragon_knight(int HP) const {
    if (HP >= 100) {
        string s = to_string(HP);
        int a = int(s[0]) - 48;
        int b = int(s[1]) - 48;
        int c = int(s[2]) - 48;
        
        if (a*a + b*b == c*c) return true;
        else if (b*b + c*c == a*a) return true;
        else if (a*a + c*c == b*b) return true;
        else return false;
    }
    else return false;
};

void BaseKnight::revival(BaseKnight* lastKnight) {
    BaseItem* item = lastKnight->bag->get_head_item();
    bool first_step = false;
    bool second_step = false;
    while (item)
    {
        if (item->canUse(lastKnight)) {
            item->use(lastKnight);
            first_step = true;
            break;
        }

        item = item->get_next_item();
    }

    if (!first_step) {
        if (lastKnight->get_gil() >= 100) {
            lastKnight->set_hp(lastKnight->get_maxhp() / 2, lastKnight->get_maxhp());
            lastKnight->set_gil(lastKnight->get_gil() - 100);
            second_step = true;
        }
        
    }
    
    if (!second_step) {
        lastKnight->died = true;
    }
};
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights (const string & file_armyknights) {
    this->file_armyknights = file_armyknights;
    this->paladin_shield = 0;
    this->lancelot_spear = 0;
    this->guinevere_hair = 0;
    this->excalibur_sword = 0;
    this->omega_weapon_flag = 0;
    this->hades = 0;

    ifstream myfile(file_armyknights);
    if (myfile.is_open()) {
        myfile >> this->number_knights;

        this->knights_arr = new BaseKnight* [this->number_knights];

        for (int i = 0, id = 1; i < this->number_knights; i++) {
            int maxhp = 0;
            int level = 0;
            int gil = 0;
            int antidote = 0; 
            int phoenixdownI = 0;

            for (int j = 0; j < 5; j++) {
                if (j == 0) 
                    {myfile >> maxhp;}
                else if (j == 1) 
                    {myfile >> level;}
                else if (j == 2) 
                    {myfile >> phoenixdownI;}
                else if (j == 3) 
                    {myfile >> gil;}
                else 
                    {myfile >> antidote;}
            }

            BaseKnight* knight = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
            this->knights_arr[i] = knight;

            // update knight id
            id ++;
        }

        this->ptr_lastKnight = this->knights_arr[this->number_knights - 1];
        myfile.close();
    }
    else {
        cout << "ERROR: File armyknights didn't opend!\n";
    }
};

ArmyKnights::~ArmyKnights() {
    delete[] this->knights_arr;
};

bool ArmyKnights::fight(BaseOpponent * opponent) {
    return this->ptr_lastKnight->fight(opponent);
    
};

bool ArmyKnights::adventure (Events * events) {
    int number_events = events->count();
    for (int i = 0; i < number_events; i++) {
        if (events->get(i) == 1) {
            pi
        }
        else if (events->get(i) == 2) {}
        else if (events->get(i) == 3) {}
        else if (events->get(i) == 4) {}
        else if (events->get(i) == 5) {}
        else if (events->get(i) == 6) {}
        else if (events->get(i) == 7) {}
        else if (events->get(i) == 8) {}
        else if (events->get(i) == 9) {}
        else if (events->get(i) == 10) {}
        else if (events->get(i) == 11) {}
        else if (events->get(i) == 112) {}
        else if (events->get(i) == 113) {}
        else if (events->get(i) == 114) {}
        else if (events->get(i) == 95) {
            if (!this->paladin_shield) {
                this->paladin_shield = true;
            }
        }
        else if (events->get(i) == 96) {
            if (!this->lancelot_spear) {
                this->lancelot_spear = true;
            }
        }
        else if (events->get(i) == 97) {
            if (!this->guinevere_hair) {
                this->guinevere_hair = true;
            }
        }
        else if (events->get(i) == 98) {
            if (this->paladin_shield && this->lancelot_spear && this->guinevere_hair) {
                if (!this->excalibur_sword) {
                    this->excalibur_sword = true;
                }
            }
        }
        else if (events->get(i) == 99) {
            
        }
    } 
};

int ArmyKnights::count() const {return this->number_knights;};
BaseKnight * ArmyKnights::lastKnight() const {return this->ptr_lastKnight;};

bool ArmyKnights::hasPaladinShield() const {return this->paladin_shield;};
bool ArmyKnights::hasLancelotSpear() const {return this->lancelot_spear;};
bool ArmyKnights::hasGuinevereHair() const {return this->guinevere_hair;}; 
bool ArmyKnights::hasExcaliburSword() const {return this->excalibur_sword;};

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure() {
    delete this->armyKnights;
    delete this->events;
};

void KnightAdventure::loadArmyKnights(const string & file_armyknight) {
    this->armyKnights = new ArmyKnights(file_armyknight);
};

void KnightAdventure::loadEvents(const string & file_events) {
    this->events = new Events(file_events);
};
void KnightAdventure::run() {
    this->armyKnights->printResult(this->armyKnights->adventure(this->events));
};

/* * * END implementation of class KnightAdventure * * */

NinaDeRings::NinaDeRings(int event_id) {
    this->id_event = event_id;
};

QueenOfCards::QueenOfCards(int i, int id_event)  {
    this->i = i;
    this->id_event = id_event;
    this->levelO = (this->i + this->id_event) % 10 + 1;
};

DurianGarden::DurianGarden(int event_id) {
    this->id_event = event_id;
};

OmegaWeapon::OmegaWeapon(int event_id){
    this->id_event = event_id;
    // if (!army->get_omega_weapon_flag()) {
    //     if ((lastKnight->get_level() == 10 && lastKnight->get_hp() == lastKnight->get_maxhp())
    //         || (lastKnight->get_knightType() == DRAGON)) 
    //     {
    //         lastKnight->set_level(10);
    //         lastKnight->set_gil(999);
    //     }
    //     else {
    //         lastKnight->set_hp(0, lastKnight->get_maxhp());
    //         lastKnight->revival(lastKnight);
    //     }

    //     army->set_omega_weapon_flag(true);
    // }
};

Hades::Hades(int event_id) {
    this->id_event = event_id;
    // if (!army->get_hades_flag()) {

    //     if (lastKnight->get_level() >= 10 || 
    //     (lastKnight->is_paladin(lastKnight->get_maxhp()) && lastKnight->get_level() >= 8)) {
    //         if (!army->hasPaladinShield())
    //             army->set_PaladinShield(true);
    //     }
    //     else {
    //         lastKnight->revival(lastKnight);
    //     }

    //     army->set_hades_flag(true);
    // }
};


bool NormalKnight::fight (BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        if (this->level >= opponent->get_levelO()) {
            this->set_gil(this->gil + opponent->get_gil());
            return true;
        }
        else {
            this->hp = this->hp - opponent->get_baseDamage() * (opponent->get_levelO() - this->level);
            BaseItem* temp = this->bag->get_head_item();
            while(temp) {
                if (temp->canUse(this)) {
                    temp->use(this);
                    break;
                }

                temp = temp->get_next_item();
            }
            if (this->hp <= 0) {
                this->revival(this);
                if (this->died) return false;
            }
            return true;
        }
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
        }
        else {
            if (this->antidote >= 1) {
                this->poisoned = true;
                // this->antidote = this->antidote - 1;
                BaseItem* temp = this->bag->get_head_item();
                while(temp) {
                    if (temp->canUse(this)) {
                        temp->use(this);
                    }
                    temp = temp->get_next_item();
                }
                return true;
            }
            else {
                int number_items = this->bag->get_number_items();
                if (number_items == 0) {
                    this->hp = this->hp - 10;
                    if (this->hp <= 0) return false;
                    return true;
                }
                else if (number_items <= 3) {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < number_items; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    this->bag->set_tail_item(0);

                    this->hp = this->hp - 10;
                    if (this->hp <= 0) return false;
                    return true;
                }
                else {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < 3; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    
                    this->hp = this->hp - 10;
                    temp = this->bag->get_head_item();
                    while(temp) {
                        if (temp->canUse(this)) {
                            temp->use(this);
                            break;
                        }
                        temp = temp->get_next_item();
                    }
                    if (this->hp <= 0) this->revival(this);
                    if (this->hp <= 0) return false;
                    return true;
                }
            }
        }
    }
    else if (opponent->get_event_id() == 7) {
        if (this->level >= opponent->get_levelO()) {
            this->gil = this->gil * 2;
            if (this->gil > 999) {
                this->gil_changes = this->gil - 999;
                this->gil = 999;
            }
        }
        else {
            this->gil = int(this->gil / 2);
        }
        
        return true;

    }
    else if (opponent->get_event_id() == 8) {
        if (this->gil >= 50) {
            if (this->hp < int(this->maxhp / 3)) {
                this->gil = this->gil - 50;
                this->hp = this->hp + int(this->maxhp / 5);
            }
        }

        return true;
    }
    else if (opponent->get_event_id() == 9) {
        this->hp = this->maxhp;
        return true;
    }
    else if (opponent->get_event_id() == 10) {
        if (this->level >= 10 && this->hp == this->maxhp) {
            this->level = 10;
            this->gil = 999;
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;
        }
    }
    else if (opponent->get_event_id() == 11) {
        if (this->level >= 10) {
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool LancelotKnight::fight (BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        this->set_gil(this->gil + opponent->get_gil());
        return true;
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
        }
        else {
            if (this->antidote >= 1) {
                this->poisoned = true;
                // this->antidote = this->antidote - 1;
                BaseItem* temp = this->bag->get_head_item();
                while(temp) {
                    if (temp->canUse(this)) {
                        temp->use(this);
                        break;
                    }
                    temp = temp->get_next_item();
                }
                return true;
            }
            else {
                int number_items = this->bag->get_number_items();
                if (number_items == 0) {
                    this->hp = this->hp - 10;
                    if (this->hp <= 0) this->revival(this);
                    if (this->hp <= 0) return false;
                    return true;
                }
                else if (number_items <= 3) {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < number_items; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    this->bag->set_tail_item(0);

                    this->hp = this->hp - 10;
                    if (this->hp <= 0) this->revival(this);
                    if (this->hp <= 0) return false;
                    return true;
                }
                else {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < 3; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    
                    this->hp = this->hp - 10;
                    if (this->hp <= 0) this->revival(this);
                    if (this->hp <= 0) return false;
                    return true;
                }
            }
        }
    }
    else if (opponent->get_event_id() == 7) {
        if (this->level >= opponent->get_levelO()) {
            this->gil = this->gil * 2;
            if (this->gil > 999) {
                this->gil_changes = this->gil - 999;
                this->gil = 999;
            }
        }
        else {
            this->gil = int(this->gil / 2);
        }
        
        return true;

    }
    else if (opponent->get_event_id() == 8) {
        if (this->gil >= 50) {
            if (this->hp < int(this->maxhp / 3)) {
                this->gil = this->gil - 50;
                this->hp = this->hp + int(this->maxhp / 5);
            }
        }

        return true;
    }
    else if (opponent->get_event_id() == 9) {
        this->hp = this->maxhp;
        return true;
    }
    else if (opponent->get_event_id() == 10) {
        if (this->level >= 10 && this->hp == this->maxhp) {
            this->level = 10;
            this->gil = 999;
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;
        }
    }
    else if (opponent->get_event_id() == 11) {
        if (this->level >= 10) {
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool DragonKnight::fight (BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        if (this->level >= opponent->get_levelO()) {
            this->set_gil(this->gil + opponent->get_gil());
            return true;
        }
        else {
            this->hp = this->hp - opponent->get_baseDamage() * (opponent->get_levelO() - this->level);
            if (this->hp <= 0) {
                this->revival(this);
                if (this->died) return false;
            }
            return true;
        }
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
        }
        
        return true;
    }
    else if (opponent->get_event_id() == 7) {
        if (this->level >= opponent->get_levelO()) {
            this->gil = this->gil * 2;
            if (this->gil > 999) {
                this->gil_changes = this->gil - 999;
                this->gil = 999;
            }
        }
        else {
            this->gil = int(this->gil / 2);
        }
        
        return true;

    }
    else if (opponent->get_event_id() == 8) {
        if (this->gil >= 50) {
            if (this->hp < int(this->maxhp / 3)) {
                this->gil = this->gil - 50;
                this->hp = this->hp + int(this->maxhp / 5);
            }
        }

        return true;
    }
    else if (opponent->get_event_id() == 9) {
        this->hp = this->maxhp;
        return true;
    }
    else if (opponent->get_event_id() == 10) {
        this->level = 10;
        this->gil = 999;
        return true;
        
    }
    else if (opponent->get_event_id() == 11) {
        if (this->level >= 10) {
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool PaladinKnight::fight (BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        this->set_gil(this->gil + opponent->get_gil());
        return true;
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
        }
        else {
            if (this->antidote >= 1) {
                this->poisoned = true;
                // this->antidote = this->antidote - 1;
                BaseItem* temp = this->bag->get_head_item();
                while(temp) {
                    if (temp->canUse(this)) {
                        temp->use(this);
                        break;
                    }

                    temp = temp->get_next_item();
                }
                return true;
            }
            else {
                int number_items = this->bag->get_number_items();
                if (number_items == 0) {
                    this->hp = this->hp - 10;
                    if (this->hp <= 0) return false;
                    return true;
                }
                else if (number_items <= 3) {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < number_items; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    this->bag->set_tail_item(0);

                    this->hp = this->hp - 10;
                    if (this->hp <= 0) return false;
                    return true;
                }
                else {
                    BaseItem* temp = this->bag->get_head_item();
                    for (int i = 0; i < 3; i++) {
                        this->bag->set_head_item(temp->get_next_item());
                        temp->set_next_item(0);
                        delete temp;
                        this->bag->set_number_items(this->bag->get_number_items() - 1);
                        temp = this->bag->get_head_item();
                    }
                    
                    this->hp = this->hp - 10;
                    temp = this->bag->get_head_item();
                    while(temp) {
                        if (temp->canUse(this)) {
                            temp->use(this);
                            break;
                        }

                        temp = temp->get_next_item();
                    }
                    if (this->hp <= 0) this->revival(this);
                    if (this->hp <= 0) return false;
                    return true;
                }
            }
        }
    }
    else if (opponent->get_event_id() == 7) {
        if (this->level >= opponent->get_levelO()) {
            this->gil = this->gil * 2;
            if (this->gil > 999) {
                this->gil_changes = this->gil - 999;
                this->gil = 999;
            }
        }
        
        return true;

    }
    else if (opponent->get_event_id() == 8) {
        if (this->hp < int(this->maxhp / 3)) {
            this->hp = this->hp + int(this->maxhp / 5);
        }
        return true;
    }
    else if (opponent->get_event_id() == 9) {
        this->hp = this->maxhp;
        return true;
    }
    else if (opponent->get_event_id() == 10) {
        if (this->level >= 10 && this->hp == this->maxhp) {
            this->level = 10;
            this->gil = 999;
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;
        }
    }
    else if (opponent->get_event_id() == 11) {
        if (this->level >= 8) {
            return true;
        }
        else {
            this->hp = 0;
            this->revival(this);
            if (this->died) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool Antidote::canUse ( BaseKnight * knight) {
    if (knight->get_antidote() >= 1 && knight->get_poisoned()) return true;
    else return false;
};
void Antidote::use ( BaseKnight * knight ) {
    BaseItem* temp = knight->get_bag()->get_head_item();
    if (temp == this) {
        knight->get_bag()->set_head_item(temp->get_next_item());
        temp->set_next_item(0);
        delete temp;
    }
    else {
        BaseItem* prev = temp;
        while (temp->get_next_item() != this) {
            prev = temp->get_next_item();
            temp = temp->get_next_item();
        }

        temp = this->get_next_item();
        prev->set_next_item(knight->get_bag()->get_head_item());
        this->set_next_item(knight->get_bag()->get_head_item()->get_next_item());
        knight->get_bag()->get_head_item()->set_next_item(temp);
        knight->get_bag()->set_head_item(this->get_next_item());
        this->set_next_item(0);

        delete this;
    }
    
    knight->set_antidote(knight->get_antidote() - 1);
    knight->get_bag()->set_number_items(knight->get_bag()->get_number_items() - 1);
    knight->set_poisoned(false);
};

bool PhoenixDownI::canUse ( BaseKnight * knight ){
    if (knight->get_hp() <= 0) return true;
    return false;
};
void PhoenixDownI::use ( BaseKnight * knight ){
    BaseItem* temp = knight->get_bag()->get_head_item();
    if (temp == this) {
        knight->get_bag()->set_head_item(temp->get_next_item());
        temp->set_next_item(0);
        delete temp;
    }
    else {
        BaseItem* prev = temp;
        while (temp->get_next_item() != this) {
            prev = temp->get_next_item();
            temp = temp->get_next_item();
        }

        temp = this->get_next_item();
        prev->set_next_item(knight->get_bag()->get_head_item());
        this->set_next_item(knight->get_bag()->get_head_item()->get_next_item());
        knight->get_bag()->get_head_item()->set_next_item(temp);
        knight->get_bag()->set_head_item(this->get_next_item());
        this->set_next_item(0);

        delete this;
    }

    knight->set_hp(knight->get_maxhp(), knight->get_maxhp());
    knight->get_bag()->set_number_items(knight->get_bag()->get_number_items() - 1);

};

bool PhoenixDownII::canUse ( BaseKnight * knight ){
    if (knight->get_hp() < int(knight->get_maxhp() / 4)) return true;
    return false;
};
void PhoenixDownII::use ( BaseKnight * knight ){
    BaseItem* temp = knight->get_bag()->get_head_item();
    if (temp == this) {
        knight->get_bag()->set_head_item(temp->get_next_item());
        temp->set_next_item(0);
        delete temp;
    }
    else {
        BaseItem* prev = temp;
        while (temp->get_next_item() != this) {
            prev = temp->get_next_item();
            temp = temp->get_next_item();
        }

        temp = this->get_next_item();
        prev->set_next_item(knight->get_bag()->get_head_item());
        this->set_next_item(knight->get_bag()->get_head_item()->get_next_item());
        knight->get_bag()->get_head_item()->set_next_item(temp);
        knight->get_bag()->set_head_item(this->get_next_item());
        this->set_next_item(0);

        delete this;
    }
    
    knight->get_bag()->set_number_items(knight->get_bag()->get_number_items() - 1);
    knight->set_hp(knight->get_maxhp(), knight->get_maxhp());
};

bool PhoenixDownIII::canUse ( BaseKnight * knight ){
    if (knight->get_hp() < int(knight->get_maxhp() / 3)) return true;
    return false;
};
void PhoenixDownIII::use ( BaseKnight * knight ){
    BaseItem* temp = knight->get_bag()->get_head_item();
    if (temp == this) {
        knight->get_bag()->set_head_item(temp->get_next_item());
        temp->set_next_item(0);
        delete temp;
    }
    else {
        BaseItem* prev = temp;
        while (temp->get_next_item() != this) {
            prev = temp->get_next_item();
            temp = temp->get_next_item();
        }

        temp = this->get_next_item();
        prev->set_next_item(knight->get_bag()->get_head_item());
        this->set_next_item(knight->get_bag()->get_head_item()->get_next_item());
        knight->get_bag()->get_head_item()->set_next_item(temp);
        knight->get_bag()->set_head_item(this->get_next_item());
        this->set_next_item(0);

        delete this;
    }
    
    if (knight->get_hp() <= 0) {
        knight->set_hp(int(knight->get_maxhp() / 3), knight->get_maxhp());
    }
    else  {
        knight->set_hp(knight->get_hp() + int(knight->get_maxhp() / 4), knight->get_maxhp());
    }

    knight->get_bag()->set_number_items(knight->get_bag()->get_number_items() - 1);
};

bool PhoenixDownIV::canUse ( BaseKnight * knight ){
    if (knight->get_hp() < int(knight->get_maxhp() / 2)) return true;
    return false;
};
void PhoenixDownIV::use ( BaseKnight * knight ){
    BaseItem* temp = knight->get_bag()->get_head_item();
    if (temp == this) {
        knight->get_bag()->set_head_item(temp->get_next_item());
        temp->set_next_item(0);
        delete temp;
    }
    else {
        BaseItem* prev = temp;
        while (temp->get_next_item() != this) {
            prev = temp->get_next_item();
            temp = temp->get_next_item();
        }

        temp = this->get_next_item();
        prev->set_next_item(knight->get_bag()->get_head_item());
        this->set_next_item(knight->get_bag()->get_head_item()->get_next_item());
        knight->get_bag()->get_head_item()->set_next_item(temp);
        knight->get_bag()->set_head_item(this->get_next_item());
        this->set_next_item(0);

        delete this;
    }
    
    if (knight->get_hp() <= 0) {
        knight->set_hp(knight->get_maxhp() / 2, knight->get_maxhp());
    }
    else {
        knight->set_hp(knight->get_hp() + int(knight->get_maxhp() / 5), knight->get_maxhp());
    }

    knight->get_bag()->set_number_items(knight->get_bag()->get_number_items() - 1);
};