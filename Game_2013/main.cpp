#include "GL/glew.h"
#include "QuickBeats.h"

//Define constants for the game such as FPS, Window size, etc.
/*********************************************************/
#define WINDOW_SCREEN_WIDTH 800
#define WINDOW_SCREEN_HEIGHT 800
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define FRAMES_PER_SECOND 30
const int FRAME_DELAY_SPRITE = 1000/FRAMES_PER_SECOND;
/*********************************************************/

int TheScore = 0;
int Health = 2;
int Sheild = 2;
int HitDelay = 300;
float JamMeter = 0;
int weaptype = 0;
bool HaveTripple = false;
float LevelTimer = 0;

//Create a new Game pointer
Game *theGame;

void init ()
{
	//Set the clear colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glClearDepth(1.f);

	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Enable 2D Textures
	glEnable(GL_TEXTURE_2D);
	
	//Enable Back Face Culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_BACK);

	//Set the viewport
	glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

	//Set the view type
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set the perspective
	gluPerspective(90.f,1.f,1.f,500.f);

	//Set the window and screen size for the game
	theGame->setNewWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	theGame->setScreenSize(WINDOW_SCREEN_WIDTH,WINDOW_SCREEN_HEIGHT);
}

int main()
{
	//Declare a new Window variable and initialize with these values. The Fullscreen is currently disabled
	sf::Window App(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Quick Beats"/*, sf::Style::Fullscreen*/);

	//Declare a new Event variable
	sf::Event Event;
glewInit();
	//Create a new game, using Polymorphism to access all the common functions that the 'QuickBeats' class has
	theGame = new QuickBeats();

	//Initialize OpenGL
	init();
	

	//Initialize the game
	theGame->initializeMenu();
	//theGame->initializeGame();

	//init fmod
	//SoundManager sound;
	//sound.loadSounds();
	//sound.playSound1();

	//Game Loop. Run while the Window is open
	while (App.isOpen())
	{
		//Clear the screen for drawing
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Check events such as key pressed, released, etc.
		while(App.pollEvent(Event))
		{
			//If the user tries to close the game, close it.
			if (Event.type == sf::Event::Closed)
				App.close();

			//When a key is pressed send the info to the game's keyboardDown function
			if (Event.type == sf::Event::KeyPressed)
				theGame->keyboardDown(Event.key.code, sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);//The Game key Press
			
			//When a key is released the info to the game's keyboardUp function
			if (Event.type == sf::Event::KeyReleased)
				theGame->keyboardUp(Event.key.code, sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);

			//When a mouse button is pressed send the info to the game's mouseClicked function
			if (Event.type == sf::Event::MouseButtonPressed)
				theGame->mouseClicked(Event.mouseButton.button, Event.mouseButton.x, Event.mouseButton.y);

			//When a mouse button is re;eased send the info to the game's mouseClicked function
			if (Event.type == sf::Event::MouseButtonReleased)
				theGame->mouseClicked(Event.mouseButton.button, Event.mouseButton.x, Event.mouseButton.y);

			if (Event.type == sf::Event::MouseMoved)
				theGame->mouseMoved(Event.mouseMove.y, Event.mouseMove.y);
		}
		//Go to the game's update function
		theGame->update();

		//Go to the game's draw function
		theGame->draw();

		//Display the window
		App.display();
	}

	//sound.releaseSounds();
	return EXIT_SUCCESS;
}