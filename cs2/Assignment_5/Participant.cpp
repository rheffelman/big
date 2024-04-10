#include "Participant.h"

Participant::Participant(string n, string e, string p){
    name = n;
    email = e;
    phoneNumber = p;
}
//--
string Participant::toString(){
    string commaSpace = ", ";
    return name + commaSpace + email + commaSpace + phoneNumber;
}
//--
void Participant::printAvailability(){
    for (int i = 0; i < availability.size(); i++){
        printf("%d  ", availability[i]);
        if (i % 6 == 5) printf("\n");
    }
    printf("\n");
}
//--