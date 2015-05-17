#include <math.h>
#include "SimulationRelay.h"
using namespace Relayspace;

int SimulationRelay::activeRange=0;
std::vector<int> SimulationRelay::Ranges= std::vector<int>(0);

void SimulationRelay::findDomain()
{
    //cout<<"findDomain "<<gridLocation<<" "<<Ranges[activeRange]<<endl;
    std::vector<Coordinate> domaintemp;


    //cout<<"limit="<<limit<<endl;
    //cout<<"range "<<Ranges[activeRange]<<endl;
    for(double ang=0.0; ang<6.283; ang=ang+0.001){

 double limit=getRange();
       double radius=0;;
    while(sqrt(pow(ceil(radius*sin(ang)),2.0)+pow(ceil(radius*cos(ang)),2.0))<limit)
    {
        //cout<<x*sin(ang)<<" "<<y*cos(ang)<<" "<<sqrt(pow(x*sin(ang),2.0)+pow(y*cos(ang),2.0))<<endl;
        try
        {

           Coordinate temp= Coordinate(   gridLocation.getRow()+ceil(radius*sin(ang)), gridLocation.getColumn()+ceil(radius*cos(ang))  ) ;
            if((*trueWorld)[temp].hasContent(ContentType::Wall))
                {
                limit--;
                }
            bool newCoord=true;
            for(int i=0; i<domaintemp.size(); i++)
            {
                if(domaintemp[i]==temp)
                {
                    newCoord=false;
                    break;
                }
            }
            if(newCoord)
                domaintemp.push_back(  temp  );
        }
        catch(std::out_of_range e) {}
    radius++;
    }
    }

    domain= domaintemp;

}

 void SimulationRelay::incRange()
{
    activeRange++;

    if (activeRange>=Ranges.size())
        throw string("out of range options");


}

 void SimulationRelay::decRange()
{
    activeRange--;
    if(activeRange<0)
         throw string("below 0 range option");



}


bool SimulationRelay::inRange(Coordinate test)
{
//std::cout<<test.getRow()<<" "<<test.getColumn()<<std::endl;

           for( int i =0; i< domain.size(); i++)
           {
               if(domain[i]==test)
               {

                return true;

               }
            }
//std::cout<<"out of range"<<std::endl;
           return false;
}
