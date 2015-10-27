#ifndef _CONNECTORS_LIST_
#define _CONNECTORS_LIST_

#include "header/connector.h"

struct AndConnector : public Connector {
    AndConnector() : Connector((char*)"&&", true, false) {}
};

struct OrConnector : public Connector {
    OrConnector() : Connector((char*)"||", false, true) {}
};

struct SemicolonConnector : public Connector {
    SemicolonConnector() : Connector((char*)"||", true, true) {}
};

#endif
