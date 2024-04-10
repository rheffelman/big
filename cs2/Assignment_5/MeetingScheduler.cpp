#include "MeetingScheduler.h"

MeetingScheduler::MeetingScheduler(int duration){
    meetingDuration = duration;
    requiredAttendance = 1;
}
//--
MeetingScheduler::MeetingScheduler(int duration, double attendanceReq){
    meetingDuration = duration;
    requiredAttendance = attendanceReq * 0.01;
}
//--
void MeetingScheduler::findAvailableMeetingTimes(){
    intersectionFiller();
    intersectionChecker();
    
    for (int i = 0; i < meetings.size(); i++){
        meetings[i].print();
    }
    for (int i = 0; i < allParticipants.size(); i++){
        allParticipants[i]->availability.clear();
        for (int j = 0; j < 7; j++) allParticipants[i]->busyAr[j] = false;
    }

}
//--
void MeetingScheduler::setAvailable(Participant* p, int day, const string& startTime, const string& endTime){
    if (!otherFind(allParticipants, p)){
        allParticipants.push_back(p);
    }

    if (inputCheck(startTime) and inputCheck(endTime)){
        int start = timeFlattener(day, startTime);
        int end = timeFlattener(day, endTime);

        for (int i = start; i <= end; i++){
            p->availability.push_back(i);
        }
    }
}
//--
int MeetingScheduler::timeFlattener(int day, const string& time){
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
string MeetingScheduler::timeUNFlattener(int time){
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
//--
bool MeetingScheduler::inputCheck(const string& input){
    int size = input.size();
    if (size != 6 and size != 7) return false;
    if (input[size - 1] != 'm') return false;
    if (input[size - 2] != 'a' and input[size - 2] != 'p') return false;
    return true;
}
//--
void MeetingScheduler::intersectionFiller(){
    vector <int> minutes(10080); //10,080 is the amount of minutes in a week. (7*24*60)

    for (int i = 0; i < allParticipants.size(); i++){
        for (int j = 0; j < allParticipants[i]->availability.size(); j++){
            minutes[allParticipants[i]->availability[j]]++;
        }
    }

    for (int i = 0; i < minutes.size(); i++){
        if (minutes[i] >= allParticipants.size() * requiredAttendance){
            intersection.push_back(i);
        }
    }
}
//--
void MeetingScheduler::intersectionChecker(){
    int count = 0;

    //checks the intersection for sequences of minutes >= meetingDuration, creates them as meetings and pushes them back into my meetings vector.
    for (int i = 0; i < intersection.size(); i++){
        if (count == meetingDuration){

            meetings.push_back(Meeting(intersection[i - meetingDuration],
             timeUNFlattener(intersection[i - meetingDuration]), meetingDuration));

            i = (i - meetingDuration) + 15; //15 to schedule meetings only in 15m increments
            count = 0;
        }
        if (i != intersection.size() - 1){
            if (intersection[i + 1] - intersection[i] == 1){
            count++;
            }
            else count = 0;
        }
    }

    //adds participants who are available to my vector of meetings
    for (int i = 0; i < meetings.size(); i++){
        for (int j = 0; j < allParticipants.size(); j++){
            if (myFind(allParticipants[j]->availability, timeFlattener(meetings[i].m_day, meetings[i].m_time))){
                meetings[i].addParticipant(allParticipants[j]);
            }
        }
    }  
}
//--
void MeetingScheduler::printersection() const{

    for (int i = 0; i < intersection.size(); i++){
        printf("%d  ", intersection[i]);
        if (i % 6 == 5) printf("\n");
    }
}
//--
bool MeetingScheduler::myFind(const vector <int>& v, int val){
    for (int i = 0; i < v.size(); i++){
        if (v[i] == val) return true;
    }
    return false;
}
//--
bool MeetingScheduler::otherFind(const vector <Participant*>& v, Participant* val){
    for (int i = 0; i < v.size(); i++){
        if (v[i]->name == val->name) return true;
    }
    return false;
}
//--
void MeetingScheduler::setBusy(Participant* p, int day, const string& startTime, const string& endTime){
    if (!otherFind(allParticipants, p)){
        allParticipants.push_back(p);
    }
    if (!p->busyAr[day]){
        p->busyAr[day] = true;
        for (int i = timeFlattener(day, "12:00am"); i < timeFlattener(day, startTime); i++){
            p->availability.push_back(i);
        }

        for (int i = timeFlattener(day, endTime); i < timeFlattener(day, "11:59pm"); i++){
            p->availability.push_back(i);
        }
    }
    else printf("sorry! you cannot setBusy() more than twice per day per participant.\n");
}
//--