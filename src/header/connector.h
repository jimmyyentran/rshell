#ifndef _CONNECTOR_
#define _CONNECTOR_

#include "runner.h"

// Abstract class
class Connector : public Runner {
    private:
        char * key;
        bool ifReceiveTrue;
        bool ifReceiveFalse;
    public:
        Connector(char *, bool, bool);
        bool run(bool);
        virtual ~Connector() = 0;
};

#endif
