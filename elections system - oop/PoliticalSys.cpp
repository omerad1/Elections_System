#include "PoliticalSys.h"
#include <fstream>
#include <sstream>

/**
 * constructor receiving file path and create politicians,parties from the file
 * @param FilePath : pointer to the filepath
 */
PoliticalSys::PoliticalSys(const char *FilePath) {
    string line;
    ifstream file(FilePath);
    string buf1, buf2, id, power, rp, ls;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find("Politicians") != string::npos) {// we at the line states politicians.
                while (getline(file, line) &&
                       line.find("Parties") == string::npos) {// load new line and make sure we are
                    //not at parties yet
                    stringstream ss(line);
                    ss >> buf1 >> buf2 >> id >> power >> rp >> ls;
                    int iid = stoi(id);
                    int ipower = stoi(power);
                    CreatePolitician(buf1, buf2, iid, ipower, rp, ls);
                }
            }
            if (line.find("Parties") != string::npos) {
                while (getline(file, line)) {
                    stringstream ss(line);// split to tokens
                    ss >> buf1 >> buf2;
                    CreateNewParty(buf1, buf2); // create new party
                }
            }
        }
    }
}
/**
 * default constructor
 */
PoliticalSys::PoliticalSys() = default;


/**
 * find the correct type and creates new Politician
 * then adds him to the data structures store him and at the end
 * finds an suitable party for him
 */
void PoliticalSys::CreatePolitician(string fname, string lname,
                                    int id, int power,const string& rp, const string& ls) {
        if (rp == "R") { // republican
            if (ls == "L") { //leader
                    auto *n_politician = new RepublicanLeader(std::move(fname), std::move(lname), id,
                                                              power);// creates new politician
                this->Politicians.push_back(
                        n_politician); // adds to the vector stores all the politicians in the system
            } else { //social
                auto *n_politician = new SocialRepublican(std::move(fname), std::move(lname), id,
                                                          power);// creates new politician
                this->Politicians.push_back(
                        n_politician); // adds to the vector stores all the politicians in the system
            }
            FindParty(*Politicians[Politicians.size() - 1]);
        } else { // democrat
            if (ls == "L") { //leader
                auto *n_politician = new DemocraticLeader(std::move(fname), std::move(lname), id,
                                                          power);// creates new politician
                this->Politicians.push_back(
                        n_politician); // adds to the vector stores all the politicians in the system
            } else { //social
                auto *n_politician = new SocialDemocrat(std::move(fname), std::move(lname), id,
                                                        power); // creates new politician
                this->Politicians.push_back(
                        n_politician); // adds to the vector stores all the politicians in the system
            }
            FindParty(*Politicians[Politicians.size() - 1]);
        }
    }


/**
 * looking for suitable party for received politician
 * @param poli : reference to the politician we need to find him party
 */
void PoliticalSys::FindParty(Politician& poli){

    for(auto party : Parties){ //search
        if(poli.GetParty() == nullptr){ // the politician has no party yet
            if(poli.CanJoin(*party)) { // checks if the politician can join the party
                Parties_Set.erase(Parties_Set.find(party)); // removes the party from the set in order to update her;
                poli.SetParty(party);               // set new party for the politician
                party->Add_Politician(poli);
                Parties_Set.insert(party); // re-add the party to party set
            }
        }
        else{
            if(poli.GetParty()->GetSize() > party->GetSize()){
                if(poli.CanJoin(*party)) { // checks if the politician can join the party
                Parties_Set.erase(Parties_Set.find(party)); // removes the party from the set in order to update her;
                Party* temp = poli.GetParty();
                Parties_Set.erase(Parties_Set.find(temp)); // removes the party from the set in order to update her;
                temp->remove_politician(poli); // removes the politician from his old party
                Parties_Set.insert(temp); // re-add the party to party set
                poli.SetParty(party); // set new party for the politician
                party->Add_Politician(poli);
                Parties_Set.insert(party); // re-add the party to party set
                }
            }
        }
    }
}


/**
 * request and receives information from the user, then with this information creates new Politician
 * and adds him to the system.
 */
void PoliticalSys::addPolitician() {

    int power; //user's input for power
    int id;//user's input for id
    string rp;//user's input for flag representing if the politician is republican or democrat
    string ls;//user's input for flag representing if the politician is Leader or Social
    string lname;//user's input for politician's last name
    string fname;//user's input for politician's first name

    cout<<"---Create Politician---"<<endl;
    while(true) {
        try {

            cout << "First name:" << endl;
            cin >> fname;
            if(fname == "aaa"){
                cout<<"omer";
            }


            cout << "Last name:" << endl;
            cin >> lname;


            string t_id;
            cout << "ID:" << endl;
            cin >> t_id;


            string t_power;
            cout << "Power:" << endl;
            cin >> t_power;


            cout << "Republican or Democratic person" << endl;
            cin >> rp;


            cout << "Leader or Social" << endl;
            cin >> ls;

            /// input verification ///
            verify_name(fname); //input verification
            verify_name(lname); //input verification
            vefiry_id(t_id); //input verification
            id = stoi(t_id);
            verify_power(t_power); //input verification
            power = stoi(t_power);
            verify_RorD(rp); //input verification
            verify_LorS(ls); //input verification
            break;
        }
        catch (BadId &a) {
            cout << "Please enter valid details" << endl;
        }
        catch (BadInformation &b) {
            cout << "Please enter valid details" << endl;
        }
        catch (BadName &c) {
            cout << "Please enter valid details" << endl;
        }
    }
    CreatePolitician(fname,lname,id,power,rp,ls); // creates new politician


}

/**
 * create new party of the type specified in the rd argument and then let all the politician to check if the party is
 * suits them, if yes they will move to her
 */
void PoliticalSys::CreateNewParty(const string& name, const string& rd) {
    Party*n_party; // will stroe the new party going to be added
    if (rd == "R") {
        n_party = new RepublicanParty(name); // creates new republican party
        Parties.push_back(n_party);
        Parties_Set.insert(n_party);

    } else {
        n_party = new DemocraticParty(name); // creates new republican party
        Parties.push_back(n_party);
        Parties_Set.insert(n_party);
    }

    // now all the existing politicians in the system will check if the new party is more suitable for them
    for(auto & poli : Politicians) {
        if (poli->GetParty() == nullptr
            || poli->GetParty()->GetSize() > n_party->GetSize()) {
            if (poli->CanJoin(*n_party)) {
                Parties_Set.erase(Parties_Set.find(n_party)); // removes the party from the set in order to update her;
                Party *temp = poli->GetParty();
                if (temp != nullptr) {
                    Parties_Set.erase(Parties_Set.find(temp)); // removes the party from the set in order to update her;
                    temp->remove_politician(*poli); // removes the politician
                    // from his old party
                    Parties_Set.insert(temp); // re-add the party to party set
                }
                poli->SetParty(n_party); // sets new party to the politician
                n_party->Add_Politician(*poli); // adds the politician to the party
                Parties_Set.insert(n_party); // re-add the party to party set
            }
        }
    }
}


/**
 * receives user's input as party information and then create new party,
 * adds the new party to the data structures hold parties in the system
 */
void PoliticalSys::addParty() {

    string name; // user's input for party name
    string rd; // user's input for flag representing if the Party is republican or democratic
    cout<<"---Create Party---"<<endl;
    while(true){
        try{
            cout<<"Name:"<<endl;
            cin>>name;


            cout<<"Republican or Democratic party"<<endl;
            cin>>rd;

            /// input verification ///
            verify_party_name(name); //input verification
            verify_RorD(rd); //input verification
            break;

        }
        catch (BadInformation &b) {
            cout << "Please enter valid details" << endl;
        }
        catch (BadName &b) {
            cout << "Please enter valid details" << endl;
        }

    }
    CreateNewParty(name,rd);  // call to create new party
}


/**
 * receives user's input for politician id, then checks if the politician id is valid and if there is politician owned
 * the given id in the system. if there is continue and calls DeletePolitician function the perform deletion
 */
void PoliticalSys::removePolitician() {
    if(Politicians.empty()){ // checks if there is any politician in the system
        return;
    }
    int r_id;
    cout<<"---Remove Politician---"<<endl;

    while(true){
        try{
            string id;
            cout<<"Enter the ID:"<<endl;
            cin>>id;
            vefiry_id(id,1); // calls the verify_id method with flag = 1 -> we want the id to be in the system
            r_id = stoi(id);
            break;
        }
        catch (BadId& e){
            cout << "Please enter valid id" << endl;
        }
    }
    DeletePolitician(r_id); // calls to delete politician method
}

/**
 * first search for the function in the vector that holds the parties *by type. there is variable called flag to store
 * the type of the party is going to be deleted.
 * after found store the party in temp pointer and looking for an suitable party to each one of the members
 * at the end, removes the party from all the data structures holds her and delete her
 * @param name : name of the party we want to remove from the system and delete
 */
void PoliticalSys::DeleteParty(const string& name) {
    Party *temp = nullptr; // the function will be called only after check has been made that the party exists
    for (int i = 0; i < Parties.size(); i++) {
        if (Parties[i]->GetName() == name) { //party found
            temp = Parties[i];
            Parties.erase(Parties.begin() + i);
            Parties_Set.erase(Parties_Set.find(temp));
        }
    }
    for(int i =0 ; i < temp->GetSize(); i++){
        Politician * t_poli = temp->GetMembers()[i] ;// gets the politician in the i th index
        t_poli->SetParty(nullptr);
        for(auto party: Parties){
            if(t_poli->GetParty() == nullptr || t_poli->GetParty()->GetSize() > party->GetSize())
            {
                if(t_poli->CanJoin(*party))
                {
                    Parties_Set.erase(Parties_Set.find(party)); // erase in order to update
                    if(t_poli->GetParty() != nullptr)
                    {
                        Party* r_p = t_poli->GetParty();
                        Parties_Set.erase(Parties_Set.find(r_p)); // erase in order to update
                        r_p->remove_politician(*t_poli);
                        Parties_Set.insert(r_p);
                        t_poli->SetParty(party); // sets new party to the politician
                        party->Add_Politician(*t_poli);
                    }
                    else
                    {
                        t_poli->SetParty(party); // sets new party to the politician
                        party->Add_Politician(*t_poli);
                    }
                    Parties_Set.insert(party);
                }
            }
        }
    }
    delete temp;

}



/**
 * iterate over the system's data structures and removes the politician from the data structures holds him,
 * at the end delete the politician and free hes allocated memory
 * @param id : id of the politician we want to remove and delete
 */
void PoliticalSys::DeletePolitician(int id) {
    Politician* poli;
    for(auto it = Politicians.begin(); it != Politicians.end();) {
        if((*it)->GetId() == id) {
            poli = *it;
            Party *p = poli->GetParty(); // the party of the politician
            if (p) {
                Parties_Set.erase(Parties_Set.find(p)); // removes the party from the set in order to update her
                p->remove_politician(*poli); // removes and inform all the politicians from the party
                Parties_Set.insert(p); // re - add the updated party
                }
            Politicians.erase(it);
        }
        else
        {
            ++it;
        }
    }
    delete poli; //! deletes tomi !
}

/**
 * receives user's input for party name, then chcecks if the party name is valid and if there is party owned the given
 * name in the system. if there is continue and calls DeleteParty function the perform deletion
 */
void PoliticalSys::removeParty() {
    if(Parties.empty()){ // there is no parties in the system.
        return;
    }
    string name;
    cout<<"---Remove Party---"<<endl;
    while(true){
        try{
            cout<<"Enter party name:"<<endl;
            cin>>name;
            verify_party_name(name,1); // call verify method with flag = 1 - states that we search for equalization
            break;
        }
        catch (BadName& b){
            cout << "Please enter valid name" << endl;
        }
    }
    DeleteParty(name); // call to delete party with the party name
}

/**
 * performs elections on the current parties in the system by comparing each party power during elections
 * and choose the winner with the max power, then print the winner party name and her chairman as prime minister
 */
void PoliticalSys::elections() const{

    if(Parties.empty() || Politicians.empty()) // if there is no parties or politicians in the system
        return;

    ///---primaries---///
    cout<<"----Primaries----"<<endl;
    for(auto & Party : Parties){
        Party->Primaries();
    }

    ///---elections---///
    cout<<"----Elections----"<<endl;
    Party* maxp = Parties.front(); // sets to first party
    int maxp_power = Parties.front()->E_power(); // will store the max power
    cout<<"Party: "<<maxp->GetName()<<",Power: "<<maxp_power<<endl;
    for(int i =1;i<Parties.size();i++){
        int temp_power = Parties[i]->E_power();
        if(temp_power>maxp_power){
            maxp = Parties[i]; // update the party with the current max power
            maxp_power = temp_power; // update max power
        }
        cout<<"Party: "<<Parties[i]->GetName()<<",Power: "<<temp_power<<endl;
    }

    ///---elections results---///
    cout<<"----Elections Results----"<<endl;
    cout<<maxp->GetName()<<" party won the elections and "<<maxp->GetChairmanName()<<" is the prime minister"<<endl;



}


/**
 * iterate over the politicians that is in the system right now and calls their print function
 */
void PoliticalSys::printPoliticians() const{
    if(Politicians.empty()){
        return;
    }
cout<<"----Politicians----"<<endl;
for(auto & Politician : Politicians){
    Politician->Print();
    }
}


/**
 * iterate over the politicians that is in the system right now and calls their print function
 */
void PoliticalSys::printParties() const {
    if(Parties.empty()){
        return;
    }
    cout<<"----Parties----"<<endl;
    for(auto & party : Parties){
        party->PrintParty();
    }
}

/**
 * prints the biggest party in the system
 */
void PoliticalSys::BiggestParty() const{
    if(Parties_Set.empty())
        return;
    auto it = Parties_Set.begin();
    Party *biggest_party = *it;
    int size = biggest_party->GetSize();
    cout<<"----Biggest Party----"<<endl;
    cout<<"["<<biggest_party->GetName()<<","<<size<<"]"<<endl;
}

/**
 * destructor
 */
PoliticalSys::~PoliticalSys() {

    for(auto pol:Politicians)
        if(pol)
            delete pol;
    for(auto party:Parties)
        if(party)
            delete party;

}


/**
 * verify that given string represents Party name is valid - valid name and distinct name.
 */
void PoliticalSys::verify_party_name(const string& name,int flag_for_verify){
    verify_name(name);
    if(Parties.empty()){
        return;
    }
    for(auto party : Parties){
        if(party->GetName() == name){
            if(flag_for_verify == 0){ // we do not want equality in the id
                throw BadName();
            }
            else{ // we search for the id
                return;
            }
        }
    }
    if(flag_for_verify == 0){
        return;
    }
    throw BadName(); // comparison with all parties are done and there is no party with the same name
}


/**
 * verify that given string represents name is valid - construct only with letters
 */
void PoliticalSys::verify_name(const string& name){
    for(char x : name){
        if(!isalpha(x) && x != '_'){
            throw BadName();
        }
    }
}


/**
 * verify that given string represents power is positive int
 */
void PoliticalSys::verify_power(const string& power){
    for(char x : power){
        if(!isdigit(x)){
            throw BadInformation();
        }
    }
}


/**
 * verify that given string represents republican or democratic flag is valid
 */
void PoliticalSys::verify_RorD(const string& rp){
    if(rp != "R" && rp != "D")
        throw BadInformation();
}


/**
 * verify that given string represents Leader or Social flag is valid
 */
void PoliticalSys::verify_LorS(const string& ls){
    if(ls != "S" && ls != "L")
        throw BadInformation();
}


/**
 * verify that received id is valid
 * @param id : string holding the received id
 */
void PoliticalSys::vefiry_id(const string& id, int flag_for_verify) const {

    int c_checker = 0;// will check if there is letter in the given id
    for(char c : id){
        if(!isdigit(c)) {
            c_checker++;
            break;
        }
    }
    if(c_checker>0) { // there is letter in the given id!
        cout << "kobi" << endl;
        throw BadId(); // throw BadId exception
    }
    else{
        if(Politicians.empty())
            return;
        if(id.empty()){
            throw BadId();
        }
        int k = stoi(id); // convert to int
        for(auto Member : Politicians){
            if(Member->GetId() == k) {// the politician is already in the system
                if(flag_for_verify == 0){ // we do not want equality in the id
                    throw BadId();
                }
                else{ // we search for the id
                    return;
                }
            }
        }
    }
    if(flag_for_verify == 0){
        return;
    }
    throw BadId ();// comparison with all politicians are done and there is no politician with the same id as received
}

