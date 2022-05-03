#include "person.h"
#include "misc.h"
#include "misc.cpp"
#include <map>

Person::Person(){
    // I'm already done! 
    set_person();
}


Person::~Person(){
    delete birthdate;
    // TODO: complete the method!
    delete phone; 
    delete email;
}



Person::Person(string fname, string lname, string bdate, string email, string phone, string age, string school,string zip){
    // TODO: Complete this method!
    // phone and email strings are in full version
    this->f_name = fname;
    this->l_name = lname;
    this->birthdate = new Date(bdate);
    map<string, string> dict_new = {{"age", age},
                                {"school", school},
                                {"zip", zip}};
    this->dict = dict_new;
    string ty, em, ph; 
    int start, end =0; 
    int len = email.length();
    //parse email strting 
    for (int i=0; i<len; i++){
        if (email[i] == '('){
            start=i+1;
            while (email[i]!=')'){
                i++;
            }
            end = i-1;
            ty = email.substr(start, end);
            i=i+2;
            em = email.substr(i); 
            i = len; 
        }
    }
    this->email = new Email(ty, em);
    //parse phone string 
    len = phone.length();
    for (int i=0; i<len; i++){
        if (phone[i] == '('){
            start=i+1;
            while (phone[i]!=')'){
                i++;
            }
            end = i-1;
            ty = phone.substr(start, end);
            i=i+2;
            ph = phone.substr(i);  
            i =len;
        }
    }
    this->phone = new Phone(ty, ph);
    this->ID = codeName(f_name,l_name);
}


Person::Person(string filename){
    set_person(filename);
}


void Person::set_person(){
    // prompts for the information of the user from the terminal
    // first/last name can have spaces!
    // date format must be "M/D/YYYY"
    // We are sure user enters info in correct format.
    // TODO: complete this method!
    
    string temp;
    string type;
    string age;
    string school;
    string zip;

    cout << "First Name: ";
    // pay attention to how we read first name, as it can have spaces!
    std::getline(std::cin,f_name);

	cout << "Last Name: ";
    std::getline(std::cin,l_name);

    cout << "Birthdate (M/D/YYYY): ";
    std::getline(std::cin,temp);
    // pay attention to how we passed argument to the constructor of a new object created dynamically using new command
    birthdate = new Date(temp); 

    cout << "Type of email address: ";
    std::getline(std::cin, type);
    // code here
    cout << "Email address: ";
    // code here
    std::getline(std::cin, temp);
    email = new Email(type, temp);

    cout << "Type of phone number: ";
    std::getline(std::cin, type);
    // code here
    cout << "Phone number: ";
    std::getline(std::cin, temp);
    phone = new Phone(type, temp);

    cout << "Age: ";
    std::getline(std::cin, age);
    // code here
    cout << "School: ";
    std::getline(std::cin, school);
    cout << "Zip: ";
    std::getline(std::cin, zip);
    map<string, string> dict_new = {{"age", age},
                                {"school", school},
                                {"zip", zip}};
    this->dict = dict_new;
    ID = codeName(f_name,l_name);
}


void Person::set_person(string filename){
    // reads a Person from a file
    // Look at person_template files as examples.     
    // Phone number in files can have '-' or not.
    // TODO: Complete this method!
    fstream f; 
    f.open(filename, fstream::in);
    string dat;
    string type, temp, age, school, zip; 
    int len, start, end;
    int i=0;
    while (getline(f, dat)){
        switch(i){
            case 0: f_name = dat; break; 
            case 1: l_name = dat; break; 
            case 2: birthdate = new Date(dat); break;
            case 3: 
                len = dat.length();
                 for (int j=0; j<len; j++){
                    if (dat[j] == '('){
                        start=j+1;
                        while (dat[j]!=')'){
                            j++;
                        }
                        end = j-1;
                        type= dat.substr(start, end);
                        j=j+2;
                        temp = dat.substr(j);
                        j=len; 
                    }
                }
                phone = new Phone(type, temp); break;
            case 4: 
                len = dat.length();
                for (int j=0; j<len; j++){
                    if (dat[j] == '('){
                        start=j+1;
                        while (dat[j]!=')'){
                            j++;
                        }
                        end = j-1;
                        type= dat.substr(start, end);
                        j=j+2;
                        temp = dat.substr(j); 
                        j=len; 
                    }
                }
                email = new Email(type,temp); break; 
            case 5:   age = dat; break;
            case 6:   school = dat; break; 
            case 7:   zip = dat; break; 
        }

        i++;
    }

    map<string, string> dict_new = {{"age", age},
                                {"school", school},
                                {"zip", zip}};

    ID = codeName(f_name,l_name);
    f.close();
}

void Person::makeFriend(Person* newFriend){
    myfriends.push_back(newFriend);
}

void Person::removeFriend(Person* newFriend){
    for(int i = 0; i < myfriends.size(); i++){
        if(myfriends.at(i) == newFriend){
            myfriends.erase(myfriends.begin() + i);
        }
    }
}

bool Person::operator==(const Person& rhs){
    // TODO: Complete this method!
    // Note: you should check first name, last name and birthday between two persons
    // refer to bool Date::operator==(const Date& rhs)
    if ( (f_name == rhs.f_name) &&
         (l_name == rhs.l_name) && 
         (birthdate->operator==(*(rhs.birthdate))) &&
         (email->get_contact() == rhs.email->get_contact()) && 
         (phone->get_contact() == rhs.phone->get_contact()) ) {
             return true; 
    }
    else 
        return false; 
}

bool Person::operator!=(const Person& rhs){ 
    // TODO: Complete this method!
    return !(*this == rhs);
}


void Person::print_person(){
    // Already implemented for you! Do not change!
	cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
    email->print();
    phone->print();
    cout<<dict["age"]<<endl;
    cout<<dict["school"]<<endl;
    cout<< dict["zip"]<<endl;
    for(int i = 0; i< myfriends.size(); i++){
        cout<<myfriends.at(i)->ID<<endl;
    }
}

bool Person::search(Person* p){
    for(int i = 0; i< myfriends.size(); i++){
        if(myfriends.at(i) == p){
            return true;
        }
    }

    return false;
}

