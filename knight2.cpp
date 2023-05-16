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
        res += temp->get_item_name();
        temp = temp->get_next_item();
        if (temp) res += ",";
    }

    res += "]";
    return res;
};

BaseItem * DragonKnight_Bag::get(ItemType itemType) {
    if (itemType == ANTIDOTE) return nullptr;
    if (this->numbers > 0) return this->head_item;
    else return nullptr;
};

/* * * END implementation of class BaseBag * * */

DragonKnight_Bag::DragonKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (int i = 0; i < number_phoenixdownI; i++){
            if (i < 5) {
                BaseItem* newItem = new PhoenixDownI();
                this->insertFirst(newItem);
            }
            else break;
        }
        
    }
    
    if (number_antidote > 0) {
        for (int i = 0; i < number_antidote; i++) {
            if (i < 5) {
                BaseItem* newItem = new Antidote();
                this->insertFirst(newItem);
            }
            else break;
        }
    }
};

LancelotKnight_Bag::LancelotKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (int i = 0; i < number_phoenixdownI; i++){
            if (i < 5) {
                BaseItem* newItem = new PhoenixDownI();
                this->insertFirst(newItem);
            }
            else break;
        }
        
    }
    
    if (number_antidote > 0) {
        for (int i = 0; i < number_antidote; i++) {
            if (i < 5) {
                BaseItem* newItem = new Antidote();
                this->insertFirst(newItem);
            }
            else break;
        }
    }
};

PaladinKnight_Bag::PaladinKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (int i = 0; i < number_phoenixdownI; i++){
            if (i < 5) {
                BaseItem* newItem = new PhoenixDownI();
                this->insertFirst(newItem);
            }
            else break;
        }
        
    }
    
    if (number_antidote > 0) {
        for (int i = 0; i < number_antidote; i++) {
            if (i < 5) {
                BaseItem* newItem = new Antidote();
                this->insertFirst(newItem);
            }
            else break;
        }
    }
};

NormalKnight_Bag::NormalKnight_Bag(BaseKnight* knight, int number_phoenixdownI, int number_antidote) {
    this->knight = knight;
    this->numbers = 0;
    this->head_item = 0;
    this->tail_item = 0;
    
    if (number_phoenixdownI > 0) {
        for (int i = 0; i < number_phoenixdownI; i++){
            if (i < 5) {    
                BaseItem* newItem = new PhoenixDownI();
                this->insertFirst(newItem);
            }
            else break;
        }
        
    }
    
    if (number_antidote > 0) {
        for (int i = 0; i < number_antidote; i++) {
            if (i < 5) {
                BaseItem* newItem = new Antidote();
                this->insertFirst(newItem);
            }
            else break;
        }
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
    BaseKnight * knight = 0;
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
    
    if (!first_step && !second_step) {
        lastKnight->died = true;
    }
};
/* * * END implementation of class BaseKnight * * */
bool NormalKnight::fight_knight(BaseOpponent* opponent) {
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
                if (this->hp <= 0) return false;
            }
            return true;
        }
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
            return true;
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
            if (this->hp <= 0) return false;
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
            if (this->hp <= 0) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool PaladinKnight::fight_knight(BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        this->set_gil(this->gil + opponent->get_gil());
        return true;
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
            return true;
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
            if (this->hp <= 0) return false;
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
            if (this->hp <= 0) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool LancelotKnight::fight_knight(BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        this->set_gil(this->gil + opponent->get_gil());
        return true;
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
            return true;
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
            if (this->hp <= 0) return false;
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
            if (this->hp <= 0) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
};

bool DragonKnight::fight_knight(BaseOpponent* opponent) {
    if (opponent->get_event_id() >= 1 && opponent->get_event_id() <= 5) {
        if (this->level >= opponent->get_levelO()) {
            this->set_gil(this->gil + opponent->get_gil());
            return true;
        }
        else {
            this->hp = this->hp - opponent->get_baseDamage() * (opponent->get_levelO() - this->level);
            if (this->hp <= 0) {
                this->revival(this);
                if (this->hp <= 0) return false;
            }
            return true;
        }
    }
    else if (opponent->get_event_id() == 6) {
        if (this->level >= opponent->get_levelO()) {
            this->set_level(this->level + 1);
            return true;
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
            if (this->hp <= 0) return false;
            else return true;  
        }
    }
    else {
        cout << "ERROR: OPPONENT->GET_EVENT_ID FAILED!" << endl;
        return false;
    }
}; 
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

            this->knights_arr[i] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);;

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
    bool win = this->ptr_lastKnight->fight_knight(opponent);
    return win;
};

bool ArmyKnights::update_army_knight_info(bool win) {
    if (!win) {
        this->number_knights = this->number_knights - 1;
        if (this->number_knights > 0) {
            this->ptr_lastKnight = this->knights_arr[this->number_knights - 1];
            return true;
        }
        else {
            return false;
        }
    } else return true;
};

void ArmyKnights::update_gil_info_army_knight() {
    if (this->ptr_lastKnight->get_gil_changes() > 0) {
        if (this->number_knights >= 2) {
            for (int j = this->number_knights - 2; j >= 0; j--) {
                this->knights_arr[j]->set_gil(this->knights_arr[j]->get_gil() + this->knights_arr[j + 1]->get_gil_changes());
                this->knights_arr[j + 1]->set_gil_changes(0);
                if (this->knights_arr[j]->get_gil_changes() > 0) continue;
                else break;
            }
        }
        else return;
    }

    this->knights_arr[0]->set_gil_changes(0); 
}

bool ArmyKnights::adventure (Events * events) {
    int number_events = events->count();
    for (int i = 0; i < number_events; i++) {
        if (events->get(i) == 1) {
            BaseOpponent* ptr_MadBear = new MadBear(i, 1);
            bool win = false;
            bool continue_flag = false;

            do
            {
                win = this->fight(ptr_MadBear);
                if (win) {
                    this->update_gil_info_army_knight();
                    break;
                }
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_MadBear;
                    this->printInfo();
                    return false;
                }

                this->printInfo();
            } while (continue_flag);
            
            delete ptr_MadBear;
        }
        else if (events->get(i) == 2) {
            BaseOpponent* ptr_Bandit = new Bandit(i, 2);
            bool win = false;
            bool continue_flag = false;
            
            do
            {
                win = this->fight(ptr_Bandit);
                if (win) {
                    this->update_gil_info_army_knight();
                    break;
                }
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_Bandit;
                    this->printInfo();
                    return false;
                }
                this->printInfo();
            } while (continue_flag);
            
            delete ptr_Bandit;
        }
        else if (events->get(i) == 3) {
            BaseOpponent* ptr_LordLupin = new LordLupin(i, 3);
            bool win = false;
            bool continue_flag = false;
            
            do
            {
                win = this->fight(ptr_LordLupin);
                if (win) {
                    this->update_gil_info_army_knight();
                    break;
                }
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_LordLupin;
                    this->printInfo();
                    return false;
                }
                this->printInfo();
            } while (continue_flag);
            
            delete ptr_LordLupin;
        }
        else if (events->get(i) == 4) {
            BaseOpponent* ptr_Elf = new Elf(i, 4);
            bool win = false;
            bool continue_flag = false;
            
            do
            {
                win = this->fight(ptr_Elf);
                if (win) {
                    this->update_gil_info_army_knight();
                    break;
                }
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_Elf;
                    this->printInfo();
                    return false;
                }
                this->printInfo();
            } while (continue_flag);
            
            delete ptr_Elf;
        }
        else if (events->get(i) == 5) {
            BaseOpponent* ptr_Troll = new Troll(i, 5);
            bool win = false;
            bool continue_flag = false;
            
            do
            {
                win = this->fight(ptr_Troll);
                if (win) {
                    this->update_gil_info_army_knight();
                    break;
                }
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_Troll;
                    this->printInfo();
                    return false;
                }
                this->printInfo();
            } while (continue_flag);
            
            delete ptr_Troll;
        }
        else if (events->get(i) == 6) {
            BaseOpponent* ptr_Tornbery = new Tornbery(i, 6);
            bool win = false;
            bool continue_flag = false;
            
            do
            {
                win = this->fight(ptr_Tornbery);
                if (win) break;
                continue_flag = update_army_knight_info(win);
                if (!continue_flag) {
                    delete ptr_Tornbery;
                    this->printInfo();
                    return false;
                }
                this->printInfo();
            } while (continue_flag);
            
            delete ptr_Tornbery;
        }
        else if (events->get(i) == 7) {
            BaseOpponent* ptr_QueenOfCards = new QueenOfCards(i, 7);
            bool win = this->fight(ptr_QueenOfCards);
            delete ptr_QueenOfCards;
            this->update_gil_info_army_knight();
            bool continue_flag = update_army_knight_info(win);
            if (!continue_flag) return false;
        }
        else if (events->get(i) == 8) {
            BaseOpponent* ptr_Nina = new NinaDeRings(8);
            bool win = this->fight(ptr_Nina);
            delete ptr_Nina;
            bool continue_flag = update_army_knight_info(win);
            if (!continue_flag) return false;
        }
        else if (events->get(i) == 9) {
            BaseOpponent* ptr_Durian = new DurianGarden(9);
            bool win = this->fight(ptr_Durian);
            delete ptr_Durian;
            bool continue_flag = update_army_knight_info(win);
            if (!continue_flag) return false;
        }
        else if (events->get(i) == 10) {
            if (!this->omega_weapon_flag) {
                BaseOpponent* ptr_OmegaWeapon = new OmegaWeapon(10);
                this->omega_weapon_flag = true;
                bool win = false;
                bool continue_flag = false;
                
                do
                {
                    win = this->fight(ptr_OmegaWeapon);
                    if (win) break;
                    continue_flag = update_army_knight_info(win);
                    if (!continue_flag) {
                        delete ptr_OmegaWeapon;
                        this->printInfo();
                        return false;
                    }
                    this->printInfo();
                } while (continue_flag);
                
                delete ptr_OmegaWeapon;
            }
        }
        else if (events->get(i) == 11) {
            if (!this->hades) {
                BaseOpponent* ptr_Hades = new Hades(11);
                this->hades = true;
                bool win = false;
                bool continue_flag = false;
                int number_items_in_bag = 0;
                int gil_before_revival = 0;
                
                do
                {
                    number_items_in_bag = this->ptr_lastKnight->get_bag()->get_number_items();
                    gil_before_revival = this->ptr_lastKnight->get_gil();
                    
                    win = this->fight(ptr_Hades);
                    if (win) {
                        if (number_items_in_bag == this->ptr_lastKnight->get_bag()->get_number_items() && this->ptr_lastKnight->get_gil() == gil_before_revival) {
                            this->paladin_shield = true;
                        }
                        break;
                    }
                    continue_flag = update_army_knight_info(win);
                    if (!continue_flag) {
                        delete ptr_Hades;
                        this->printInfo();
                        return false;
                    }
                    this->printInfo();
                } while (continue_flag);
                
                delete ptr_Hades;
            }
        }
        else if (events->get(i) == 112) {
            BaseItem* new_item = new PhoenixDownII;
            bool insert = this->ptr_lastKnight->get_bag()->insertFirst(new_item);
            if (!insert) {
                if (this->number_knights >= 2) {
                    for (int j = this->number_knights - 2; j >= 0; j--) {
                        insert = this->knights_arr[j]->get_bag()->insertFirst(new_item);
                        if (insert) break;
                    }

                    if (!insert) delete new_item;
                }
                else {
                    delete new_item;
                }
            }
        }
        else if (events->get(i) == 113) {
            BaseItem* new_item = new PhoenixDownIII;
            bool insert = this->ptr_lastKnight->get_bag()->insertFirst(new_item);
            if (!insert) {
                if (this->number_knights >= 2) {
                    for (int j = this->number_knights - 2; j >= 0; j--) {
                        insert = this->knights_arr[j]->get_bag()->insertFirst(new_item);
                        if (insert) break;
                    }

                    if (!insert) delete new_item;
                }
                else {
                    delete new_item;
                }
            } 
        }
        else if (events->get(i) == 114) {
            BaseItem* new_item = new PhoenixDownIV;
            bool insert = this->ptr_lastKnight->get_bag()->insertFirst(new_item);
            if (!insert) {
                if (this->number_knights >= 2) {
                    for (int j = this->number_knights - 2; j >= 0; j--) {
                        insert = this->knights_arr[j]->get_bag()->insertFirst(new_item);
                        if (insert) break;
                    }

                    if (!insert) delete new_item;
                }
                else {
                    delete new_item;
                }
            }
        }
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
            if (this->excalibur_sword) {
                this->printInfo(); 
                return true;
            }
            else {
                if (this->paladin_shield && this->guinevere_hair && this->lancelot_spear) {
                    int HP_ultimecia = 5000;
                    double lancelot_base_damage = 0.05;
                    double paladin_base_damage = 0.06;
                    double dragon_base_damage = 0.075;
                    bool first_normal_knight = false;

                    for (int j = this->number_knights - 1; j >= 0; j--) {
                        if (this->knights_arr[j]->get_knightType() == LANCELOT && !this->knights_arr[j]->get_died()) 
                        {
                            int level = this->knights_arr[j]->get_level();
                            int HP = this->knights_arr[j]->get_hp();
                            HP_ultimecia = HP_ultimecia - floor(HP * level * lancelot_base_damage);
                        }
                        else if (this->knights_arr[j]->get_knightType() == PALADIN && !this->knights_arr[j]->get_died())
                        {
                            int level = this->knights_arr[j]->get_level();
                            int HP = this->knights_arr[j]->get_hp();
                            HP_ultimecia = HP_ultimecia - floor(HP * level * paladin_base_damage);
                        }
                        else if (this->knights_arr[j]->get_knightType() == DRAGON && !this->knights_arr[j]->get_died()) {
                            int level = this->knights_arr[j]->get_level();
                            int HP = this->knights_arr[j]->get_hp();
                            HP_ultimecia = HP_ultimecia - floor(HP * level * dragon_base_damage);
                        }
                        else {
                            if (!first_normal_knight && !this->knights_arr[j]->get_died()) {
                                this->ptr_lastKnight = this->knights_arr[j];
                                first_normal_knight = true;
                            }
                        }

                        if (HP_ultimecia > 0) {
                            this->knights_arr[j]->set_died(true);
                            this->knights_arr[j]->set_hp(0, this->knights_arr[j]->get_maxhp());
                            this->number_knights = this->number_knights - 1;
                        }
                    }

                    if (HP_ultimecia > 0) {
                        this->ptr_lastKnight = 0;
                        this->number_knights = 0;
                        this->printInfo(); 
                        return false;                        
                    }
                    else {
                        this->printInfo(); 
                        return true;
                    }
                }
                else {
                    this->ptr_lastKnight = 0;
                    this->number_knights = 0;
                    this->printInfo(); 
                    return false;
                
                }
            }
        }

        this->printInfo();  
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
};

Hades::Hades(int event_id) {
    this->id_event = event_id;
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
    if (knight->get_hp() < int(knight->get_maxhp() / 4)) 
        return true;
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