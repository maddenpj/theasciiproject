#pragma once
/*
 
 TileMap.h
 -Jon Rumion (yamamushi@gmail.com)
 2-25-2013
 
 Our TileMap class, used for storing Tiles...
 
 */

#include "../serialization/Boost_Serialization.h"
#include <memory>
#include <vector>
#include <string>
#include <mutex>
#include <boost/shared_ptr.hpp>
#include "Tile.h"


class TileMap : public std::enable_shared_from_this<TileMap>{
    
private:
    
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & length;
        ar & width;
        ar & virtualMap;
        ar & posX;
        ar & posY;
        ar & posZ;
    }
    
    int length, width;
    int posX, posY, posZ;
    
    int OwnerWorldID;

    std::mutex m_lock;
    
    void init();
    void fillSolid();
    
public:
    
    TileMap(){};
    TileMap(int l, int w, int posX, int posY, int posZ) : length(l), width(w), posX(posX), posY(posY), posZ(posZ){init();};
    
    std::vector< std::vector<boost::shared_ptr<Tile> > > virtualMap;
    
    void backupToDisk(std::string path);
    
    ~TileMap(){};
    
    void setOwnerWorldID(int ID){OwnerWorldID = ID;}
    
    // Mutex Functions
    bool attemptMLock(){return m_lock.try_lock();}
    void waitMLock(){m_lock.lock();} // This is called "waitMLock, because if our mutex is locked the call will block until its released.
    void releaseMLock(){m_lock.unlock();}
    
    // Dimension Functions
    int getLength(){return length;}
    int getWidth(){return width;}
    
    // Tile Functions
    Tile* getTilePtr(int x, int y){
        if(x >= length || y >= width) return nullptr;
        return virtualMap.at(x).at(y).get();
    }
    
    Tile* returnTile(int x, int y){return getTilePtr(x, y);}
    
    void setTileSymbol(int x, int y, int symbol){
        Tile *tmp = returnTile(x, y);
        if(tmp != nullptr)
            tmp->setSymbol(symbol);};
    
};

BOOST_SERIALIZATION_SHARED_PTR(TileMap)
//BOOST_CLASS_EXPORT(TileMap)
