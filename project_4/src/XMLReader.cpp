#include "XMLReader.h"
#include <iostream>

CXMLReader :: CXMLReader(std::istream &is) : input(is)
{
    // initialize
    Parser = XML_ParserCreate(NULL);
    XML_SetUserData(Parser,this);
    XML_SetElementHandler(Parser, CallBackStart, CallBackEnd);
    XML_SetCharacterDataHandler(Parser, CallBackHandler);
}
CXMLReader :: ~CXMLReader()
{
    // free the memory
    XML_ParserFree(Parser);
}

void CXMLReader :: CallBackStart(void *userData,const XML_Char *name,const XML_Char **atts)
{
    CXMLReader *Ptr = static_cast<CXMLReader *>(userData);
    SXMLEntity NewEntity;
    
    NewEntity.DType = SXMLEntity::EType::StartElement;
    NewEntity.DNameData = std::string(name);
    
    for(int i = 0; atts[i]; i += 2)
    {
        NewEntity.DAttributes.push_back(std::make_pair(std::string(atts[i]),std::string(atts[i+1])));
        Ptr->bufferedAtts.push(NewEntity);
    }
}

void CXMLReader::CallBackEnd(void *userData,const XML_Char *name)
{
    CXMLReader *Ptr = static_cast<CXMLReader *>(userData);
    SXMLEntity NewEntity;
    
    NewEntity.DType = SXMLEntity::EType::EndElement;
    NewEntity.DNameData = "/" + std::string(name);
    
    Ptr->bufferedAtts.push(NewEntity);
}

void CXMLReader::CallBackHandler(void *userData, const XML_Char *s, int len)
{
    CXMLReader *Ptr = static_cast<CXMLReader *>(userData); //a ptr to access the member
    SXMLEntity NewEntity; // new atts/row
    NewEntity.DType = SXMLEntity::EType::CharData;
    NewEntity.DNameData = std::string(s);
    
    Ptr->bufferedAtts.push(NewEntity);
}

bool CXMLReader::End()
{
    return input.eof();
    // if(!bufferedAtts.empty() or input.eof())
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata = false)
{
    // < > 
    // when there is a / has to have a  <，and / only with </ or /> 
    // start should be the same with the end
    bool isRead = false;
    while(!bufferedAtts.empty() or !input.eof())
    {
        char buffer [256];
        input.read(buffer, 256);
        // parse it
        XML_Parse(Parser, buffer, input.gcount(), input.eof());// parse the row
        bufferedAtts.push(entity);
    }
    if(skipcdata == true)
    {
        while(!bufferedAtts.empty() and bufferedAtts.front.DType == SXMLEntity::EType::CharData)
        {
            bufferedAtts.pop();
        }
    }
    if(!bufferedAtts.empty())
    {
        entity = bufferedAtts.front();
        isRead = true;
    }
    return isRead;
    // if(skipcdata == true and entity. DType == SXMLEntity::EType::CharData)
    // {
    //         bufferedAtts.pop();
    //         return true;
    // }
    
    // return false;
    //  csv_fini(&Parser, CallBackField, CallBackRow);// stop reading
    //  row = bufferRows.front();
    //  BufferRows.pop();

    // char buffer [2048];
    // if(skipcdata == false)
    // {
    //     while(!input.eof())
    //     {
    //         if(entity.AttributeExists(entity.DNameData))//check if it's exits
    //         {
    //             input.read(buffer, 2048);
    //             // push it to the quene;

    //         }
    //     }
    //     return true;
    // }
    // return true;
}

