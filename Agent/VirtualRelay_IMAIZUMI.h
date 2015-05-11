#ifndef VIRTUALRELAY_IMAIZUMI_H
#define VIRTUALRELAY_IMAIZUMI_H
#include "VirtualRelay.h"

class VirtualRelay_IMAIZUMI: public VirtualRelay
{
    public:
        VirtualRelay_IMAIZUMI(Coordinate _Location):VirtualRelay(_Location){};
        void findForces(Grid& knownWorld);
        void Move();
    private:

};

#endif // VIRTUALRELAY_IMAIZUMI_H
