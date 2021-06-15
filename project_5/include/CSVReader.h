#ifndef CSVREADER_H
#define CSVREADER_H

#include <istream>
#include <string>
#include <vector>
#include <csv.h>
#include <queue>

class CCSVReader{
    protected:
        std::istream &Input;
        struct csv_parser Parser;
        std::vector <std::string> RowBuffer;
        std::queue <std::vector<std::string>> BufferRows;
        static void CallbackField(void *str, size_t len, void *data);
        static void CallbackRow(int ch, void *data);
        
    public:
        CCSVReader(std::istream &in);
        ~CCSVReader();
        
        bool End() const;
        bool ReadRow(std::vector< std::string > &row);
};

#endif
