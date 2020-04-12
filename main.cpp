#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <random>
#include <cmath>
#include <stack>
#include <queue>
#include <time.h>
#include <utility>
#include "graph3.h"
#include "WeightedGraph.h"
#include "GridNode.h"
#include "GridGraph.h"
using namespace std;

WeightedGraph createRandomCompleteWeightedGraph(const int n){
    WeightedGraph wg;
    for(int i=0;i<n;i++){
        wg.addNode(i);
    }

    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            wg.addWeightedEdge(wg.getNode(i),wg.getNode(j),rand()%10+1);
        }
    }
    return wg;
}

WeightedGraph createLinkedList(const int n){
    WeightedGraph wg;
    for(int i=0; i<n;i++){
        wg.addNode(i);
    }
    for(int i=0; i<n-1;i++){
        wg.addWeightedEdge(wg.getNode(i),wg.getNode(i+1),1);
    }
    return wg;
}
std::unordered_map<const Node,int,NodeHash> dijkstras(const Node start){
    std::unordered_map<const Node,int,NodeHash> dmap;
    std::unordered_set<int> visited;
    dmap.insert(std::make_pair(start,0));
    Node curr=start;
    for(auto node:curr.getNeighbors()){
        dmap.insert(std::make_pair(*node.first,100));
    }
    int numNodes=start.getNeighbors().size()+1;
    while((int)visited.size()!=numNodes){
        int minDis=100;
        visited.insert(curr.getVal());
        for(auto node: curr.getNeighbors()){
            if(visited.find(node.first->getVal())==visited.end()){
                    dmap.find(*node.first)->second=std::min(node.second,node.second+dmap.find(curr)->second);
            }
        }
        for(auto node: dmap){
            if(node.second<minDis && visited.find(node.first.getVal())==visited.end()){
                minDis=node.second;
                curr=node.first;
            }
        }
    }
    return dmap;

}

GridGraph createRandomGridGraph(int n){
    GridGraph gg;
    for(int i=0;i<n;i++){
        for(int j=0; j<n;j++){
            std::string str=std::to_string(i)+std::to_string(j);
            gg.addNode(i,j,str);
        }
    }
    for(auto node: gg.getAllNodes()){
        if(rand()%2)
            gg.addUndirectedEdge(node,gg.getNode(node->getX()+1,node->getY()));
        if(rand()%2)
            gg.addUndirectedEdge(node,gg.getNode(node->getX()-1,node->getY()));
        if(rand()%2)
            gg.addUndirectedEdge(node,gg.getNode(node->getX(),node->getY()+1));
        if(rand()%2)
            gg.addUndirectedEdge(node,gg.getNode(node->getX(),node->getY()-1));
    }

    return gg;
}

int getHeuristic(const GridNode curr, const GridNode dest){
    return abs(dest.getX()-curr.getX())+abs(dest.getY()-curr.getY());

}

vector<GridNode> astar(const GridNode sourceNode, const GridNode destNode){
    vector<GridNode> ag;
    unordered_map<GridNode,GridNode,GridNodeHash> parentMap;
    unordered_map<GridNode,pair<int,int>,GridNodeHash> hmap;


    pair<int,int> dh=make_pair<int,int>(0,getHeuristic(sourceNode,destNode));
    hmap.insert(pair<GridNode,pair<int,int>>(sourceNode,dh));
    GridNode curr=sourceNode;
    while(curr!=destNode){
        GridNode oldcurr=curr;
        int gh=200;
        int counter=0;
        hmap.find(curr)->first.visit();
        for(auto node: curr.getNeighbors()){
            if(hmap.find(*node)==hmap.end()){
                pair<int,int> intPair=make_pair(hmap.find(curr)->second.first+1,getHeuristic(*node,destNode));
                pair<GridNode,pair<int,int>> insertPair=pair<GridNode,pair<int,int>>(*node,intPair);
                hmap.insert(insertPair);
                parentMap.insert(pair<GridNode,GridNode>(*node,curr));
            }
            if(!node->isVisited()){
                hmap[*node].first=min(hmap[curr].first+1,hmap[*node].first);
                if(hmap[curr].first+1<hmap[*node].first){
                    parentMap[*node]=curr;
                }
            }
        }
        for(auto nodePair: hmap){

            if(!nodePair.first.isVisited()){
                if(nodePair.second.first+nodePair.second.second<gh){
                    gh=nodePair.second.first+nodePair.second.second;
                    curr=nodePair.first;
                }
            }
        }
        if(curr==oldcurr){
            return ag;
        }
    }
    curr=destNode;
    ag.push_back(curr);
    while(curr!=sourceNode){
        ag.push_back(parentMap[curr]);
        curr=parentMap[curr];
    }
    vector<GridNode> ag2;
    for(vector<GridNode>::reverse_iterator it=ag.rbegin(); it!=ag.rend();it++){
        ag2.push_back(*it);
   }
    return ag2;
}

int main()
{
    WeightedGraph wg=createRandomCompleteWeightedGraph(500);
    for(auto node:dijkstras(*wg.getNode(1))){
        cout<<node.first.getVal()<<": "<<node.second<<endl;
    }
    GridGraph gg=createRandomGridGraph(100);
    GridNode sourceNode=*gg.getNode(0,0);
    GridNode destNode=*gg.getNode(99,99);

    vector<GridNode> vec=astar(sourceNode,destNode);
    if(vec.empty()){
        cout<<"No path"<<endl;
    }
    for(auto node: vec){
        cout<<node.getVal()<<endl;
    }
    return 0;
}
