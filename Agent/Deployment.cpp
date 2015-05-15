#include "Deployment.h"
#include <cmath>
#include "../Grid/SubGrid.h"
#include "VirtualRelay_Vieira.h"
#include "VirtualRelay_IMAIZUMI.h"
using namespace DeploymentSpace;
using namespace std;



vector<Coordinate> Deployment::MidWayPlacement(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{
    vector<Coordinate> relayPositions;
    relayPositions.push_back(Base);
    relayPositions.push_back(Client);
    int WallSignal_Relation = 3;
    while(relayCount+2>relayPositions.size())
    {

        vector<Coordinate> templist= relayPositions;
        for(int i = 1; i< relayPositions.size(); i++)
        {
            //cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
            int rowMidPoint    = (relayPositions[i-1].getRow()+relayPositions[i].getRow())/2;
            int columnMidPoint = (relayPositions[i-1].getColumn()+relayPositions[i].getColumn())/2;
            cout<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
            /** adujust position based on walls bettewen points */
            SubGrid subgrid(knownWorld,relayPositions[i-1], relayPositions[i]);

            int walls_left_top, walls_right_bot;
            subgrid.Wall_count(Coordinate(rowMidPoint,columnMidPoint), walls_left_top, walls_right_bot);

            //cout<<"Wall changes: -"<<walls_left_top<<"+"<<walls_right_bot<<endl;
            rowMidPoint=rowMidPoint
                        -walls_left_top/WallSignal_Relation
                        +walls_right_bot/WallSignal_Relation;

            columnMidPoint=columnMidPoint
                           -walls_left_top/WallSignal_Relation
                           +walls_right_bot/WallSignal_Relation;
            //cout<<"gives "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
            /**  */
            //if adjustment made it not in between any more, put it on the boarder.


            //make sure not on top of wall
            int moveRange = 1;
            while(  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Wall)
                  ||knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Jormungandr_Wall)
                  ||  knownWorld[Coordinate(rowMidPoint,columnMidPoint)].hasContent(ContentType::Unknown)
                 )

            {
                for(int i=-(moveRange); i<=moveRange; i++)
                {
                    for(int j=-(moveRange); j<=moveRange; j++)
                    {
try{
                        if(  !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Wall))  &&
                           !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Jormungandr_Wall))  &&
                                !(knownWorld[Coordinate(rowMidPoint+i,columnMidPoint+j)].hasContent(ContentType::Unknown))
                          )
                        {


                            rowMidPoint=rowMidPoint+i;
                            columnMidPoint=columnMidPoint+j;
                            i=moveRange+1;//break outer for-loop too
                            break;

                        }
                        }
                            catch (std::out_of_range){}
                    }
                }
                moveRange++;
            }
            //cout<<"on wall fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
            templist.insert(templist.begin()+i, Coordinate(rowMidPoint, columnMidPoint));
            //cout<<Coordinate(rowMidPoint, columnMidPoint)<<" just added";

            if(rowMidPoint<subgrid.Get_top())
                rowMidPoint=subgrid.Get_top()+1;
            if(rowMidPoint>subgrid.Get_bot())
                rowMidPoint=subgrid.Get_bot()-1;
            if(columnMidPoint<subgrid.Get_left())
                columnMidPoint=subgrid.Get_left()+1;
            if(columnMidPoint>subgrid.Get_right())
                columnMidPoint=subgrid.Get_right()-1;

            //cout<<"out of bounds fix "<<Coordinate(rowMidPoint,columnMidPoint)<<endl;
        }
        cout<<endl;
        relayPositions= templist;
    }

    relayPositions.pop_back();
    relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list

    return relayPositions;

}


vector<Coordinate> Deployment::MidWayPlacementPotentialState(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld)
{
    int Wall_signal_effect=1; //how much a wall effects the possition of a relay.
    vector<Coordinate> relayPositions;
    relayPositions.push_back(Base);
    relayPositions.push_back(Client);

    while(relayCount+2>relayPositions.size())
    {

        vector<Coordinate> templist= relayPositions;
        for(int i = 1; i< relayPositions.size(); i++)
        {
            //cout<<"from "<<relayPositions[i-1] <<" and "<< relayPositions[i]<<endl;
            SubGrid subgrid(knownWorld, relayPositions[i-1], relayPositions[i]);

            Coordinate bestCord;
            double bestScore=99999;
            for(int x=subgrid.Get_left(); x<=subgrid.Get_right(); x++)
            {
                for (int y=subgrid.Get_top(); y<=subgrid.Get_bot(); y++)
                {
                    Coordinate current_examin =Coordinate(y,x);
                    int walls_left_top, walls_right_bot;
                    //look thorugh all cells bweteen points for best placemtnet
                    if(!knownWorld[current_examin].hasContent(ContentType::Wall)&&!knownWorld[current_examin].hasContent(ContentType::Unknown))
                    {
                        subgrid.Wall_count(current_examin,walls_left_top, walls_right_bot );
                        double scoreCOL=  ( (x-subgrid.Get_left())+walls_left_top*Wall_signal_effect ) - ( (subgrid.Get_right()-x)+walls_right_bot*Wall_signal_effect );
                        double scoreROW= ( (y-subgrid.Get_top())+walls_left_top*Wall_signal_effect ) - ( (subgrid.Get_bot()-y)+walls_right_bot*Wall_signal_effect );
                        double score= sqrt( pow(scoreROW,2.0) + pow(scoreCOL,2.0));
                        //cout<<score<<" "<<Coordinate(y,x)<<endl;
                        if(score<bestScore)
                        {
                            bestScore=score;
                            bestCord=Coordinate(y,x);
                        }
                    }
                }
            }



            //cout<<bestCord<<endl;
            templist.insert(templist.begin()+i, bestCord);
        }
        cout<<endl;
        relayPositions= templist;
    }

    relayPositions.pop_back();
    relayPositions.erase(relayPositions.begin()); //remove the base and clinet from the list
    return relayPositions;
}


/**not done yet*/
vector<Coordinate> Deployment::VirtualForce(int relayCount,Coordinate Base, Coordinate Client, Grid& knownWorld, int type)
{
    vector<VirtualRelay*> Relays;

    VirtualRelay* Base_VF;
    VirtualRelay* Client_VF; //these are define out of the vecoor, as they will not be movoing

    if( type==1)
    {
        Base_VF= new VirtualRelay_Vieira(Base);
        Client_VF= new VirtualRelay_Vieira(Client); //these are define out of the vecoor, as they will not be movoing
    }
    else
    {
        Base_VF= new VirtualRelay_IMAIZUMI(Base);
        Client_VF= new VirtualRelay_IMAIZUMI(Client); //these are define out of the vecoor, as they will not be movoing
    }

    for(int relay_index =0; relay_index< relayCount; relay_index++) //create new relays on top of the base
    {
        if( type==1)
            Relays.push_back(new VirtualRelay_Vieira(Base)); //not, base, relay on top of base at start
        else
            Relays.push_back(new VirtualRelay_IMAIZUMI(Base));
    }

    for(int relay_index =0; relay_index< relayCount; relay_index++)
    {
        Relays[relay_index]->addNeighbour(Base_VF);
        Relays[relay_index]->addNeighbour(Client_VF);
        for(int second_relay_index =0; second_relay_index< relayCount; second_relay_index++)
        {
            if(relay_index!=second_relay_index)
            {
                Relays[relay_index]->addNeighbour(Relays[second_relay_index]);
            }
        }
    }

    int testlooper=0;
    while(testlooper<10)
    {
        testlooper++;
        for(int relay_index =0; relay_index< relayCount; relay_index++)
        {
            Relays[relay_index]->findForces(knownWorld);
        }
        for(int relay_index =0; relay_index< relayCount; relay_index++)
        {
            Relays[relay_index]->Move();
        }
    }

    //done
    vector<Coordinate> toReturn;
    for(int i =0; i< relayCount; i++)
    {
        toReturn.push_back(Relays[i]->getLocation());
    }

    for(int relay_index=0; relay_index<Relays.size(); relay_index)
    {
        delete Relays[relay_index];
    }
    delete Base_VF;
    delete Client_VF;
    return toReturn;
}


vector<Coordinate> Deployment::positionRelays(int method, int relayCount, Coordinate Base, Coordinate Client, Grid& knownWorld)
{
    //cout<<"start finding positons"<<endl;

    switch (method)
    {
    case 2:
        return MidWayPlacement(relayCount, Base,  Client, knownWorld);
    case 3:
        return MidWayPlacementPotentialState(relayCount, Base,  Client, knownWorld);
    case 4:
        return VirtualForce(relayCount, Base,  Client, knownWorld,1);
    case 5:
        return VirtualForce(relayCount, Base,  Client, knownWorld,2);
    default:
        vector<Coordinate> fail; //return this if method 0, 1 or error and method is not defined
        return fail;
    }



}
