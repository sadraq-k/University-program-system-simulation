#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<array>
#include <cstdlib>
#include<algorithm>
#include<sstream>
using namespace std;

class course;
class courseLocation;
class date;

//void automaticLocationDetermination(courseLocation );
void mothercheck(course );







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
    // friend auto calcuteTime(date object);
    friend void sortDay(course temp[4]);
    friend bool checkTime(course temp , course dayOfWeek);
    // friend bool checkTime(course temp , courseLocation dayOfWeek);
private:
    /*int day;
    int month;
    int year;*/
    int hourStart =0;
    int minStart=0;
    int hourEnd=0;
    int minEnd=0;
    int durationMin=0;
    int durationHour=0;
    string day1;
    string day2;
public:
    double st,et;
    //bool occupied = 0;
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






// baraye mohasebe saat payan dars kelas
/*
auto calcuteTime(date object)
{

    object.minEnd = object.minStart + object.durationMin;
    if(object.minEnd > 59)
    {
        object.minEnd -=60;
        object.hourEnd =1;
    }

    object.hourEnd += object.hourStart + object.durationHour;
    if(object.hourEnd>23)
        object.minEnd -=24;

    array<int , 2> timeEnd = {object.hourEnd , object.minEnd};
    return timeEnd;
}
*/
class commonInformartion{
    friend int checkRoom(courseLocation room);
    friend void specify(course temp[10]);
    friend void babycheck();
    friend  void automaticLocationDetermination(courseLocation rooms[3]);
    friend void weekShow();
protected:
    string id=" ";
    int capacity = 45;
    bool videoprojector;

public:
    virtual void inputInformation(string help) = 0;
    
};



//class classroom : etalaat kelas
class courseLocation : public commonInformartion{
    friend void mothercheck(course temp[10]);
    friend void automaticLocationDetermination(courseLocation rooms[3]);
    // friend void check();
    // friend void inputClassroom(classroom& temp ,string help);
//private:

    //bool occupied = 0;
    /*string idClass;
    int capacityClass;
    bool videoprojector;*/
    //date dateClass;
    //string idCourse;


public:


    void show(){
        cout<<boolalpha;
        cout<<id<<endl<<capacity<<endl<<videoprojector<<endl;
    }

    void inputInformation(string help){
        /*char auxiliary[80];
        char assist[80];*/
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


//template<typename N , typename B>
//class course: etelaat dars
class course: public commonInformartion{
    friend void babycheck();
   friend int checkRoom(courseLocation room);
    friend void weekShow();
    friend void sortDay(course temp[10]);
    friend void mothercheck(course temp[10]);
    friend bool checkTime(course , course);
    friend void automaticLocationDetermination(courseLocation rooms[3]);

    //friend void inputCourse(course&temp , string help);
private:
    //string idCourse;
    string name;
    string teachername;
    //bool videoprojector[2];
    bool temprary;
    //int capacityCourse[2];

    vector<int>studentList;
    //int* studentList{new int[capacity]};

public:
    date DTime;
    courseLocation location;
    //date DTime;
    void show(){
        cout<<boolalpha;
        cout<<"idcourse:"<<id<<endl<<"name:"<<name<<endl<<"teacher name:"<<teachername<<endl<<"videoprojector:"<<videoprojector<<endl<<"temperary:"<<temprary<<endl<<"capacity course:"<<capacity<<endl;
        cout<<"student list : ";
        /*for(int i=0;i<capacity;i++){
            cout<<studentList[i]<<" ";
        }*/

    }

    void inputInformation(string help){

        /*char auxiliary[80];
        char assist[80];*/
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
                    //courseTime.set_Day(auxiliary);
                    string d1;
                    string d2;
                    istringstream helping(auxiliary);
                    helping>>d1;
                    //cout<<auxiliary<<endl;
                    //coursetemp.ignore(1,' ');
                    helping>>d2;
                    DTime.set_Day(d1 , d2);
                    //cout<<courseTime.ret_day1()<<endl;
                    //cout<<courseTime.ret_day2()<<endl;

                   // cout<<d1<<endl<<d2<<endl;
                }


                if(i == j+11){
                    //cout<<auxiliary<<endl;
                    istringstream helping(auxiliary);
                    //cout<<auxiliary<<endl;
                    /*or(int k=0; k<capacity ;k++){
                        studentList.push_back(helping);
                        //cout<<studentList[k]<<endl;
                        //coursetemp.ignore(1,' ');
                       // cout<<studentList[k]<<"\t";
                    }*/
                    int x;
                    while(helping>>x)
                        studentList.push_back(x);
                    cout<<endl;
                    //cout<<auxiliary<<endl;

                }

            }

        }
        coursetemp.close();


    }

    /*void operator=(courseLocation temp){
        temp.DTime.et = DTime.et;
        temp.DTime.st = DTime.st;
        
    }*/

};


/*template <typename T>
T stringToInteger(string str){
    T result;
    istringstream convert(str);
    if ( !(convert >> result) )
        throw "Can not convert";

    return result;}*/
//template<typename F , typename G , typename L>    
/*course min(course a , course b){

    if(a.DTime.st<b.DTime.st)
        return a;
    else
        return b;
}
//template<typename M , typename W , typename K>
course max(course a , course b){

    if(a.DTime.st>b.DTime.st)
        return a;
    else
        return b;
}
//template<typename Z , typename H >
 bool checkTime(course temp , course dayOfWeek){
        course A = min(temp , dayOfWeek);
        course B = max(temp , dayOfWeek);
        if (!(A.DTime.st < B.DTime.st && A.DTime.et < B.DTime.et && A.DTime.et < B.DTime.st))
            {
                
                return 1;
            }
        else
            return 0;    

    }**/
bool checkTime(course temp , course dayOfWeek){
    if( (( (dayOfWeek.DTime.st<temp.DTime.st) && (temp.DTime.st<dayOfWeek.DTime.et) )||( (dayOfWeek.DTime.st<temp.DTime.et) && (temp.DTime.et<dayOfWeek.DTime.et) ))||(( (temp.DTime.st<dayOfWeek.DTime.st) && (dayOfWeek.DTime.st<temp.DTime.et) )||( (temp.DTime.st<dayOfWeek.DTime.et) && (dayOfWeek.DTime.et<temp.DTime.et) )) ){
        return 1;}
    else{
        return 0;}
}




//hanooz kamel nashode vali baraye moshakhas kardan mahal ya hamoon kelase
void specify(course temp[10] /*,courseLocation rooms[3]*/)
{

    /* help[0].inputClassroom("401");
     help[1].inputClassroom("402");
     help[2].inputClassroom("501");*/

    /* course AdvanceProgramming;
     course Math;
     course physics;
     course workshop*/
    //bool check;
    //cout<<"you want to determine the location of each course yourself (enter 1)| the program specifies the location of each course (enter 0) "<<endl;
    //cin>>check;
   // if(check)
    //{
        for(int i{0}; i<10; i++)
        {
            string questionForCourse;
            string questionForClassroom;
            cout<<i+1<<" : "<<"to determine the classroom , enter the desired course : ";
            //getline(cin , questionForCourse);
            cin>>questionForCourse;
            if(questionForCourse == "AdvanceProgramming")
            {
                //AdvanceProgramming.inputCourse("AP101");
                //temp[0].inputInformation("AP101");
                cout<<"enter the desired classroom for the Advance Programming course : ";
                //getline(cin , questionForClassroom);
                cin>>questionForClassroom;
                //(AdvanceProgramming.location).inputClassroom(questionForClassroom);
                (temp[0].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Math")
            {
                // Math.inputCourse("MH101");
                //temp[1].inputInformation("MH101");
                cout<<"enter the desired classroom for the Math course : ";
                //getline(cin , questionForClassroom);
                cin>>questionForClassroom;
                //(Math.location).inputClassroom(questionForClassroom);
                (temp[1].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Physics")
            {
                //Physics.inputCourse("PH101");
                //temp[2].inputInformation("PH101");
                cout<<"enter the desired classroom for the Phycsics course : ";
                //getline(cin , questionForClassroom);
                cin>>questionForClassroom;
                //(Physics.location).inputClassroom(questionForClassroom);
                (temp[2].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Workshop")
            {
                //workshop.inputCourse("WH101");
                //temp[3].inputInformation("WH101");
                cout<<"enter the desired classroom for the Workshop course : ";
                //getline(cin , questionForClassroom);
                cin>>questionForClassroom;
                //(workshop.location).inputClassroom(questionForClassroom);
                (temp[3].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Differntial" ){
                // temp[4].inputInformation("DH101");
                cout<<"enter the desired classroom for the Differntial course : ";
                cin>>questionForClassroom;
                (temp[4].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "Statistics"){
                // temp[5].inputInformation("SH101");
                cout<<"enter the desired classroom for the Statistics course : ";
                cin>>questionForClassroom;
                (temp[5].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "History"){
                //temp[6].inputInformation("HH101");
                cout<<"enter the desired classroom for the History course : ";
                cin>>questionForClassroom;
                (temp[6].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "DataStructure"){
                // temp[7].inputInformation("DSH101");
                cout<<"enter the desired classroom for the DataStructure course : ";
                cin>>questionForClassroom;
                (temp[7].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "LogicalCircuit"){
                //temp[8].inputInformation("LCH101");
                cout<<"enter the desired classroom for the LogicalCircuit course : ";
                cin>>questionForClassroom;
                (temp[8].location).inputInformation(questionForClassroom);
            }

            if(questionForCourse == "DiscreteMath"){
                //temp[9].inputInformation("DMH101");
                cout<<"enter the desired classroom for the DiscreteMath course : ";
                cin>>questionForClassroom;
                (temp[9].location).inputInformation(questionForClassroom);
            }
        }
        //mothercheck(temp);
    //} //else
        //automaticLocationDetermination(rooms[3]);


}

course week[7][4];

void sortDay(course temp[10])
{
    //cout<<"aaaa"<<endl;
    //cout<<temp[7].name<<endl<<temp[7].DTime.day2<<endl;
    for(int u =0; u<10 ; u++){
        temp[u].DTime.calcuteTime();
        
    }
    /*course saturday[4];
    course sunday[4];
    course monday[4];
    course tuesday[4];
    course wednesday[4];
    course thurday[4];
    course friday[4];*/
    int j{0};int z{0};int w{0};int k{0};int y{0};int m{0};int n{0};
    for(int i =0; i<10; i++){
        if(temp[i].DTime.day1 == "saturday" || temp[i].DTime.day2 == "saturday")
        {
            //  for(int j=0; j<4; j++)
            week[0][j] = temp[i];
            j++;
            //cout<<temp[i].name<<endl;
        }
        //week[0][4]=saturday[4];
        if(temp[i].DTime.day1 == "sunday" || temp[i].DTime.day2 == "sunday")
        {
            //for(int j=0; j<4; j++)
            week[1][z] = temp[i];
            z++;
        }
        //week[1][4]= sunday[4];
        if(temp[i].DTime.day1 == "monday" || temp[i].DTime.day2 == "monday")
        {
            // for(int j=0; j<4; j++)
            week[2][w] = temp[i];
            w++;
        }
        //week[2][4]=monday[4];
        if(temp[i].DTime.day1 == "tuesday" || temp[i].DTime.day2 == "tuesday")
        {
            //for(int j=0; j<4; j++)
            week[3][k] = temp[i];
            k++;
        }
        //week[3][4]=tuesday[4];
        if(temp[i].DTime.day1 == "wednesday" || temp[i].DTime.day2 == "wednesday")
        {
            // for(int j=0; j<4; j++)
            week[4][y] = temp[i];
            y++;
        }
        //week[4][4]=wednesday[4];
        if(temp[i].DTime.day1 == "thurday" || temp[i].DTime.day2 == "thurday")
        {
            // for(int j=0; j<4; j++)
            week[5][m] = temp[i];
            m++;
        }
        //week[5][4]=thurday[4];
        if(temp[i].DTime.day1 == "friday" || temp[i].DTime.day2 == "friday")
        {
            // for(int j=0; j<4; j++)
            week[6][n] = temp[i];
            n++;
        }
        //week[6][4]=friday[4];

    }
    /*for(int y=0; y<7; y++){
        for(int l=0; l<4; l++){
            week[y][l].DTime.calcuteTime();
        }
    }*/

}
void weekShow(){
    cout<<boolalpha;
    for(int i{0};i<5;i++ ){
        for(int j{0} ; j<4; j++){
            //week[i][j].DTime.calcuteTime();
            cout<<endl<<week[i][j].name<<endl<<week[i][j].teachername<<'\t'<<week[i][j].videoprojector<<'\t'<<week[i][j].temprary<<'\t'<<week[i][j].capacity<<'\t'<<week[i][j].DTime.st<<','<<week[i][j].DTime.et<<'\t'<<week[i][j].DTime.ret_day1()<<','<<week[i][j].DTime.ret_day2()<<endl<<week[i][j].location.id<<endl;
        }
        cout<<"------------------------------------------------------------------------------------------------"<<endl<<endl;
    }
    /*bool a;
    cout<<"If there is a class on Thursday and Friday and you want the information of those classes to be displayed, enter the number 1."<<endl;
    cin>>a;
    if(a){
        for(int i{5}; i<7; i++){
            for(int j{0}; j<4; j++){
                cout<<endl<<week[i][j].name<<endl<<week[i][j].teachername<<'\t'<<week[i][j].videoprojector<<'\t'<<week[i][j].temprary<<'\t'<<week[i][j].capacity<<'\t'<<week[i][j].DTime.st<<','<<week[i][j].DTime.et<<'\t'<<week[i][j].DTime.ret_day1()<<','<<week[i][j].DTime.ret_day2()<<endl<<week[i][j].location.id<<endl;
            }
            cout<<"------------------------------------------------------------------------------------------------"<<endl<<endl;
        }
    }*/
}


//template <typename T>


/*course stackForTime[4];
course stackForTeacher[4];
course stackForIdCourse[4];
course stackForStudent[40];*/
void babycheck()
{
    //int j{0};
    for (int i = 0; i < 7; ++i)
    {
        for(int j=0 ; j < 4 ; j++)
        {
            for (int k = j+1; k < 4 ; k++)
            {

                if( (week[i][j].location.id == week[i][k].location.id) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j] , week[i][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time overlap on "<<i+1<<"of the week "<<endl;


                if( (week[i][j].teachername == week[j][k].teachername) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j], week[i][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time teacher interfrence on "<<i+1<<"of the week "<<endl;


                /*if((week[i][j].id == week[i][k].id) && (week[i][j].name != week[j][k].name)){
                    cout<<"The id of "<<week[i][j].name<<" is the same as "<<week[i][k].name<<endl;

                }*/
                /*for(int z{0} ; z<(week[i][j].capacity); z++){

                    for(int q{0};q<(week[i][k].capacity);q++){

                        if((week[i][j].studentList[z] == week[i][k].studentList[q]) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j] , week[i][k])))
                            cout<<"student number"<<week[i][j].studentList[z]<<"is present in both "<<week[i][j].name<<" and "<<week[i][k].name<<" courses and there is a time overlap"<<endl;

                    }
                }*/
                

            }
        }
    }

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
        
       // int j{0};

        /*for(int j=0 ; j < 4 ; j++)
        {
            for (int k = j+1; k < 4 ; k++)
            {

                if( (week[i][j].location.id == week[i][k].location.id) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j], week[j][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time overlap on "<<i<<"of the week "<<endl;


                if( (week[i][j].teachername == week[j][k].teachername) && (week[i][j].name != week[i][k].name) && (checkTime(week[i][j], week[j][k])) )
                    cout<<week[i][j].name<<" and "<<week[i][k].name<<" have time teacher interfrence on "<<i<<"of the week "<<endl;


                if((week[i][j].id == week[i][k].id) && (temp[i].name != week[j][k].name)){
                    cout<<"The id of "<<week[i][j].name<<" is the same as "<<week[i][k].name<<endl;

                }
                //check student
                for(int z{0} ; z<(week[i][j].capacity); z++){

                    for(int q{0};q<(week[i][k].capacity);q++){

                        if((week[i][j].studentList[z] == week[i][k].studentList[q]) && (week[i][j].name != week[j][k].name) && (checkTime(week[i][j] , week[j][k])))
                            cout<<"student number"<<week[i][j].studentList[z]<<"is present in both "<<week[i][j].name<<" and "<<week[i][k].name<<" courses and there is a time overlap"<<endl;

                    }
                }



            }
        }*/
    }
    cout<<"---------------"<<endl;
    babycheck();
}
/*( !( (temp[i].courseTime.st>saturday[j].courseTime.st)&&(temp[i].courseTime.et>saturday[j].courseTime.et)&&(temp[i].courseTime.st>saturday[j].courseTime.et) ) ||
!( (temp[i].courseTime.st < saturday[j].courseTime.st)&&(temp[i].courseTime.et < saturday[j].courseTime.et)&&(temp[i].courseTime.et < saturday[j].courseTime.st) )  )*/

/*auto maximum(course temp , courseLocation help ){
    if (temp.DTime.st<help.DTime.st)
        return help;
    else
        return temp;
}

auto minimum(course temp , courseLocation help){
    if(temp.DTime.st<help.DTime.st)
        return temp;
    else
        return help;
}*/


/*
bool chekingTime(course temp , courseLocation help)
{
    if( ((help.DTime.st<temp.DTime.st<help.DTime.et)||(help.DTime.st<temp.DTime.et<help.DTime.et))
    ||((temp.DTime.st<help.DTime.st<temp.DTime.et)||(temp.DTime.st<help.DTime.et<temp.DTime.et)) )

        return 1;
    else
        return 0;

        
}*/


int p = 0;
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


void automaticLocationDetermination(courseLocation rooms[3])
{   int selectedRoom = 11;
//cout<<week[0][0].id<<endl;
    for ( p = 0; p <7 ; p++) //day
    {
        for (int j = 0; j <4 ; j++) //class
        {
            
            for (int z = 0; z < 3; z++) //location
            {
                
                if((week[p][j].capacity < rooms[z].capacity)&&(week[p][j].videoprojector == rooms[z].videoprojector) ){
                    selectedRoom = z;
                    //cout<<"a = "<<a<<" "<<week[p][j].name<<" : " <<rooms[a].id<<endl;                   
                     //break;
                }
            }
            //int index;
        if( 0<= selectedRoom < 3){

            int index = checkRoom(rooms[selectedRoom]);

            if(index == 10){
                week[p][j].location= rooms[selectedRoom];
                //cout<<"in"<<endl;
            }
            else{
                //cout<<y<<endl;
                if( !(checkTime(week[p][j] , week[p][index])) ){
                    //cout<<"in "<<p<<" "<<j<<" "<<y<<endl;
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
    /*
    for(int h=0; h<7; h++){
    for(int x=0; x<4; x++){
    cout<<week[h][x].location.id<<week[h][x].name<<endl;}
   cout<<"|||||||||||||||||||||||||||"<<endl;
    }*/
   // babycheck();*/
}






int main()
{
    cout<<"run program :"<<endl;

    /* date temp(8,2,1401,8,30,1,30);
     array<int , 2>myarr{calcuteTime(temp)};
     for(int i=0 ; i<2; i++){
         cout<<myarr[i]<<":";


     }
     cout<<endl;
     */
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
    course courses[10] = {advanceprogramming , math , physics , workshop , differntial , statistics , history , datastructure , logicalcircuit , discretemath};
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


    //specify(courses);

    courseLocation a;
    courseLocation b;
    courseLocation c;
    courseLocation locations[3] = {a,b,c};
    locations[0].inputInformation("401");
    locations[1].inputInformation("402");
    locations[2].inputInformation("501");

    //specify(courses , locations);
/*
    course math;
    math.courseTime.set_DH(1);
    math.courseTime.set_DM(45);
    math.courseTime.set_HS(16);
    math.courseTime.set_MS(00);
    array<int , 2>myarr = calcuteTime(math.courseTime);
    for(int i =0; i<2; i++)
        cout<<myarr[i]<<'\t';*/
    //specify(courses);

    //courses[5].inputInformation("HH101");
    //weekShow();

    //sortDay(courses);
    bool check;
    cout<<"you want to determine the location of each course yourself (enter 1)| the program specifies the location of each course (enter 0) "<<endl;
    cin>>check;
    if(check){
        specify(courses);
        sortDay(courses);
        cout<<"________________________________________________________________________________________________________________"<<endl;
        mothercheck(courses);    
    }
    
    else{
        sortDay(courses);
        automaticLocationDetermination(locations);
        cout<<"-------------"<<endl;
        babycheck();
    }



//cout<<courses[7].DTime.ret_day1()<<endl;
cout<<"------------------------------------------------"<<endl;

    //specify(courses /*,locations*/
//sortDay(courses);
    //mothercheck(courses);
    weekShow();
/*advanceprogramming.DTime.calcuteTime();
history.DTime.calcuteTime();
cout<<checkTime(advanceprogramming , history)<<endl;
cout<<history.DTime.st<<','<<history.DTime.et <<endl<<advanceprogramming.DTime.st<<','<<advanceprogramming.DTime.et<<endl;
*/

/*sortDay(courses);

cout<<checkTime(courses[4],courses[7])<<endl;
cout<<courses[1].DTime.st<<endl;
cout<<checkTime(courses[1],courses[7])<<endl;
//weekshow();
weekShow();*/
    cout<<"------------------------------------------------------------------------\ntesting for show :\n";

    //sortDay(courses);
    cout<<checkTime(courses[1] , courses[9]);
    cout<<courses[1].DTime.st<<endl<<courses[9].DTime.st<<endl;
    course AdvanceProgramming;
    courseLocation a101;
    //inputCourse(AdvanceProgramming , "MH101");
    AdvanceProgramming.inputInformation("HH101");
    AdvanceProgramming.show();
    cout<<endl<<"------------TESTING SATURDAY-------------------------"<<endl;

    //courses[5].inputInformation("HH101");
    sortDay(courses);
    for (int i = 0; i<4; i++)
    {

        week[0][i].show();
        cout<<endl;
    }



    return 0;

}