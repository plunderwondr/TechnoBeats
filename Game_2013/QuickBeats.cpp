#include "QuickBeats.h"
#include <windows.h>
sf::Image img_data;
GLuint *texture_handle = new GLuint[20];
float move;
bool up;
Model* weap = new Model;
Model* Level1 = new Model;
Model* title = new Model;
extern int weaptype;

//Default constructor
QuickBeats::QuickBeats(void)
{
	std::cout<<"Starting up..."<<std::endl;
	int x, y,z = 0;
	firsttime = true;
	firstbox = true;

	//Initialize all variables to 0
	cameraPosition.x = cameraPosition.y = cameraPosition.z =
		cameraTarget.x = cameraTarget.y = cameraTarget.z = 
		cameraUp.x = cameraUp.y = cameraUp.z = 0.0f;

	MenuObjects[0].loadObject("Menu/play.obj","Tex/test.png");
	MenuObjects[1].loadObject("Menu/exit.obj","Tex/test.png");
	
	LoadTexture("Galaxy.png",5);

	CameraPath.AddWaypoint(Vector3<float>(0.0,0.0,-20.0));
	CameraPath.AddWaypoint(Vector3<float>(-20.0,0.0,0.0));
	CameraPath.AddWaypoint(Vector3<float>(0.0,70.0,0.0));
	CameraPath.SetTime(6.0);

	CameraDir.AddWaypoint(Vector3<float>(0.0,0.0,1.0));
	CameraDir.AddWaypoint(Vector3<float>(1.0,0.0,0.0));
	CameraDir.AddWaypoint(Vector3<float>(0.0,-1.0,0.0));
	CameraDir.SetTime(6.0);

	CameraRight.AddWaypoint(Vector3<float>(1.0,0.0,0.0));
	CameraRight.AddWaypoint(Vector3<float>(0.0,0.0,-1.0));
	CameraRight.AddWaypoint(Vector3<float>(-1.0,0.0,0.0));
	CameraRight.SetTime(6.0);
}

//Default deconstructor
QuickBeats::~QuickBeats(void)
{
}

void QuickBeats::initializeMenu()
{
	temp.LoadMesh("NavMesh/MeshTest.obj");
	temp.FindPath(0);
	CurrentState = Menu;
	CurrentMenuSelect = 0;
	rotation = 0.0f;

	sound.loadSounds();
	menuLoop = false; 
	selectLoop = false;

	if((CurrentState == Menu) && menuLoop == false)
	{
		sound.menuMusic();
		menuLoop = true; 
		std::cout<<"Playing menu music"<<std::endl;
	}

	std::cout<<"Initializing Menu..."<<std::endl;

	if(firsttime)
	{
	title->loadModel("Menu/quickbeat.obj");
	title->loadTex("test.png");

	firsttime = false;
	}

	LoadTexture("Galaxy.png",5);
	
	Cam.Target.y = 0;
	Cam.Position.setPosition(0.0,0.0,20.0);
	Cam.cameraFrame.setDir(Vector3<float>(0.0,0.0,-1.0));
	Cam.cameraFrame.setRight(Vector3<float>(-1.0,0.0,0.0));
	Cam.cameraFrame.calcUp();

	//cameraPosition.setPosition(0.0,0.0,20);
	//cameraUp.setPosition(0.0,1.0,0.0);
	//cameraTarget.setPosition(0.0,0.0,0.0);

	EntityManager::GetInstance()->Terminate();
	//ParticleManager::GetInstance()->Terminate();
	//EventManager::GetInstance()->Terminate();
	MessageRelay::GetInstance()->Terminate();

	std::cout<<"Done."<<std::endl;
}

//Initialize the game
void QuickBeats::initializeGame()
{
	CurrentState = GameMode;
	std::cout<<"Releasing menu music..."<<std::endl;
	sound.releaseMenu();

	std::cout<<"Initializing Game..."<<std::endl;
	EventManager::GetInstance()->LoadEvents();
	//The following camera changes set up to a birds-eye view of the origin

	cameraUp.z = -1.0f;			//Set the up to be -1 in the Z-axis
	Cam.Target.y = 0;

	LoadModels();				//Load the models for the game
	
	player.setOrientation(Vector3<float>(0.0,0.0,-1.0));
	player.EntityFrame.setDir(Vector3<float>(0.0,0.0,-1.0));
	player.EntityFrame.setRight(Vector3<float>(1.0,0.0,0.0));
	player.EntityFrame.calcUp();

	player.initializePlayer();
	CameraPath.Start();
	CameraDir.Start();
	CameraRight.Start();
	updateTimer.restart();

	weap->loadModel("TestPower.obj");
	
	




//	   glMatrixMode(GL_MODELVIEW);
//glLoadIdentity();
//glMatrixMode(GL_PROJECTION);
//glLoadIdentity();
//glOrtho(0, 800, 0, 800, -1, 1);
////gluOrtho2D(-100, 100, -100, 100);
//glDisable(GL_DEPTH_TEST);
//glDisable(GL_CULL_FACE);
//glDisable(GL_TEXTURE_2D);
//glDisable(GL_LIGHTING);
//glColor3f(1, 1, 1);

	//selectLoop = false;
	gameLoop = false;
	if((CurrentState == GameMode) && gameLoop == false)
	{
		sound.gameMusic();
		gameLoop = true; 
		std::cout<<"Playing game music..."<<std::endl;
	}









	std::cout<<"Running."<<std::endl;
}

//Call all the draw functions
void QuickBeats::draw()
{
	//PreDraw and Post draw are Game functions, DrawGame is updated in this class
	PreDraw();

	if (CurrentState == Menu)
		DrawMenu();
	else if (CurrentState == GameMode)
		DrawGame();

	PostDraw();
}

//Draw the game
void QuickBeats::DrawGame()
{

	std::cout << player.Position.x << " X " << player.Position.y << " Y " << player.Position.z << " Z " << std::endl;
	if(firstbox)
	{
		MessageBoxA(0,"The game is starting!!", "Quick Beats Error Message", MB_OK );
		firstbox = false;
	}
	extern int TheScore;

	extern int Health;
	extern int Sheild;
	extern float LevelTimer;
	extern bool HaveTripple;
	extern float JamMeter;


	LevelTimer = LevelTimer + 0.03;


	//if(LevelTimer > 10 && LevelTimer < 30)
	//{

	//}

	//Set the camera position
	gluLookAt(Cam.Position.x, Cam.Position.y, Cam.Position.z,
			  Cam.Target.x, Cam.Target.y, Cam.Target.z,
			  Cam.cameraFrame.Up.x, Cam.cameraFrame.Up.y, Cam.cameraFrame.Up.z);

	//Read the models for the game
	EntityManager::GetInstance()->DrawEntities();
	














	glPushMatrix();
	glColor3f(1, 1, 1);
	scoredisplay (-50, -50, -110, 3, TheScore);
	glPopMatrix();

		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(0,-300, LevelTimer - 600);
			Level1->readObject();
		glPopMatrix();
	ParticleManager::GetInstance()->renderSystems();

	if(HaveTripple)
	{
	//if(Player.he
		glBindTexture(GL_TEXTURE_2D, texture_handle[4]);
		glPushMatrix();
			glColor3f(1, 1, 1);
			glTranslatef(45,20,45);
			weap->readObject();
		glPopMatrix();
		
	}

	if(JamMeter > 0)
	{
		JamMeter = JamMeter - 0.001;
	}
	glBindTexture(GL_TEXTURE_2D, texture_handle[2]); 
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-36.4,0,-41.5);
		
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-10.0f, 20.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-10.0f, 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-10.0f + (Health*2), 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-10.0f + (Health*2), 20.0f, 0.0f); 
		glEnd(); 
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texture_handle[3]); 
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-36.4,0,-36.5);
		
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-10.0f, 20.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-10.0f, 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-10.0f + (Sheild*2), 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-10.0f + (Sheild*2), 20.0f, 0.0f); 
		glEnd(); 
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texture_handle[4]); 
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(-36.4,0,0);
		
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-10.0f, 20.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-10.0f, 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(-8.0f + (JamMeter*2), 20.0f, 4.6f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(-8.0f + (JamMeter*2), 20.0f, 0.0f); 
		glEnd(); 
	glPopMatrix();


	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glBindTexture(GL_TEXTURE_2D, texture_handle[0]); 
	glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(0,0,0);
		
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-50.0f, 20.0f, -50.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-50.0f, 20.0f, 50.0f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(50.0f, 20.0f, 50.0f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(50.0f, 20.0f, -50.0f); 
		glEnd(); 
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texture_handle[1]);
	glPushMatrix();
		glColor3f(1, 1, 1);


		if(player.currentType == 0)
		{
			glTranslatef(-40,0,45.6);
		}
		else if(player.currentType == 1)
		{
			glTranslatef(-34,0,45.6);		
		}
		else
		{	
			glTranslatef(-45.5,0,45.6);
		}		
		
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-2.0f, 22.0f, -2.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-2.0f, 22.0f, 2.0f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(2.0f, 22.0f, 2.0f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(2.0f, 22.0f, -2.0f); 
		glEnd(); 
	glPopMatrix();





	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho( 0, 800 , 800 , 0, -1, 1 );				// Select Ortho Mode
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();


	if(LevelTimer > 40 && LevelTimer < 400)
	{
	glBindTexture(GL_TEXTURE_2D, texture_handle[6]); 
	glPushMatrix();
		//glColor3f(1, 0, 1);
		glTranslatef(0,0,0);
		//glRotatef(rotation,0.0,1.0,0.0);
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(200.0f, 600.0f, 0.0f); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(200.0f, 700.0f, 0.0f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(600.0f, 700.0f, 0.0f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(600.0f, 600.0f, 0.0f); 
		glEnd(); 
	glPopMatrix();
	}


	glMatrixMode( GL_PROJECTION );					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode( GL_MODELVIEW );					// Select Modelview
	glPopMatrix();		





}

void QuickBeats::DrawMenu()
{



	//Set the camera position
	gluLookAt(Cam.Position.x, Cam.Position.y, Cam.Position.z,
			  Cam.Target.x, Cam.Target.y, Cam.Target.z,
			  Cam.cameraFrame.Up.x, Cam.cameraFrame.Up.y, Cam.cameraFrame.Up.z);








	glBindTexture(GL_TEXTURE_2D, texture_handle[5]); 
	glPushMatrix();
		//glColor3f(1, 0, 1);
		glTranslatef(0,0,0);
		//glRotatef(rotation,0.0,1.0,0.0);
		glBegin(GL_QUADS); 
			glTexCoord2f(0.0f, 1.0f);glVertex3f(-50.0f, -50.0f, -30.0f); 
			glTexCoord2f(1.0f, 1.0f);glVertex3f(50.0f, -50.0f, -30.0f); 
			glTexCoord2f(1.0f, 0.0f);glVertex3f(50.0f, 50.0f, -30.0f); 
			glTexCoord2f(0.0f, 0.0f);glVertex3f(-50.0f, 50.0f, -30.0f); 
		glEnd(); 
	glPopMatrix();


		//glBindTexture(GL_TEXTURE_2D, texture_handle[6]);
		glPushMatrix();
			//glColor3f(1, 1, 1);
			glTranslatef(0,12,-3);
			title->readObject();
		glPopMatrix();



	if(move>1)
	{
		up = false;
	}
	if(move<0)
	{
		up = true;
	}
	

	for (int i = 0; i < 2; i++)
	{
		glPushMatrix();

		if (i == CurrentMenuSelect)
		{
			if(up)
			{
				move= move +0.001;
			}
			else
			{
				move= move -0.001;
			}
			//glRotatef(rotation,0.0,1.0,0.0);
			glTranslatef(0.0,0.0+move,0.0);
		}

		Vector3<float> start(0.0,2.5,0.0);

		Vector3<float> space(0.0,5.0,0.0);

		glTranslatef((start.x - space.x * i), (start.y - space.y * i), (start.z - space.z * i));
			glTranslatef((start.x - space.x), (start.y - space.y), (start.z - space.z));

		MenuObjects[i].readObject();
		glPopMatrix();
	}


	







}
//Update the game
void QuickBeats::update()
{
	if (CurrentState == Menu)
	{
		rotation+=0.05;
	}
	else if(CameraPath.GetRunning())
	{

		
//	glDisable(GL_LIGHTING);
//glColor3f(1, 1, 1);
//	glPushMatrix();
//	//glColor3f(1, 1, 1);
//	//		Vector3<float> start(0.0,2.5,0.0);
//
//	//	Vector3<float> space(0.0,5.0,0.0);
//	//glTranslatef((start.x - space.x), (start.y - space.y), (start.z - space.z));
//
//	glColor3f(1, 1, 1);
//
//	glTranslatef(0,0,0);
//	glBegin(GL_QUADS); 
//		glVertex3f(-10.0f, 0.0f, -10.0f); 
//		glVertex3f(-10.0f, 0.0f, 10.0f); 
//		glVertex3f(10.0f, 0.0f, 10.0f); 
//		glVertex3f(10.0f, 0.0f, -10.0f); 
//		std::cout<< "adadawhere";
//	glEnd(); 
//
//
//
//		glPopMatrix();
//
//glEnable(GL_DEPTH_TEST);

		time = updateTimer.getElapsedTime();
		updateTimer.restart();

		float dt = time.asSeconds();

		CameraPath.Update(dt);
		CameraDir.Update(dt);
		CameraRight.Update(dt);

		Cam.Position = CameraPath.GetCurrentPoint();
		Cam.cameraFrame.setDir(CameraDir.GetCurrentPoint());
		Cam.cameraFrame.setRight(CameraRight.GetCurrentPoint());
		Cam.cameraFrame.calcUp();
	}
	else
	{
		if (MessageRelay::GetInstance()->EndMessage())
		{
			MessageRelay::GetInstance()->ResetEnd();
			initializeMenu();
			//currentstate = menu;
			//DrawMenu();
			return;
		}

		time = updateTimer.getElapsedTime();
		updateTimer.restart();

		float dt = time.asSeconds();

		//EDIT COLLISION SO IT WORKS
		EntityManager::GetInstance()->CheckCollision();
		
		EntityManager::GetInstance()->UpdateEntities(dt);
		ParticleManager::GetInstance()->updateSystems(dt);
		EventManager::GetInstance()->Update(dt);



//glColor3f(1, 1, 1);
//	glPushMatrix();
//
//
//
//	glColor3f(1, 1, 1);
//
//	glTranslatef(0,0,0);
//	glBegin(GL_QUADS); 
//		glVertex3f(-50.0f, 0.0f, 50.0f); 
//		glVertex3f(50.0f, 0.0f, 50.0f); 
//		glVertex3f(50.0f, 0.0f, -50.0f); 
//		glVertex3f(-50.0f, 0.0f, -50.0f); 
//		std::cout<< player.Position.z << "\n";
//	glEnd(); 
//
//
//		glPopMatrix();

//		glDisable(GL_LIGHTING);
//glColor3f(1, 1, 1);
//	glPushMatrix();
//	//glColor3f(1, 1, 1);
//	//		Vector3<float> start(0.0,2.5,0.0);
//
//	//	Vector3<float> space(0.0,5.0,0.0);
//	//glTranslatef((start.x - space.x), (start.y - space.y), (start.z - space.z));
//
//	glColor3f(1, 1, 1);
//
//	glTranslatef(0,0,0);
//	glBegin(GL_QUADS); 
//		glVertex3f(-10.0f, 0.0f, -10.0f); 
//		glVertex3f(-10.0f, 0.0f, 10.0f); 
//		glVertex3f(10.0f, 0.0f, 10.0f); 
//		glVertex3f(10.0f, 0.0f, -10.0f); 
//		std::cout<< "adadawhere";
//	glEnd(); 
//
//
//
//		glPopMatrix();
//
//glEnable(GL_DEPTH_TEST);





	}
}

void QuickBeats::checkCollision()
{
}

//When a key is pressed
void QuickBeats::keyboardDown(unsigned int key, int mouseX, int mouseY)
{
	//Check which key was pressed
	if (CurrentState == Menu)
	{
		switch (key)
		{
			//If the key is Escape, close the game
			case sf::Keyboard::Escape:
				exit(1);
				sound.releaseMenu();
				break;
		}
	}
	else if (CurrentState == GameMode)
	{
		switch (key)
		{
			//If the key is Escape, close the game
			case sf::Keyboard::Escape:
				exit(1);
				sound.releaseGame();
				break;

			//Player movement input
			case sf::Keyboard::Left:
				z = z + 5;
				player.userInput.Left = true;
				break;
			case sf::Keyboard::Right:
				z = z - 5;
				player.userInput.Right = true;
				break;
			case sf::Keyboard::Up:
				player.userInput.Up = true;
				break;
			case sf::Keyboard::Down:
				player.userInput.Down = true;
				break;

			//Fire the player's current weapon
			case sf::Keyboard::Space:
				player.Fire();
				player.userInput.Space = true;
				break;

			//Change the current type (Techno, Rock, Classical) based on number keys
			case sf::Keyboard::Num1:
				weaptype = 2;
				player.currentType = 2;
				break;
			case sf::Keyboard::Num2:
				weaptype = 0;
				player.currentType = 0;
				break;
			case sf::Keyboard::Num3:
				weaptype = 1;
				player.currentType = 1;
				break;
				
			case sf::Keyboard::LShift:
				player.Activate();
				break;
		}
	}
}

//When a key is released
void QuickBeats::keyboardUp(unsigned int key, int mouseX, int mouseY)
{
	//Check which key is released
	if (CurrentState == Menu)
	{
		switch (key)
		{
			case sf::Keyboard::Up:
				if (CurrentMenuSelect != 0)
					CurrentMenuSelect--;
				else
					CurrentMenuSelect = 1;

				rotation = 0.0f;
				
				break;
			case sf::Keyboard::Down:
				if (CurrentMenuSelect != 1)
					CurrentMenuSelect++;
				else
					CurrentMenuSelect = 0;
				
				rotation = 0.0f;

				break;

			case sf::Keyboard::Space:
			case sf::Keyboard::Return:
				if ((CurrentMenuSelect == PlayGame) && selectLoop == false)
				{
					sound.optionMusic();
					selectLoop = true;
					initializeGame();
				}
				else if (CurrentMenuSelect == EndGame)
				{
					exit(1);
				}

				break;
		}
	}
	else if (CurrentState == GameMode)
	{
		switch (key)
		{
			case sf::Keyboard::Left:
				player.userInput.Left = false;
				break;
			case sf::Keyboard::Right:
				player.userInput.Right = false;
				break;
			case sf::Keyboard::Up:
				if (CurrentState == Menu)
				{
					if (CurrentMenuSelect != 0)
						CurrentMenuSelect--;
					else
						CurrentMenuSelect = 1;

					rotation = 0.0f;
				}
				else
				{
					player.userInput.Up = false;
				}
				break;
			case sf::Keyboard::Down:
				if (CurrentState == Menu)
				{
					if (CurrentMenuSelect != 1)
						CurrentMenuSelect++;
					else
						CurrentMenuSelect = 0;
					
					rotation = 0.0f;
				}
				else
				{
					player.userInput.Down = false;
				}
				break;

			case sf::Keyboard::Space:
				if (CurrentState == Menu)
				{
					if (CurrentMenuSelect == PlayGame)
					{
						initializeGame();
					}
					else if (CurrentMenuSelect == EndGame)
					{
						exit(1);
					}
				}
				else
				{
					player.userInput.Space = false;
				}
				break;
		}
	}
}

//When a mouse button is pressed
void QuickBeats::mouseClicked(unsigned int button, int x, int y)
{
	//Check which button is released
	switch (button)
	{
	}
}

//When a mouse button is released
void QuickBeats::mouseReleased(unsigned int button, int x, int y)
{
	//Check which button is released
	switch (button)
	{
	}
}

//When the mouse is moved
void QuickBeats::mouseMoved(int x, int y)
{
}

//Load in the models for the game
void QuickBeats::LoadModels()
{
	std::cout<<"Loading in Models..."<<std::endl;

	float floatHolder;

	char modelFile[32], texFile[32],statFile[32];							//Char arrays for the file names
	int fileEnd = 1;											//fileEnd, used for checking for end of file
	char line[32];												//Char array used for reading stream
	FILE* list;													//FILE pointer for the stream
	list = fopen("fileList.txt", "rt");							//Open a read-only stream to the file list and assign it to list

	//Loop until the end of the file
	while (fileEnd != EOF)
	{
		fileEnd = fscanf(list, "%s", line);						//Scan for a string and assign it to line

		//Check what the line is and act accordingly
		if (strcmp(line, "p:") == 0)							//In this case "t:" is "test"
		{
			fscanf(list, "%s %s", modelFile, texFile);			//Read the stream for the obj file and the texture file
			player.model = new Model(modelFile, texFile);
		}
		else if (strcmp(line,"e:") == 0)
		{
			fscanf(list,"%s %s %s", modelFile, texFile, statFile);
			Enemy tempE;
			tempE.model = new Model(modelFile, texFile);
			tempE.LoadStats(statFile);
			EventManager::GetInstance()->AddEnemy(tempE);
		}
		else if (strcmp(line,"i:") == 0)
		{
			fscanf(list,"%s %s %f", modelFile, texFile, &floatHolder);
			Item tempI;
			tempI.model = new Model(modelFile, texFile);
			tempI.CollisionBox.Type = ItemDrop;
			tempI.DropType = floatHolder;
			ItemSpawner::GetInstance()->AddItem(tempI);
		}
	}

	fclose(list);												//Close the stream

	glGenTextures(20, texture_handle);
	LoadTexture("UI800.png",0);
	LoadTexture("HighlightShoottype.png",1);
	LoadTexture("Health.png",2);
	LoadTexture("Sheild.png",3);	
	LoadTexture("JamMeter.png",4);
	LoadTexture("test.png",5);
	LoadTexture("popup.png",6);
	weap->loadTex("test.png");
	Level1->loadModel("Level/Lev1.obj");
	Level1->loadTex("Level/technoLevelUV.png");
	
	
	
}

void QuickBeats::LoadTexture(char* FileName, int TexNum)
{
	img_data.loadFromFile(FileName);
	glBindTexture(GL_TEXTURE_2D, texture_handle[TexNum]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void QuickBeats::scoredisplay (int posx, int posy, int posz, int space_char, int scorevar)
{
        int j=0,p,k;
        GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
       
        p = scorevar;
        j = 0;
        k = 0;
        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((posx-(j*space_char)),posy, posz);   
            glutBitmapCharacter(font_style1,48+k);
            j++;
            p /= 10;
        }
        glRasterPos3f ((posx-(j*space_char)), posy, posz);   
        glutBitmapCharacter(font_style1,48+p);
}