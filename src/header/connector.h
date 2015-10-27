#ifndef _CONNECTOR_
#define _CONNECTOR_

#include "runner.h"

class Connector : public Runner {
    private:
        char * key;
    public:
        Connector(char *);

};

#endif
