#ifndef _CONNECTORS_CLASSES_
#define _CONNECTORS_CLASSES_

#include "connector.h"

struct AndConnector : public Connector {
    AndConnector() : Connector((char*)"&&", true, false) {}
};

struct OrConnector : public Connector {
    OrConnector() : Connector((char*)"||", false, true) {}
};

struct SemicolonConnector : public Connector {
    SemicolonConnector() : Connector((char*)";", true, true) {}
};

#endif
