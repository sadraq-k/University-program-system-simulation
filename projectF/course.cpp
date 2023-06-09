#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include <cstdlib>
#include<algorithm>
#include<sstream>
using namespace std;


//forward declaration
class course;
class courseLocation;
class date;

void mothercheck(course);



//Auxiliary function to convert string to Boolean
bool stringToBool(string temp){
    bool check{true};
    if(temp == "true" || temp == "True" || temp == "TRUE")
        check = true;
    else if(temp == "false" || temp == "False" || temp == "FALSE" )
        check = false;
    return check;

}




class date{

    friend void sortDay(course temp[4]);
    friend bool checkTime(course temp , course dayOfWeek);

private:

    int hourStart =0;
    int minStart=0;
    int hourEnd=0;
    int minEnd=0;
    int durationMin=0;
    int durationHour=0;

//Variables for storing course days
    string day1;
    string day2;
public:

//Variables to store start and end time
    double st,et;

    void set_HS(int a = 0)
    {
        hourStart = a;
    }
    void set_MS(int a = 0)
    {
        minStart = a;
    }
    void set_DH(int a = 0)
    {
        durationHour = a;
    }
    void set_DM(int a = 0)
    {
        durationMin = a;
    }
    void set_Day(string d1,string d2){
        day1=d1;
        day2 =d2;
    }
    string ret_day1(){
        return day1;
    }
    string ret_day2(){
        return day2;
    }

//Calculation of the end time of the course according to the start time and its duration
    void calcuteTime()
    {
        minEnd = minStart + durationMin;
        if(minEnd > 59)
        {
            minEnd -=60;
            hourEnd =1;
        }

        hourEnd += hourStart + durationHour;
        if(hourEnd>23)
            hourEnd -=24;


        st=hourStart+(0.01*minStart);
        et=hourEnd+(0.01*minEnd);

    }



};


class commonInformartion{
    friend int checkRoom(courseLocation room);
    friend void specify(course temp[10]);
    friend void babycheck();
    friend  void automaticLocationDetermination(courseLocation rooms[3]);
    friend void weekShow();
    friend void studentcheck();
    friend void WriteInTheFile();

protected:
    //Common information between two classes, course and courselocation
    string id=" ";
    int capacity = 45;
    bool videoprojector;

public:
    //pure virtual fuction
    virtual void inputInformation(string help) = 0;
    
};




class courseLocation : public commonInformartion{
    friend void mothercheck(course temp[10]);
    friend void automaticLocationDetermination(courseLocation rooms[3]);

public:

//Read information from the file
    void inputInformation(string help){

        string auxiliary;
        string assist;
        fstream classtemp;
        classtemp.open("location.txt" , ios::in);
        if(classtemp.fail()){
            cout<<"fail\the file has a problem"<<endl;
        }
        int j;
        for(j = 1; !classtemp.eof(); j++ ){
            getline(classtemp,assist);
            if(assist == help)
                break;
        }


        classtemp.close();
        classtemp.open("location.txt" , ios::in);

        for(int i{1}; !classtemp.eof(); i++){
            getline(classtemp,auxiliary);
            if(i>=j-1 && i<=j+6){

                if(i == j)
                    id = auxiliary;
                if(i == j+1){
                    const char* x = auxiliary.c_str();
                    capacity = atoi(x);}
                if(i == j+2)
                    videoprojector = stringToBool(auxiliary);

            }

        }
        classtemp.close();
    }

};



class course: public commonInformartion{
    friend void babycheck();
    friend int checkRoom(courseLocation room);
    friend void weekShow();
    friend void sortDay(course temp[10]);
    friend void mothercheck(course temp[10]);
    friend bool checkTime(course , course);
    friend void automaticLocationDetermination(courseLocation rooms[3]);
    friend void studentcheck();
    friend void WriteInTheFile();



private:

    string name;
    string teachername;
    bool temprary;
    vector<int>studentList;


public:
//An object to store the time of each course
    date DTime;
//An object to store the location of each course
    courseLocation location;

//Read information from the file
    void inputInformation(string help){
        string auxiliary;
        string assist;
        fstream coursetemp;
        coursetemp.open("proj.txt" , ios::in);
        if(coursetemp.fail()){
            cout<<"fail\the file has a problem"<<endl;
        }

        int j;
        for(j = 1;!coursetemp.eof();j++)
        {
            getline(coursetemp,assist);
            if(assist == help)
                break;
        }
        coursetemp.close();


        coursetemp.open("proj.txt" , ios::in);

        for(int i{1};!coursetemp.eof();i++){
            getline(coursetemp,auxiliary);
            
            if(i>=j-1 && i<=j+11){

                if(i == j)
                    id = auxiliary;
                if(i == j+1)
                    name = auxiliary;
                if(i == j+2)
                    teachername = auxiliary;
                if(i == j+3)
                    videoprojector = stringToBool(auxiliary);
                if(i == j+4)
                    temprary = stringToBool(auxiliary);
                if(i == j+5){
                    const char* x = auxiliary.c_str();
                    capacity = atoi(x);
                }

                if(i == j+6){
                    const char* x = auxiliary.c_str();
                    DTime.set_HS(atoi(x));

                }
                if(i == j+7){
                    const char* x = auxiliary.c_str();
                    DTime.set_MS(atoi(x));

                }
                if(i == j+8){
                    const char* x = auxiliary.c_str();
                    DTime.set_DH(atoi(x));
                }
                if(i == j+9){
                    const char* x = auxiliary.c_str();
                    DTime.set_DM(atoi(x));
                }

                if(i == j+10){
                    string d1;
                    string d2;
                    istringstream helping(auxiliary);
                    helping>>d1;
                    helping>>d2;
                    DTime.set_Day(d1 , d2);

                }

                //Storing students' student numbers in a vector using istringstream
                if(i == j+11){
                    istringstream helping(auxiliary);
                    int x;
                    while(helping>>x)
                        studentList.push_back(x);
                    cout<<endl;
                   

                }

            }

        }
        coursetemp.close();


    }

};
//Checking the time overlap between two courses
bool checkTime(course temp , course dayOfWeek){
    if( (( (dayOfWeek.DTime.st<temp.DTime.st) && (temp.DTime.st<dayOfWeek.DTime.et) )||( (dayOfWeek.DTime.st<temp.DTime.et) && (temp.DTime.et<dayOfWeek.DTime.et) ))||(( (temp.DTime.st<dayOfWeek.DTime.st) && (dayOfWeek.DTime.st<temp.DTime.et) )||( (temp.DTime.st<dayOfWeek.DTime.et) && (dayOfWeek.DTime.et<temp.DTime.et) )) ){
        return 1;}
    else{
        return 0;}
}




//Getting the location of each course manually from the user
void specify(course temp[10] )
{

        for(int i{0}; i<10; i++)
        {
            string questionForCourse;
            string questionForClassroom;
            cout<<i+1<<" : "<<"to determine the classroom , enter the desired course : ";

            cin>>questionForCourse;
            if(questionForCourse == "AdvanceProgramming")
            {
                cout<<"enter the desired classroom for the Advance Programming course : ";
                cin>>questionForClassroom;
                (temp[0].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Math")
            {
                cout<<"enter the desired classroom for the Math course : ";
                cin>>questionForClassroom;
                (temp[1].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Physics")
            {
                cout<<"enter the desired classroom for the Phycsics course : ";
                cin>>questionForClassroom;
                (temp[2].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Workshop")
            {
                cout<<"enter the desired classroom for the Workshop course : ";
                cin>>questionForClassroom;
                (temp[3].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Differntial" ){

                cout<<"enter the desired classroom for the Differntial course : ";
                cin>>questionForClassroom;
                (temp[4].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Statistics"){

                cout<<"enter the desired classroom for the Statistics course : ";
                cin>>questionForClassroom;
                (temp[5].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "History"){

                cout<<"enter the desired classroom for the History course : ";
                cin>>questionForClassroom;
                (temp[6].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "DataStructure"){

                cout<<"enter the desired classroom for the DataStructure course : ";
                cin>>questionForClassroom;
                (temp[7].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "LogicalCircuit"){

                cout<<"enter the desired classroom for the LogicalCircuit course : ";
                cin>>questionForClassroom;
                (temp[8].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "DiscreteMath"){

                cout<<"enter the desired classroom for the DiscreteMath course : ";
                cin>>questionForClassroom;
                (temp[9].location).inputInformation(questionForClassroom);
            }
        }



}
//Array for storing courses based on days of the week
course week[7][4];

//Sort courses by days of the week
void sortDay(course temp[10])
{

//Calculate the end time of each courses
    for(int u =0; u<10 ; u++){
        temp[u].DTime.calcuteTime();
        
    }

    int j{0};int z{0};int w{0};int k{0};int y{0};int m{0};int n{0};
    for(int i =0; i<10; i++){
        if(temp[i].DTime.day1 == "saturday" || temp[i].DTime.day2 == "saturday")
        {

            week[0][j] = temp[i];
            j++;

        }

        if(temp[i].DTime.day1 == "sunday" || temp[i].DTime.day2 == "sunday")
        {

            week[1][z] = temp[i];
            z++;
        }

        if(temp[i].DTime.day1 == "monday" || temp[i].DTime.day2 == "monday")
        {

            week[2][w] = temp[i];
            w++;
        }

        if(temp[i].DTime.day1 == "tuesday" || temp[i].DTime.day2 == "tuesday")
        {

            week[3][k] = temp[i];
            k++;
        }

        if(temp[i].DTime.day1 == "wednesday" || temp[i].DTime.day2 == "wednesday")
        {

            week[4][y] = temp[i];
            y++;
        }
  
        if(temp[i].DTime.day1 == "thurday" || temp[i].DTime.day2 == "thurday")
        {

            week[5][m] = temp[i];
            m++;
        }

        if(temp[i].DTime.day1 == "friday" || temp[i].DTime.day2 == "friday")
        {

            week[6][n] = temp[i];
            n++;
        }


    }

}

//showing the weekly courses plan
void weekShow(){
    cout<<boolalpha;
    for(int i{0};i<5;i++ ){
        for(int j{0} ; j<4; j++){
           
            cout<<endl<<"course name : "<<week[i][j].name<<endl<<"teacher name : "<<week[i][j].teachername<<"\t video projector : "<<week[i][j].videoprojector<<"\ttemprary : "<<week[i][j].temprary<<"\tcourse capacity : "<<week[i][j].capacity<<"\t start and end time : "<<week[i][j].DTime.st<<','<<week[i][j].DTime.et<<"\t course days : "<<week[i][j].DTime.ret_day1()<<','<<week[i][j].DTime.ret_day2()<<endl<<"course location : "<<week[i][j].location.id<<endl;
        }
        cout<<"------------------------------------------------------------------------------------------------"<<endl<<endl;
    }

}

//Writing the weekly courses plan in the file
void WriteInTheFile(){
    fstream writing;
    writing.open("plan.txt" , ios::out);
    for(int i{0};i<5;i++ ){
        for(int j{0} ; j<4; j++){
            
            writing<<endl<<"course name : "<<week[i][j].name<<endl<<"teacher name : "<<week[i][j].teachername<<"\t video projector : "<<week[i][j].videoprojector<<"\ttemprary : "<<week[i][j].temprary<<"\tcourse capacity : "<<week[i][j].capacity<<"\t start and end time : "<<week[i][j].DTime.st<<','<<week[i][j].DTime.et<<"\t course days : "<<week[i][j].DTime.ret_day1()<<','<<week[i][j].DTime.ret_day2()<<endl<<"course location : "<<week[i][j].location.id<<endl;
        }
        writing<<"------------------------------------------------------------------------------------------------"<<endl<<endl;
    }
}


//Checking student interference
void studentcheck(){

    for(int i=0; i<7; i++){
        for(int j=0; j<4;j++){
            for(int k=j+1; k<4;k++){
                for(int z=0;z<week[i][j].studentList.size();z++){
                    for(int q=0;q<week[i][k].studentList.size();q++){
                      
                        if( (week[i][j].studentList.at(z)==week[i][k].studentList.at(q)) && checkTime(week[i][j],week[i][k]) ){
                            cout<<"student number"<<week[i][j].studentList[z]<<"is present in both "<<week[i][j].name<<" and "<<week[i][k].name<<" courses and there is a time overlap"<<endl;
                            
                        }
                    }
                }
                
            }
        }
    }
}



//Checking time overlap and teacher interference and student interference
void babycheck()
{

    for (int i = 0; i < 7; ++i)
    {
        for(int j=0 ; j < 4 ; j++)
        {
            for (int k = j+1; k < 4 ; k++)
            {

                if( (week[i][j].location.id == week[i][k].location.id) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j] , week[i][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time overlap on "<<i+1<<"of the week "<<endl;


                if( (week[i][j].teachername == week[i][k].teachername) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j], week[i][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time teacher interfrence on "<<i+1<<"of the week "<<endl;

            }
        }
    }
//Checking student interference
    studentcheck();

}



void mothercheck(course temp[10])
{

    for (int i = 0; i < 10; ++i)
    {
        if (temp[i].capacity > temp[i].location.capacity)
        {
            cout<<"The capacity of "<<temp[i].name<<" is greater than the capacity of the location"<<endl;



        }
        if ( (temp[i].videoprojector) && (!temp[i].location.videoprojector))
        {
            cout<<temp[i].name<<" needs a video projector and location have not a video projector "<<endl;

        }
        for(int j=i+1; j<10-i; j++){
            if(temp[i].id == temp[j].id){
                 cout<<"The id of "<<temp[i].name<<" is the same as "<<temp[j].name<<endl;


            }
        
        }
        
    }
    cout<<"---------------"<<endl;


//Checking time overlap and teacher interference and student interference
    babycheck();
}


//Common variable between the checkRoom and automaticLocationDetermination functions to transfer between days
int p = 0;


//Finding the index of course whose assigned location is the same as the location in the function input
int checkRoom(courseLocation room){
    int t = 10;
    for(int k=0; k<4; k++){
       if(week[p][k].location.id == room.id){
        t=k;
        break;
       }

    }
    return t;
}

//Automatic arrangement of the location of each course
void automaticLocationDetermination(courseLocation rooms[3])
{   int selectedRoom = 11;

    for ( p = 0; p <7 ; p++) //day
    {
        for (int j = 0; j <4 ; j++) //class
        {
            
            for (int z = 0; z < 3; z++) //location
            {
                //Initial check of capacity and video projector and finding a index of place for each course
                if((week[p][j].capacity < rooms[z].capacity)&&(week[p][j].videoprojector == rooms[z].videoprojector) ){
                    selectedRoom = z;
                                       
                    
                }
            }
            
        if( 0<= selectedRoom < 3){

            int index = checkRoom(rooms[selectedRoom]);

            if(index == 10){
                week[p][j].location= rooms[selectedRoom];
               
            }
            else{
                
                if( !(checkTime(week[p][j] , week[p][index])) ){
                    
                    week[p][j].location = rooms[selectedRoom];
                }

                else{
                     cout<<"program could not assign a location to the  "<<week[p][j].name <<" course "<<"Because the program considers the place of "<<week[p][j].name <<" course in class"<<rooms[selectedRoom].id<<", which has a time conflict with the "<<week[p][index].name<<" course that is held in class "<<rooms[selectedRoom].id<<".(on "<<week[p][j].DTime.ret_day1()<<" or "<<week[p][j].DTime.ret_day2()<<")"<<endl;
                }
            }
        }
        else
            cout<<"program could not assign a location to the  "<<week[p][j].name <<" course "<<endl;


        }
    }

}






int main()
{
   cout<<"run program :"<<endl;

//Definition of 10 courses
    course advanceprogramming;
    course math;
    course physics;
    course workshop;
    course differntial;
    course statistics;
    course history;
    course datastructure;
    course logicalcircuit;
    course  discretemath;

//Storing objects(courses) in an array
   
 course courses[10] = {advanceprogramming , math , physics , workshop , differntial , statistics , history , datastructure , logicalcircuit , discretemath};
//Read information from the file
    courses[0].inputInformation("AP101");
    courses[1].inputInformation("MH101");
    courses[2].inputInformation("PH101");
    courses[3].inputInformation("WH101");
    courses[4].inputInformation("DH101");
    courses[5].inputInformation("SH101");
    courses[6].inputInformation("HH101");
    courses[7].inputInformation("DSH101");
    courses[8].inputInformation("LCH101");
    courses[9].inputInformation("DMH101");


//Definition of 3 locations(classrooms)
    courseLocation a;
    courseLocation b;
    courseLocation c;

//Storing objects(locations) in an array
    courseLocation locations[3] = {a,b,c};
    
//Read information from the file
    locations[0].inputInformation("401");
    locations[1].inputInformation("402");
    locations[2].inputInformation("501");


//Choice of automatic or manual sorting of locations
    bool check;
    cout<<"you want to determine the location of each course yourself (enter 1)| the program specifies the location of each course (enter 0) "<<endl;
    cin>>check;
    if(check){
        cout<<"Courses : AdvanceProgramming , Math , Physics , Workshop , Differntial , Statistics , History , DataStructure , LogicalCircut , DiscreteMath "<<endl;
        cout<<"Locations : 401 , 402 , 501"<<endl;
        specify(courses);
        sortDay(courses);
        cout<<"________________________________________________________________________________________________________________"<<endl;
        mothercheck(courses);
        WriteInTheFile();    
    }
    
    else{
        sortDay(courses);
        automaticLocationDetermination(locations);
        cout<<"-7------------"<<endl;
        babycheck();
        WriteInTheFile();
    }




cout<<"------------------------------------------------"<<endl;

//General display of the program in the terminal environment
    weekShow();



    


    return 0;

}