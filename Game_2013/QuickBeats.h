#pragma once


#include "Game.h"
#include "EntityManager.h"
#include "ParticleManager.h"
#include "ItemSpawner.h"
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Item.h"
#include "MessageRelay.h"
#include "EventManager.h"
#include "Model.h"
#include "NavMesh.h"
#include "Camera.h"
#include "CatmullPath.h"
#include "OrientationPath.h"
#include "vars.h"
#include "GL/glut.h"
#include <SFML\OpenGL.hpp>
#include "SoundManager.h"

enum State{Menu, GameMode, Score};
enum MenuOptions{PlayGame, EndGame};




//QuickBeats class, inherits the Game class
class QuickBeats: public Game
{
public:

bool firstbox;
	//Default constructor
	QuickBeats(void);
	//Default deconstructor
	~QuickBeats(void);

	//Initialize the menu
	virtual void initializeMenu();

	//Initialize the game
	virtual void initializeGame();

	//Draw the game
	virtual void draw();

	//Draw functions, uncomment when they deviate from the original
	//virtual void PreDraw();			//Commented out because it is not unique
	virtual void DrawGame();
	void LoadTexture(char* , int );

	void scoredisplay (int, int, int, int, int);
	void DrawMenu();

	//virtual void PostDraw();			//Commented out because it is not unique
	
	//Update the game
	virtual void update();

	void checkCollision();

	//User inputs
	virtual void keyboardDown(unsigned int key, int mouseX, int mouseY);
	virtual void keyboardUp(unsigned int key, int mouseX, int mouseY);
	virtual void mouseClicked(unsigned int button, int x, int y);
	virtual void mouseReleased(unsigned int button, int x, int y);
	virtual void mouseMoved(int x, int y);

	//Load the models
	virtual void LoadModels();

	//Read the models
	//virtual void ReadModels();		//Commented out because it is not unique

	Controls playerControls;

	//Camera variables
	Vector3<float> cameraPosition;		//Position
	Vector3<float> cameraTarget;		//Target
	Vector3<float> cameraUp;			//Up

	Player player;


	bool firsttime;
	int CurrentState;
	int x ,y ,z;
	
	

	sf::Time time;
	sf::Clock updateTimer;

	Model MenuObjects[2];
	int CurrentMenuSelect;

	float rotation;

	//init sound 
	SoundManager sound;
	
	//bool for playing menu sound once
	bool menuLoop;
	bool gameLoop;
	bool selectLoop;

	Camera Cam;
	CatmullPath CameraPath;
	OrientationPath CameraDir;
	OrientationPath CameraRight;

	NavMesh temp;
};

