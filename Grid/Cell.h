#ifndef CELL_H
#define CELL_H

#include "Content.h"
#include <vector>
using namespace ContentType;

namespace environment
{
 class Cell
{
   public:

	Cell(){viewed=false;}

	//gets
	inline std::vector<Content>& getContent() {return content;}
	const bool hasContent(Content cont);
        inline const bool getViewed() const {return viewed;} //gets if this cell has been already seen as a potential 		path point

//set
		void addContent(const Content cont);//only add content if new, stops two Robots or two walls.
		bool removeContent(const Content cont);// returns true if removed, false if was not there.
		inline void setViewed(const bool view){viewed=view;}

 private:
     std::vector<Content> content;
     bool viewed; //check if already thought of this point as a path. If it has already been looked at, the first time it was looked at was a quicker path to this cell.

};
}


#endif
