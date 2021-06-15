#ifndef CSVREADER_H
#define CSVREADER_H

#include <istream>
#include <string>
#include <queue>
#include <vector>
#include <csv.h>

class CCSVReader{
    protected:
        std::istream &input;
        struct csv_parser Parser;
        std::vector< std::string > rowBuffer; // storing the row
        std::queue< std::vector < std::string > > bufferedRows;// storing every row
        static void CallBackField(void *str, size_t len, void *data); // get the data from the field
        static void CallBackRow(int ch, void *data);// get the data from the row
    
    public:
        CCSVReader(std::istream &in);
        ~CCSVReader();
        
        bool End() const;
        bool ReadRow(std::vector< std::string > &row);
};

#endif
