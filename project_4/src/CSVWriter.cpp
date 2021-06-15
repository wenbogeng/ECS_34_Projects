#include "CSVWriter.h"
#include "StringUtils.cpp"

CCSVWriter :: CCSVWriter(std::ostream &ou) : output(ou)
{
    //don't need anything
}

CCSVWriter :: ~CCSVWriter()
{
    //don't need anything
}

bool CCSVWriter :: WriteRow(const std::vector< std::string > &row)
{
    //csv_write();
    std::vector<std::string> outPutRow;
    for(auto &Field : row)
    {
        outPutRow.push_back(std::string("\"") + StringUtils::Replace(Field,"\"","\"\"")+"\"");
    }
    output << StringUtils::Join(",",outPutRow) << std::endl;
    return output.good();
    // if(!output or !row.empty())
    // {
    //     return false;
    // }
    // else
    // {
    //     char buffer [128];
    //     output.write(buffer, 128);
    //     // check if it's writing to the end
    //     while()
    //     {

    //     }
    //     // row.push_back(static_cast<std::string>(buffer));
    //     delete [] buffer;
    //     return true;
    // }
    
}




