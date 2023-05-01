#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
//#include<sstream>
using namespace std;

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


class course{
    friend void inputCourse(course&temp , string help);

protected:
    string idCourse;
    string name;
    string teachername;
    bool videoprojector;
    bool temprary;
    int capacityCourse;
    date courseTime;
private:
    //vector<int>studentList
    int* studentList{new int[capacityCourse]};

public:
    void show(){
        cout<<boolalpha;
        cout<<idCourse<<endl<<name<<endl<<teachername<<endl<<videoprojector<<temprary<<endl<<capacityCourse<<endl;
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


/*template <typename T>
T stringToInteger(string str){
    T result;
    istringstream convert(str);
    if ( !(convert >> result) )
        throw "Can not convert";

    return result;}*/


bool stringToBool(string temp){
    bool check{true};
    if(temp == "true" || temp == "True" || temp == "TRUE")
        check = true;
    else if(temp == "false" || temp == "False" || temp == "FALSE" )
        check = false;
    return check;

}

void inputCourse(course& temp ,string help){
    char auxiliary[80];
    char assist[80];

    fstream coursetemp;
    coursetemp.open("proj.txt" , ios::in);
    if(coursetemp.fail()){
        cout<<"fail\tthe file has a problem"<<endl;
    }
    int j;
    for(j = 1; assist == help; j++ ){
        coursetemp.getline(assist , 80);
    }
    coursetemp.close();
    coursetemp.open("proj.txt" , ios::in);

    for(int i{1}; !coursetemp.eof(); i++){
        coursetemp.getline(auxiliary , 80);
        if(i>=j-1 && i<j+5){
            /* switch (i)
             {
             case (j-1) :
                 temp.idCourse = auxiliary;
                 break;
             case j:
                 temp.name = auxiliary;
                 break;
             case (j+1):
                 temp.teachername = auxiliary;
                 break;
             case (j+2):
                 temp.videoprojector = stringToBool(auxiliary);
                 break;
             case (j+3):
                 temp.temprary = stringToBool(auxiliary);
                 break;
             case (j+4):
                 temp.capacityCourse = stringToInteger<int>(auxiliary);
                 break;
             default:
                 ;
                 break;
             }*/
            if(i == j-1)
                temp.idCourse = auxiliary;
            if(i == j)
                temp.name = auxiliary;
            if(i == j+1)
                temp.teachername = auxiliary;
            if(i == j+2)
                temp.videoprojector = stringToBool(auxiliary);
            if(i == j+3)
                temp.temprary = stringToBool(auxiliary);
            //if(i == j+4)
                //temp.capacityCourse = stringToInteger<int>(auxiliary);

        }

    }
    coursetemp.close();
}



int main(){
    cout<<"run program :"<<endl;

    date temp(8,2,1401,8,30,1,30);
    array<int , 2>myarr{calcuteTime(temp)};
    for(int i=0 ; i<2; i++){
        cout<<myarr[i]<<":";


    }
    cout<<endl;
    course AdvanceProgramming;
    inputCourse(AdvanceProgramming , "AP101");
    AdvanceProgramming.show();

    return 0;
}