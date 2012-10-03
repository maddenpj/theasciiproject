//
//  init.cpp
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/1/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include "init.h"

Init::Init(int argc, const char * argv) {
    
    ac = argc;
    av = argv;
    
    ReadConfig();
    CheckDirs();
    
    
}


void Init::ReadConfig() {
    
    po::options_description optionsDesc("Allowed Options");
    
    optionsDesc.add_options()
    ("config,c", po::value<std::string>(&configFile)->default_value("server.conf"),"Configuration file, default is server.conf")
    ("help,h", "Display this help text")
    ("version,v", "Display version number")
    ;
    
    po::options_description config("Config File Options");
    //configFileOptions.add_options()
    
    po::options_description configFileOptions;
    configFileOptions.add(config);
    
    po::variables_map vm;
    po::store(po::parse_command_line(ac, &av, optionsDesc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        std::cout << optionsDesc << std::endl;
        //std::cout << config << std::endl;
        exit(0);
    }
    
}



void Init::CheckDirs() {
    
    bfs::path dataDir("data");
    bfs::path mapDir("maps");
    bfs::path scriptDir("scripts");
    
    if(!bfs::exists(dataDir))
        bfs::create_directory(dataDir);
    
    if(!bfs::exists(mapDir))
        bfs::create_directory(mapDir);
    
    if(!bfs::exists(scriptDir))
        bfs::create_directory(scriptDir);
    
    std::cout << "Directory Check Complete" << std::endl;
    
}