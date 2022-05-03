#include <iostream>
#include "person.h"
#include "person.cpp"
#include "contact.h"
#include "contact.cpp"
#include "date.h"
#include "date.cpp"

int main(){

    Person c1;

    c1.print_person();
    cout << "----------------\n";


   

    Person c2("person_template.txt");
    c2.print_person();
    cout << "----------------\n";
    Person c3("Emily", "London", "11/14/2001", "(School) elondon@usc.edu", "(Cell) 571-643-6858");
    c3.print_person();
    cout << "----------------\n";


    cout << "Is c1 equal to c2: " << (c1==c2) << endl;
    cout << "Is c1 not equal to c2: " << (c1!=c2) << endl;

    return 0;
}
