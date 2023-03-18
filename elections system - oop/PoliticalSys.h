#ifndef POLITICALSYS_H
#define POLITICALSYS_H
#include "vector"
#include "DemocraticLeader.h"
#include "DemocraticParty.h"
#include "SocialDemocrat.h"
#include "RepublicanLeader.h"
#include "RepublicanParty.h"
#include "SocialRepublican.h"
#include <iostream>
#include <set>
using namespace std;


/**
 * operator() compare two parties by size and then by their name,
 * return true if p2 bigger then p1
 */
class PartyCompare {
public:

    PartyCompare() = default;  // default constructor

    bool operator()(const Party* p1, const Party* p2)  const {
        if (p1->GetSize() != p2->GetSize()) {
            return p1->GetSize() > p2->GetSize();
        } else {
            // Use the party name as a tiebreaker
            return p1->GetName() > p2->GetName();
        }
    }
};


class PoliticalSys {

    vector<Politician *> Politicians;  // vector stores the politicians in the system

    vector<Party *> Parties; // vector stores the parties in the system

    set<Party *, PartyCompare> Parties_Set;  // set stores the parties in the system,
                                                    // sorted by number of members (greatest to least)

public:
    /**
     * constructor receiving file path and create politicians,parties from the file
     * @param FilePath : pointer to the filepath
     */
    PoliticalSys(const char *FilePath);


    /**
     * default constructor - receives 0 arguments
     */
    PoliticalSys();


    /**
     * receives Politician information from user, creates new politician
     * and adds him to the system by 2 steps:
     * 1.checks correlation between the politician and the parties that is in the system
     * 2.if the politician and the party checked is both republican or both democratic
     * the politician will be added to the party
     */
    void addPolitician();


    /**
     * receives party information from user and adds her to the system.
     * after adding the party to the system the politicians that is in the system
     * checks if they need / can to join the new party and perform the action needed
     */
    void addParty();


    /**
     * receives an wanted to remove Politician's id and removes him from his party and
     * from the system. if the politician deleted was the chairman of the party, all the
     * party members will get update about the change
     */
    void removePolitician();


    /**
     * receives an wanted to remove party name, if there is no parties in the system nothing happens,
     * else the party is removes from the system and all the politicians was belong to he search for an
     * new party.
     */
    void removeParty();


    /**
     * first checks if there is politicians and parties in the system, if yes - there is elections!
     * the elections works in 3 steps:
     * 1. Primaries - every party iterate over her members
     *    and chooses chairman (the strongest politician during the elections), then informs all her members
     *    about the new chairman elected and prints her primaries results
     * 2. elections - every party calculate her power during elections and list of parties with their power is printed
     * 3. results - the results of the elections are printed and state who is the chairman of the winner party
     */
    void elections() const;


    /**
     * prints all the politicians in the system by their seniority
     */
    void printPoliticians() const;


    /**
     * prints all the parties in the system by their seniority
     */
    void printParties() const;


    /**
     * Prints the biggest party from the filed biggest_party that is maintained during all the actions
     * perform on the system
     */
    void BiggestParty() const;


    /**
     * destructor for the system
     */
    ~PoliticalSys();

///++++++++++++++++++++++++++++++++++++++++++++++++ verifications +++++++++++++++++++++++++++++++++++++++++++++++++++///
    /**
     * verify that received id is valid
     * @param id : string holding the received id
     */
    void vefiry_id(const string& id, int verify_id=0)const ;

    /**
     * verify that given string represents power is positive int
     * @param power : string represents power we want to check his validation
     */
    static void verify_power(const string &power);
    /**
     * verify that given string represents republican or democratic flag is valid
     */
    static void verify_RorD(const string &rp);

    /**
     * verify that given string represents Leader or Social flag is valid
     */
    static void verify_LorS(const string &ls);

    /**
     * verify that given string represents name is valid - construct only with letters
     */
    void verify_name(const string &name);

    /**
     * verify that given string represents Party name is valid - valid name and distinct name.
     */
    void verify_party_name(const string &name,int flag_for_verify = 0);


///+++++++++++++++++++++++++++++++++++++++++++++++++ exceptions +++++++++++++++++++++++++++++++++++++++++++++++++++++///

    /*!
     * Exception for the case of not valid Id
     */
    class BadId : public exception {
    public:
        std::string id;
        BadId()= default;

    };

    /*!
     * Exception for the case of not valid Name
     */
    class BadName : public exception {
    public:
        std::string id;
        BadName()= default;

    };

    /*!
     * Exception for the case of not valid Information
     */
    class BadInformation : public exception {
    public:
        std::string id;
        BadInformation()= default;

    };

///-----------------------------------------------------------------------------------------------------------------///

    /**
     * creates new Politician and adds him to the system
     * @param fname : string represents first name of the new politician
     * @param lname : string represents last name of the new politician
     * @param id : int represents the id of the new politician
     * @param power : int represents the power of the new politician
     * @param rp : string used as flag represents if the new politician is republican or democrat
     * @param ls :  string used as flag represents if the new politician is Leader or Social typed
     */
    void CreatePolitician(string fname, string lname, int id, int power, const string& rp, const string& ls);


    /**
     * iterate over the system's data structures and removes the politician from the data structures holds him,
     * at the end delete the politician and free hes allocated memory
     * @param id : id of the politician we want to remove and delete
     */
    void DeletePolitician(int id);


    /**
     * looking for suitable party for received politician
     * @param poli : reference to the politician we need to find him party
     */
    void FindParty(Politician &poli);


    /**
     * first search for the function in the vector that holds the parties *by type. there is variable called flag to store
     * the type of the party is going to be deleted.
     * after found store the party in temp pointer and looking for an suitable party to each one of the members
     * at the end, removes the party from all the data structures holds her and delete her
     * @param name : name of the party we want to remove from the system and delete
     */
    void DeleteParty(const string& name);

    /**
     * create new party of the type specified in the rd argument and then let all the politician to check if the party is
     * suits them, if yes they will move to her
     * @param name : name of the new party
     * @param rd  : flag indicates if the party is republican or democratic
     */
    void CreateNewParty(const string& name, const string& type);
};

#endif //POLITICALSYS_H
