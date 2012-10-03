//
//  init.h
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/1/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef Legends_of_Meru_init_h
#define Legends_of_Meru_init_h

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace bfs = boost::filesystem;

class Init {

    std::string configFile;
    int ac;
    const char * av;
    
    
public:
    
    Init(int argc, const char * argv);
    
    void ReadConfig();
    void CheckDirs();
    
    
    
};




#endif

