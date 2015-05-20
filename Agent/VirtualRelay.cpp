#include "VirtualRelay.h"
#include <cmath>
#include "../Grid/SubGrid.h"

static const double WL = 3 ;
static const double d0=1;
static const double path_loss_exp =2.5; //between 1.8 and 5
double VirtualRelay::mass=0;
 double VirtualRelay::viscous_friction=0;
static const double  time_step =1; //number of time step in  sec





void VirtualRelay::findForces(Grid& knownWorld)
{
    Force_j=0;
    Force_i=0;


    for(int neighbour_index=0; neighbour_index<Neighbours.size(); neighbour_index++)
    {
        double Force_temp;
        VirtualRelay* interactor = Neighbours[neighbour_index];

        double d_j=interactor->getLocation().getRow()-Location.getRow();
        double d_i=interactor->getLocation().getColumn()-Location.getColumn();
        double d_ij = sqrt(pow(d_i,2.0)+pow(d_j,2.0));

        SubGrid subgrid(knownWorld, Location, interactor->getLocation());

        int walls_left_top, walls_right_bot;
        subgrid.Wall_count(Location,walls_left_top, walls_right_bot );

        //cout<<"Walls"<<walls_left_top+walls_right_bot<<endl;
        double PL_do=10*path_loss_exp*log(d0);



        if(d_ij==0)
        {
            Force_temp = 0;
            Force_temp= 0;
        }
        else
        {
            Force_temp =  (PL_do + 10*path_loss_exp*log(d_ij)+WL*(walls_left_top+walls_right_bot));
        }



        double theta;

       // cout<<d_j<<"/"<<d_i<<endl;

        if(d_i==0)
        {
            theta =3.141519/2; //stop dev by 0 error
        }
        else
        {
            double ratio =d_j /d_i;

       //     cout<<"Ratio"<<ratio<<endl;
            theta= atan(ratio);
        }



        if(d_j>0 && d_i>0)
        {
            //first quata
          theta=theta;
        }
        else  if(d_j>=0 && d_i<0)
        {
            //second quata
              theta=3.141519-theta;
        }
        else if(d_j<=0 && d_i<0)
        {
            //thrid quata
            theta=theta+3.141519;
        }
        else  if(d_j>0 && d_i>0)
        {
            //fourth
              theta= -theta;
        }


      //  cout<<"theta:"<<theta<<endl;
      //  cout<<"Force:"<<Force_temp<<endl;
        Force_j=Force_j+Force_temp*sin(theta);
        Force_i=Force_i+Force_temp*cos(theta);
      //  cout<<"i:"<<Force_temp*cos(theta)<<" j:"<<Force_temp*sin(theta)<<endl;
    }

    //cout<<"i fin:"<<Force_i<<" j fin:"<<Force_j<<endl<<endl;
}
bool VirtualRelay::Move(Grid& knownWorld)
{

   if(abs(viscous_friction*vel_j)< abs(Force_j))
    {
        accel_j = (Force_j-viscous_friction*vel_j)/mass;
    }
    else
        accel_j=0;


    if(abs(viscous_friction*vel_i)< abs(Force_i))
    {
        accel_i = (Force_i-viscous_friction*vel_i)/mass;
    }
    else
        accel_i=0;

 //cout<<"F"<<Force_i<<" "<<Force_j<<endl;
    // cout<<"A"<<accel_i<<" "<<accel_j<<endl;
    vel_j=vel_j+accel_j*time_step;
    vel_i=vel_i+accel_i*time_step;
   // cout<<"V"<<vel_i<<" "<<vel_j<<endl;
    //double pos_j = Location.getRow()+vel_j*time_step;
    //double pos_i = Location.getColumn()+vel_i*time_step;;

    double pos_j = (double)Location.getRow();
    double pos_i = (double)Location.getColumn();

    bool clash_i =true, clash_j=true;

    Coordinate new_pos;
    double vel_i_temp=vel_i;
    double   vel_j_temp=vel_j;
       while( (clash_i||clash_j ) && ((int)vel_i_temp!=0 || (int)vel_j_temp!=0)  )
    {

        clash_i=false;
        clash_j=false;
        try
        {
            new_pos=Coordinate(pos_j,(pos_i+vel_i_temp*time_step));
            //cout<<"trying"<<new_pos;
            for(int neighbour_index=0; neighbour_index<Neighbours.size(); neighbour_index++)
            {
                if(new_pos==Neighbours[neighbour_index]->getLocation())
                {
                    //cout<<"neighbour clash i";
                    clash_i=true;
                }
            }

            if(knownWorld[new_pos].hasContent(ContentType::Object))
            {
                // cout<<"object clash i";
                clash_i=true;
            }
        }
        catch(std::out_of_range)
        {
            clash_i=true;
             //cout<<"error clash i";

        }

        if(!clash_i)
        {
            pos_i= pos_i+vel_i_temp*time_step;
        }
        else
        {
            if(vel_i_temp>0)
                vel_i_temp--;
            else if(vel_i_temp<0)
                vel_i_temp++;
        }

   // cout<<"vel_i_temp"<<vel_i_temp<<endl;
        try
        {
            new_pos=Coordinate((pos_j+vel_j_temp*time_step),pos_i);
           // cout<<"now trying"<<new_pos;

            for(int neighbour_index=0; neighbour_index<Neighbours.size(); neighbour_index++)
            {
                if(new_pos==Neighbours[neighbour_index]->getLocation())
                {
                    clash_j=true;
                 //   cout<<"neighbour clash j";
                }
            }

            if(knownWorld[new_pos].hasContent(ContentType::Object))
            {
                clash_j=true;
             //   cout<<"object clash j";
            }

        }
        catch(std::out_of_range s)
        {
            clash_j=true;
           // cout<<"error clash j";
        }

        if(!clash_j)
        {
            pos_j= pos_j+vel_j_temp*time_step;
        }
        else
        {

            if(vel_j_temp>0)
                vel_j_temp--;
            else if(vel_j_temp<0)
                vel_j_temp++;

        }

              //cout<<"vel_j_temp"<<vel_j_temp<<endl;

    }

    //cout<<"ok";



    if((int)pos_j==Location.getRow() && (int)pos_i==Location.getColumn())
    {
       // cout<<"no move"<<endl;
        return false;
    }
    else
    {
       // cout<<"move by"<<pos_j-Location.getRow()<<" "<<pos_i-Location.getColumn()<<endl;
        Location= Coordinate(pos_j,pos_i);
        return true;
    }

}

