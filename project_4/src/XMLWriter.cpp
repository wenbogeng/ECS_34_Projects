#include "XMLWriter.h"
#include <iostream>
#include "StringUtils.cpp"

CXMLWriter :: CXMLWriter(std::ostream &ou) : output(ou)
{
    //don't need anything
}

CXMLWriter :: ~CXMLWriter()
{
    //don't need anything
}

bool CXMLWriter :: Flush()
{
    SXMLEntity NewEntity;
    // NewEntity = XML_ParserCreate(NULL);

    while(!bufferedAtts.empty())
    {
        output << "</" << bufferedAtts.top().DNameData<<">";
        // NewEntity.DAttributes = NULL;
        // NewEntity.DType = NULL;
        // NewEntity.SetAttribute(NewEntity.DNameData,NULL);
        // std::cout << bufferedAtts.top()<< std::endl;
        bufferedAtts.pop();
    }
    return true;
    
}

bool CXMLWriter :: WriteEntity(const SXMLEntity &entity)
{
    SXMLEntity NewEntity;
    std::vector < std::pair<std::string, std::string>> attT;
    attT = entity.DAttributes;

    // std::string str;
    // using TAttribute = std::pair<std::string("\""), StringUtils::Replace(Field,"\"","\"\"")>;
    if(entity.DType == SXMLEntity :: EType :: StartElement or entity.DType == SXMLEntity :: EType :: CompleteElement)
    {
        if(entity.DType == SXMLEntity :: EType :: StartElement)
        {
            bufferedAtts.push(entity); 
        }
        output << "<" << entity.DNameData;
        for(auto &Feild : entity.DAttributes)
        {
            // str = entity.DAttributes.data;
            std::string newName = std::get<0>(Feild);
            newName = StringUtils::Replace(newName, "&", "&amp");
            newName = StringUtils::Replace(newName, "\"", "&quot");
            newName = StringUtils::Replace(newName, "'", "&apos");
            newName = StringUtils::Replace(newName, "<", "&lt");
            newName = StringUtils::Replace(newName, ">", "&gt");
            // switch (str)
            // {
            //     case("&")
            //     {
            //         std::string newName = StringUtils::Replace(str,"&","&amp");
            //         std::string newValue = StringUtils::Replace(str,"&","&amp");
            //         break;
            //     }
            // }
            std::string newValue = std::get<1>(Feild);
            //std::string newValue = StringUtils::Replace(str,"\"","&quot");
            newValue = StringUtils::Replace(newValue, "&", "&amp");
            newValue = StringUtils::Replace(newValue, "\"", "&quot");
            newValue = StringUtils::Replace(newValue, "'", "&apos");
            newValue = StringUtils::Replace(newValue, "<", "&lt");
            newValue = StringUtils::Replace(newValue, ">", "&gt");
            output << newName << "=\"" <<newValue << " ";
        }
        if(entity.DType == SXMLEntity::EType::StartElement)
        {
            output<< ">" ;
        }
        else if(entity.DType == SXMLEntity::EType::CompleteElement)
        {
            output<<"/>";
        }
        else if(entity.DType == SXMLEntity::EType::EndElement)
        {
            output<<"</"<<bufferedAtts.top().DNameData<<">";
        }

        return bufferedAtts.empty();
    }

 
   
    return true;
    // output << StringUtils::Join(",",outPutRow) << std::endl;
    // return output.good();
    /*
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
    */
}

