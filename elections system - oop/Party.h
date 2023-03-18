
#ifndef PARTY_H
#define PARTY_H
#include <typeinfo>
#include "string"
#include "Politician.h"
#include "vector"

using namespace std;
class Politician;
class Party {
protected:
    string name; // name of the party
    Politician* c_man{}; // name of the party's chairman
    vector <Politician*> Members;// vector to store the party members

public:


    Party();
    /**
     * constructor
     * @param n : string represents the name of the party needed to be created in the constructor
     */
    explicit Party(string n , Politician* cman = nullptr);

    /**
     * copy constructor that copies source into this
     * @param source : reference to another Party object we want to copy
     */
    Party(const Party& source);

    void Add_Politician(Politician& poli);

    /**
     * destructor
     */
    virtual ~Party() = default;

    /**
    * iterates over the vector element and when found erase him from the party
    * @param politician : reference to the politician we want to remove from the party
    */
    void remove_politician( Politician &politician);

    /**
     * iterates over the members of the party, and compare them based on their power, the comperation will work only
     * in the case there are comperation between leaders or between leader to nullptr.
     * after finding the max, make him the chairman of the party and inform all the party members about the change
     */
    void Primaries();

    /**
     * iterate over the members and sums all their power during elections
     */
    int E_power() const;

    /**
     *update the chairman of the party and all his member's chairman
     * @param poli : the politician elected to be the chairman
     */
    void UpdateChairMan(Politician* poli);

    /**
     * getter to the size of the party
     * @return : int represents the amount of members in the party
     */
    int GetSize() const;

    /**
     * prints party information and then iterate over her members and print each one of them information
     */
    virtual void PrintParty() const = 0;

    /**
     * getter to the size of the party
     * @return: the name of the party
     */
    string GetName() const;

    /**
     * get all the party's members
     */
    vector <Politician*> GetMembers() const;
    /**
     * getter for the chairman name
     */
    string GetChairmanName() const;
    /**
     * getter for the party chairman
     */
    Politician *GetChairman() const;

    /**
     * override the operator> for party comparison based size
     * @param other :other party to compare to
     * @return true if this party is bigger then other party and either false
     */
    bool operator>(const Party& other) const;

    /**
     * pure virtual function will return bool represents if the party allows republican politician to join or not
     */
    virtual bool CanAddRepublican() const = 0;
    /**
     * pure virtual function will return bool represents if the party allows democratic politician to join or not
     */
    virtual bool CanAddDemocratic() const = 0;
};

#endif //PARTY_H
