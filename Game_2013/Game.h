#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>

#include "SFML\include\SFML\Graphics.hpp"
#include "SFML\include\SFML\Window.hpp"
#include "SFML\include\SFML\OpenGL.hpp"

#include "Vector.h"
#include "AnimationMath.h"

#include "Model.h"

//Define PI for calculations
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//RGBColor struct, used for color
typedef struct _RGBColor
{
	float red,green,blue;		//Floats for red, green, blue
}RGBColor;

//GameStateInfo struct, maintains clearscreen, gameState and other information
typedef struct _GameStateInfo
{
	int gameState;						//Current state
	RGBColor bgClearColor;				//Clear background color

	int windowWidth, windowHeight;		//The window size
	int screenWidth, screenHeight;		//The screen size

	float ratioWidth, ratioHeight;		//Ratio for screen-to-window
}GameStateInfo;

//Game Class
class Game
{
public:
	//Constructor
	Game(void);
	//Deconstructor
	~Game(void);

	virtual void initializeMenu();

	//initialize the game
	virtual void initializeGame();

	//Set the screen size with sent in parameters
	void setScreenSize(int w, int h)
	{
		//Update the game's screen size
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
	}

	//Update the screen ratio
	void updateScreenRation()
	{
		//Update ratio based on current sizes
		stateInfo.ratioWidth = stateInfo.screenWidth/(float)stateInfo.windowWidth;
		stateInfo.ratioHeight = stateInfo.screenHeight/(float)stateInfo.windowHeight;
	}

	//Set the window size with sent in parameters
	void setNewWindowSize(int width, int height)
	{
		//Update the game's window size
		stateInfo.windowHeight = height;
		stateInfo.windowWidth = width;
	}

	//Access all draw functions
	virtual void draw();
	//Update the game and all objects
	virtual void update();

	//Pre-draw the game (set up OpenGL stuff)
	virtual void PreDraw();
	//Draw the objects that need drawing
	virtual void DrawGame();
	//Post draw clean-up
	virtual void PostDraw();

	//If a key is pressed, send in key number and mouse position
	virtual void keyboardDown(unsigned int key, int mouseX, int mouseY);
	//If a key is released, send in key number and mouse position
	virtual void keyboardUp(unsigned int key, int mouseX, int mouseY);
	//If a mouse button is pressed, send in mouse button and position
	virtual void mouseClicked(unsigned int button, int x, int y);
	//If a mouse button is pressed, send in mouse button and position
	virtual void mouseReleased(unsigned int button, int x, int y);
	//If the mouse is moved, send in new position
	virtual void mouseMoved(int x, int y);

	//Load all the models for the game
	virtual void LoadModels();

	//Read all the models for the game
	virtual void DrawModels();

	//Variables
	GameStateInfo stateInfo;				//GameStateInfo

	std::vector<Model*> models;				//Dynamic array of all the models in the game
	//int score = 0;
};

#endif