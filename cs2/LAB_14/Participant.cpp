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