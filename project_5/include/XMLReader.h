#ifndef XMLREADER_H
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <queue>

class CXMLReader{
    private:
        std::istream &Input;
        XML_Parser DExpatParser;
        static void StaticStartElement(void *userData, const XML_Char*name, const XML_Char **atts);
        static void StaticEndElement(void *userData, const XML_Char *name);
        static void StaticCharacterData(void *userData, const XML_Char *s, int len);
        std::queue <struct SXMLEntity> BufferEntities;

    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif
