#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "XMLEntity.h"
#include <stack>
#include <expat.h>
#include <istream>

class CXMLWriter{
    private:
        std::ostream &output;
        std::stack < SXMLEntity > bufferedAtts; 
        //std::stack<>
    public:
        CXMLWriter(std::ostream &os);
        ~CXMLWriter();
        
        bool Flush();
        bool WriteEntity(const SXMLEntity &entity);
};

#endif
                                      