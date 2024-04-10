#include "Meeting.h"

Meeting::Meeting(int day, string time, int duration):
m_time(time),
m_day((day / 60) / 24),
m_duration(duration){}
//--
void Meeting::addParticipant(Participant* p_participant){
allParticipants.push_back(p_participant);
}
//--
void Meeting::print(){
    string ar[7] {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    string endTime = timeUNFlattener(timeFlattener(m_day, m_time) + m_duration);
    printf("Meeting available on %s from %s to %s\n", ar[m_day].c_str(), m_time.c_str(), endTime.c_str());
    for (int i = 0; i < allParticipants.size(); i++){
        printf("-%s\n", allParticipants[i]->toString().c_str());
    }
    printf("\n");
}
//--
int Meeting::timeFlattener(int day, const string& time){
    int minutes = day * 24 * 60;
    int hours = 0;
    if (time.length() == 7){
        hours = stoi(time.substr(0, 2));
        minutes += stoi(time.substr(3, 6));
    }
    else{
        hours = time[0] - '0';
        minutes += stoi(time.substr(2, 5));
    }
    if (time[time.length() - 2] == 'p' and hours != 12) hours += 12;
    else if (time[time.length() - 2] == 'a' and hours == 12) hours = 0;
    minutes += hours * 60;

    return minutes;
}
//--
string Meeting::timeUNFlattener(int time){
    int days = (time / 60) / 24;
    time -= (days * 60)  * 24;

    int hours = time / 60;
    time -= hours * 60;

    int minutes = time;
    char aORp = 'a';
    if (hours > 12){
        hours -= 12;
        aORp = 'p';
    }
    return to_string(hours) + ':' + ((minutes < 10)? "0":"") + to_string(minutes) + aORp + 'm';
}