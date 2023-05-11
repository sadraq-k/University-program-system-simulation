#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include <cstdlib>
//#include<sstream>

using namespace std;
//tabdil string be bool 
bool stringToBool(string temp){
    bool check{true};
    if(temp == "true" || temp == "True" || temp == "TRUE")
        check = true;
    else if(temp == "false" || temp == "False" || temp == "FALSE" )
        check = false;
    return check;

}
//class date: braye neshan dadan tarikh va saat dars va kelas
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

//class course: etelaat dars
class course{
    //friend void inputCourse(course&temp , string help);

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
        cout<<idCourse<<endl<<name<<endl<<teachername<<endl<<videoprojector<<endl<<temprary<<endl<<capacityCourse<<endl;
    }

    void inputCourse(string help){
    char auxiliary[80];
    char assist[80];

    fstream coursetemp;
    coursetemp.open("proj.txt" , ios::in);
    if(coursetemp.fail()){
        cout<<"fail\tthe file has a problem"<<endl;
    }
    int j;
    for(j = 1; !coursetemp.eof(); j++ )
    {
        coursetemp.getline(assist , 80);
        if(assist == help)
            break;
    }
    coursetemp.close();
    coursetemp.open("proj.txt" , ios::in);

    for(int i{1}; !coursetemp.eof(); i++)
    {
        coursetemp.getline(auxiliary , 80);
        if(i>=j-1 && i<=j+6)
        {

            if(i == j)
                idCourse = auxiliary;
            if(i == j+1)
                name = auxiliary;
            if(i == j+2)
                teachername = auxiliary;
            if(i == j+3)
                videoprojector = stringToBool(auxiliary);
            if(i == j+4)
                temprary = stringToBool(auxiliary);
            if(i == j+5)
            {
                const char* x = auxiliary;
                capacityCourse = atoi(x);
            }


        }

    }
    coursetemp.close();
}

};



//class classroom : etalaat kelas
class classroom{ 
   // friend void check();
   // friend void inputClassroom(classroom& temp ,string help);
protected:
    string idClass;
    int capacityClass;
    bool videoprojector;
    date dateClass;
    string idCourse;


public:

    void show()
    {
        cout<<boolalpha;
        cout<<idClass<<endl<<capacityClass<<endl<<videoprojector<<endl;
    }

    void inputClassroom(string help)
{
    char auxiliary[80];
    char assist[80];

    fstream classtemp;
    classtemp.open("proj.txt" , ios::in);
    if(classtemp.fail()){
        cout<<"fail\tthe file has a problem"<<endl;
    }
    int j;
    for(j = 1; !classtemp.eof(); j++ )
    {
        classtemp.getline(assist , 80);
        if(assist == help)
            break;
    }
    classtemp.close();
    classtemp.open("proj.txt" , ios::in);

    for(int i{1}; !classtemp.eof(); i++)
    {
        classtemp.getline(auxiliary , 80);
        if(i>=j-1 && i<=j+6)
        {

            if(i == j)
                idClass = auxiliary;
            if(i == j+1)
                capacityClass = atoi(auxiliary);
            if(i == j+2)
                videoprojector = stringToBool(auxiliary);


            /* if(i == j+5)
             {
                 const char* x = auxiliary;
                 temp.capacityCourse = atoi(x);
             }*/


        }

    }
    classtemp.close();
}

};




// baraye mohasebe saat payan dars kelas
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




/*void inputCourse(course& temp ,string help){
    char auxiliary[80];
    char assist[80];

    fstream coursetemp;
    coursetemp.open("proj.txt" , ios::in);
    if(coursetemp.fail()){
        cout<<"fail\tthe file has a problem"<<endl;
    }
    int j;
    for(j = 1; !coursetemp.eof(); j++ )
    {
        coursetemp.getline(assist , 80);
        if(assist == help)
            break;
    }
    coursetemp.close();
    coursetemp.open("proj.txt" , ios::in);

    for(int i{1}; !coursetemp.eof(); i++)
    {
        coursetemp.getline(auxiliary , 80);
        if(i>=j-1 && i<=j+6)
        {

            if(i == j)
                temp.idCourse = auxiliary;
            if(i == j+1)
                temp.name = auxiliary;
            if(i == j+2)
                temp.teachername = auxiliary;
            if(i == j+3)
                temp.videoprojector = stringToBool(auxiliary);
            if(i == j+4)
                temp.temprary = stringToBool(auxiliary);
            if(i == j+5)
            {
                const char* x = auxiliary;
                temp.capacityCourse = atoi(x);
            }


        }

    }
    coursetemp.close();
}*/



int main(){
    cout<<"run program :"<<endl;

    date temp(8,2,1401,8,30,1,30);
    array<int , 2>myarr{calcuteTime(temp)};
    for(int i=0 ; i<2; i++){
        cout<<myarr[i]<<":";


    }
    cout<<endl;
    course AdvanceProgramming;
    //inputCourse(AdvanceProgramming , "MH101");
    AdvanceProgramming.inputCourse("MH101");
    AdvanceProgramming.show();

    return 0;
}