#include "Meeting.h"

Meeting::Meeting(string date, string time, int duration){
    m_date = date;
    m_time = time;
    m_duration = duration;
}
//--
void Meeting::addParticipant(Participant* p_participant){
allParticipants.push_back(p_participant);
}
//--
void Meeting::print(){
    printf("There is a %d minute meeting on %s starting at %s between participants:\n", m_duration, m_date.c_str(), m_time.c_str());
    for (int i = 0; i < allParticipants.size(); i++){
        printf("%s\n", allParticipants[i]->toString().c_str());
    }
    printf("\n");
}