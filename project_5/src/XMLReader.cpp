
#include "XMLReader.h"
#include "XMLWriter.h"
#include "XMLEntity.h"
#include<iostream>
#include <expat.h>

#include <string>

CXMLReader::CXMLReader(std::istream &in) : Input(in){
    DExpatParser = XML_ParserCreate(NULL);
    XML_SetUserData(DExpatParser, this);
    XML_SetElementHandler(DExpatParser, StaticStartElement,StaticEndElement);
    XML_SetCharacterDataHandler(DExpatParser, StaticCharacterData);

}

CXMLReader::~CXMLReader() {
    XML_ParserFree(DExpatParser);
}
void CXMLReader::StaticStartElement (void *data, const XML_Char *name, const XML_Char **attrs){
    CXMLReader *Ptr = static_cast<CXMLReader*>(data);
    SXMLEntity newEntity;
    newEntity.DNameData = std::string(name);
    newEntity.DType = SXMLEntity::EType::StartElement;
    for (int i = 0; attrs[i]; i+=2){
        newEntity.DAttributes.push_back(std::make_pair(std::string(attrs[i]),std::string(attrs[i+1])));
    }
    Ptr->BufferEntities.push(newEntity);
}

void CXMLReader::StaticEndElement (void *data, const XML_Char *name){
    CXMLReader *Ptr = static_cast<CXMLReader*>(data);
    SXMLEntity newEntity;
    newEntity.DNameData = std::string(name);
    newEntity.DType = SXMLEntity::EType::EndElement;
    Ptr->BufferEntities.push(newEntity);

}

void CXMLReader::StaticCharacterData (void *data, const XML_Char *s, int len){
    CXMLReader *Ptr = static_cast<CXMLReader*>(data);

    SXMLEntity newEntity;
    newEntity.DNameData = std::string(s,len);
    newEntity.DType = SXMLEntity::EType::CharData;
    Ptr->BufferEntities.push(newEntity);

}


bool CXMLReader::End(){
    if (Input.eof() and BufferEntities.empty()){
        return true;
    }
    else{
        return false;
    }

}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    int count = 0;
    while (!Input.eof() and BufferEntities.empty()) {
        char buffer[16384];
        Input.read(buffer, 16384);
        XML_Parse(DExpatParser,buffer, Input.gcount(),Input.eof());
    }
    if (skipcdata) {
        while (!BufferEntities.empty() and (BufferEntities.front().DType == SXMLEntity::EType::CharData)) {
            BufferEntities.pop();
        }
    }

    if (BufferEntities.empty()){
        return false;
    }
    else{
        entity.DAttributes = BufferEntities.front().DAttributes;
        entity.DType = BufferEntities.front().DType;
        entity.DNameData = BufferEntities.front().DNameData;
        BufferEntities.pop();
        return true;
    }

}