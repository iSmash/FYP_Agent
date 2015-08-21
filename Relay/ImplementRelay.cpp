#include "ImplementRelay.h"
#include <iostream>
#include <fstream>
#define CommFile  "ComSetting.txt"
using namespace Relayspace;

using namespace std;

 SerialPort* ImplementRelay::communication= 0;
 ImplementRelay::ImplementRelay():Relay()
		    {

		        if(ID==0) // all share the com port, as all go trhough arduino
                {
                    ifstream ComFile("ComSetting.txt");
                    string comName;

                    if(ComFile.good())
                    {
                        ComFile>>comName;
                    }
                    comName=comName.substr(0,comName.find(";"));
                    cout<<comName;
                    ComFile.close();
                    char* comNameChar= new char[comName.length()+1];
                    strcpy(comNameChar,comName.c_str());
                    communication= new SerialPort(comNameChar);
                    char start='0';
                    communication->Write(&start,1);
                }
                char up[2] ={ID,'u'};
                char down[2] ={ID,'d'};
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
