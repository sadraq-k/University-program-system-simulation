//
// Created by User on 28/04/2023.
//

#include "numberclass.h"
#include "toolsproject.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class classroom{
    friend void inputClassroom(classroom& temp ,string help);
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

};

void inputClassroom(classroom& temp ,string help)
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
                temp.idClass = auxiliary;
            if(i == j+1)
                temp.capacityClass = atoi(auxiliary);
            if(i == j+2)
                temp.videoprojector = stringToBool(auxiliary);


           /* if(i == j+5)
            {
                const char* x = auxiliary;
                temp.capacityCourse = atoi(x);
            }*/


        }

    }
    classtemp.close();
}

int main()
{
    classroom c1;

    inputClassroom(c1,"203");

    c1.show();
}

