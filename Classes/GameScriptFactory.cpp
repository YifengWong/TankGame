#include "GameScriptFactory.h"

GameScriptFactory::GameScriptFactory() {
}

GameScriptFactory* GameScriptFactory::getInstance() {
    static GameScriptFactory instance;
    return &instance;
}
