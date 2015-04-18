#include <math.h>
#include "SimulationRelay.h"
using namespace Relayspace;


std::vector<Coordinate> SimulationRelay::domain()
 {
           std::vector<Coordinate> domaintemp;


           for(int i = 0; i<= Ranges[activeRange]; i++)
           {

                for(int j=0; j<=Ranges[activeRange]-i; j++)
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

          return domaintemp;

        }

bool SimulationRelay::inRange(Coordinate test)
{

     std::vector<Coordinate> temp = domain();

           for( int i =0; i< temp.size(); i++)
           {
               if(temp[i]==test)
               {
                //std::cout<<test.getRow()<<" "<<test.getColumn()<<std::endl;
                return true;

               }
            }

           return false;
}
