#ifndef CONTENT_H
#define CONTENT_H

#include <exception>
namespace ContentType{
   //what can be in a cell, may be several at once
	enum Content {Wall, Robot, Goal, Unknown, Empty, RelayMarker, Client, Object}; //Object is collection of Client, RelayMarker or Wall.
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
