#include <math.h>
#include "SimulationRelay.h"
using namespace Relayspace;


void SimulationRelay::findDomain()
{
    //cout<<"findDomain "<<gridLocation<<" "<<Ranges[activeRange]<<endl;
    std::vector<Coordinate> domaintemp;

    //cout<<"range "<<Ranges[activeRange]<<endl;
    for(double ang=0.0; ang<6.283; ang=ang+0.1){

    double limit=Ranges[activeRange];
       double radius=0;;
    bool up=true;
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

void SimulationRelay::setRange(int range)
{
    if(range>=0 && range<Ranges.size())
        activeRange=range;

        findDomain();

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
