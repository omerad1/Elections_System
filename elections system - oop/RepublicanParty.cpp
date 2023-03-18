
#include "RepublicanParty.h"
#include "iostream"
using namespace std;

/**
 * constructor for Republican Party
 * @param n : string represents the name of the partry
 */
RepublicanParty::RepublicanParty(string n,Politician* cman):Party(std::move(n),cman) {
}

/**
 * prints the party information and then her members information
 */
void RepublicanParty::PrintParty() const {

    if(c_man == nullptr){ // there is no chairman yet
        cout<<"Republican Party: "<<this->name<<", chairman:"<<"None"<<", Size:"<<Members.size()<<endl;
    }

    else { //there is chairman
        cout<<"Republican Party: "<<this->name<<", chairman:"<<this->c_man->GetFiName()<<", Size:"<<Members.size()<<endl;
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
RepublicanParty::~RepublicanParty() {
    this->Members.clear();
}
/**
 * return false - do not accept democratic politicians
 */
bool RepublicanParty::CanAddDemocratic() const {
    return false;
}
/**
 * return true - accept democratic politicians
 */
bool RepublicanParty::CanAddRepublican() const {
    return true;
}
