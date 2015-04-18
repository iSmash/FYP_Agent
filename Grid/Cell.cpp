#include "Cell.h";
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
    }
}

const bool Cell::hasContent(Content cont)
{
 for(int i =0; i< content.size(); i++)
 {
    // printContent(content[i]);
    //cout<<"vs";
   // printContent(cont);
	if(content[i]==cont)
	 {
	      //cout<<"ok"<<endl;
	     return true;
	     }
	     // cout<<endl;
 }
//if at this point, contnent is not in cell
return false;
}


bool Cell::removeContent(const Content cont)
{
 bool ContentFound=false;
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

//overlapting contnet is walls, goals and robots

void Cell::addContent(const Content cont)
{
     removeContent(Unknown); //if adding stuff, its no longer unknonw
    removeContent(Empty); //if adding stuff it wont be empty;

    if(cont==ContentType::Unknown)
    {
        content.empty();        //if making unkonw, we cant know anything else about it.
    }


    if(!hasContent(cont))
    {
        content.push_back(cont);
    }
}//only add content if new, stops two Robots or two walls.
