//
//  BackgroundMusic.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 8/23/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "BackgroundMusic.h"


using namespace Adventure;

Music* BackgroundMusic::playing = nullptr;
Music* BackgroundMusic::intersect = nullptr;

bool BackgroundMusic::onIntersection=false;
bool BackgroundMusic::breakIntersection=false;

string BackgroundMusic::relativePath="";

BackgroundMusic::~BackgroundMusic(){
    if(playing!=nullptr){
        delete playing;
        playing=nullptr;
    }
    if(intersect!=nullptr){
        delete intersect;
        intersect=nullptr;
    }
}
void BackgroundMusic::loadSong(string path){
    if(playing!=nullptr)
        throw std::runtime_error("There is a song playing already, please use close() method first, then load another song.");
    
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    playing = new Music();
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
    if(!playing->openFromFile(loadPath))
        throw std::runtime_error("Unable to open the file:" + loadPath);
}
bool BackgroundMusic::close(){
    if(playing==nullptr)
        throw std::runtime_error("There is not a song playing already, please use loadSong() method first.");
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    if(playing->getStatus()==SoundSource::Status::Playing){
        playing->stop();
        delete playing;
        playing=nullptr;
        return true;
    }
    return false;
}
bool BackgroundMusic::play(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    if(playing!=nullptr)
        playing->play();
    else return false;
    
    return true;
}
bool BackgroundMusic::restart(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    if(playing!=nullptr){
        playing->stop();
        playing->play();
        return true;
    }
    return false;
}
bool BackgroundMusic::resume(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    if(playing!=nullptr && playing->getStatus()==SoundSource::Status::Paused){
        playing->play();
        return true;
    }
    return false;
}

bool BackgroundMusic::stop(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    if(playing!=nullptr){
        playing->stop();
        return true;
    }
    return false;
}
bool BackgroundMusic::pause(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    if(playing!=nullptr){
        playing->pause();
        return true;
    }
    return false;
}

void BackgroundMusic::setloop(bool loop){
    playing->setLoop(loop);
}
bool BackgroundMusic::returnLoop(){
    return playing->getLoop();
}

void BackgroundMusic::setVolume(float volume){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    playing->setVolume(volume);
}
float BackgroundMusic::returnVolume(){
    if(BackgroundMusic::onIntersection)
        throw std::runtime_error("Every action is blocked until the intersection ends.");
    
    return playing->getVolume();
}

long BackgroundMusic::getPositionInSeconds(){
    return (long)playing->getPlayingOffset().asSeconds();
}
long BackgroundMusic::getDurationInSeconds(){
    return (long)playing->getDuration().asSeconds();
}
void BackgroundMusic::doBreakIntersection(){
    if(BackgroundMusic::onIntersection)
        breakIntersection=true;
}
//The moment the intersectWith is called the intersect will run until the music ends
void BackgroundMusic::intersectWith(string path, IntersectMode im, long long timeToEnd){
    if(BackgroundMusic::onIntersection==true){
        throw std::runtime_error("[Background Music] Cannot call intersectWith method more then one time.");
    }
    if(BackgroundMusic::playing==nullptr){
        throw std::runtime_error("[Background Music] Cannot call intersectWith without a music playing.");
    }
    
    intersect = new Music();
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

    if(!intersect->openFromFile(loadPath))
       throw std::runtime_error("[Background Music] Unable to open the file:" + loadPath + ".");
    
    thread th([=](){
        BackgroundMusic::onIntersection=true;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        long long elapsedMilliseconds;
        float baseVolume = playing->getVolume();
        float perMillisecond = baseVolume/(timeToEnd*1000);
        start = std::chrono::system_clock::now();
        
        if(im!=IntersectMode::NONE)
            intersect->setVolume(0);
        if(im!=IntersectMode::FADEPLAYING)
            intersect->play();
        while(true){
            //Force to break BackgroundMusic
            if(breakIntersection){
                playing->stop();
                intersect->stop();
                delete playing;
                playing=nullptr;
                delete intersect;
                intersect=nullptr;
                onIntersection=breakIntersection=false;
                break;
            }
            end = std::chrono::system_clock::now();
            elapsedMilliseconds=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
            
            if(im==IntersectMode::FADEPLAYING){
                playing->setVolume(baseVolume-elapsedMilliseconds*perMillisecond);
            }
            else if(im==IntersectMode::CROSS) {
                playing->setVolume(baseVolume-elapsedMilliseconds*perMillisecond);
                intersect->setVolume(elapsedMilliseconds*perMillisecond);
            }
            if(elapsedMilliseconds/1000>=timeToEnd){
                BackgroundMusic::playing->stop();
                if(im==IntersectMode::FADEPLAYING)
                    intersect->play();
                //Set the intersect volume to its final value
                BackgroundMusic::intersect->setVolume(baseVolume);
                delete BackgroundMusic::playing;
                BackgroundMusic::intersect->setLoop(BackgroundMusic::playing->getLoop());
                BackgroundMusic::playing=BackgroundMusic::intersect;
                BackgroundMusic::intersect=nullptr;
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        BackgroundMusic::onIntersection=false;
        
    });
    th.detach();
}
