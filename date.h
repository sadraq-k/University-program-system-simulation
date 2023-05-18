//
// Created by User on 5/1/2023.
//

#ifndef UNIVERSITY_PROGRAM_SYSTEM_SIMULATION_DATE_H
#define UNIVERSITY_PROGRAM_SYSTEM_SIMULATION_DATE_H

#endif //UNIVERSITY_PROGRAM_SYSTEM_SIMULATION_DATE_H
class date{
    friend auto calcuteTime(date object);
private:
    int day;
    int month;
    int year;
    int hourStart;
    int minStart;
    int hourEnd;
    int minEnd;
    int durationMin;
    int durationHour;
public:
    date(int d = 1 , int m = 1 , int y = 1401 ,int hS = 0 , int mS = 0 , int duH = 0 , int duM = 0 ){
        day = d;
        month = m;
        year = y;
        hourStart = hS;
        minStart = mS;
        hourEnd = 0;
        minEnd = 0;
        durationMin = duM;
        durationHour = duH;

    }

};
auto calcuteTime(date object){

    object.minEnd = object.minStart + object.durationMin;
    if(object.minEnd > 59){
        object.minEnd -=60;
        object.hourEnd =1;
    }

    object.hourEnd += object.hourStart + object.durationHour;
    if(object.hourEnd>23)
        object.minEnd -=24;

    array<int , 2> timeEnd = {object.hourEnd , object.minEnd};
    return timeEnd;
}

