
#ifndef REPUBLICANLEADER_H
#define EPUBLICANLEADER_H
#include "Politician.h"
class RepublicanLeader: public Politician{

public:

    /**
     * Republican - Leader - politician constructor
     * @param first_name : string represents the politician first name
     * @param last_name  : string represents the politician last name
     * @param d_id  : int represents the politician id
     * @param power : int represents the politician power
     * @param cha_man : pointer to Politician represents the chairman of the party this politician is member of
     * @param p : Pointer to party represent the party this politician is member of
     */
    explicit RepublicanLeader(string  first_name, string  last_name , int d_id , int power = 0,
                          Politician* cha_man = nullptr , Party* p = nullptr);

    /**
     * destructor
     */
    ~RepublicanLeader() override;

    /**
     * prints the democratic leader, first checks if there is chairman to the politician party, if there is he will be printed
     * during the print of this, else will print None in the chairman field.
     */
    void Print() const override;

    /**
     * getter for the politician power
     * @return : the politician power
     */
    int GetPower() const override;

    /**
     * override the operator> - comparison based on the power
     * @param other : other politician we want to compare to
     * @return : true if this > other
     */
    bool operator> (Politician* other) const override;

    /**
     * calls function from the party class specify if this politician can join her or not
     * @param party : reference to party we want to check if we can join to
     * @return : true if the party allows the politician to join her and false either
     */
    bool CanJoin(const Party& party) const override;
};


#endif //REPUBLICANLEADER_H
