#include "Politician.h"


/**
 * politician constructor
 */
Politician::Politician(string first_name, string last_name,
                       int d_id, int power, Politician* cha_man, Party* p) : F_name(std::move(first_name)) , L_name(std::move(last_name)), id(d_id)
                       ,power(power) ,chairman(cha_man), t_party(p) {}

/**
 * politician copy constructor from source
 */
Politician::Politician(const Politician &source): F_name(source.F_name) , L_name(source.L_name), id(source.id)
        ,power(source.power) ,chairman(source.chairman), t_party(source.t_party){}

/**
 * operator= override
 */
Politician &Politician::operator=(const Politician &source) {
    if(this == &source){ // checks for self assignment
        return *this;
    }
    this->id = source.id;
    this->F_name = source.F_name;
    this->L_name = source.L_name;
    this->power = source.power;
    this->chairman = source.chairman;
    this->t_party = source.t_party;
    return *this;
}

/**
 * getter for the politician power
 * @return
 */
int Politician::GetPower() const {
    return this->power;
}

/**
 * override == operator to compare 2 politicians based on the assumption the id is unique
 */
bool Politician::operator==(const Politician &other) const {
    bool res = this->id == other.id;
    return res;
}

/**
 * getter for the first name of the politician
 */
string Politician::GetFiName() const {
    return this->F_name;
}

/**
 * getter fo the id of the politician
 */
int Politician::GetId() const{
    if(this == nullptr){
        return -1;
    }
    return this->id;
}

/**
 * when called, updates the Politician Chairman
 * @param n_cman: the new chairman of the politician
 */
void Politician::UpdateCman(Politician *n_cman) {
    if(n_cman == nullptr){
        this->chairman = nullptr;
    }
    else {
        this->chairman = n_cman;
    }
}

/**
 * set new party to the politician
 * @param p : reference to the party we want to set
 */
void Politician::SetParty(Party* p) {
    if(p== nullptr){
        t_party = nullptr;
        chairman = nullptr;
        return;
    }
    this->t_party = p;
    this->chairman = p->GetChairman();
}

/**
 * getter for the party of this politician
 */
Party* Politician::GetParty() const {
    return this->t_party;
}





