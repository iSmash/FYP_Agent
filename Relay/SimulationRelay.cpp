#include <math.h>
#include "SimulationRelay.h"
using namespace Relayspace;


void SimulationRelay::findDomain()
 {
         //cout<<"findDomain "<<gridLocation<<" "<<Ranges[activeRange]<<endl;
	   std::vector<Coordinate> domaintemp;

           for(int i = 0; i< Ranges[activeRange]; i++)
           {

                 for(int j=0; j<sqrt(Ranges[activeRange]*Ranges[activeRange]-i*i); j++)
                {
                    try{

                        Coordinate temp= Coordinate(   gridLocation.getRow()-i, gridLocation.getColumn()-j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
                    try{
                         Coordinate temp= Coordinate(   gridLocation.getRow()-i, gridLocation.getColumn()+j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
                    try{
                     Coordinate temp= Coordinate(   gridLocation.getRow()+i, gridLocation.getColumn()-j  ) ;
                        domaintemp.push_back( temp  );
                        }
                    catch(std::out_of_range e){}
                     try{
                      Coordinate temp= Coordinate(   gridLocation.getRow()+i, gridLocation.getColumn()+j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
               }

           }

          domain= domaintemp;

        }

void SimulationRelay::setRange(int range)
{
    if(range>=0 && range<Ranges.size())
        activeRange=range;
    if(!(gridLocation == Coordinate(0,0))) // no !- operator, so just use this
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
