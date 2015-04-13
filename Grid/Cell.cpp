#include "Cell.h";

using namespace environment;

const bool Cell::hasContent(Cotent cont)
{
 for(int i =0; i< content.size(); i++)
 {
	if(content[i]==cont)
	 {return true;}
 }
//if at this point, contnent is not in cell
return false;
}


void bool Cell::removeContent(const Content cont)
{
 bool ContentFound=false;
 for(int i =0; i< content.size(); i++)
 {
	if(content[i]==cont)
	 {
	     if(ContentFound)
		{
		  //if here it means there were two of the same contnet in this cell, thats not cool, im telling the teacher on you.
		throw(ContentError("double content found on remove"));
		}
	     ContentFound=true;
   	     content.erase(i);
	 }
 }
 return ContentFound;
}
