#include "MapRouter.h"
#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include <cmath>
#include <algorithm>
#include "CSVReader.h"
#include "CSVWriter.h"
#include "XMLReader.h"

std::vector< std::string > Split(const std::string &str, const std::string &splt){
    // part of these codes is cited from the StackoverFlow, check the readme file for detail
    std::string value = str;
    std::string spliter = splt;
    std::vector <std::string> result;
    std::string element;
    size_t index = 0;
    
    if (splt == ""){
        while ((index = value.find('\t')) != std::string::npos)
            value[value.find('\t')] = ' ';
        while ((index = value.find('\n')) != std::string::npos)
            value[value.find('\n')] = ' ';
        spliter = " ";
    }

    while ((index = value.find(spliter)) != std::string::npos) {   
        element = value.substr(0, index);
        result.push_back(element);
        value.erase(0, index + spliter.length());
    }
    result.push_back(value);
    
    if (splt == ""){
        while(find(result.begin(), result.end(), "") != result.end())   // cited from GeekforGeek
            result.erase(find(result.begin(), result.end(),""));    // cited from GeekforGeek
    }
    
    return result;
}

int main(int argc, char *argv[])
{
    // Your code here
    CMapRouter cmp;
    std::vector< CMapRouter::TNodeID > path;
    std::vector< CMapRouter::TPathStep > Steps;

    std::ifstream osm_Reader, stop_Reader, route_Reader;
    osm_Reader.open ("data/davis.osm", std::ios::in);
    std::istream& osmfile = osm_Reader;
    stop_Reader.open("data/stops.csv", std::ios::in);
    std::istream& stopsfile = stop_Reader;
    route_Reader.open("data/routes.csv", std::ios::in);
    std::istream& routesfile = route_Reader;

    cmp.LoadMapAndRoutes(osmfile, stopsfile, routesfile);
    std::cout<<"Successfull load the Map"<<std::endl;

    osm_Reader.close();
    stop_Reader.close();
    route_Reader.close();

    while (true)
    {
        std::string user_Input;
        std::cout<<"Please Enter a function you want to choose";
        std::cout<<"findroute [--data=path | --resutls=path]\n"
                    "------------------------------------------------------------------------\n"
                    "help     Display this help menu\n"
                    "exit     Exit the program\n"
                    "count    Output the number of nodes in the map\n"
                    "node     Syntax \"node [0, count)\n" 
                    "         Will output node ID and Lat/Lon for node\n"
                    "fastest  Syntax \"fastest start end\n" 
                    "         Calculates the time for fastest path from start to end\n"
                    "shortest Syntax \"shortest start end\n" 
                    "         Calculates the distance for the shortest path from start to end\n"
                    "save     Saves the last calculated path to file\n"
                    "print    Prints the steps for the last calculated path\n"
                    <<std::endl;
        try
        {
            std::getline(std::cin,user_Input);
        }
        catch(std::exception &ex)
        {
            std::cout << &ex << std::endl;
            std::cout << "Invalid node command, Please renter the fuction you want to choose or see help" << std::endl;
        }

        double shortestPath, fastestTime, minutes, seconds;
        int minutesInt;
        

        if (user_Input.substr(0,4) == "help"){
            std::cout<<"findroute [--data=path | --resutls=path]\n"
                       "------------------------------------------------------------------------\n"
                       "help     Display this help menu\n"
                       "exit     Exit the program\n"
                       "count    Output the number of nodes in the map\n"
                       "node     Syntax \"node [0, count)\n" 
                       "         Will output node ID and Lat/Lon for node\n"
                       "fastest  Syntax \"fastest start end\n" 
                       "         Calculates the time for fastest path from start to end\n"
                       "shortest Syntax \"shortest start end\n" 
                       "         Calculates the distance for the shortest path from start to end\n"
                       "save     Saves the last calculated path to file\n"
                       "print    Prints the steps for the last calculated path\n"<<std::endl;
        }

        else if (user_Input.substr(0,8) == "shortest") 
        {
            std::vector<std::string> user_String = Split(user_Input, " ");
            CMapRouter::TNodeID param1 = std::stoul(user_String[1]);
            CMapRouter::TNodeID param2 = std::stoul(user_String[2]);
            std::cout << "Shortest path is " << cmp.FindShortestPath(param1, param2, path) << "mi" << std::endl;
        }

        else if (user_Input.substr(0,7) == "fastest") {
            std::vector<std::string> user_String = Split(user_Input, " ");
            CMapRouter::TNodeID start = std::stoul(user_String[1]);
            CMapRouter::TNodeID end = std::stoul(user_String[2]);
            double fastestTime = cmp.FindFastestPath(start, end, Steps);
            
            std::cout << "Fastest path takes " << fastestTime<< "hours" << std::endl;            
        }

        else if (user_Input.substr(0,5) == "count") {
            std::cout << cmp.NodeCount() << " nodes" << std::endl;
        }

        else if (user_Input.substr(0,4) == "node") {
            std::vector<std::string> user_String = Split(user_Input, " ");
            CMapRouter::TNodeID nodeID = cmp.GetSortedNodeIDByIndex(std::stoi(user_String[1]));
            CMapRouter::TLocation location = cmp.GetSortedNodeLocationByIndex(std::stoi(user_String[1]));
            double lat = std::get<0>(location); //location returns two doubles; we are assigning them to strings
            double lon = std::get<1>(location);
            std::cout << "Node " << user_String[1] << ": id = " << nodeID << " is at " << lat << ", " << lon << std::endl;
        }


        else if (user_Input.substr(0,5) == "print") {
            std::cout<<path.size()<<std::endl;
            if (Steps.size()>0){
                std::vector<std::string> description;
                std::cout<<"fastest"<<std::endl;
                cmp.GetPathDescription(Steps, description); //Steps is a vector of TPathSteps
                for (int i = 0; i < description.size(); i++) {
                    std::cout << description[i] << std::endl;
                }
            }
            //shortest
            else if (path.size()>0){
                std::cout<<"shortest"<<std::endl;
                for (int i = 0; i < path.size(); i++){
                    if (i == 0){
                        double startlat = std::get <0> (cmp.GetNodeLocationByID(path[i]));
                        double startlon = std::get <1> (cmp.GetNodeLocationByID(path[i]));
                        std::cout<<"startlat = "<<startlat<<std::endl;
                        std::cout<<"startlon = "<<startlon<<std::endl;
                        std::cout<<cmp.FindLatString(startlat)<<std::endl;
                        std::cout<<cmp.FindLonString(startlon)<<std::endl;
                        std::cout<<"Start at "<<cmp.FindLatString(startlat)<<cmp.FindLonString(startlon)<<std::endl;
                    }
                    else {
                        double prevlat = std::get <0> (cmp.GetNodeLocationByID(path[i-1]));
                        double prevlon = std::get <1> (cmp.GetNodeLocationByID(path[i-1]));
                        double currlat = std::get <0> (cmp.GetNodeLocationByID(path[i]));
                        double currlon = std::get <1> (cmp.GetNodeLocationByID(path[i]));
                        double Bearing = cmp.CalculateBearing(prevlat, prevlon, currlat, currlon);
                        std::cout<<"Walk "<<cmp.CalculateDirection(Bearing)<<" to "<<cmp.FindLatString(currlat)<<cmp.FindLonString(currlon)<<std::endl;
                    }
                }
                double endlat = std::get <0> (cmp.GetNodeLocationByID(path[path.size()-1]));
                double endlon = std::get <1> (cmp.GetNodeLocationByID(path[path.size()-1]));
                std::cout<<"End at"<<cmp.FindLatString(endlat)<<cmp.FindLonString(endlon)<<std::endl;

            }
        }
        else if (user_Input.substr(0,4) == "exit")
        {
            //break;
            return EXIT_SUCCESS;
        }
        user_Input.clear();
        //return EXIT_SUCCESS;
    }

    // CMapRouter MapRouter;
    // isteam mapReader = open("davis.osm");
    // isteam stopReader = open("stops.csv");
    // isteam routeReader = open("routes.csv");
    
    // MapRouter.LoadMapAndRoutes(mapReader, stopReader, routeReader);
    // mapReader.close();
    // stopReader.close();
    // routeReader.close();
    
    // while(true)
    // {
    //     try
    //     {
    //         std::string input;
    //         std::cin >> input;
    //         if(input == "Nodes")
    //         {
    //             for(auto &nodeID : Nodes)
    //             {
    //                 std::cout << nodeID.NodeID << std::endl;
    //                 std::cout << nodeID.Location << std::endl;
    //             }
                
    //         }
    //         else if(input == "Help")
    //         {
    //             std::cout << "Noode: Output the NodeID and Location " << std::endl;
    //             std::cout << "count: Number of Nodes in the Map " << std::endl;
    //             std::cout << "Fastest: Calculate the fastest path from start to end" << std::endl;
    //             std::cout << "Shortest: Calculate the shortest path from start to end " << std::endl;
    //             std::cout << "Print: Output the steps for the last path " << std::endl;
    //             std::cout << "Save: Save the last path to the file" << std::endl;
    //         }
    //         else if(input == "Save")
    //         {
    //             std::vector <std::string> Save;
    //             Save.push_back(input);
    //         }
    //         else if(input == "ShortestPath")
    //         {
    //             std::cin >> std::src;
    //             std::cin >> std::dest;
    //             std::vector <TNodeID> path;
    //             std::cout << MapRouter.FindShortestPath(src, dest, path) << std::endl;
    //         }
    //         else if(input == "FastestPath")
    //         {
    //             std::cin >> std::src;
    //             std::cin >> std::dest;
    //             std::vector <TNodeID> path;
    //             std::cout << MapRouter.FindFastestPath(src, dest, path) << std::endl;
    //         }
    //         else if(input == "Exist")
    //         {
    //             return EXIT_SUCCESS;
    //         }
    //         else if(input == "Count")
    //         {
    //             std::cout << MapRouter.NodeCount() << std::endl;
    //         }
            
    //     }
    //     catch(expection &ex)
    //     {
    //         std::cout << ex << std::endl;
    //     }
}
