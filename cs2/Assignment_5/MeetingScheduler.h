#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Meeting.h"
#include "Participant.h"

using namespace std;

enum {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

class MeetingScheduler{
public:
    MeetingScheduler(int duration);
    MeetingScheduler(int duration, double attendanceReq);
    void findAvailableMeetingTimes();
    void setAvailable(Participant* p, int day, const string& startTime, const string& endTime);
    void setBusy(Participant* p, int day, const string& startTime, const string& endTime);

    static int timeFlattener(int day, const string& time);
    string timeUNFlattener(int time);
    bool inputCheck(const string& input);
    void intersectionFiller();
    void intersectionChecker();
    void printersection() const;
    bool myFind(const vector <int>& v, int val);
    bool otherFind(const vector <Participant*>& v, Participant* val);

    double requiredAttendance = 1;
    vector <int> intersection;
    vector <Meeting> meetings;
    vector < Participant* > allParticipants;
    int meetingDuration = -1;
private:
};