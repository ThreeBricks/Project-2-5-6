#include <math.h>
bool isValid(const GridNode* first, const GridNode* second){
    if(first==NULL || second==NULL){
        return false;
    }
    else if(second->getY()==first->getY()+1 || second->getY()==first->getY()-1){
        if(second->getX()==first->getX()){
            return true;
        }
    }
    else if(second->getX()==first->getX()+1 || second->getX()==first->getX()-1){
        if(second->getY()==first->getY()){
            return true;
        }
    }
    return false;
}


class GridGraph{
private:
    std::vector<GridNode*> adjList;
public:
    void addNode(const int xVal, const int yVal,const std::string& nodeStr){
        GridNode* newNode=new GridNode(xVal,yVal,nodeStr);
        adjList.push_back(newNode);
        return;
    }
    void addUndirectedEdge(const GridNode* first, const GridNode* second){
        if(isValid(first,second)){
            first->addNeighbor(second);
            second->addNeighbor(first);
        }
        return;
    }
    void removeDirectedEdge(const Node*first, const Node* second){
        first->removeNeighbor(second);
        second->removeNeighbor(first);
        return;
    }
    std::unordered_set<GridNode*> getAllNodes()const{
        std::unordered_set<GridNode*> s;
        for(auto node: adjList){
            s.insert(node);
        }
        return s;
    }
    GridNode* getNode(const int x, const int y){
        for(auto node:adjList){
            if(node->getX()==x && node->getY()==y){
                return node;
            }
        }
        return NULL;
    }
    std::vector<GridNode*> getAdjList()const{
        return adjList;
    }

    void displayNodes(){
        int counter=0;
        int skip=sqrt(adjList.size());
        for(auto node: adjList){
            std::cout<<node->getVal()<<" ";
            counter++;
            if(counter%skip==0){
                std::cout<<std::endl;
            }

        }
    }
    void displayEdges(){
        for(auto node: adjList){
            for(auto neighNode: node->getNeighbors()){
                std::cout<<node->getVal()<<" "<<neighNode->getVal()<<" ";
            }
            std::cout<<std::endl;
        }
    }


};
