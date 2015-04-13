#include <math.h>
#include "SimulationRelay.h"

std::vector<Coordinate> Relay::domain()
 {
           std::vector<Coordinate> domaintemp;
          	

           int halfRange=ceil((double)range/2.0);
      

           for(int i = 0; i<= halfRange; i++)
           {
                for(int j=0; j<=halfRange-i; j++)
                {
                    try{

                        Coordinate temp= Coordinate(   position.getRow()-i, position.getColumn()-j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
                    try{
                         Coordinate t= Coordinate(   position.getRow()-i, position.getColumn()+j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
                    try{
                     Coordinate t= Coordinate(   position.getRow()+i, position.getColumn()-j  ) ;
                        domaintemp.push_back( temp  );
                        }
                    catch(std::out_of_range e){}
                     try{
                      Coordinate t= Coordinate(   position.getRow()+i, position.getColumn()+j  ) ;
                        domaintemp.push_back(  temp  );
                        }
                    catch(std::out_of_range e){}
               }

           }
          return domaintemp;

        }
