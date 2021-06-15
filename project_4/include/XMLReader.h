#ifndef XMLREADER_H
#define XMLREADER_H

#include "XMLEntity.h"
#include <istream>
#include <expat.h>
#include <queue>
#include <vector>
#include <csv.h>

class CXMLReader{
    private:
        
        std::istream &input;
        SXMLEntity NewEntity;
        XML_Parser Parser;
        std::queue< SXMLEntity > bufferedAtts; 
        static void CallBackStart(void *userData,const XML_Char *name,const XML_Char **atts);
        static void CallBackEnd(void *userData,const XML_Char *name);
        static void CallBackHandler(void *userData, const XML_Char *s, int len);
    
    public:
        CXMLReader(std::istream &is);
        ~CXMLReader();
        
        bool End();
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false);
};

#endif
