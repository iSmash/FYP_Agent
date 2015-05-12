#ifndef CONTENT_H
#define CONTENT_H

#include <exception>
namespace ContentType{
   //what can be in a cell, may be several at once
	enum Content {Wall, Robot, Goal, Unknown, Empty, RelayMarker, Client, Object, Jormungandr_Wall}; //Object is collection of Client, RelayMarker or Wall. Jormungandr_Wall is world edige wall
    }

namespace environment
{
//snuk this in the same file, coz its not worth its own, special exeption if the contnent is faulty
class ContentError: public std::exception
{
		public:
			virtual const char* what() const throw()
	{
		return "Content was not good";
	}
};

}
#endif
