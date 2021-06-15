#ifndef MAPROUTER_H
#define MAPROUTER_H

#include <vector>
#include <istream>
#include <map>
#include <unordered_map>
#include <functional>
#include <utility>
#include <string>

// From professor Nitta's office hour
// We are going to use hash table
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;  
    }
};

class CMapRouter{
    public:
        using TNodeID = unsigned long;
        using TStopID = unsigned long;
        using TLocation = std::pair< double, double >;
        using TPathStep = std::pair< std::string, TNodeID >;
        using TBusEdge = std::pair< TNodeID, TNodeID >;
    
        static const TNodeID InvalidNodeID;
        static const double WalkSpeed;


        
    private:
        using TNodeIndex = int;
    
        struct Edge
        {
            bool isBusEdge;
            double Distance;
            double Time;
            double Speed;
            double SpeedLimit;
            TNodeIndex OtherNode;
        };

        struct Route
        {
            std::string Name;
            std::vector < TNodeIndex > StopIndices;
        };

        struct Node
        {
            TNodeID NodeID;
            TLocation Location;
            std::vector < Edge > Edges;
        };

        std::vector < Node > Nodes;
        std::vector< TNodeID > SortedNodeIDs;
        std::vector < std::string > SortedRouteNames;
    
        std::vector< std::vector<std::string> > stops_Vect;
        std::vector< std::vector<std::string> > routes_Vect;
    


        std::map < TNodeID , TNodeIndex > NodeTranslation;
    
        std::map <TNodeID,TStopID> NodeToStopTranslationByID;
        std::map < TStopID,TNodeID > StopToNodeTranslationByID;
        std::map <std::string, std::vector<TStopID>> RouteToStopTranslation;
    
        std::unordered_map<std::pair<TNodeID,TNodeID>, std::vector<CMapRouter::Route>, pair_hash> HashNodeIDAndRoutes;

public:
    CMapRouter();
    ~CMapRouter();
    
    static double HaversineDistance(double lat1, double lon1, double lat2, double lon2);
    static double HaversineDistance_2(TLocation src, TLocation dest);
    static double Dijkstra(TNodeIndex src, TNodeIndex dest, std::vector< TNodeIndex > &path, int searchtype);
    
    static double CalculateBearing(double lat1, double lon1,double lat2, double lon2);
    
    bool LoadMapAndRoutes(std::istream &osm, std::istream &stops, std::istream &routes);
    size_t NodeCount() const;
    TNodeID GetSortedNodeIDByIndex(size_t index) const;
    TLocation GetSortedNodeLocationByIndex(size_t index) const;
    TLocation GetNodeLocationByID(TNodeID nodeid) const;
    TNodeID GetNodeIDByStopID(TStopID stopid) const;
    size_t RouteCount() const;
    std::string GetSortedRouteNameByIndex(size_t index) const;
    bool GetRouteStopsByRouteName(const std::string &route, std::vector< TStopID > &stops);
    
    double FindShortestPath(TNodeID src, TNodeID dest, std::vector< TNodeID > &path);
    double FindFastestPath(TNodeID src, TNodeID dest, std::vector< TPathStep > &path);
    bool GetPathDescription(const std::vector< TPathStep > &path, std::vector< std::string > &desc) const;
};

#endif


