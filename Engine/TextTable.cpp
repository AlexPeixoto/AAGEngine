//
//  TextTable.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 9/14/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "TextTable.h"


using namespace Core;

string TextTable::relativePath="";

map<string, string> TextTable::text;
/* Load using the format
    Key
    Text Text Text Text
    Text Text Text Text
    EOK
    Key
    Text Text Text Text
    Text Text Text Text
    EOK
 */
void TextTable::loadFromFile(string path){
    string loadPath;
    if(relativePath.size()>0){
        size_t lastIndex=path.find_last_of("/");
        if(lastIndex!=string::npos)
            //if path have the / on the end
            loadPath=path[path.size()-1]=='/' ? relativePath+path.substr(lastIndex+1) : relativePath+"/"+path.substr(lastIndex+1);
        else
            loadPath=path[path.size()-1]=='/' ? relativePath+path : relativePath+"/"+path;
    }
    else
        loadPath=path;
#ifdef _WIN32
	std::replace(loadPath.begin(), loadPath.end(), '/', '\\');
#endif
    ifstream file(loadPath);
    if(!file.is_open())
        throw std::runtime_error("[TextTable] Impossible to load file: " + loadPath);
    string line;
    string key;
    stringstream text;
    int mode=0;
    while(!file.eof()){
        getline(file, line);
        if(mode==0){
            // Remove the : on the end of the key
            key=line.substr(0, line.length()-1);
            mode=1;
        }
        else if( mode==1 && line!="EOK" )
            text<<line;
        else if(line == "EOK"){
            map<string, string>::iterator it;
            if(((it=TextTable::text.find(key))!=TextTable::text.end())){
                it->second=text.str();
            }
            else
                TextTable::text.insert(make_pair(key, text.str()));
            text.str("");
            mode=0;
        }
    }
}
string TextTable::getByKey(string key){
    map<string, string>::iterator it;
    if(((it=TextTable::text.find(key))!=TextTable::text.end())){
        return it->second;
    }
    throw std::runtime_error("[TextTable] Could not find the key: " + key);
}
bool TextTable::addKeyValue(string key, string value){
    map<string, string>::iterator it;
    if(((it=TextTable::text.find(key))!=TextTable::text.end())){
        return false;
    }
    TextTable::text.insert(make_pair(key, value));
    return true;
}
bool TextTable::updateKeyValue(string key, string value){
    map<string, string>::iterator it;
    if(((it=TextTable::text.find(key))!=TextTable::text.end())){
        it->second=value;
        return true;
    }
    return false;
}
bool TextTable::removeKey(string key){
    map<string, string>::iterator it;
    if(((it=TextTable::text.find(key))!=TextTable::text.end())){
        TextTable::text.erase(it);
        return true;
    }
    return false;
    
}
void TextTable::removeAll(){
    TextTable::text.clear();
}
map<string, string> TextTable::getAllKeyValues(){
    return text;
}