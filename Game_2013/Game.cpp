#include "Game.h"

//Default constructor
Game::Game()
{
	//Changes based on game

}

//Default deconstructor
Game::~Game()
{
	//Changes based on game
}

void Game::initializeMenu()
{
}

//Initialize the game
void Game::initializeGame()
{
	//Changes based on game
}

//Draw the game
void Game::draw()
{
	PreDraw();

	DrawGame();

	PostDraw();
}

//Update the game
void Game::update()
{
	//Changes based on game
}

//Prepare to draw
void Game::PreDraw()
{
	//Clear the screen and get ready to draw
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Draw
void Game::DrawGame()
{
	//Changes based on game
}

//Clean up
void Game::PostDraw()
{
	//Changes based on game
}

//Key pressed
void Game::keyboardDown(unsigned int key, int mouseX, int mouseY)
{
	//Changes based on game
}

//Key released
void Game::keyboardUp(unsigned int key, int mouseX, int mouseY)
{
	//Changes based on game
}

//Mouse clicked
void Game::mouseClicked(unsigned int button, int x, int y)
{
	//Changes based on game
}

//Mouse clicked
void Game::mouseReleased(unsigned int button, int x, int y)
{
	//Changes based on game
}

//Mouse moved
void Game::mouseMoved(int x, int y)
{
	//Changes based on game
}

//Load models
void Game::LoadModels()
{
	//Changes based on game
}

//Draw models
void Game::DrawModels()
{
	//Create an iterator for the model pointer vector and run through it
	for (std::vector<Model*>::iterator i = models.begin(); i != models.end(); i++)
	{
		Model *m = (*i);		//Assign the current index to a temporary model pointer
		m->readObject();		//Draw the model at the current index
	}
}