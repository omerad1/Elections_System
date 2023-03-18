
#include "SocialDemocrat.h"
#include "iostream"

using namespace std;

/**
 * constructor for SocialDemocratic class, using only the constructor of the father class Politician
 */
SocialDemocrat::SocialDemocrat(string first_name, string last_name, int d_id, int power, Politician *cha_man, Party* p) : Politician(
        std::move(first_name), std::move(last_name), d_id, power, cha_man, p){}

/**
 * prints the Republican leader, first checks if there is chairman to the politician party, if there is he will be printed
 * during the print of this, else will print None in the chairman field.
 */
void SocialDemocrat::Print() const {
    if(chairman == nullptr){
        cout<<"Democratic Person:"<<this->F_name<<" "<<L_name<<", Id:"<<id<<", Power:"<<power<<", Type:S, Chairman: None"<<endl;
    }
    else{
        cout<<"Democratic Person:"<<this->F_name<<" "<<L_name<<", Id:"<<id<<", Power:"<<power<<", Type:S, Chairman: "
            <<chairman->GetFiName()<<endl;
    }

}

/**
 * default constructor
 */
SocialDemocrat::~SocialDemocrat() = default;

/**
 * getter for the politician power - during the elections the power is multiply by 2
 * @return : the politician power
 */
int SocialDemocrat::GetPower() const {
    return 2*power;
}

/**
 * fake comperation - always return false
 * @param other :  reference to other
 * @return : false
 */
bool SocialDemocrat::operator>(Politician *other) const {
    return false;

}
/**
 * calls function from the party class specify if this politician can join her or not
 */
bool SocialDemocrat::CanJoin(const Party &party) const {
    return party.CanAddDemocratic();
}

