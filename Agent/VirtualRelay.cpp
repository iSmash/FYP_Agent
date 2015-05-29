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
    force.j=0;
    force.i=0;


    for(int neighbour_index=0; neighbour_index<Neighbours.size(); neighbour_index++)
    {
        double force_temp;
        VirtualRelay* interactor = Neighbours[neighbour_index];

        IJ_Componet d;
        d.j=interactor->getLocation().getRow()-Location.getRow();
        d.i=interactor->getLocation().getColumn()-Location.getColumn();
        d.set_magnetude();
        SubGrid subgrid(knownWorld, Location, interactor->getLocation());

        int walls_left_top, walls_right_bot;
        subgrid.Wall_count(Location,walls_left_top, walls_right_bot );

        //cout<<"Walls"<<walls_left_top+walls_right_bot<<endl;
        double PL_do=10*path_loss_exp*log(d0);



        if(d.magnetude==0)
        {
            force_temp = 0;
        }
        else
        {
            force_temp =  (PL_do + 10*path_loss_exp*log(d.magnetude)+WL*(walls_left_top+walls_right_bot));
        }



        double theta;

       // cout<<d_j<<"/"<<d_i<<endl;

        if(d.i==0)
        {
            theta =3.141519/2; //stop dev by 0 error
        }
        else
        {
            double ratio =d.j /d.i;

       //     cout<<"Ratio"<<ratio<<endl;
            theta= atan(ratio);
        }



        if(d.j>0 && d.i>0)
        {
            //first quata
          theta=theta;
        }
        else  if(d.j>=0 && d.i<0)
        {
            //second quata
              theta=3.141519-theta;
        }
        else if(d.j<=0 && d.i<0)
        {
            //thrid quata
            theta=theta+3.141519;
        }
        else  if(d.j>0 && d.i>0)
        {
            //fourth
              theta= -theta;
        }


      //  cout<<"theta:"<<theta<<endl;
      //  cout<<"Force:"<<Force_temp<<endl;
        force.j=force.j+force_temp*sin(theta);
        force.i=force.i+force_temp*cos(theta);
      //  cout<<"i:"<<Force_temp*cos(theta)<<" j:"<<Force_temp*sin(theta)<<endl;
    }

    //cout<<"i fin:"<<Force_i<<" j fin:"<<Force_j<<endl<<endl;
}
bool VirtualRelay::Move(Grid& knownWorld)
{

   if(abs(viscous_friction*velocity.j)< abs(force.j))
    {
        accelleration.j = (force.j-viscous_friction*velocity.j)/mass;
    }
    else
        accelleration.j=0;


    if(abs(viscous_friction*velocity.i)< abs(force.i))
    {
        accelleration.i = (force.i-viscous_friction*velocity.i)/mass;
    }
    else
        accelleration.i=0;

 //cout<<"F"<<force.i<<" "<<force.j<<endl;
   //  cout<<"A"<<accelleration.i<<" "<<accelleration.j<<endl;
    velocity.j=velocity.j+accelleration.j*time_step;
    velocity.i=velocity.i+accelleration.i*time_step;
   // cout<<"V"<<velocity.i<<" "<<velocity.j<<endl;
    //double pos_j = Location.getRow()+velocity_j*time_step;
    //double pos_i = Location.getColumn()+velocity_i*time_step;;

    IJ_Componet pos;
    pos.j = (double)Location.getRow();
    pos.i = (double)Location.getColumn();

    bool clash_i =true, clash_j=true;

    Coordinate new_pos;
    IJ_Componet velocity_temp;
    velocity_temp.i=velocity.i;
    velocity_temp.j=velocity.j;
       while( (clash_i||clash_j ) && ((int)velocity_temp.i!=0 || (int)velocity_temp.j!=0)  )
    {

        clash_i=false;
        clash_j=false;
        try
        {
            new_pos=Coordinate(pos.j,(pos.i+velocity_temp.i*time_step));
           // cout<<"trying"<<new_pos;
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
            pos.i= pos.i+velocity_temp.i*time_step;
        }
        else
        {
            if(velocity_temp.i>0)
                velocity_temp.i--;
            else if(velocity_temp.i<0)
                velocity_temp.i++;
        }

   // cout<<"velocity_i_temp"<<velocity_i_temp<<endl;
        try
        {
            new_pos=Coordinate((pos.j+velocity_temp.j*time_step),pos.i);
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
            pos.j= pos.j+velocity_temp.j*time_step;
        }
        else
        {

            if(velocity_temp.j>0)
                velocity_temp.j--;
            else if(velocity_temp.j<0)
                velocity_temp.j++;

        }

              //cout<<"velocity_j_temp"<<velocity_j_temp<<endl;

    }

    //cout<<"ok";



    if((int)pos.j==Location.getRow() && (int)pos.i==Location.getColumn())
    {
       // cout<<"no move"<<endl;
        return false;
    }
    else
    {
       // cout<<"move by"<<pos_j-Location.getRow()<<" "<<pos_i-Location.getColumn()<<endl;
        Location= Coordinate(pos.j,pos.i);
        return true;
    }

}

