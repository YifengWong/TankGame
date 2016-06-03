#include "GameScriptFactory.h"
#include "CCFileUtils.h"
#include <fstream>

using std::string;
using std::ifstream;
USING_NS_CC;

string GameScriptFactory::CHECKPOINT_FN = "script/checkpoint.json";

GameScriptFactory::GameScriptFactory() {
}

GameScriptFactory* GameScriptFactory::getInstance() {
    static GameScriptFactory instance;
    return &instance;
}

void GameScriptFactory::preloadScript() {
    string fullpath = FileUtils::getInstance()->fullPathForFilename(CHECKPOINT_FN);
    string content = FileUtils::getInstance()->getStringFromFile(fullpath);
    log(content.c_str());
}
