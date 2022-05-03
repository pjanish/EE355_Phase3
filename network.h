
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
#include "contact.h"
// You may need to add more libraries 
#include <stdlib.h>
class Network{

    private:
        Person* head;
        Person* tail;
        int count; 
        Person* search(Person* searchEntry);
        Person* search(string fname, string lname);
        Person* search(string ID);

    public:
        Network();
        Network(string fileName);
        ~Network();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname);
        void saveDB(string filename);
        void loadDB(string filename);
        void printDB();
        void showMenu();
        void sendEmail(string addr, string subject, string content, string attachment);
        void sendMsg(string number, string content);
        int age_score(Person* p1, Person* p2);
        int school_score(Person* p1, Person* p2);
        int zip_score(Person* p1, Person* p2);
        int email_score(Person* p1, Person* p2);
        void reccomendConnection(Person* person); 

};

#endif