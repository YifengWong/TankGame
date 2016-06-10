#pragma once

#include <string>
#include <vector>

/*
A class that parse the game script
This is a singleton class
*/
class GameScriptFactory {
public:
    // Checkpoint struct declaration
    enum EnemyType {
        NORMAL,
        BOSS
    };

    struct EnemyObj {
        EnemyType type;
        unsigned enemyRow;
        unsigned enemyCol;
    };

    struct WallObj {
        bool breakable;
        unsigned wallRow;
        unsigned wallCol;
    };

    struct Stage {
        unsigned player1Row;
        unsigned player1Col;
        unsigned player2Row;
        unsigned player2Col;
        std::vector<EnemyObj> enemies;
        std::vector<WallObj> walls;
    };

    /*
    Return the only instance
    Author: ChuyangLiu
    */
    static GameScriptFactory* getInstance();

    /*
    Preload game scripts
    Author: ChuyangLiu
    */
    void loadScripts();

    /*
    Return the checkpoints vector
    Author: ChuyangLiu
    */
    const std::vector<Stage>* getStages() const;

    /*
    Return the checkpoints size
    Author: ChuyangLiu
    */
    unsigned getStageCount() const;

private:

    /*
    Constructor
    Author: ChuyangLiu
    */
    GameScriptFactory();

    /*
    Get script content from file
    Author: ChuyangLiu
    */
    std::string getScriptFromFile(const std::string &filename);

    /*
    Parse the checkpoint file content
    Author: ChuyangLiu
    */
    void parseStageStr(const std::string &json);

    /*
    Load default checkpoint scripts
    Author: ChuyangLiu
    */
    void loadDefaultStageScript();

    // Checkpoints of the game
    std::vector<Stage> stages;

    // Script filename
    const char *CHECKPOINT_FILENAME = "script/stage.json";
    const char *CHECKPOINT_DEFAULT_FILENAME = "script/default_stage.json";
    // Script attributes
    const char *PLAYER_1_ROW_ATTR = "player1_row";
    const char *PLAYER_1_COL_ATTR = "player1_col";
    const char *PLAYER_2_ROW_ATTR = "player2_row";
    const char *PLAYER_2_COL_ATTR = "player2_col";
    const char *ENEMIES_ATTR = "enemies";
    const char *TYPE_ATTR = "type";
    const char *ENEMY_ROW_ATTR = "enemy_row";
    const char *ENEMY_COL_ATTR = "enemy_col";
    const char *WALLS_ATTR = "walls";
    const char *BREAKABLE_ATTR = "breakable";
    const char *WALL_ROW_ATTR = "wall_row";
    const char *WALL_COL_ATTR = "wall_col";
};
