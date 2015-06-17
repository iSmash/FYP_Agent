#include "Cell.h"
#include <iostream>
using namespace environment;
using namespace ContentType;
using namespace std;
void printContent(ContentType::Content toprint)
{
     switch(toprint)
    {
        case ContentType::Wall: cout<<"Wall; ";break;
        case ContentType::Robot: cout<<"Robot; "; break;
        case ContentType::Goal: cout<<"Goal; ";break;
        case ContentType::Unknown: cout<<"Unknown; ";break;
        case ContentType::Empty: cout<<"Empty; ";break;
        case ContentType::Jormungandr_Wall: cout<<"World end; "; break;
    }
}

const bool Cell::hasContent(Content cont)
{
 if(cont == Object)
    return hasContent(Wall)||hasContent(Client)||hasContent(RelayMarker)||hasContent(Jormungandr_Wall)||hasContent(Base);
  if(cont == Path_Object)
    return hasContent(Wall)||hasContent(RelayMarker)||hasContent(Jormungandr_Wall)||hasContent(Client);

 for(int i =0; i< content.size(); i++)
 {
	if(content[i]==cont)
	 {
	     return true;
	 }
 }
//if at this point, contnent is not in cell
return false;
}


bool Cell::removeContent(const Content cont)
{
 bool ContentFound=false;

  if(cont == Object||cont == Path_Object)
  {
      cout<<"Illegal remove type."<<endl;
      return false; //dont do this
  }

 for(int i =0; i< content.size(); i++)
 {
	if(content[i]==cont)
	 {
	     if(ContentFound)
		{
		  //if here it means there were two of the same contnet in this cell, thats not cool, im telling the teacher on you.
		throw(ContentError());
		}
	     ContentFound=true;
   	     content.erase(content.begin()+i);
	 }
 }
 return ContentFound;
}

//overlapping content is walls, goals and robots.

void Cell::addContent(const Content cont)
{
    if(cont == Object||cont == Path_Object)
  {
      cout<<"Illegal add type"<<endl;
      return; //dont do this
  }

    if(cont!= Goal)
    {
     removeContent(Unknown); //if adding stuff, its no longer unknown
     removeContent(Empty);   //if adding stuff it wont be empty;
    }

    if(cont==ContentType::Unknown)
    {
        content.empty();        //if making unknown, we cant know anything else about it.
    }


    if(!hasContent(cont))
    {
        content.push_back(cont);
    }
}//only add content if new, stops two Robots or two walls.

void Cell::printAllContent()
{
    for(int contint_index=0; contint_index<content.size(); contint_index++)
    {
        printContent(content[contint_index]);
        cout<<endl;
    }
}
