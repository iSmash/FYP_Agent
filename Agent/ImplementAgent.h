 #ifndef IMPLAMENTAGENT_H
#define IMPLAMENTAGENT_H

namespace Agent{

class ImplementAgent: protected Agent
{
	public:
		inline bool done() {return false;}//this keeps the robot doing things, this being true would require a hard restart.
};
}
#endif
