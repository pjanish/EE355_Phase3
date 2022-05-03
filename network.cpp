
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include "person.h"
#include "date.h"
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <string>
#include <limits>
#include <dirent.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <algorithm>



using namespace std;

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);

}

Network::~Network(){
    // Copy from lab5

    while(head != tail){
        Person* temp = head;
        head = head->next;
        delete temp;
    }

    Person* temp_last = head;
    head = NULL;
    tail = NULL;

    delete temp_last;
}


void Network::push_front(Person* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    if(search(newEntry) == NULL){
        newEntry->prev = NULL;
        newEntry->next = head;

        if (head != NULL)
            head->prev = newEntry;
        else
            tail = newEntry;
        
        head = newEntry;
        count++;
        cout<<"Connection added successfully."<<endl;
    } 
    else{
        cout<<"Connection already exists."<<endl;
    }
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // Adds a new Connection (newEntry) to the back of LL
    // Copy from your lab5
    if(search(newEntry) == NULL){
        if(head == NULL){
            head = newEntry;
            tail = newEntry;
            newEntry->prev = NULL;
            newEntry->next = NULL;
        }
        else{
            tail->next = newEntry;
            newEntry->prev = tail;
            tail = newEntry;
            newEntry->next = NULL;
        }

        count++;
    } 
   
}


Person* Network::search(Person* searchEntry){
    // Searches the Network for searchEntry
    // if found, returns a pointer to it, else returns NULL
    // Copy from lab5 
    Person* temp = head;


    while(temp != NULL){
        //cout<<temp->f_name<<endl;
        if(*temp == *searchEntry){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}


Person* Network::search(string fname, string lname){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 
    Person* temp = head;

    while(temp != NULL){
        if((temp->f_name == fname) && (temp->l_name == lname)){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Person* Network::search(string new_ID){
    // New == for Connection, only based on fname and lname
    // if found, returns a pointer to it, else returns NULL
    // TODO: Complete this method
    // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly. 
    Person* temp = head;

    while(temp != NULL){
        if((temp->ID == new_ID)){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.txt as a template
    // TODO: Update this method with new requirements
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
    fstream ofile;
    ofile.open(filename);
    Person* temp = head;

    while(temp != NULL){
        ofile<<temp->l_name + ", " + temp->f_name<<endl<<temp->birthdate->get_date()<<endl<<temp->email->get_contact()<<endl<<temp->phone->get_contact()<<endl;
        ofile<<temp->dict["age"]<<endl<<temp->dict["school"]<<endl<<temp->dict["zip"]<<endl;
        for(int i = 0; i< temp->myfriends.size();i++){
            ofile<<temp->myfriends.at(i)->ID<<endl;
        }
        ofile<<"------------------------------"<<endl;
        temp = temp->next;
    }

    ofile.close();
}


void Network::loadDB(string filename){
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
    // Connection::Connection(fname, lname, bdate, email, phone)
    // TODO: Update this method with new requirements 

    fstream ifile;
    ifile.open(filename);
    string line, fname, lname, bday, email, phone, age, school,zip;
    int count = 0;
    int pos = 0;
    int size;
    Person* person;
    Person* friend_point;
    vector<vector<string>> storage;
    vector<string> temp;

    while (getline(ifile, line)){
        
        switch(count){
            case 0:
                while(line[pos] != ','){
                    pos++;
                }
                lname = line.substr(0,pos);
                fname = line.substr(pos + 2); 
                temp.push_back(lname);
                temp.push_back(fname);
                break;
            case 1:
                bday = line;
                break;
            case 2:
                email = line;
                break;
            case 3:
                phone = line;
                break;
            case 4:
                age = line;
                break;
            case 5:
                school = line;
                break;
            case 6:
                zip = line;
                break;
            default:
                temp.push_back(line);                
        }
        count++;

        if(line[0] == '-'){
            person = new Person(fname, lname, bday, email, phone, age, school, zip);
            count = 0;
            pos = 0;
            if(search(person) == NULL){
                storage.push_back(temp);
            }
            temp.clear();
            push_back(person);
            person = person->next;
            
        }   
    }
    ifile.close();
    for(int i = 0; i < storage.size(); i++){
        lname = storage.at(i).at(0);
        fname = storage.at(i).at(1);
        person = search(fname, lname);
        if(person != NULL){
            for(int j = 2; j< storage.at(i).size();j++){
                friend_point = search(storage.at(i).at(j));
                if(friend_point != NULL){
                    person->makeFriend(friend_point);
                }
            }
        }

    }
}


bool Network::remove(string fname, string lname){
    // We modified the definition of == for Connection in Connection definition itself, 
    // So we should not be worried about changes we made in Connection to modify this method!
    // Copy from lab5

    Person* p_remove = search(fname, lname);
    Person* p_search_ahead = head->next;
    Person* p_search_middle = head;
    Person* p_search_behind = head->prev;
    vector<Person *> temp = p_remove->myfriends;
    Person* p1;
    vector<Person *> iterate_vec;

    for(int i = 0; i < temp.size(); i++){
        //go through the temp vector, into each of the people, and remove the person who is being removed their ID from their
        //my friends vector
        p1 = temp.at(i);
        p1->removeFriend(p_remove);
    }

    while(p_search_middle != NULL){
        if(p_search_middle == p_remove){
            count--;

            if(p_search_ahead == NULL && p_search_behind == NULL){
                head = NULL;
                tail = NULL;
                delete p_search_middle;
            }
            else if(p_search_behind == NULL){
                head = p_search_ahead;
                p_search_ahead->prev = NULL;
                delete p_search_middle;
            }
            else if(p_search_ahead == NULL){
                tail = p_search_behind;
                p_search_behind->next = NULL;
                delete p_search_middle;
            }else{
                p_search_ahead->prev = p_search_behind;
                p_search_behind->next = p_search_ahead;
                delete p_search_middle;
            }

            return true;
        }
        p_search_behind = p_search_middle;
        p_search_middle = p_search_ahead;
        p_search_ahead = p_search_ahead->next;
    }


    
    return false;

}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
    // Sending a command looks like:
    // echo "content" | mailx -s "subject" -a "attachment" addr;
    // TODO: Search how you can run a unix command in C++
    // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
    // string new_str = '?' + old_str + '?'
    // TODO: Complete this method
    string new_str;
    
    for(int i = 0; i <4;i++){
        if(i == 0 ){
            new_str = "SMTPClient = New-Object Net.Mail.SmtpClient(smtp.gmail.com, 587)";
            int len = new_str.length();
            char buff1[len+1];
            strcpy(buff1, new_str.c_str());
            system(buff1); 
        } else if(i == 1){
            new_str = "SMTPClient.EnableSsl = $true";
            int len = new_str.length();
            char buff2[len+1];
            strcpy(buff2, new_str.c_str());
            system(buff2); 
        } else if (i ==2 ){
            new_str = "SMTPClient.Credentials = New-Object System.Net.NetworkCredential(“usr”, “pass”)";
            int len = new_str.length();
            char buff3[len+1];
            strcpy(buff3, new_str.c_str());
            system(buff3); 
        } else{
            new_str = "SMTPClient.Send($prjjanish@gmail.com, $" + addr +", $" + subject +", $" + content +")";
            int len = new_str.length();
            char buff4[len+1];
            strcpy(buff4, new_str.c_str());
            system(buff4); 
        }

    }
}
int Network::age_score(Person* p1, Person* p2){

    string age1 = p1->dict["age"];
    string age2 = p2->dict["age"];
    // Scores are as follow: 1 if within 5 yrs, 2 if within 10 yrs, or 3 if greater than 10 yrs
    int age1_num = stoi(age1);
    int age2_num = stoi(age2);
    int diff = abs(age1_num - age2_num);
    if(diff >= 0 && diff <= 5){
        return 1;
    }
    else if(diff > 5 && diff <= 10){
        return 2;
    }
    else{
        return 3;
    }
}
int Network::email_score(Person* p1, Person* p2){


    string email1 = p1->email->getEmail();
    string email2 = p2->email->getEmail();
    // Scores are as follow: 1 if same service, 2 if same type (.edu, .org, etc.), 3 if no similarity
    string email1_service;
    string email2_service;
    string email1_type;
    string email2_type;

    int service_flag = 0; // flag to indicate if @ has been detected
    int type_flag = 0; // flag to indicate if . has been detected

    for(int i = 0; i < email1.length(); i++){
        if(email1.at(i) == '@'){
            service_flag = 1;
        }
        if(service_flag == 1){
            email1_service += email1.at(i);
            if(email1.at(i) == '.'){
                type_flag = 1;
            }
            if(type_flag == 1){
                email1_type += email1.at(i);
            }
        }
    }

    service_flag = 0;
    type_flag = 0;

    for(int i = 0; i < email2.length(); i++){
        if(email2.at(i) == '@'){
            service_flag = 1;
        }
        if(service_flag == 1){
            email2_service += email2.at(i);
            if(email2.at(i) == '.'){
                type_flag = 1;
            }
            if(type_flag == 1){
                email2_type += email2.at(i);
            }
        }
    }
    
    if(email1_service == email2_service){
        return 1;
    }
    else if(email1_service != email2_service && email1_type == email2_type){
        return 2;
    }
    else{
        return 3;
    }
}

int Network::school_score(Person* p1, Person* p2){

    string school1 = p1->dict["school"];
    string school2 = p2->dict["school"];
    
    // Scores are as follow: 1 if exact same school/university, 2 if same type (both in high school, both in university, etc.), 3 if no similarity
    // Make both strings lower case
    for_each(school1.begin(), school1.end(), [](char & c){
        c = ::tolower(c);
    });
    for_each(school2.begin(), school2.end(), [](char & c){
        c = ::tolower(c);
    });

    // exact same school/university
    if(school1 == school2){
        return 1;
    }

    // both in high school
    size_t high_school1_found = school1.find("high school");
    size_t high_school2_found = school2.find("high school");
    if(high_school1_found != string::npos && high_school2_found != string::npos){
        return 2;
    }

    // both in university/college
    size_t uni1_found = school1.find("university");
    size_t uni2_found = school2.find("university");
    size_t college1_found = school1.find("college");
    size_t college2_found = school2.find("college");
    if((uni1_found != string::npos || college1_found != string::npos) && (uni2_found != string::npos || college2_found != string::npos)){
        return 2;
    }

    // no similarity
    return 3;
}

int Network::zip_score(Person* p1, Person* p2){

    string zip1 = p1->dict["zip"];
    string zip2 = p2->dict["zip"];
    // Scores are as follow: 1 if within same region in group (first 3 numbers the same), 2 if within same group (first number the same), 3 if in neither
    for(int i = 0; i < zip1.length(); i++){
        // if no match at first number
        if(zip1.at(i) != zip2.at(i) && i == 0){
            return 3;
        }
        // if no match at second or third number
        else if(zip1.at(i) != zip2.at(i) && (i == 1 || i == 2)){
            return 2;
        }
        // if loop is able to reach fourth number (meaning the first 3 numbers matched)
        else if(i == 3){
            return 1;
        }
    }
}

void Network::reccomendConnection(Person* person){
    Person* temp = head;
    vector<Person*> new_possibillities;
    bool found;

    while(temp != NULL){
        found = person->search(temp);
        if(!found && temp != person){
            new_possibillities.push_back(temp);
        }
        temp = temp->next;
    }

    int scores[new_possibillities.size() - 1][4];
    int i = 0;

    while(i < new_possibillities.size()){
        temp = new_possibillities.at(i);
        scores[i][0] = age_score(temp, person);
        scores[i][1] = school_score(temp, person);
        scores[i][2] = zip_score(temp, person);
        scores[i][3] = email_score(temp, person);
        i++;
    }

    double averages[new_possibillities.size()];
    Person* mins[new_possibillities.size()];
    int min = 4;
    int num_mins = 0;
    i = 0;
    int k = 0;
    double value = 0;

    while(i < new_possibillities.size()){
        temp = new_possibillities.at(i);
        value = (scores[i][0] + scores[i][1] + scores[i][2] + scores[i][3]) / 4;
        if(value < min) {
            min = value;
            for(int j = 0; j< new_possibillities.size(); j++){
                mins[j] = nullptr;
            }
            num_mins = 1;
            k = 1;
            mins[0] = new_possibillities.at(i);

        }
        else if(value == min){
            mins[k] = new_possibillities.at(i);
            k++;
            num_mins++;
        }

        i++;
    }

    if(num_mins == 0){
        cout<<"Sorry! You are already friends with everyone in this network!"<<endl;
    }

    else{
        cout<<"Connections Reccomended For You!"<<endl<<endl;

        for(int l = 0; l < num_mins; l++){
            mins[l]->print_person();
            cout<<endl<<endl;
        }

        cout<<"Would You like to connect with these people? Y/N: ";
        string yesno;
        cin>> yesno;
        if(yesno == "Y"){
            for(int l = 0; l < num_mins; l++){
                mins[l]->makeFriend(person);
                person->makeFriend(mins[l]);
            }
        }

    }

    
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Save network database \n";
        cout << "2. Load network database \n";
        cout << "3. Add a new connection \n";
        cout << "4. Remove a connection \n";
        cout << "5. Search \n";
        cout << "6. Send an email \n";
        cout << "7. Get Reccomendations \n";
        cout << "8. Print database \n";
        cout << "9. Connect\n";
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cin>>fileName;
            saveDB(fileName);
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            vector<string> files;
            DIR *dr;
            string name;
            bool flag = false;
            struct dirent *en;
            dr = opendir("."); //open all directory
            system("dir *.txt");
            cout << "Enter the name of the load file: ";
            getline(cin,fileName);
            loadDB(fileName);
            if(count == 0){
                cout << "File " + fileName + " does not exist!" << endl;
            }
            else{
                 // If file is loaded successfully, also print the count of connections in it:
                loadDB(fileName);
                cout << "Network loaded from " << fileName << " with " << count << " connections \n";
            }
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
            Person* new_person = new Person();
            fname = new_person->f_name;
            lname = new_person->l_name;

            if(search(fname,lname) == NULL){
                push_back(new_person);
                cout<<"Connection added successfully."<<endl;
            } else{
                cout<<"Connection already exists."<<endl;
            }
            cin.clear();
        }
        else if (opt == 4){
            
            // TODO: Complete me!
            cout << "Removing a connection \n";
            cout << "First name: ";
            getline(cin, fname);
            cout << "Last name: ";
            getline(cin, lname);

            if(search(fname, lname) == NULL){
                cout<<"Connection not found! \n";
            } else{
                remove(fname,lname);
                cout<<"Remove Successful \n";
            }
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Connection not found! \n";
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "First Name: ";
            getline(cin,fname);
            cout << "Last Name: ";
            getline(cin,lname);
            cout << "Searching: \n";
            if(search(fname,lname) == NULL){
                cout<<"Not found! \n";
            } else{
                Person* p = search(fname,lname);
                p->print_person();
            }
            
            // if found: print connection
            // if not, cout << "Not found! \n";
        }
        else if (opt==6){
            // Note: Completed!
            cout << "Sending email to: \n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Person* ptr = search(fname, lname);
            if (ptr){
                string subject, content, attachment;
                cout << "Sending email to: \n";
                ptr->print_person();
                cout << "Subject: ";
                std::getline (std::cin, subject);
                cout << "Content: ";
                std::getline (std::cin, content);
                cout << "Attachment: ";
                std::getline (std::cin, attachment);
                string addr = ptr->email->get_contact("1");
                sendEmail(addr, subject, content, attachment);
            }
            else 
                cout << "Contact not found! \n";
        }
        else if (opt==7){
            cout << "Please enter connection name to see reccomendations\n";
            cout << "First Name: ";
            std::getline (std::cin, fname);
            cout << "Last Name: ";
            std::getline (std::cin, lname);
            Person* ptr = search(fname, lname);

            if(ptr){
                cout<<"Reccomending Connections... "<<endl<<endl;
                reccomendConnection(ptr);

            }
            else{
                cout<<"Sorry! Person does not exist"<<endl;
            }
        }
        else if (opt==8){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else if (opt == 9){
            cout<<"Make friends:"<<endl;
            cout<<"Person 1"<<endl<<"First Name: ";
            getline(cin,fname);
            cout<<"Last Name: ";
            getline(cin,lname);
            Person* p1 = search(fname,lname);
            if(p1 != NULL){
                cout<<"Person 2"<<endl;
                cout<<"First Name: ";
                getline(cin, fname);
                cout<<"Last Name: ";
                getline(cin,lname);
                Person* p2 = search(fname, lname);
                if(p2 != NULL){
                    bool flag = FALSE;
                    for(int i = 0; i < p1->myfriends.size(); i++){
                        if(p1->myfriends.at(i) == p2){
                            flag = TRUE;
                        }
                    }
                    if(!flag){
                        p1->makeFriend(p2);
                        p2->makeFriend(p1);
                        cout<<"Connection Successful! \n";
                    } else{
                        cout<<"Contacts are already connected. \n";
                    }
                }
                else{
                    cout<<"Connection not found \n";
                }
            }
            else{
                cout<<"Connection not found"<<endl;
            }
            
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}

