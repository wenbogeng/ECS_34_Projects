#include "MapRouter.h"
#include "CSVReader.h"
#include "XMLReader.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

const CMapRouter::TNodeID CMapRouter::InvalidNodeID = -1;
const double CMapRouter::WalkSpeed = 3.0;

CMapRouter::CMapRouter(){
    
}

CMapRouter::~CMapRouter(){
    
}
// From TA Nik's office hour
// Which those fuctions are from C++ references
double HoursToMins(double hours)
{
    double mins;
    mins = hours*60;
    return mins;
}

double MinsToSeconds(double mins)
{
    double sec;
    float decMins = mins - floor(mins);
    sec = decMins*60;
    return sec;
}

std::string GetLatDirection(int lat)
{
    std::string latDir;
    if(lat < 0)
    {
        latDir = "S";
    }
    else
    {
        latDir = "N";
    }
    return latDir;
}

std::string GetLonDirection(int lon)
{
    std::string lonDir;
    if(lon < 0)
    {
        lonDir = "W";
    }
    else
    {
        lonDir = "E";
    }
    return lonDir;
}

std::string CalculateDirection(double bearing)
{
    std::string direction;
    
    if(bearing < 22.5 and bearing > -22.5)
    {
        direction = "N";
    }
    else if (bearing > 22.5 and bearing < 67.5)
    {
        direction = "NE";
    }
    else if (bearing > 67.5 and bearing < 112.5)
    {
        direction = "E";
    }
    else if (bearing < -22.5 and bearing > -135)
    {
        direction = "W";
    }
    else if (bearing > 112.5 and bearing < 157.5)
    {
        direction = "SE";
    }
    else if (bearing > 157.5 or bearing < -157.5)
    {
        direction = "S";
    }
    else if(bearing > 157.5 and bearing < -112.5)
    {
        direction = "SW";
    }
    else if (bearing > -112.5 and bearing < -67.5)
    {
        direction = "W";
    }
    else if (bearing > -67.5 and bearing < -22.5)
    {
        direction = "NW";
    }
    
    return direction;
}

std::string FindLatString(double lat)
{
    std::string LatCoordinates, LatDirection;
    
    double Latminutes, Latseconds, fraction, wholepart;
    int LatminutesInt, LatsecondsInt, latInt;
    
    fraction = lat - floor(lat);
    
    Latminutes = HoursToMins(Latminutes - fraction);
    
    if(Latminutes == floor(Latminutes))
    {
        Latseconds = 0;
    }
    else
    {
        Latseconds = MinsToSeconds(Latminutes - floor(Latminutes));
    }
    
    LatminutesInt = static_cast<int> (Latminutes);
    LatsecondsInt = static_cast<int> (Latseconds);
    latInt = static_cast<int> (lat);
    
    LatDirection = GetLatDirection(latInt);
    
    LatCoordinates = std::to_string(latInt) + "d " + std::to_string(LatminutesInt) + "' " + std::to_string(LatsecondsInt) + "\" " + LatDirection + ", ";
    
    return LatCoordinates;
    
}

std::string FindLonString(double lon)
{
    std::string LonCoordinates, LonDirection;
    double Lonminutes, Lonseconds, fraction, wholepart;
    int LonminutesInt, LonsecondsInt, lonInt;
    
    fraction = lon - floor(lon);
    //finding lon minutes and seconds
    Lonminutes = HoursToMins(Lonminutes - fraction);
    
    if(Lonminutes == floor(Lonminutes))
    {
        Lonseconds = 0;
    }
    else
    {
        Lonseconds = MinsToSeconds(Lonminutes - floor(Lonminutes));
    }
    
    LonminutesInt = static_cast<int> (Lonminutes);
    LonsecondsInt = static_cast<int> (Lonseconds);
    lonInt = static_cast<int> (lon);
    
    
    LonDirection = GetLonDirection(lonInt);
    
    LonCoordinates = std::to_string(lonInt) + "d " + std::to_string(LonminutesInt) + "' " + std::to_string(LonsecondsInt) + "\" " + LonDirection;
    return LonCoordinates;
}
// double CMapRouter::Dijkstra(TNodeIndex src, TNodeIndex dest, std::vector< TNodeIndex > &path, int searchtype)
// {
//     std::vector< TNodeIndex > Previous(Nodes.size());
//     std::vector< double > Distance(Nodes.size(), std::numeric_limits<double>::max());
//     std::vector< TNodeIndex > Heap;

//     auto Compare = [&Distance](TNodeIndex idx1, TNodeIndex idx2)
//     {
//         return Distance[idx1] < Distance[idx2];
//     };

//     Previous[src] = src;
//     Distance[src] = 0.0;
//     Heap.push_back(src);

//     while(!Heap.empty())
//     {
//         std::make_heap(Heap.begin(), Heap.end(),Compare);
//         std::pop_heap(Heap.begin(), Heap.end(),Compare);
//         auto Current = Heap.back();
//         for(auto &Edge : Nodes[Current].Edges)
//         {
//             double EdgeDistance;
//             switch(searchtype)
//             {
//                 case 0:
//                     EdgeDistance = Edge.Distance;
//                     break;
//                 case 1:
//                     EdgeDistance = Edge.Time;
//                 default:
//                     EdgeDistance = Edge.Distance / Edge.SpeedLimit;
//                     break;
//             }
//             auto AltDistance = Distance[Current] + EdgeDistance;
//             if(AltDistance < Distance[Edge.OtherNode])
//             {
//                 if(Distance[Edge.OtherNode] == std::numeric_limits<double> :: max())
//                 {
//                     Heap.push_back(Edge.OtherNode);
//                 }
//                 Distance[Edge.OtherNode] = AltDistance;
//                 Previous[Edge.OtherNode] = Current;
//             }
//         }

//     }
//     if(Distance[dest] == std::numeric_limits<double>::max())
//     {

//     }
//     return Distance[dest];
// }

// Provided function to calculate the distance in miles
double CMapRouter::HaversineDistance(double lat1, double lon1, double lat2, double lon2)
{
    auto DegreesToRadians = [](double deg){return M_PI * (deg) / 180.0;};
    double LatRad1 = DegreesToRadians(lat1);
    double LatRad2 = DegreesToRadians(lat2);
    double LonRad1 = DegreesToRadians(lon1);
    double LonRad2 = DegreesToRadians(lon2);
    double DeltaLat = LatRad2 - LatRad1;
    double DeltaLon = LonRad2 - LonRad1;
    double DeltaLatSin = sin(DeltaLat/2);
    double DeltaLonSin = sin(DeltaLon/2);
    double Computation = asin(sqrt(DeltaLatSin * DeltaLatSin + cos(LatRad1) * cos(LatRad2) * DeltaLonSin * DeltaLonSin));
    const double EarthRadiusMiles = 3959.88;
    
    return 2 * EarthRadiusMiles * Computation;
}
// Provided function to calculate the distance in miles
double CMapRouter::HaversineDistance_2(TLocation src, TLocation dest)
{
    return HaversineDistance(std::get<0>(src), std::get<1>(src),std::get<0>(dest), std::get<1>(dest));;
}

// Provided function to calculate the bearing in degrees
double CMapRouter::CalculateBearing(double lat1, double lon1,double lat2, double lon2)
{
    auto DegreesToRadians = [](double deg){return M_PI * (deg) / 180.0;};
    auto RadiansToDegrees = [](double rad){return 180.0 * (rad) / M_PI;};
    double LatRad1 = DegreesToRadians(lat1);
    double LatRad2 = DegreesToRadians(lat2);
    double LonRad1 = DegreesToRadians(lon1);
    double LonRad2 = DegreesToRadians(lon2);
    double X = cos(LatRad2)*sin(LonRad2-LonRad1);
    double Y = cos(LatRad1)*sin(LatRad2)-sin(LatRad1)*cos(LatRad2)*cos(LonRad2-LonRad1);
    return RadiansToDegrees(atan2(X,Y));
}

// Loads the map, stops, and routes given the input streams
bool CMapRouter::LoadMapAndRoutes(std::istream &osm, std::istream &stops, std::istream &routes)
{
    // Your code HERE
    // bool isRead;
    CXMLReader osm_Reader(osm);
    SXMLEntity TempEntity;
    osm_Reader.ReadEntity(TempEntity, true);
    //std::cout << "5:" << std::endl;
    if(TempEntity.DType != (SXMLEntity::EType::StartElement) or (TempEntity.DNameData != "osm"))
    {
        return false;
    }
    //std::cout << "6:" << std::endl;
    while (!osm_Reader.End())
    {
        // std::cout << "4:" << std::endl;
        osm_Reader.ReadEntity(TempEntity, true);
        
        if (TempEntity.DType == SXMLEntity::EType::StartElement)
        {
            //std::cout << "5:" << std::endl;
            if(TempEntity.DNameData == "node")
            {
                TNodeID TempID = std::stoul(TempEntity.AttributeValue("id"));
                double TempLat = std::stod(TempEntity.AttributeValue("lat"));
                double TempLon = std::stod(TempEntity.AttributeValue("lon"));
                Node TempNode;
                TempNode.NodeID = TempID;
                TempNode.Location = std::make_pair(TempLat, TempLon);
                NodeTranslation[TempID] = Nodes.size();
                
                Nodes.push_back(TempNode);
                SortedNodeIDs.push_back(TempID);
            }
            
            //discussion
            else if (TempEntity.DNameData == "way")
            {
                bool isBus = false;
                bool OneWay = false;
                double SpeedLimit = 25.0;
                
                std::vector < TNodeID > WayNodes;
                while (!osm_Reader.End())
                {
                    osm_Reader.ReadEntity(TempEntity,true);
                    //std::cout << "2:" << std::endl;

                    if (TempEntity.DType == SXMLEntity::EType::StartElement)
                    {
                        //std::cout << "1:" << std::endl;

                        if (TempEntity.DNameData == "nd")
                        {
                            TNodeID ref = std::stoul(std::get<1>(TempEntity.DAttributes[0]));
                            auto LookUp = NodeTranslation.find(ref);
                            if(NodeTranslation.end()!= LookUp)
                            {
                                WayNodes.push_back(ref);
                            }
                        }
                        else if (TempEntity.DNameData == "tag")
                        {
                            auto Key = TempEntity.AttributeValue("k");
                            auto Value = TempEntity.AttributeValue("v");
                            if (Key == "maxspeed")
                            {
                                SpeedLimit = std::stod(Value);
                            }
                            else if (Key == "oneway")
                            {
                                OneWay = Value=="yes";
                            }
                        }
                    }
                    if (TempEntity.DType == SXMLEntity::EType::EndElement)
                    {
                        if (TempEntity.DNameData == "way")
                        {
                            break;
                        }
                    }
                }
                
                if (OneWay)
                {
                    for (size_t i=0; i<WayNodes.size()-1;i++){
                        Edge TempEdge;
                        TNodeID cur_Node = WayNodes[i];
                        TNodeID next_Node = WayNodes[i+1];
                        
                        TNodeIndex cur_Index = NodeTranslation.find(cur_Node)->second;
                        TNodeIndex next_Index = NodeTranslation.find(next_Node)->second;
                        
                        TempEdge.OtherNode = next_Index;
                        
                        double lat1 = std::get<0>(Nodes[cur_Index].Location);
                        double lon1 = std::get<1>(Nodes[cur_Index].Location);
                        
                        double lat2 = std::get<0>(Nodes[next_Index].Location);
                        double lon2 = std::get<1>(Nodes[next_Index].Location);
                        double distance = HaversineDistance(lat1,lon1,lat2,lon2);
                        
                        TempEdge.Distance = distance;
                        TempEdge.Speed = 3.0;
                        TempEdge.SpeedLimit = SpeedLimit;
                        TempEdge.Time = TempEdge.Distance/TempEdge.Speed;
                        TempEdge.isBusEdge = isBus;
                        
                        Nodes[cur_Index].Edges.push_back(TempEdge);
                    }
                    
                }
                else if (!OneWay){
                    for (size_t i=0; i<WayNodes.size()-1;i++){
                        Edge TempEdge;
                        TNodeID cur_Node = WayNodes[i];
                        TNodeID next_Node = WayNodes[i+1];
                        
                        TNodeIndex cur_Index = NodeTranslation.find(cur_Node)->second;
                        TNodeIndex next_Index = NodeTranslation.find(next_Node)->second;
                        
                        TempEdge.OtherNode = next_Index;
                        
                        double lat1 = std::get<0>(Nodes[cur_Index].Location);
                        double lon1 = std::get<1>(Nodes[cur_Index].Location);
                        
                        double lat2 = std::get<0>(Nodes[next_Index].Location);
                        double lon2 = std::get<1>(Nodes[next_Index].Location);
                        double distance = HaversineDistance(lat1,lon1,lat2,lon2);
                        
                        TempEdge.Distance = distance;
                        TempEdge.Speed = 3.0;
                        TempEdge.SpeedLimit = SpeedLimit;
                        TempEdge.Time = TempEdge.Distance/TempEdge.Speed;
                        TempEdge.isBusEdge = isBus;
                        
                        Nodes[cur_Index].Edges.push_back(TempEdge);
                    }
                    for (size_t j=WayNodes.size()-1; j>0; j--){
                        Edge TempEdge;
                        TNodeID cur_Node = WayNodes[j];
                        TNodeID next_Node = WayNodes[j-1];
                        
                        TNodeIndex cur_Index = NodeTranslation.find(cur_Node)->second;
                        TNodeIndex next_Index = NodeTranslation.find(next_Node)->second;
                        
                        TempEdge.OtherNode = next_Index;
                        
                        double lat1 = std::get<0>(Nodes[cur_Index].Location);
                        double lon1 = std::get<1>(Nodes[cur_Index].Location);
                        
                        double lat2 = std::get<0>(Nodes[next_Index].Location);
                        double lon2 = std::get<1>(Nodes[next_Index].Location);
                        double distance = HaversineDistance(lat1,lon1,lat2,lon2);
                        
                        TempEdge.Distance = distance;
                        TempEdge.Speed = 3.0;
                        TempEdge.SpeedLimit = SpeedLimit;
                        TempEdge.Time = TempEdge.Distance/TempEdge.Speed;
                        TempEdge.isBusEdge = isBus;
                        
                        Nodes[cur_Index].Edges.push_back(TempEdge);
                        //     std::string RouteName = Row[RouteIndex];
                        //     TStopID TempStopID = std::stoul(Row[StopIndex]);
                        //     //TNodeID TempNodeID = StopToNodeTranslation.find(TempStopID)->second;
                        //     TNodeIndex TempNodeIndex = StopToNodeTranslation.find(TempStopID)->second;
                        
                        //     if(TempRoute.Name != RouteName)
                        //     {
                        //         //std::cout<< "asdasdasdasd"<< std::endl;
                        //         if(!TempRoute.Name.empty())
                        //         {
                        //             //std::cout << "asdasd" << std::endl;
                        //             RouteTranslation[TempRoute.Name] = TempRoute;
                        //             SortedRouteNames.push_back(TempRoute.Name);
                        //         }
                        //         TempRoute.Name = RouteName;
                        //         TempRoute.StopIndices.clear();
                        //     }
                        //     TempRoute.StopIndices.push_back(TempNodeIndex);
                        // }                    
                    // if(!TempRoute.Name.empty())
                    // {
                    //     RouteTranslation[TempRoute.Name] = TempRoute;
                    //     SortedRouteNames.push_back(TempRoute.Name);
                    // }
                        
                    }
                }
            }
        }
    }
    
    std::sort(SortedNodeIDs.begin(),SortedNodeIDs.end());
    
    CCSVReader stops_Reader(stops);
    std::vector<std::string> Row;
    stops_Reader.ReadRow(Row);
    
    while (!stops_Reader.End())
    {
        // if(!Row.empty())
        // {
        stops_Reader.ReadRow(Row);
        stops_Vect.push_back(Row);
        
        TNodeID nodeid = std::stoul(Row[1]);
        TStopID stopid = std::stoul(Row[0]);
        //}
        NodeToStopTranslationByID[nodeid] = stopid;
        StopToNodeTranslationByID[stopid] = nodeid;
    }
    
    CCSVReader routes_Reader(routes);
    std::vector<std::string> Header;
    routes_Reader.ReadRow(Header);
    while (!routes_Reader.End())
    {
        routes_Reader.ReadRow(Header);
        routes_Vect.push_back(Header);
        // if(!Header.empty())
        // {
        if (RouteToStopTranslation.find(Header[0]) == RouteToStopTranslation.end())
        {
            std::vector<TStopID> SmallRouteVector;
            TStopID bus_stop = std::stoul(Header[1]);
            SmallRouteVector.push_back(bus_stop);
            RouteToStopTranslation[Header[0]] = SmallRouteVector;
            
            SortedRouteNames.push_back(Header[0]);
        }
        // }
        else if (RouteToStopTranslation.find(Header[0]) != RouteToStopTranslation.end())
        {
            RouteToStopTranslation.find(Header[0])->second.push_back(std::stoul(Header[1]));
        }
    }
    
    
    for (auto routes_Name : SortedRouteNames){
        Route TempRoute;
         TempRoute.Name = routes_Name;
        for (size_t j = 0; j< RouteToStopTranslation.find(routes_Name)->second.size()-1; j++)
        {
            TStopID cur_Stop = RouteToStopTranslation.find(routes_Name)->second[j];
            TStopID next_Stop = RouteToStopTranslation.find(routes_Name)->second[j+1];
            
            TNodeIndex currindex = NodeTranslation.find(StopToNodeTranslationByID.find(cur_Stop)->second)->second;
            TNodeIndex nextindex = NodeTranslation.find(StopToNodeTranslationByID.find(next_Stop)->second)->second;
            
            std::pair<TNodeID, TNodeID> BusEdge = std::make_pair(StopToNodeTranslationByID.find(cur_Stop)->second, StopToNodeTranslationByID.find(next_Stop)->second);
            std::vector<TNodeIndex> structnodevector;
            
            for (size_t z = currindex; z<nextindex; z++)
            {
                TNodeIndex index = z;
                structnodevector.push_back(index);
                for (size_t x = 0; x< Nodes[z].Edges.size(); x++)
                {
                    if (Nodes[z].Edges[x].OtherNode == z+1)
                    {
                        Nodes[z].Edges[x].isBusEdge = true;
                        Nodes[z].Edges[x].Speed = Nodes[z].Edges[x].SpeedLimit;
                        
                        if (Nodes[z].Edges[x].OtherNode != nextindex)
                        {
                            Nodes[z].Edges[x].Time = Nodes[z].Edges[x].Distance/Nodes[z].Edges[x].Speed;
                        }
                        else
                        {
                            Nodes[z].Edges[x].Time = Nodes[z].Edges[x].Distance/Nodes[z].Edges[x].Speed + double(30)/double(3600);
                        }
                        
                    }
                }
            }
             TempRoute.StopIndices = structnodevector;
            auto keyiter = HashNodeIDAndRoutes.find(BusEdge);
            if (keyiter == HashNodeIDAndRoutes.end())
            {
                std::vector<Route> structroutes_Vect;
                structroutes_Vect.push_back( TempRoute);
                HashNodeIDAndRoutes[BusEdge] = structroutes_Vect;
            }
            else if (keyiter != HashNodeIDAndRoutes.end())
            {
                HashNodeIDAndRoutes.find(BusEdge)->second.push_back( TempRoute);
            }
        }
        
    }
    std::sort(SortedRouteNames.begin(), SortedRouteNames.end());
    return true;
}

size_t CMapRouter::NodeCount() const
{
    // Your code HERE
    return SortedNodeIDs.size();
}

CMapRouter::TNodeID CMapRouter::GetSortedNodeIDByIndex(size_t index) const
{
    // Your code HERE
    return SortedNodeIDs[index];
}

CMapRouter::TLocation CMapRouter::GetSortedNodeLocationByIndex(size_t index) const
{
    // Your code HERE
    if(index >= SortedNodeIDs.size())
    {
        return std::make_pair(180.0, 360.0);
    }
    auto node_Id = SortedNodeIDs[index];
    //Node mynode;
    auto node_Index = NodeTranslation.find(node_Id)->second;
    return Nodes[node_Index].Location;
}

CMapRouter::TLocation CMapRouter::GetNodeLocationByID(TNodeID nodeid) const
{
    // Your code HERE
    auto node_Index = NodeTranslation.find(nodeid)->second;
    return Nodes[node_Index].Location;
}

CMapRouter::TNodeID CMapRouter::GetNodeIDByStopID(TStopID stopid) const
{
    // Your code HERE
    // return Nodes[StopToNodeTranslation.find(stopid)->second].NodeID;
    std::string str;
    unsigned long longrat;

    for (size_t i=0; i<stops_Vect.size(); ++i)
    {
        TStopID StopVecID = std::stol(stops_Vect[i][0]);
        if (StopVecID == stopid)
        {
            str = stops_Vect[i][1];
        }
    }
    longrat = std::stoul(str);
    return longrat;
    
}

size_t CMapRouter::RouteCount() const{
    // Your code HERE

    return SortedRouteNames.size();
}

std::string CMapRouter::GetSortedRouteNameByIndex(size_t index) const
{
    // Your code HERE

    return routes_Vect[index][0];
}

bool CMapRouter::GetRouteStopsByRouteName(const std::string &route, std::vector< TStopID > &stops)
{
    // Your code HERE

    for(size_t i=0; i<routes_Vect.size(); ++i){
        if (routes_Vect[i][0] == route)
        {
            TStopID stopID = std::stoul(routes_Vect[i][1]);
            stops.push_back(stopID);
        }
    }
    if (!stops.empty()){
        return true;
    }
    else
    {
        return false;
    }
}
// Finds the shortest path from the src node to dest node. The
// list of nodes visited will be filled in path. The return
// value is the distance in miles,
// std::numeric_limits<double>::max() is returned if no path
// exists.
double CMapRouter::FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path)
{
    // Your code HERE

    // From piazza and discussion
    std::vector <TNodeIndex> Heap;
    
    TNodeIndex src_Index = NodeTranslation.find(src)->second;;
    TNodeIndex dest_Index = NodeTranslation.find(dest)-> second;
    
    std::vector <double> Distance(Nodes.size(), std::numeric_limits<double>::max());
    std::vector <double> Previous(Nodes.size(), -1);
    

    
    Distance[src_Index] = 0;
    Previous[src_Index] = src_Index;
    
    auto Campare = [&Distance](TNodeIndex idx1, TNodeIndex idx2)
    {
        return Distance[idx1] > Distance[idx2];
        
    };
    
    Heap.push_back(src_Index);
    
    while(!Heap.empty()){
        make_heap(Heap.begin(), Heap.end(), Campare);
        TNodeIndex Current = Heap.front();

        pop_heap(Heap.begin(), Heap.end(), Campare);
        Heap.pop_back();
        for (auto TempEdge: Nodes[Current].Edges)
        {
            double AltDist = Distance[Current] + TempEdge.Distance;
            if (AltDist < Distance[TempEdge.OtherNode])
            {
                if (Distance[TempEdge.OtherNode] == std::numeric_limits<double>::max())
                {
                    Heap.push_back(TempEdge.OtherNode);
                }
                Distance[TempEdge.OtherNode] = AltDist;
                Previous[TempEdge.OtherNode] = Current;
            }
        }
    }
    std::stack <TNodeIndex> stack_Nodes;
    TNodeID cur_Index = dest_Index;
    stack_Nodes.push(cur_Index);
    while (Previous[cur_Index] != src_Index)
    {
        stack_Nodes.push(Previous[cur_Index]);
        cur_Index = Previous[cur_Index];
    }
    
    stack_Nodes.push(src_Index);
    while (!stack_Nodes.empty())
    {
        path.push_back(Nodes[stack_Nodes.top()].NodeID);
        stack_Nodes.pop();
    }
    return Distance[dest_Index];
}

// Finds the fastest path from the src node to dest node. The
// list of nodes and mode of transit will be filled in path.
// The return value is the time in hours,
// std::numeric_limits<double>::max() is returned if no path
// exists. When a bus can be taken it should be taken for as
// long as possible. If more than one bus can be taken for the
// same length, the one with the earliest route name in the
// sorted route names.
double CMapRouter::FindFastestPath(TNodeID src, TNodeID dest, std::vector< TPathStep > &path){

    std::string ways;
    std::string routes_Name;
    
    TNodeIndex src_Index = NodeTranslation.find(src)->second;;
    TNodeIndex dest_Index = NodeTranslation.find(dest)-> second;
    
    std::vector <double> Time(Nodes.size(), std::numeric_limits<double>::max());
    std::vector <double> Previous(Nodes.size(), -1);
    
    std::vector <TNodeIndex> Heap;
    
    Heap.push_back(src_Index);
    Time[src_Index] = 0;
    Previous[src_Index] = src_Index;
    
    auto Campare = [&Time](TNodeIndex idx1, TNodeIndex idx2){return Time[idx1] > Time[idx2];};
    
    //from professor nitta's office hour
    while(!Heap.empty())
    {
        make_heap(Heap.begin(), Heap.end(), Campare);
        auto Current = Heap.front();
        pop_heap(Heap.begin(), Heap.end(), Campare);
        
        Heap.pop_back();
        
        for (auto TempEdge: Nodes[Current].Edges)
        {
            double AltTime = Time[Current] + TempEdge.Time;
            if (AltTime < Time[TempEdge.OtherNode])
            {
                if (Time[TempEdge.OtherNode] == std::numeric_limits<double>::max())
                {
                    Heap.push_back(TempEdge.OtherNode);
                }
                Time[TempEdge.OtherNode] = AltTime;
                Previous[TempEdge.OtherNode] = Current;
            }
        }
    }

    std::stack <TNodeIndex> stack_Nodes;
    TNodeID cur_Index = dest_Index;
    stack_Nodes.push(cur_Index);

    while (Previous[cur_Index] != src_Index)
    {
        stack_Nodes.push(Previous[cur_Index]);
        cur_Index = Previous[cur_Index];
    }
    
    stack_Nodes.push(src_Index);
    std::vector<TNodeIndex> nodes_Index;
    
    while (!stack_Nodes.empty())
    {
        nodes_Index.push_back(NodeTranslation.find(Nodes[stack_Nodes.top()].NodeID)->second);
        stack_Nodes.pop();
    }
    
    std::vector<std::pair<TNodeID,TNodeID>> pairsNodeID_Map;
    path.push_back(std::make_pair("Walk", Nodes[nodes_Index[0]].NodeID));
    
    for (size_t i=0; i<nodes_Index.size()-1; i++)
    {
        TNodeIndex cur_Index = nodes_Index[i];

        TNodeIndex next_Index = nodes_Index[i+1];
        
        for (size_t j=0; j<Nodes[cur_Index].Edges.size(); j++)
        {
            if (Nodes[cur_Index].Edges[j].OtherNode == next_Index)
            {

                if (Nodes[cur_Index].Edges[j].Speed == double(3.0))
                {
                    ways = "Walk";
                    path.push_back(std::make_pair(ways,Nodes[nodes_Index[i+1]].NodeID));
                }
                else if (Nodes[cur_Index].Edges[j].Speed > double(3.0))
                {
                    ways = "Bus ";
                    
                    for (size_t z = next_Index+1; z < nodes_Index.size()-1; z++)
                    {
                        TBusEdge bus_Edges = std::make_pair(Nodes[next_Index].NodeID, Nodes[z].NodeID);
                        
                        auto cur_BusEdge = HashNodeIDAndRoutes.find(bus_Edges);
                        if (cur_BusEdge != HashNodeIDAndRoutes.end())
                        {
                            pairsNodeID_Map.push_back(bus_Edges);
                        }
                    }
                    if (pairsNodeID_Map.size() != 0)
                    {
                        std::vector<int> stop_Counter;
                        std::vector<int>::iterator result;
                        std::vector<TNodeIndex> routes_Vect;
                        
                        for (size_t keyIndex = 0; keyIndex<pairsNodeID_Map.size(); keyIndex++)
                        {
                            int count_Stops = std::get<1>(pairsNodeID_Map[keyIndex]) - std::get<0>(pairsNodeID_Map[keyIndex]);
                            stop_Counter.push_back(count_Stops);
                        }
                        
                        result = std::max_element(stop_Counter.begin(),stop_Counter.end());
                        
                        std::pair<TNodeID, TNodeID> fastest_Path = pairsNodeID_Map[std::distance(stop_Counter.begin(),result)];
                        
                        routes_Name = HashNodeIDAndRoutes.find(fastest_Path)->second[0].Name;
                        routes_Vect = HashNodeIDAndRoutes.find(fastest_Path)->second[0].StopIndices;
                        
                        TNodeIndex end = NodeTranslation.find(std::get<1>(fastest_Path))->second;
                        while (nodes_Index[i]!=end)
                        {
                            path.push_back(std::make_pair(ways+routes_Name,Nodes[nodes_Index[i+1]].NodeID));
                            i ++;
                        }
                        i --;
                    }
                }
            }
        }
    }
    
    return Time[dest_Index];
    
}

// Returns a simplified set of directions given the input path
bool CMapRouter::GetPathDescription(const std::vector< TPathStep > &path, std::vector< std::string > &desc) const
{
    // Your code HERE
    // From TA Nik's office hour
    bool isPath = false;
    std::string ways, nextBus, currentLatString, currentLonString, nextLatString, nextLonString, LatString, LonString;
    std::string DirectionString, direction, startString, endString;
    
    double currentLat, currentLon, nextLat, nextLon, Degrees;
    
    TNodeID currentNodeID, nextNodeID;
    
    TLocation currentNodeLocation, nextNodeLocation;

    currentNodeID = std::get<1>(path[0]);
    currentNodeLocation = GetNodeLocationByID(currentNodeID);
    
    currentLat = std::get<0>(currentNodeLocation);
    currentLon = std::get<1>(currentNodeLocation);
    
    LatString = FindLatString(currentLat);
    LonString = FindLonString(currentLon);
    
    DirectionString = "Start at " + LatString + LonString;
    desc.push_back(DirectionString);
    
    for(size_t i=0; i< path.size()-1; ++i)
    {
        // std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAA" << std::endl;

        ways = std::get<0>(path[i+1]);
        
        if ( i < path.size() -2)
        {
            // std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAA" << std::endl;
            nextBus = std::get<0>(path.at(i+2));
        }
        else
        {
            //std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAA" << std::endl;
            nextBus = std::get<0>(path.at(i+1));
        }
        
        currentNodeID = std::get<1>(path[i]);
        nextNodeID = std::get<1>(path[i+1]);
        
        currentNodeLocation = GetNodeLocationByID(currentNodeID);
        nextNodeLocation = GetNodeLocationByID(nextNodeID);

        currentLat = std::get<0>(currentNodeLocation);
        currentLon = std::get<1>(currentNodeLocation);
        
        nextLat = std::get<0>(nextNodeLocation);
        nextLon = std::get<1>(nextNodeLocation);
        
        
        Degrees = CalculateBearing(currentLat, currentLon, nextLat, nextLon);
        direction = CalculateDirection(Degrees);
        
        LatString = FindLatString(nextLat);
        LonString = FindLonString(nextLon);
        
        if(ways == "Walk")
        {
            DirectionString = "Walk " + direction + " to " + LatString + LonString;
            
        }
        else
        {
            if(nextBus == ways)
            {
                //std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAAconitue" << std::endl;
                continue;
            }
            else
            {
                //std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAA" << std::endl;
                DirectionString = "Take " + ways + " and get off at stop " + std::to_string(NodeToStopTranslationByID.find(nextNodeID)->second);
            }
        }
        
        desc.push_back(DirectionString);
    }
    
    DirectionString = "End at " + LatString + LonString;
    desc.push_back(DirectionString);
    // std::cout << "AAAAAAAAAAAsadasdasdaAAAAAAAAAAA" << std::endl;

    if(!desc.empty())
    {
        return true;
    }
    
    return isPath;
    
}
