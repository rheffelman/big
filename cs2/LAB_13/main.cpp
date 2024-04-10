#include <iostream>
#include <string>

#include "Participant.h"

using namespace std;

int main(){
    Participant* Mark = new Participant("Mark", "mmahoney@carthage.edu", "(262) 551-5869");
    printf("%s\n", Mark->toString().c_str());
    delete Mark;

    Participant* Laura = new Participant("Laura", "laura@mail.com", "(262) 551-1234");
    printf("%s\n", Laura->toString().c_str());
    delete Laura;

    Participant* Buddy = new Participant("Buddy", "buddy@mail.com", "(262) 551-2345");
    printf("%s\n", Buddy->toString().c_str());
    delete Buddy;

    Participant* Patrick = new Participant("Patrick", "patrick@mail.com", "(262) 551-3456");
    printf("%s\n", Patrick->toString().c_str());
    delete Patrick;
}