#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem* item) {
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
        if (temp->get_item_type() == itemType) {return temp;}
        else temp = temp->get_next_item();
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
            res += "PhoenixII";
        else if (temp->get_item_type() == PHOENIXDOWNIII) 
            res += "PhoenixIII";
        else if (temp->get_item_type() == PHOENIXDOWNIV)
            res += "PhoenixIV";
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
            BaseItem* newItem = new PhoenixDownI(PHOENIXDOWNI);
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote(ANTIDOTE);
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
            BaseItem* newItem = new PhoenixDownI(PHOENIXDOWNI);
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote(ANTIDOTE);
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
            BaseItem* newItem = new PhoenixDownI(PHOENIXDOWNI);
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote(ANTIDOTE);
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
            BaseItem* newItem = new PhoenixDownI(PHOENIXDOWNI);
            this->insertFirst(newItem);
        }
        
    }
    
    if (number_antidote > 0) {
        BaseItem* newItem = new Antidote(ANTIDOTE);
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
    
    if (knight->is_paladin(maxhp)) {
        knight = new PaladinKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->bag = new PaladinKnight_Bag(knight, phoenixdownI, antidote);

        knight->knightType = PALADIN;
    }
    else if (knight->is_lancelot(maxhp)) {
        knight = new LancelotKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;

        knight->bag = new LancelotKnight_Bag(knight, phoenixdownI, antidote);
        knight->knightType = LANCELOT;
    }
    else if (knight->is_dragon_knight(maxhp)) {
        knight = new DragonKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        knight->bag = new DragonKnight_Bag(knight, phoenixdownI, antidote);

        knight->knightType = DRAGON;
    }
    else {
        knight = new NormalKnight;
        knight->id = id;
        knight->hp = maxhp;
        knight->maxhp = maxhp;
        knight->level = level;
        knight->gil = gil;
        knight->antidote = antidote;
        
        knight->bag = new NormalKnight_Bag(knight, phoenixdownI, antidote);
        knight->knightType = NORMAL;
    }

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

bool ArmyKnights::fight(BaseOpponent * opponent) {};
bool ArmyKnights::adventure (Events * events){};
int ArmyKnights::count() const {return this->number_knights;};
BaseKnight * ArmyKnights::lastKnight() const {return this->ptr_lastKnight;};

bool ArmyKnights::hasPaladinShield() const {};
bool ArmyKnights::hasLancelotSpear() const {};
bool ArmyKnights::hasGuinevereHair() const {}; 
bool ArmyKnights::hasExcaliburSword() const {};

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
void KnightAdventure::run() {};

/* * * END implementation of class KnightAdventure * * */