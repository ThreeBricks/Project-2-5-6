#include <unordered_map>
class Node{
private:
    int val;
    mutable int inDegree;
    mutable std::unordered_map<const Node*,int> neighbors;
public:
    Node(const int num){
        val=num;
    }

    int getVal()const{
        return val;
    }
    void addNeighbor(const Node* n, int edgeWeight)const{
        if(n->getVal()!=val){
           neighbors[n]=edgeWeight;
        }
    }
    void removeNeighbor(const Node* n)const{
        if(neighbors.find(n)!=neighbors.end()){
            neighbors.erase(neighbors.find(n));
            return;
        }
    }

    bool operator==(const Node&n2)const{
        if(val==n2.getVal()){
            return true;
        }
        else{
            return false;
        }
    }
    std::unordered_map<const Node*,int> getNeighbors()const{
        return neighbors;
    }
    int getInDegree()const{
        return inDegree;
    }
    void updateInDegree()const{
        inDegree+=1;
        return;
    }
    void decreaseInDegree()const{
        inDegree-=1;
        return;
    }

};
struct NodeHash{
    public:
        size_t operator() (const Node& n) const{
            int val=n.getVal();
            return std::hash<int>()(val);
        }
};

struct NodeHashEqual{
    public:
        bool operator() (const Node& first, const Node& second) const{
            if(first.getVal()==second.getVal()){
                return true;
            }
            else{
                return false;
            }
        }
};

class Graph{
public:
    virtual void addNode(const int& nodeVal)=0;
    virtual std::unordered_set<Node*> getAllNodes()const=0;
    virtual std::vector<Node*> getAdjList()const=0;
};

