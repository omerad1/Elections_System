#ifndef HW_5_POLITICIAN_H
#define HW_5_POLITICIAN_H
#include <typeinfo>
#include "string"
#include "Politician.h"
#include "vector"
#include "Party.h"
using namespace std;

class Party;
class Politician{
protected:
    string F_name; // politician First name
    string L_name; // politician Last name
    int id; // distinct id represents the politician
    int power; // the power of the politician
    Politician* chairman; // the chairman of the politician party
    Party* t_party; // Pointer to the party the politician is part of

public:

    /**
     * politician constructor
     * @param first_name : string represents the politician first name
     * @param last_name  : string represents the politician last name
     * @param d_id  : int represents the politician id
     * @param power : int represents the politician power
     * @param cha_man : pointer to Politician represents the chairman of the party this politician is member of
     * @param p : Pointer to party represent the party this politician is member of
     */
    explicit Politician(string first_name, string last_name , int d_id ,int power,
                        Politician* cha_man = nullptr , Party* p = nullptr);

    /**
     * politician copy constructor from source
     * @param source : reference to the source of the politician we intend to copy
     */
    Politician(const Politician &source);

    /**
    * operator= override
    * @param source : reference to the source of the politician we intend to assign into this
    * @return : this value
    */
    Politician& operator=(const Politician& source);

    /**
     * virtual distructor
     */
    virtual ~Politician(){}

    /**
     * set new party to the politician
     * @param p : string represents the name of the party
     */
    void SetParty(Party* p);

    /**
     * getter for the politician party
     */
    Party* GetParty() const;

    /**
     * getter for the politician power
     * @return
     */
    virtual int GetPower() const ;

    /**
     * getter for the first name of the politician
     * @return : the first name of the politician
     */
    string GetFiName() const;

    /**
    * getter fo the id of the politician
    */
    int GetId() const;

    /**
     * virtual method for print, the subclasses of politician will need to implement this method by themself
     */
    virtual void Print() const = 0;


    /**
    * override == operator to compare 2 politicians based on the assumption the id is unique
     * @param other : reference to Politician other we want to compare with this
     * @return : true if their id's are the same and otherwise - false
     */
    bool operator==(const Politician& other)const;

    /**
     * updates the politician's party's chairman
     * @param n_cman : pointer to the new chairman of the party
     */
    void UpdateCman(Politician* n_cman);

    /**
     * virtual override operator > for politician based on power
     */
    virtual bool operator>(Politician* other) const =0;

    /**
     * pure virtual function to check if party can add politician
     * @param party : reference to party we want to check if we can join to
     * @return : true if the party allows the politician to join her and false either
     */
    virtual bool CanJoin(const Party& party) const = 0;


};

#endif //HW_5_POLITICIAN_H
