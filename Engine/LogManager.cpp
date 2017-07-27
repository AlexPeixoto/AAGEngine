//
//  LogManager.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 3/7/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "LogManager.h"

using namespace Debug;
using namespace std;

map<LogLevel, ofstream*> *LogManager::fileOpenPool = new map<LogLevel, ofstream*>();
map<LogLevel, ofstream*> *LogManager::devOpenPool = new map<LogLevel, ofstream*>();
map<LogLevel, ScreenLog*> *LogManager::screenOpenPool = new map<LogLevel, ScreenLog*>();
vector<pair<LogLevel, Destiny>>* LogManager::ld= new vector<pair<LogLevel, Destiny>>();
ofstream *LogManager::_stdout=nullptr;
string LogManager::levelPre[] = {"[ERROR]:", "[WARNING]:", "[MESSAGE]", "[UNKNOWN]"};

/*
 * Here i am able to add a lot of associations to Log -> Output.
 * If i want to associate to a file i just add the destinyFile parameter and it is added to the openPool
 */
void LogManager::addLevelDestiny(LogLevel logLevel, Destiny destiny, string destinyFile, bool isDevice){
    for(auto& _ld : *ld)
        if(_ld.first==logLevel && _ld.second==destiny)
            return;
    
    if (isDevice!=false && destinyFile.length()>0 && fileOpenPool->find(logLevel)!=fileOpenPool->end())
        return;
    
    if (isDevice==true && destinyFile.length()>0 && devOpenPool->find(logLevel)!=devOpenPool->end())
        return;
    if(destinyFile.length()>0){
        ofstream* ofs = new ofstream(destinyFile, ofstream::out);
        if(!ofs->is_open())
            throw std::runtime_error("Unable to open the file: " + destinyFile);
        
        if(isDevice!=true)fileOpenPool->insert(make_pair(logLevel, ofs));
        else devOpenPool->insert(make_pair(logLevel, ofs));
    }
    ld->push_back(make_pair(logLevel, destiny));
}
void LogManager::addLevelDestiny(LogLevel logLevel, Destiny destiny, ScreenLog *screen){
    for(auto& _ld : *ld)
        if(_ld.first==logLevel && _ld.second==destiny)
            return;
    ld->push_back(make_pair(logLevel, destiny));
    screenOpenPool->insert(make_pair(logLevel, screen));
    
}
void LogManager::removeLevelDestiny(LogLevel logLevel, Destiny destiny){
    ld->erase(
              remove_if(ld->begin(), ld->end(), [=](pair<LogLevel, Destiny>& _ld) -> bool{ return _ld.first==logLevel && _ld.second==destiny;}),
              ld->end()
              );

    if(destiny==Destiny::File) {
        for(auto i=fileOpenPool->begin(); i!= fileOpenPool->end(); i++)
            if((*i).first==logLevel){
                if(i->second->is_open())
                    i->second->close();
        //        delete i->second;
            }
        fileOpenPool->erase(logLevel);
    }
#ifndef _WIN32
    else if(destiny==Destiny::Device) {
        for(auto i=devOpenPool->begin(); i!= devOpenPool->end(); i++)
            if((*i).first==logLevel){
                if(i->second->is_open())
                    i->second->close();
               // delete i->second;
                
            }
        devOpenPool->erase(logLevel);
    }
#endif
    else if(destiny==Destiny::Screen){
        for(auto i=screenOpenPool->begin(); i!= screenOpenPool->end(); i++){
            if((*i).first==logLevel)
                delete i->second;
        }
        screenOpenPool->erase(logLevel);
    }
}