# TankGame
A tank game written in cocos2d-x.

## Game script usage

You can design the checkpoints of the game through the script file "Resources/script/checkpoint.json".

The script is constructed as  a json array:

	[
		// Checkpoint 1 start
	    {
	        "player_row": 13,
	        "player_col": 2,
	        "enemies": [
	            {
	                "type": 0,
	                "enemy_row": 2,
	                "enemy_col": 23
	            }
	        ],
	        "walls": [
	            {
	                "breakable": true,
	                "wall_row": 0,
	                "wall_col": 7
	            }
	        ]
	    },
	    // Checkpoint 2 start
	    {
	        "player_row": 12,
	        "player_col": 2,
	        "enemies": [
	            {
	                "type": 0,
	                "enemy_row": 2,
	                "enemy_col": 21
	            },
	            {
	                "type": 1,
	                "enemy_row": 10,
	                "enemy_col": 10
	            },
	        ],
	        "walls": [
	        ]
	    }
	]
	
The game map is partitioned as 16*26 matrix. Each "*_row" and "*_col" json attribute describes the position of the sprite.

The above script create 2 checkpoints with different enemies and walls in it. The "type" attrbute describes the enemy type. Currently we only support 2 types of enemy so the value is only valid with 0 and 1.

WARNING: Don't modify the file "Resources/script/default_checkpoint.json" unless you know what you are doing.

## Links
* [Cocos2d-x stable versions](http://www.cocos2d-x.org/download)
* [Github: cocos2d/cocos2d-x: cocos2d-x for C++](https://github.com/cocos2d/cocos2d-x)
