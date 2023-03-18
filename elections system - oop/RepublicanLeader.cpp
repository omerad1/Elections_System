
#include "RepublicanLeader.h"
#include "iostream"

using namespace std;

/**
 * constructor for RepublicanLeader class, using only the constructor of the father class Politician
 */
RepublicanLeader::RepublicanLeader(string first_name, string last_name, int d_id, int power, Politician *cha_man, Party* p) : Politician(
        std::move(first_name), std::move(last_name), d_id, power, cha_man, p){}

/**
 * prints the Republican leader, first checks if there is chairman to the politician party, if there is he will be printed
 * during the print of this, else will print None in the chairman field.
 */
void RepublicanLeader::Print() const {
    if(chairman == nullptr){
        cout<<"Republican Person:"<<this->F_name<<" "<<L_name<<", Id:"<<id<<", Power:"<<power<<", Type:L, Chairman: None"<<endl;
    }
    else{
        cout<<"Republican Person:"<<this->F_name<<" "<<L_name<<", Id:"<<id<<", Power:"<<power<<", Type:L, Chairman: "
            <<chairman->GetFiName()<<endl;
    }

}

/**
 * default constructor
 */
RepublicanLeader::~RepublicanLeader() = default;

/**
 * getter for the politician power
 * @return : the politician power
 */
int RepublicanLeader::GetPower() const {
    return power;
}



/**
 * override the operator> - comparison based on the power
 * @param other : other politician we want to compare to
 * @return : true if this > other
 */
bool RepublicanLeader::operator>(Politician *other) const {
    if(other == nullptr){
        return true;
    }
    bool res;
    res = this->power > other->GetPower();
    return res;
}
/**
 * calls function from the party class specify if this politician can join her or not
 */
bool RepublicanLeader::CanJoin(const Party &party) const {
    return party.CanAddRepublican();
}
