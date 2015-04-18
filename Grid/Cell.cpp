#include "Cell.h";

using namespace environment;
using namespace ContentType;

const bool Cell::hasContent(Content cont)
{
 for(int i =0; i< content.size(); i++)
 {
	if(content[i]==cont)
	 {return true;}
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

void Cell::addContent(const Content cont)
{
     removeContent(Unknown); //if adding stuff, its no longer unknonw

    if(cont==ContentType::Unknown)
    {
        content.empty();        //if making unkonw, we cant know anything else about it.
    }

    if(!hasContent(cont))
    {
        content.push_back(cont);
    }
}//only add content if new, stops two Robots or two walls.
