#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <stdio.h>
#include <queue>
#include "StringUtils.h"
#include "CSVReader.h"
#include "CSVWriter.h"
#include "XMLEntity.h"
#include "XMLReader.h"
#include "XMLWriter.h"

int main(int argc, char *argv[])
{
    // take user's input 
    if(argc >= 2)
    {
        for(int i = 0; i < argc; i++)
        {
            std::cout<<argv[i]<<std::endl;
        }
    }
    char buffer[100];
    std::vector<std::string> row;
    std::vector<std::string> bufferChar;
    std::vector<std::string> bufferData;

    //std::vector<std::string> handler;

    // check what kind of file it is
    std::string fileName_1;//file to read
    std::cout << "which file do you want to read enter a dir"<< std::endl;
    std::cin >> fileName_1;

    std::string fileName_2;//file write
    std::cout<<"which file do you want to write enter a dir" << std::endl;
    std::cin >> fileName_2;

    std::ifstream infile;
    infile.open(fileName_1, std::ios::in);
    std::ofstream outfile;
    outfile.open(fileName_2, std::ios::out);

    // we read the file
    CCSVReader rCSV(infile);
    CXMLReader rXML(infile);
    CXMLWriter wXML(outfile);

    std::string suffixStr_1 = fileName_1.substr(fileName_1.find_last_of('.') + 1);
    std::string suffixStr_2 = fileName_2.substr(fileName_2.find_last_of('.') + 1);
    
    // then convert
    // from Firday TA Nick's office hour 
    std::queue<SXMLEntity> handler;

    //std::<std::string> header = StringUtils::Split(fi);
    std::vector<std::string> def = {"SUBJ","CRSE","SEC"};


    if(suffixStr_1 != "csv" or suffixStr_1 != "xml")
    {
        std::cout<<"Wrong file"<<std::endl;
    }
    if(suffixStr_1 == "csv")
    {
        while(rCSV.End() == false)
        {
            int index = 1;
            if(index == 1 or rCSV.ReadRow(row))
            {
                bufferChar = row;
            }
            else
            {
                bufferData = row;
                for(int i =0; i< bufferChar.size(); i++)
                {
                    SXMLEntity NewEntity;
                    NewEntity.SetAttribute(bufferChar[i], bufferData[i]);
                    handler.push(NewEntity);
                }

                // std::vector<std::string> handler;
        // while(!rXML.End() == false)
        // {
        //     std::vector<std::string> row;
        //     if(rXML.ReadRow(row))
        //     {
        //         XMLEntity NewEntity;
        //         NewEntity.DNameData = "Student";
        //         for(int i = 0; i < hander.size(); i++)
        //         {
        //             NewEntity.SetAttribute(handler[i], row[i]);
        //         }
        //         wXML.WriteEntity(NewEntity);
        //     }
        // }
            }
            index++;
        }
        wXML.Flush();
        infile.close();
        outfile.close();

    }
    if(suffixStr_1 == "xml")
    {
        std::vector<std::string> vec;
        SXMLEntity NewEntity;
        while(!rXML.End() == false)
        {
            std::vector<std::string> row;
            if(rXML.ReadEntity(NewEntity))
            {
                NewEntity.DNameData = "Student";
                for(int i = 0; i < vec.size(); i++)
                {
                    NewEntity.SetAttribute(vec[i], row[i]);
                }
                wXML.WriteEntity(NewEntity);
            }
        }
        wXML.Flush();
        infile.close();
        outfile.close();

        
    }
    return EXIT_SUCCESS;
    // if (argc != 3) 
    // {
    //     fprintf(stderr, "Usage: csv_fix infile outfile\n");
    //     return EXIT_FAILURE;
    // }

    // if (!strcmp(argv[1], argv[2])) 
    // {
    //     fprintf(stderr, "Input file and output file must not be the same!\n");
    //     exit(EXIT_FAILURE);
    // }

    // infile = fopen(argv[1], "rb");
    // if (infile == NULL) 
    // {
    //     fprintf(stderr, "Failed to open file %s: %s\n", argv[1], strerror(errno));
    //     exit(EXIT_FAILURE);
    // }

    // outfile = fopen(argv[2], "wb");
    // if (outfile == NULL) 
    // {
    //     fprintf(stderr, "Failed to open file %s: %s\n", argv[2], strerror(errno));
    //     fclose(infile);
    //     exit(EXIT_FAILURE);
    // }
    // while ((i=fread(buf, 1, 1024, infile)) > 0)
    // {
    //     if (csv_parse(&p, buf, i, cb1, cb2, outfile) != i) 
    //     {
    //         fprintf(stderr, "Error parsing file: %s\n", csv_strerror(csv_error(&p)));
    //         fclose(infile);
    //         fclose(outfile);
    //         remove(argv[2]);
    //         exit(EXIT_FAILURE);
    //     }
    // }
    
    // csv_fini(&p, cb1, cb2, outfile);
    // csv_free(&p);

    // if (ferror(infile)) 
    // {
    //     fprintf(stderr, "Error reading from input file");
    //     fclose(infile);
    //     fclose(outfile);
    //     remove(argv[2]);
    //     exit(EXIT_FAILURE);
    // }
    // fclose(infile);
    // fclose(outfile);
    // return EXIT_SUCCESS;
}
