
#ifndef DEMOCRATICPARTY_H
#define DEMOCRATICPARTY_H
#include "Party.h"

class DemocraticParty: public Party {

    public:


        /**
         * construcctor
         * @param n : name of party
         * @param cman : pointer to party's chairman - default value nullptr
         */
        explicit DemocraticParty(string n , Politician* cman= nullptr);

        /**
         * override to print party
         */
        void  PrintParty() const override;

        /**
         * override to the virtual destructor of Party
         */
        ~DemocraticParty() override;

        /**
        * returns true - accept new democratic politicians to join
        * @return
        */
         bool CanAddDemocratic() const override;

         /**
        * return false  - do not accept republican politicians
        */
         bool CanAddRepublican() const override;

};
#endif //DEMOCRATICPARTY_H
