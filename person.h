
#ifndef PERSON_H
#define PERSON_H

#include "date.h"
#include "contact.h"
#include "fstream"
#include <vector>
#include <map>

class Person{
    friend class Network;

private:
	string f_name;
	string l_name;
	Date *birthdate;
    Email *email;
    Phone *phone;
    // the following to attributes are used in the linked list.
    Person* next;
    Person* prev;
    string ID;
    map<string, string> dict = {{"age", "19"},
                                {"school", "University of Southern California"},
                                {"zip", "90007"}};


public: 
    Person();
    ~Person();
    Person(string filename);
    Person(string f_name, string l_name, string bdate, string email, string phone, string age, string school, string zip);
    vector<Person *> myfriends;
	void print_person();
	void set_person();
	void set_person(string filename);
    void makeFriend(Person* newFriend);
    void removeFriend(Person* newFriend);
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
    bool search(Person* p);
    
};





#endif