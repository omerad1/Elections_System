#include "DemocraticParty.h"
#include "iostream"
using namespace std;

/**
 * constructor for Democratic Party
 * @param n : string represents the name of the partry
 */
DemocraticParty::DemocraticParty(string n,Politician* cman):Party(std::move(n),cman) {
}

/**
 * prints the party information and then her members information
 */
void DemocraticParty::PrintParty() const {

    if(c_man == nullptr){ // there is no chairman yet
        cout<<"Democrat Party: "<<this->name<<", chairman:"<<"None"<<", Size:"<<Members.size()<<endl;
    }

    else { //there is chairman
        cout<<"Democrat Party: "<<this->name<<", chairman:"<<this->c_man->GetFiName()<<", Size:"<<Members.size()<<endl;
    }

    for(auto Member : Members){ // iterate over the party's members and print them
        cout<<"\t";
        Member->Print();
    }
}
/**
 * destructor
 * calls the clear function on the members vector
 */
DemocraticParty::~DemocraticParty() {
    this->Members.clear();
}

/**
 * returns true - accept new democratic politicians to join
 */
bool DemocraticParty::CanAddDemocratic() const {
    return true;
}

/**
 * returns false - do not accept new republican politicians to join
 */
bool DemocraticParty::CanAddRepublican() const {
    return false;
}
