#include "CSVReader.h"

CCSVReader :: CCSVReader(std::istream &in) : input(in)
{
    csv_init(&Parser, 0);
}

CCSVReader :: ~CCSVReader()
{
    csv_free(&Parser);
}

void CCSVReader :: CallBackField(void *str, size_t len, void *data)
{
    std::string *Str = static_cast<std::string*>(str);
    CCSVReader *Ptr = static_cast<CCSVReader*>(data);
    Ptr->rowBuffer.push_back(std::string(*Str,len));
    // Ptr->rowBuffer.push_back(*Str);
}

void CCSVReader :: CallBackRow(int ch, void *data)
{
    // ch's row
    CCSVReader *Ptr = static_cast<CCSVReader*>(data);// change the return type of the data
    // push back to the queue
    Ptr->bufferedRows.push(Ptr -> rowBuffer);
    Ptr->rowBuffer.clear();
}

bool CCSVReader :: End() const
{
    return input.eof();
    // if(bufferedRows.empty() and input.eof())
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
}

bool CCSVReader :: ReadRow(std::vector<std:: string> & row)//  a 0 , b 1  , c2  ,d3
{
    while(rowBuffer.empty() and !input.eof())
    {
        char buffer [256];
        input.read(buffer, 256);
        csv_parse(&Parser, buffer, input.gcount(), CallBackField, CallBackRow, this);// parse the row
        row.push_back(static_cast<std::string>(buffer));
    }
     csv_fini(&Parser, CallBackField, CallBackRow,this);// stop reading
     row = this->bufferedRows.front();
     if(!bufferedRows.empty())
     {
        this->bufferedRows.pop();
     }
     
     return bufferedRows.empty();
//     if(!input or row.empty())// if the file is empty
//     {
//         return false;
//     }
//     else
//     {
//         char buffer[128]; // store each feild store binary fields
// //        std::string lineStr; // to store the row
// //        linestr = row's data push back the row
//         input.read(buffer, 128); // return how many bytes is going to read
//         csv_parse(&Parser, buffer, input.gcount(), CallBackField, CallBackRow, this);// parse the row
//         row.push_back(static_cast<std::string>(buffer));
//         bufferedRows.push(row);
//         delete [] buffer;
//         //input.close();
//         //csv_fini(&Parser, CallBackField, CallBackRow);// stop reading
//         return true;
//     }
}


