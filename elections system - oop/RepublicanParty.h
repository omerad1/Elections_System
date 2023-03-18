
#ifndef REPUBLICANPARTY_H
#define REPUBLICANPARTY_H
#include "Party.h"


class RepublicanParty: public Party {


public:

    /**
     * Republican party construcctor
     * @param n : string represents the name of the party
     * @param cman : Pointer to Politician is the chairman of the party or nullptr if there is no one elected yet
     */
    explicit RepublicanParty(string n , Politician* cman = nullptr);

    /**
     * override to print party
     */
    void  PrintParty() const override;

    /**
     * override to the virtual destructor of Party
     */
    ~RepublicanParty() override;

    bool CanAddDemocratic() const override;

    bool CanAddRepublican() const override;

};


#endif //REPUBLICANPARTY_H
