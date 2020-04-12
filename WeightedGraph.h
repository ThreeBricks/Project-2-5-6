class WeightedGraph: public Graph{
private:
    std::vector<Node*> adjList;
public:
    void addNode(const int& nodeVal){
        Node* newNode=new Node(nodeVal);
        adjList.push_back(newNode);
        return;
    }
    void addWeightedEdge(const Node* first, const Node* second,const int& edgeWeight){
        first->addNeighbor(second,edgeWeight);
        return;
    }
    void removeDirectedEdge(const Node*first, const Node* second){
        first->removeNeighbor(second);
        return;
    }
    std::unordered_set<Node*> getAllNodes()const{
        std::unordered_set<Node*> s;
        for(auto node: adjList){
            s.insert(node);
        }
        return s;
    }
    Node* getNode(const int& i){
        for(auto node:adjList){
            if(node->getVal()==i){
                return node;
            }
        }
        return NULL;
    }
    std::vector<Node*> getAdjList()const{
        return adjList;
    }

    void displayNodes(){
        for(auto node: adjList){
            std::cout<<node->getVal()<<" : ";
            for(auto neighNode: node->getNeighbors()){
                std::cout<<neighNode.first->getVal()<<":"<<neighNode.second<<" ";
            }
            std::cout<<std::endl;

        }
    }

};

