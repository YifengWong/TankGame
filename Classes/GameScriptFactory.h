#pragma once

#include <string>

/*
A class that parse the game script
This is a singleton class
*/
class GameScriptFactory {
public:
    /*
    Return the only instance
    Author: ChuyangLiu
    */
    static GameScriptFactory* getInstance();

    /*
    Preload game scripts
    Author: ChuyangLiu
    */
    void preloadScript();

private:
    // Filename of the checkpoint script
    static std::string CHECKPOINT_FN;

    /*
    Constructor
    Author: ChuyangLiu
    */
    GameScriptFactory();
};
