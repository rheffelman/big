#include <iostream>
#include <string>

#include "Participant.h"
#include "Meeting.h"

using namespace std;

int main(){
    Participant* p_p1 = new Participant("Mark", "mmahoney@carthage.edu", "(262) 551-5869");
    Participant* p_p2 = new Participant("Laura", "laura@mail.com", "(262) 551-1234");
    Participant* p_p3 = new Participant("Buddy", "buddy@mail.com", "(262) 551-2345");
    Participant* p_p4 = new Participant("Patrick", "patrick@mail.com", "(262) 551-3456");

    Meeting m1("4/26/2023", "9:00am", 60);
    m1.addParticipant(p_p1);
    m1.addParticipant(p_p2);
    m1.addParticipant(p_p3);
    m1.addParticipant(p_p4);

    Meeting m2("4/27/2023", "10:00am", 30);
    m2.addParticipant(p_p1);
    m2.addParticipant(p_p2);

    m1.print();
    m2.print();

    delete p_p1;
    delete p_p2;
    delete p_p3;
    delete p_p4;
}