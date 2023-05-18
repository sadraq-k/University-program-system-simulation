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
    /*int day;
    int month;
    int year;*/
    int hourStart;
    int minStart;
    int hourEnd;
    int minEnd;
    int durationMin;
    int durationHour;
public:
    /*date(int d = 1 , int m = 1 , int y = 1401 ,int hS = 0 , int mS = 0 , int duH = 0 , int duM = 0 ){
        day = d;
        month = m;
        year = y;
        hourStart = hS;
        minStart = mS;
        hourEnd = 0;
        minEnd = 0;
        durationMin = duM;
        durationHour = duH;

    }*/

    void set_HS(int a = 0){
        hourStart = a;
    }
    void set_MS(int a = 0){
        minStart = a;
    }
    void set_DH(int a = 0){
        durationHour = a;
    }
    void set_DM(int a = 0){
        durationMin = a;
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




//class classroom : etalaat kelas
class classroom{ 
   // friend void check();
   // friend void inputClassroom(classroom& temp ,string help);
private:
    string idClass;
    int capacityClass;
    bool videoprojector;
    //date dateClass;
    //string idCourse;


public:

    void show(){
        cout<<boolalpha;
        cout<<idClass<<endl<<capacityClass<<endl<<videoprojector<<endl;
    }

    void inputClassroom(string help){
    char auxiliary[80];
    char assist[80];

    fstream classtemp;
    classtemp.open("proj.txt" , ios::in);
    if(classtemp.fail()){
        cout<<"fail\tthe file has a problem"<<endl;
    }
    int j;
    for(j = 1; !classtemp.eof(); j++ ){
        classtemp.getline(assist , 80);
        if(assist == help)
            break;
    }
    classtemp.close();
    classtemp.open("proj.txt" , ios::in);

    for(int i{1}; !classtemp.eof(); i++){
        classtemp.getline(auxiliary , 80);
        if(i>=j-1 && i<=j+6){

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



//class course: etelaat dars
class course{
    //friend void inputCourse(course&temp , string help);
private:
    string idCourse;
    string name;
    string teachername;
    bool videoprojector;
    bool temprary;
    int capacityCourse;
    
    //vector<int>studentList
    //int* studentList{new int[capacityCourse]};

public:
    classroom location; 
    date courseTime;
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

    for(int i{1}; !coursetemp.eof(); i++){
        coursetemp.getline(auxiliary , 80);
        if(i>=j-1 && i<=j+6){

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
            if(i == j+5){
                const char* x = auxiliary;
                capacityCourse = atoi(x);
            }
            
            if(i == j+6){
                const char* x = auxiliary;
                courseTime.set_HS(atoi(x));
            }
            if(i == j+7){
                const char* x = auxiliary;
                courseTime.set_MS(atoi(x));
            }
            if(i == j+8){
                const char* x = auxiliary;
                courseTime.set_DH(atoi(x)); 
            }
            if(i == j+9){
                const char* x = auxiliary;
                courseTime.set_DM(atoi(x));
            }


        }

    }
    coursetemp.close();
}

};



/*template <typename T>
T stringToInteger(string str){
    T result;
    istringstream convert(str);
    if ( !(convert >> result) )
        throw "Can not convert";

    return result;}*/




//hanooz kamel nashode vali baraye moshakhas kardan mahal ya hamoon kelase
void specify(course temp[4]){
   /* course AdvanceProgramming;
    course Math;
    course physics;
    course workshop*/
    bool check;
    cout<<"you want to determine the location of each course yourself (enter 1)| the program specifies the location of each course (enter 0) "<<endl; 
    cin>>check; 
    if(check){
        string questionForCourse;
        string questionForClassroom; 
        cout<<"to determine the classroom , enter the desired course : ";
        getline(cin , questionForCourse);
        if(questionForCourse == "Advance Programming"){
            //AdvanceProgramming.inputCourse("AP101");
            temp[0].inputCourse("AP101");
            cout<<"enter the desired classroom for the Advance Programming course : ";
            getline(cin , questionForClassroom);
            //(AdvanceProgramming.location).inputClassroom(questionForClassroom);
            (temp[0].location).inputClassroom(questionForClassroom);
        }   

        if(questionForCourse == "Math"){
           // Math.inputCourse("MH101");
            temp[1].inputCourse("MH101");
            cout<<"enter the desired classroom for the Math course : ";
            getline(cin , questionForClassroom);
            //(Math.location).inputClassroom(questionForClassroom);
            (temp[1].location).inputClassroom(questionForClassroom);    
        }

         if(questionForCourse == "Physics"){
            //Physics.inputCourse("PH101");
            temp[2].inputCourse("PH101");
            cout<<"enter the desired classroom for the Math course : ";
            getline(cin , questionForClassroom);
            //(Physics.location).inputClassroom(questionForClassroom);
            (temp[2].location).inputClassroom(questionForClassroom);    
        }

         if(questionForCourse == "Workshop"){
            //workshop.inputCourse("WH101");
            temp[3].inputCourse("HH101");
            cout<<"enter the desired classroom for the Math course : ";
            getline(cin , questionForClassroom);
            //(workshop.location).inputClassroom(questionForClassroom);
            (temp[3].location).inputClassroom(questionForClassroom);    
        }
    }

}
int main(){
    cout<<"run program :"<<endl;

   /* date temp(8,2,1401,8,30,1,30);
    array<int , 2>myarr{calcuteTime(temp)};
    for(int i=0 ; i<2; i++){
        cout<<myarr[i]<<":";


    }
    cout<<endl;
    
    /*course advp; 
    course math; 
    course  physics; 
    course workshop; 
    course courses[4] = {advp , math , physics , workshop};
    specify(courses);*/



    /*course math;
    math.courseTime.set_DH(1);
    math.courseTime.set_DM(45);
    math.courseTime.set_HS(16);
    math.courseTime.set_MS(00);
    array<int , 2>myarr = calcuteTime(math.courseTime);
    for(int i =0; i<2; i++)
        cout<<myarr[i]<<'\t';*/

    course AdvanceProgramming;
    classroom a101;
    //inputCourse(AdvanceProgramming , "MH101");
    AdvanceProgramming.inputCourse("AP101");
    AdvanceProgramming.show();


   return 0;
    
    }








