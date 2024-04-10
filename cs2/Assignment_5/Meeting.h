#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Participant.h"

class Meeting{
public:
Meeting(int day, string time, int duration);
vector < Participant* > allParticipants;
void addParticipant(Participant* p_participant);
void print();
static int timeFlattener(int day, const string& time);
string timeUNFlattener(int time);

int m_day = -1;
string m_time = "!!!";
int m_duration = -1;

private:

};