//
// Created by User on 28/04/2023.
//

#ifndef LOTFI_PROJECT_CLASSROOM_H
#define LOTFI_PROJECT_CLASSROOM_H
#include "toolsproject.h"
#include <iostream>
#include <string>
#include <fstream>

//#include "functions.h"


class classroom{ friend void check();
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
void check ()
{
    int number;
    cin>>number;

    string a;
    a= to_string(number);

    classroom c1;

    inputClassroom(c1,a);

    c1.show();

    if (c1.videoprojector == 1)
        cout<<"have videoprojector";


}


#endif //LOTFI_PROJECT_CLASSROOM_H
