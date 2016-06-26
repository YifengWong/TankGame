#pragma once

/*
Help Scene
*/
class HelpScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);

private:

	/*
	Inaccessible default constructor from outside the class.
	Use createScene() to create the instance from outside the class.
	Author: ChuyangLiu
	*/
	HelpScene() {}

	/*
	Add event listeners.
	Author: ChuyangLiu
	*/
	void addKeyboardListener();

	/*
	Add button to get help
	Author: YifengWong
	*/
	void addHelp();
};
