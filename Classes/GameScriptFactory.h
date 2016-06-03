#pragma once

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

private:

    /*
    Constructor
    Author: ChuyangLiu
    */
    GameScriptFactory();
};
