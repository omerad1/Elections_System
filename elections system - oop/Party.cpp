#include <iostream>
#include "Party.h"

/**
 * constructor
 * @param n
 */
Party::Party(string n, Politician* cman):name(std::move(n)),Members(vector<Politician*>()),c_man(cman){}

/**
 * default constructor receives 0 arguments
 */
Party::Party() = default;

/**
 * copy constructor
 * @param source
 */
Party::Party(const Party &source) {
    this->name = source.name; // names
    this->Members = source.Members; // vector of members
    this->c_man = source.c_man; // chairman politician
}

/**
 * iterates over the vector element and when found erase him from the party
 * @param politician : reference to the politician we want to remove from the party
 */
void Party::remove_politician(Politician &politician) {
    for(auto it = Members.begin(); it != Members.end(); ++it){ // iterate over the vector members and looking for the wanted
        // member we want to delete
        if(politician == **it){
            if(c_man == nullptr || politician.GetId() == c_man->GetId()){ // this is the chairman
                UpdateChairMan(nullptr);
            }
            politician.UpdateCman(nullptr);
            Members.erase(it); // deletes the politician found
            break;
        }
    }
}

/**
 * iterates over the members of the party, and compare them based on their power, the comperation will work only
 * in the case there are comperation between leaders or between leader to nullptr.
 * after finding the max, make him the chairman of the party and inform all the party members about the change
 */
void Party::Primaries() {
    if (Members.empty()) // checks that there is members in the party
    {

        cout<<"None"<<" is the chairman of "<<name<<endl; // prints the results of the primaries
        return;
    }
    Politician* max = nullptr; // initialize max to nullptr
    for (Politician *politician: Members) {
        if (*politician > max) { // compare  politician to max, the comparation will  work only if they are both Leader derived
            // or if max = nullptr
            max = politician; // update max
        }
    }
    this->c_man = max; // the party's chairman will be the max
    UpdateChairMan(max); // inform the party members about the change
    if(max != nullptr) {
        cout << max->GetFiName() << " is the chairman of " << name << endl; // prints the results of the primaries
    }
    else{
        cout<<"None"<<" is the chairman of "<<name<<endl; // prints the results of the primaries
    }
}

/**
 * iterate over the members and sums all their power during elections
 */
int Party::E_power() const {
    int total_power =0;
    for(auto Member : Members){
        total_power+=Member->GetPower(); // add the power of the member, during elections the Social politicians multiply their power by 2
        // and Leader politicians have their normal power

    }
    return total_power;
}

/**
 * adds new politician to the party
 * @param poli : reference to the politician we want to add
 */
void Party::Add_Politician(Politician& poli) {
    Members.push_back(&poli);
}

/**
 * update the chairman of the party and all his member's chairman
 */
void Party::UpdateChairMan(Politician *poli) {
    for(Politician* pol : Members){
        pol->UpdateCman(poli);
    }
    this->c_man = poli;
}


/**
 * getter to the size of the party
 */
int Party::GetSize() const {
    if(Members.empty()){
        return 0;
    }
    return (int)this->Members.size();
}

/**
 * getter to the size of the party
 * @return: the name of the party
 */
string Party::GetName() const {
    return this->name;
}

/**
 * getter for the members of the party
 */
vector<Politician *> Party::GetMembers() const {
    return this->Members;
}

/**
 * getter for the chairman name
 */
string Party::GetChairmanName() const{
    if(c_man!= nullptr) {
        string chair_man_name = c_man->GetFiName();
        return chair_man_name;
    }
    return "None";
}
/**
 * getter for the party chairman
 */
Politician* Party::GetChairman() const{
    return c_man;
}

/**
 * override the operator> for party comparison based size
 */
bool Party::operator>(const Party &other) const {
    int a = Members.size();
    int b = other.Members.size();
    return a>b;
}
