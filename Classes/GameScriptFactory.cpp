#include "GameScriptFactory.h"
#include "CCFileUtils.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include <fstream>

using std::string;
using std::ifstream;
using rapidjson::Document;
using rapidjson::Value;
using cocos2d::FileUtils;
using cocos2d::log;

GameScriptFactory::GameScriptFactory() {
}

GameScriptFactory* GameScriptFactory::getInstance() {
    // According to C++11, static field constructor is thread-safe
    static GameScriptFactory instance;
    return &instance;
}

void GameScriptFactory::loadScripts() {
    stages.clear();
    string script = getScriptFromFile(CHECKPOINT_FILENAME);
    log(script.c_str());
    if (script.empty()) return;

    parseStageStr(script);  // Parse script content

    if (stages.empty()) {  // Parse failed
        loadDefaultStageScript();  // Load default scripts
    }
}

void GameScriptFactory::loadDefaultStageScript() {
    parseStageStr(getScriptFromFile(CHECKPOINT_DEFAULT_FILENAME));
}

void GameScriptFactory::parseStageStr(const std::string &json) {
    Document doc;
    doc.Parse<0>(json.c_str());
    if (doc.HasParseError() || !doc.IsArray()) {
        return;
    }

    for (unsigned i = 0; i < doc.Size(); ++i) {
        Value &cptVal = doc[i];
        if (!cptVal.IsObject()) {
            return;
        }

        Stage cpt;

        if (cptVal.HasMember(PLAYER_1_ROW_ATTR) && cptVal[PLAYER_1_ROW_ATTR].IsUint()) {
            cpt.player1Row = cptVal[PLAYER_1_ROW_ATTR].GetUint();
        } else {
            return;
        }
        if (cptVal.HasMember(PLAYER_1_COL_ATTR) && cptVal[PLAYER_1_COL_ATTR].IsUint()) {
            cpt.player1Col = cptVal[PLAYER_1_COL_ATTR].GetUint();
        } else {
            return;
        }
        if (cptVal.HasMember(PLAYER_2_ROW_ATTR) && cptVal[PLAYER_2_ROW_ATTR].IsUint()) {
            cpt.player2Row = cptVal[PLAYER_2_ROW_ATTR].GetUint();
        } else {
            return;
        }
        if (cptVal.HasMember(PLAYER_2_COL_ATTR) && cptVal[PLAYER_2_COL_ATTR].IsUint()) {
            cpt.player2Col = cptVal[PLAYER_2_COL_ATTR].GetUint();
        } else {
            return;
        }

        Value &enemiesArray = cptVal[ENEMIES_ATTR];
        if (enemiesArray.IsArray()) {
            for (unsigned i = 0; i < enemiesArray.Size(); ++i) {
                Value &val = enemiesArray[i];
                EnemyObj enemy;
                if (val.HasMember(TYPE_ATTR) && val[TYPE_ATTR].IsUint()) {
                    enemy.type = static_cast<EnemyType>(val[TYPE_ATTR].GetUint());
                } else {
                    return;
                }
                if (val.HasMember(ENEMY_ROW_ATTR) && val[ENEMY_ROW_ATTR].IsUint()) {
                    enemy.enemyRow = static_cast<EnemyType>(val[ENEMY_ROW_ATTR].GetUint());
                } else {
                    return;
                }
                if (val.HasMember(ENEMY_COL_ATTR) && val[ENEMY_COL_ATTR].IsUint()) {
                    enemy.enemyCol = static_cast<EnemyType>(val[ENEMY_COL_ATTR].GetUint());
                } else {
                    return;
                }
                cpt.enemies.push_back(enemy);
            }
        }

        Value &wallsArray = cptVal[WALLS_ATTR];
        if (wallsArray.IsArray()) {
            for (unsigned i = 0; i < wallsArray.Size(); ++i) {
                Value &val = wallsArray[i];
                WallObj wall;
                if (val.HasMember(BREAKABLE_ATTR) && val[BREAKABLE_ATTR].IsBool()) {
                    wall.breakable = static_cast<EnemyType>(val[BREAKABLE_ATTR].GetBool());
                } else {
                    return;
                }
                if (val.HasMember(WALL_ROW_ATTR) && val[WALL_ROW_ATTR].IsUint()) {
                    wall.wallRow = static_cast<EnemyType>(val[WALL_ROW_ATTR].GetUint());
                } else {
                    return;
                }
                if (val.HasMember(WALL_COL_ATTR) && val[WALL_COL_ATTR].IsUint()) {
                    wall.wallCol = static_cast<EnemyType>(val[WALL_COL_ATTR].GetUint());
                } else {
                    return;
                }
                cpt.walls.push_back(wall);
            }
        }

        stages.push_back(cpt);
    }
}

string GameScriptFactory::getScriptFromFile(const string &filename) {
    string fullpath = FileUtils::getInstance()->fullPathForFilename(filename);
    string content = FileUtils::getInstance()->getStringFromFile(fullpath);
    return content;
}

const std::vector<GameScriptFactory::Stage>* GameScriptFactory::getStages() const {
    return &stages;
}

unsigned GameScriptFactory::getStageCount() const {
    return stages.size();
}
