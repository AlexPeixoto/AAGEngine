//
//  Node.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/13/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "Node.h"

using Core::Node;
Node::Node(int x, int y){
    id=Point2i(x, y);
    costF=costG=costMovement=MAX_COST;
    parent=nullptr;
}
Node::Node(Point2i ID):Node(ID.x, ID.y){
}
bool Node::addNode(Node* child){
    for(const auto& node : childNode){
        if(node->getID() == child->getID())
            return false;
    }
    childNode.push_back(child);
    return true;
}
bool Node::removeNode(Node* child){
    for(auto node=childNode.begin(); node!=childNode.begin();node++){
        if((*node)->getID() == child->getID()){
            childNode.erase(node);
            return true;
        }
    }
    childNode.push_back(child);
    return true;
}

Point2i Node::getID(){
    return this->id;
}
void Node::setID(int x, int y){
    this->id=Point2i(x, y);
}

vector<Node*> Node::getNodes() const{
    return this->childNode;
}

void Node::setCostF(int costF){
    this->costF=costF;
}
int Node::getCostF(){
    return costF;
}
void Node::setCostG(int costG){
    this->costG=costG;
}
int Node::getCostG(){
    return costG;
}
void Node::setParent(Node* parent){
    this->parent=parent;
}
Node* Node::getParent(){
    return parent;
}
void Node::setClearance(int clearance){
    this->clearance=clearance;
}
int Node::getClearance(){
    return clearance;
}

void Node::setCostMovement(int costMovement){
    this->costMovement=costMovement;
}
int Node::getCostMovement(){
    return costMovement;
}