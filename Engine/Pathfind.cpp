//
//  Pathfind.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Pathfind.h"
#include <map>


using Core::Pathfind;
using Core::Node;


Pathfind::Pathfind() : moveMap(nullptr),
clearanceMap(nullptr),
beginNode(nullptr),
firstNode(nullptr)
{
    this->heuristicFunc=std::bind(&Pathfind::hMethod, this, std::placeholders::_1, std::placeholders::_2);   
    size=Vector2i(0, 0);
}
Pathfind::~Pathfind(){
    //Map and MoveMap is from parameter, i do not delete it
    delete clearanceMap;
    deleteNodeContent();

	clearanceMap = nullptr;
	firstNode = nullptr;
}
void Pathfind::setHeuristicFunction(std::function<int (Point2i origin, Point2i destiny)> heuristicFunc){
    this->heuristicFunc=heuristicFunc;
}
int Pathfind::analyzeNode(int* map, Point2i origin, Vector2i size){
    Vector2i position=origin;
    int clearance=0;
    int minSize=size.x<size.y?size.x:size.y;
    for(; clearance<minSize;++clearance){

        if(position.x+clearance>=size.x || position.y+clearance>=size.y)return clearance;
        if(map[(position.y*size.x) + position.x+clearance] < 0)return clearance;
        if(map[((position.y+clearance)*size.x) + position.x] < 0)return clearance;
    }
    return clearance;
}
int* Pathfind::returnWithClearance(int* map, Vector2i size){
    int* _map = new int[size.x*size.y];
    for(int position=0; position<size.x*size.y; ++position)
		//This will create a map with the clearances
        _map[position]=analyzeNode(map, Point2i(position%size.y, position/size.y), size);
    return _map;
}
bool Pathfind::isValid(Vector2i size, Point2i position){
    return size.x>position.x && size.y>position.y && position.x>=0 && position.y>=0;
}
void Pathfind::addNodeAndCheck(int* clearanceMap, int* movementMap, Vector2i size, Point2i origin, Node* node, std::vector<Node*>& ol, std::vector<Node*> cl, std::vector<int>& iol){
    //Here I will add a node, but I also need to check if I am not adding an node that already exists.
	//If I am I just get that node, from the closed list and add as a reference to another node.
	
	//This is the node that I am creating
	Node* tmpNode;
    
    if(isValid(size, Point2i(origin.x, origin.y))){
        //Cannot walk throught this node
        if(movementMap[origin.y*size.x+origin.x]<0)
			return;
        
        //If node was already analyzed I get the existing one
        tmpNode=cl.at(origin.y*size.x+origin.x);
        //if node is on the closed list I just get it
        if(tmpNode!=nullptr){
            node->addNode(tmpNode);
            return;
        }
        //If the node exists
        if(tmpNode==nullptr){
            for(auto& _ol : ol){
                //If the node I am searching for is on the openList I get it and proceed with the calculation
                if(_ol->getID() == Point2i(origin.x, origin.y)){
                    node->addNode(_ol);
                    return;
                }
            }
        }
        //If the node does not exists and is not on the open List I will create it, set the clearance, cost movement and add to the other lists
        if(tmpNode==nullptr)
            tmpNode=new Node(origin.x, origin.y);
        
        tmpNode->setClearance(clearanceMap[origin.y*size.x+origin.x]);
        tmpNode->setMovemenetCost(movementMap[origin.y*size.x+origin.x]);
        //Add as child, even if i already checked it
        node->addNode(tmpNode);

        if(cl.at(origin.y*size.x+origin.x)==nullptr && iol.at(origin.y*size.x+origin.x)==0){
            ol.push_back(tmpNode);
            iol.at(origin.y*size.x+origin.x)=1;
        }
    }
}
Node* Pathfind::generateNodes(int* clearanceMap, int* moveMap, Vector2i size){
    Node *node=new Node(0, 0);
    //! the openlist i check if it is empty, the iol i check if the element exists using the index.
    //open list
    std::vector<Node*> ol;
    //closed list
    std::vector<Node*> cl;
    
    //Fast access
    /*Just open list because on the open list I use the position (index) as a the index position to stop or continue to generate the nodes*/
    std::vector<int> iol;
    try{
        iol.reserve(size.x*size.y+1);
        cl.reserve(size.x*size.y+1);
        ol.reserve(size.x*size.y+1);
    }
    catch(...){
        std::cout << "Could not allocate enough memory" << std::endl;
        exit(1);
    }

    for(int x=0;x<=size.x*size.y;x++){
        iol.push_back(0);
        cl.push_back(nullptr);
    }

    ol.push_back(node);
    iol.at(0)=1;
    while(!ol.empty()){
        Node* current=ol.back();
        ol.pop_back();

		//Closed list, this contains all the nodes already analysed. If I already analysed this node, just skup
        if(cl.at(current->getID().y*size.x + current->getID().x)!=nullptr)
            continue;

        cl.at(current->getID().y*size.x + current->getID().x)=current;
        
        Point2i origin=current->getID();
		//Lets set the clearance for this node
        current->setClearance(clearanceMap[origin.y*size.x + origin.x]);
        
		//Here I will add the 4 positions, those 4 positions are the origins that will lead to this node.
        addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x+1, origin.y), current, ol, cl, iol);
        addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x, origin.y+1), current, ol, cl, iol);
    
        addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x-1, origin.y), current, ol, cl, iol);
        addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x, origin.y-1), current, ol, cl, iol);
        
		//If I have a diagonal I will create the nodes that represent the diagonal
        if(diagonal){
            addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x+1, origin.y-1), current, ol, cl, iol);
            addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x+1, origin.y+1), current, ol, cl, iol);
        
            addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x-1, origin.y+1), current, ol, cl, iol);
            addNodeAndCheck(clearanceMap, moveMap, size, Point2i(origin.x-1, origin.y-1), current, ol, cl, iol);
        }
        
    }
    return node;
}
Node* Pathfind::getBestOnList(std::vector<Node*>* openList, bool remove){
    if(openList->size()==0)
		return nullptr;
    
    std::vector<Node*>::iterator bIt=openList->begin(); //best node
    Node* bestNode=openList->at(0);
    for(auto it=openList->begin(); it!=openList->end(); it++){
        if((*it)->getFCost() < bestNode->getFCost()){
            bIt=it;
            bestNode=(*it);
        }
    }
    if(remove)
        openList->erase(bIt);
    return bestNode;
}
int Pathfind::hMethod(Point2i origin, Point2i destiny){
    if(!diagonal)return (abs(origin.x-destiny.x)+abs(origin.y-destiny.y));
    else return sqrt((pow(abs(origin.x-destiny.x), 2)+pow(abs(origin.y-destiny.y), 2)));
}
void Pathfind::initMatrix(Vector2i size,  int* moveMap, bool diagonal){
    this->diagonal=diagonal;

    this->moveMap=moveMap;
    this->size=size;
    
	//From the movementMap that the developer provides I will calculate the clearance
    clearanceMap=returnWithClearance(moveMap, Vector2i(size.x, size.y));
	//After that, I will create a graph from the movementMap
    firstNode=generateNodes(clearanceMap, moveMap, size);
    beginNode=firstNode;
}
void Pathfind::initMatrix(Vector2i size,  int** moveMap, bool diagonal){
    int* tmpMoveMap=new int[size.x*size.y];
    for(int index=0; index<size.x*size.y; ++index){
        tmpMoveMap[index]=moveMap[index%size.x][index/size.y];
    }
    initMatrix(size, tmpMoveMap, diagonal);
}
void Pathfind::setOrigin(Point2i origin){
    std::vector<Node*> nodeList;
    Node* current;
    nodeList.reserve(size.x*size.y);
    for(int x=0;x<size.x*size.y;++x)
        nodeList.push_back(nullptr);
    
    std::vector<Node*> ol;
    ol.push_back(beginNode);
    while(!ol.empty()){
        current=ol.back();
        ol.pop_back();
        if (current->getID()==origin){
            beginNode=current;
            return;
        }
        if(nodeList.at(current->getID().y*size.x + current->getID().x)!=nullptr)
            continue;
        
        nodeList.at(current->getID().y*size.x + current->getID().x)=current;
        
        for(const auto& _node : current->getNodes()){
            if(nodeList.at(_node->getID().y*size.x + _node->getID().x)!=nullptr)
                continue;
            ol.push_back(_node);
        }
    }
}
Node* Pathfind::getFirstNode(){
    return this->firstNode;
}
Node* Pathfind::generatePathfind(Point2i origin, Point2i destiny, int clearance){
    //Load collision map on a separate function to generate the graphs
    //Create a weight map so the F cost is real
    if(Pathfind::moveMap==nullptr || Pathfind::size!=size)
        return nullptr;
    
    if(origin!=beginNode->getID())
        setOrigin(destiny);
    
    int tmpCost=-1;
    std::vector<Node*> cl, ol;
    std::vector<int> icl, iol;
    for(int x=0;x<size.x*size.y;x++){
        icl.push_back(0);
        iol.push_back(0);
    }
    Node* current;
    beginNode->setFCost(beginNode->getGCost()+heuristicFunc(destiny, origin));
    beginNode->setGCost(0);
    ol.push_back(beginNode);
    while(!ol.empty()){
        //Here i remove the node and then return it (bool remove = true)
        current=getBestOnList(&ol);
        if(current->getID().x==origin.x && current->getID().y==origin.y)
            return current;
        
        cl.push_back(current);
        icl.at(current->getID().y * size.x + current->getID().x)=1;
        if(current->getClearance() < clearance)
            continue;
        
        for(int x=0;x<current->getNodes().size();x++){
            Node* openNode=current->getNodes().at(x);
            
            tmpCost=openNode->getMovementCost()+current->getGCost()+heuristicFunc(current->getID(), openNode->getID());
            
            if(icl.at(openNode->getID().y*size.x+openNode->getID().x)==1 || openNode->getClearance()<clearance)
                continue;

            if(iol.at(openNode->getID().y*size.x+openNode->getID().x)==0 || tmpCost < openNode->getGCost()){
                openNode->setParent(current);
                openNode->setGCost(tmpCost);
                openNode->setFCost(openNode->getGCost()+heuristicFunc(openNode->getID(), origin));
                if(iol.at(openNode->getID().y*size.x+openNode->getID().x)==1)
                    continue;
                iol.at(openNode->getID().y*size.x+openNode->getID().x)=1;
                ol.push_back(openNode);
            }
        }
    }
    return nullptr;
}
void Pathfind::deleteNodeContent(){
    std::vector<Node*> nodeList;
    if(this->beginNode==nullptr)
        return;
    Node* current;
    nodeList.reserve(size.x*size.y);
    for(int x=0;x<size.x*size.y;x++)
        nodeList.push_back(nullptr);
    
    std::vector<Node*> ol;
    ol.push_back(this->firstNode);
    while(!ol.empty()){
        current=ol.back();
        ol.pop_back();
        
        if(nodeList.at(current->getID().y*size.x + current->getID().x)!=nullptr)
            continue;
        
        nodeList.at(current->getID().y*size.x + current->getID().x)=current;
        
        for(const auto& _node : current->getNodes()){
            if(nodeList.at(_node->getID().y*size.x + _node->getID().x)!=nullptr)
                continue;
            ol.push_back(_node);
        }
    }
    for(const auto& _node : nodeList){
        if(_node==nullptr){
            continue;
        }
        delete _node;
    }
}