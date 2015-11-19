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

struct ParenthesisConnector: public Connector {
    bool isOpen;
    ParenthesisConnector(bool b) : isOpen(b){
        b ? setKey((char*)"(") : setKey((char*)")");
    }
};

struct BracketConnector: public Connector {
    BracketConnector(bool b){
        b ? setKey((char*)"[") : setKey((char*)"]");
    }
};

#endif
