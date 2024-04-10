#include <iostream>
#include <string>

#include "MeetingScheduler.h"

using namespace std;

void testCase0(Participant* p1, Participant* p2, Participant* p3, Participant* p4);
void testCase1(Participant* p1, Participant* p2, Participant* p3, Participant* p4);
void testCase2(Participant* p1, Participant* p2, Participant* p3, Participant* p4);
void testCase3(Participant* p1, Participant* p2, Participant* p3, Participant* p4);
void testCase4(Participant* p1, Participant* p2, Participant* p3, Participant* p4);

int main(){

    cout << "Meeting Scheduler" << endl;

    Participant* p1 = new Participant("Mark", "mmahoney@carthage.edu", "(262) 551-5869");
    Participant* p2 = new Participant("Laura", "laura@mail.com", "(262) 551-1234");
    Participant* p3 = new Participant("Buddy", "buddy@mail.com", "(262) 551-2345");
    Participant* p4 = new Participant("Patrick", "patrick@mail.com", "(262) 551-3456");

    testCase0(p1, p2, p3, p4); 
    testCase1(p1, p2, p3, p4);
    testCase2(p1, p2, p3, p4);
    testCase3(p1, p2, p3, p4);
    testCase4(p1, p2, p3, p4); 
    
    delete p1; delete p2; delete p3; delete p4;
}
//--
void testCase0(Participant* p1, Participant* p2, Participant* p3, Participant* p4){
    MeetingScheduler s0(45);
    s0.setAvailable(p1, Monday, "9:00am", "10:00am");
    s0.setAvailable(p2, Monday, "8:00am", "1:00pm");
    s0.setAvailable(p3, Monday, "8:15am", "10:15am");
    s0.setBusy(p4, Monday, "1:00pm", "2:00pm");
    s0.setBusy(p4, Monday, "1:00pm", "2:00pm");

    cout<<"Test Meeting 0"<<endl;
    //Monday 9:00-9:45, 9:15-10:00
    s0.findAvailableMeetingTimes();
    cout<<endl;
}
//--
void testCase1(Participant* p1, Participant* p2, Participant* p3, Participant* p4){
    MeetingScheduler s1(45, 75.0);
    s1.setAvailable(p1, Monday, "9:00am", "10:00am");
    s1.setAvailable(p2, Monday, "8:00am", "1:00pm");
    s1.setAvailable(p3, Monday, "8:15am", "10:15am");
    s1.setBusy(p4, Monday, "1:00pm", "2:00pm");
    
    cout<<"Test Meeting 1"<<endl;
    //Monday 8:15-9:00 (3), 8:30-9:15 (3), 8:45-9:30 (3), 9:00-9:45 (4), 9:15-10:00 (4), 9:30-10:15 (3)
    s1.findAvailableMeetingTimes();
    cout<<endl;
}
//--
void testCase2(Participant* p1, Participant* p2, Participant* p3, Participant* p4){
    MeetingScheduler scheduler2(25);
    scheduler2.setAvailable(p1, Monday, "9:00am", "10:00am");
    scheduler2.setAvailable(p1, Tuesday, "9:00am", "10:00am");
    scheduler2.setAvailable(p1, Wednesday, "9:00am", "10:00am");

    scheduler2.setAvailable(p2, Monday, "8:00am", "1:00pm");
    scheduler2.setAvailable(p2, Monday, "4:00pm", "5:30pm");
    scheduler2.setAvailable(p2, Friday, "8:00am", "1:00pm");
    scheduler2.setAvailable(p2, Friday, "4:00pm", "5:30pm");

    scheduler2.setAvailable(p3, Monday, "8:15am", "10:15am");
    scheduler2.setAvailable(p3, Monday, "11:15am", "12:00pm");
    scheduler2.setAvailable(p3, Monday, "4:15pm", "5:30pm");
    scheduler2.setAvailable(p3, Thursday, "8:15am", "10:15am");
    scheduler2.setAvailable(p3, Friday, "8:15am", "10:15am");

    scheduler2.setBusy(p4, Monday, "1:00pm", "2:00pm");
    scheduler2.setBusy(p4, Friday, "1:00pm", "2:00pm");

    cout<<"Test Meeting 2"<<endl;
    //Monday 9:00-9:30, 9:15-9:45, 9:30-10:00
    scheduler2.findAvailableMeetingTimes();
    cout<<endl;
}
//--
void testCase3(Participant* p1, Participant* p2, Participant* p3, Participant* p4){
    MeetingScheduler scheduler3(25, 50.0);
    scheduler3.setAvailable(p1, Monday, "9:00am", "10:00am");
    scheduler3.setAvailable(p1, Monday, "11:00am", "12:00pm");
    scheduler3.setAvailable(p1, Monday, "2:00pm", "3:00pm");

    scheduler3.setAvailable(p2, Monday, "9:30am", "11:30am");

    scheduler3.setAvailable(p3, Thursday, "8:15am", "10:15am");
    scheduler3.setAvailable(p3, Friday, "8:15am", "8:45am");

    scheduler3.setBusy(p4, Friday, "1:00pm", "2:00pm");

    cout<<"Test Meeting 3"<<endl;
    //Monday 9:30-10:00 (2), 11:00-11:30 (2)
    //Friday 8:15-8:45 (2)
    scheduler3.findAvailableMeetingTimes();
    cout<<endl;
}
//--
void testCase4(Participant* p1, Participant* p2, Participant* p3, Participant* p4){
    MeetingScheduler scheduler4(25, 75.0);
    scheduler4.setAvailable(p1, Monday, "9:00am", "10:00am");
    scheduler4.setAvailable(p1, Monday, "11:00am", "12:00pm");
    scheduler4.setAvailable(p2, Monday, "9:30am", "11:30am");
    scheduler4.setAvailable(p3, Monday, "9:00am", "9:45am");
    scheduler4.setAvailable(p4, Monday, "9:45am", "10:30am");

    cout<<"Test Meeting 4"<<endl;
    //None- no meeting times with 3 people
    scheduler4.findAvailableMeetingTimes();
    cout<<endl;
}