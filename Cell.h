#ifndef CELL_H
 #define CELL_H
namespace environment
{
 class Cell
{
   public:
	//what can be in a cell, may be several at once       
	enum Content {Wall, Robot, Goal, Empty, Unknown};
		
	Cell();

	//gets
	inline const std::vector<Content> getContent() const {return content;}
	const bool hasContent(Cotent cont);
        inline const bool getViewed() const {return viewed;} //gets if this cell has been already seen as a potential 		path point
	
//set
		inline void addContent(const Content cont) {if(!hasContent(cont)){content.push_back(cont);}}//only add content if new, stops two Robots or two walls.
		void bool removeContent(const Content cont);// returns true if removed, false if was not there.
{}
		inline void setViewed(const bool view){Viewed=view;}

 private:
     std::vector<Content> content;
     bool Viewed; //check if already thought of this point as a path. If it has already been looked at, the first time it was looked at was a quicker path to this cell.

}
};

//snuk this in the same file, coz its not worth its own, special exeption if the contnent is faulty
class ContentError: public std::exception
{
		public: 
			virtual const char* what() const throw()
	{
		return "Content was not good";
	}
}
#endif
