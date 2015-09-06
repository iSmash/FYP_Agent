#include "ImplementRelay.h"
#include <iostream>
#include "../FileRead.h"
#define CommFile  "ComSetting.txt"
#include <sstream>
using namespace Relayspace;

using namespace std;

 SerialPort* ImplementRelay::communication= 0;
 ImplementRelay::ImplementRelay():Relay()
{

    if(ID==0) // all share the com port, as all go trhough arduino
    {
        char comNameChar[5];
        readfileLifter(comNameChar);
        communication= new SerialPort(comNameChar, 9600);
        Sleep(100);
        char start[]={'1','d'};
        communication->Write(start,2);
    }

ostringstream temp;
temp<<ID;
    char up[2] ={0,'u'};
    char down[2] ={0,'d'};
up[0]=*temp.str().c_str();
down[0]=*temp.str().c_str();

    Sleep(500);
    communication->Write(up,2);
}

bool ImplementRelay::inRange(Coordinate test)
{

    std::cout<<"no in Range"<<std::endl;
    return false;
}

void ImplementRelay::place(Coordinate newPos)
{
    communication->Write(down,2);
    Sleep(1000);
    gridLocation= newPos;
}


 void ImplementRelay::pickUp()
 {
        communication->Write(up,2);
        Sleep(1000);
        gridLocation=Coordinate(0,0);
 }
