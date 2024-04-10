#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Participant.h"

class Meeting{
public:
Meeting(string date, string time, int duration);
vector < Participant* > allParticipants;
void addParticipant(Participant* p_participant);
void print();

string m_date = "!!!";
string m_time = "!!!";
int m_duration = -1;

private:

};