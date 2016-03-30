#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif
//#define MUNCHIECOUNT 10

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
struct Player
{
	// Data to represent Player
	Rect* position;
	Rect* sourceRect;
	Texture2D* texture;
	int direction;
	int frame;
	int currentFrameTime;
	float speedMultiplier;
	bool dead;

};
struct Enemy
{
	// Data to represent Arrows
	int frameCount;
	Rect* sourceRect;
	Rect* rect;
	Texture2D* texture;
	int currentFrameTime;
	int frameTime;
	int direction;
	float speed;
	bool eaten;
};
struct Menu
{
	// Data for Menu
	Texture2D* background;
	Rect* rectangle;
	Vector2* stringPosition;
	bool paused;
	bool pKeyDown;
	bool rKeyDown;
	bool start;
	bool spaceKeyDown;
	bool restart;
};
struct MovingEnemy 
{ 
	Rect* posRect;
	Rect* sourceRect;
	Texture2D* texture;
	int direction;
	float speed;
	bool gone;
	
};
struct Dwarf
{
	Rect* posRect;
	Rect* sourceRect;
	Texture2D* texture;
	int direction;
	float speed;
	bool dead;
	int frameTime;
	int frameCount;
	int currentFrameTime;

};
class Pacman : public Game
{
private:
	
	Player* _pacman;
	vector<Enemy*> _arrows;
	vector<MovingEnemy*> _fireball;
	vector<Dwarf*> _enemy;
	Menu* _menu;
	SoundEffect* _pop;
	bool spawnKeyDown;
	bool spawn;
	int spawnTimer;
	int gameOver;
	int score;

	Texture2D* _rampart;
	Rect* _rampartPosRect;

	// Position for String
	Vector2* _stringPosition;

	//Constant data for Game Variables
	const float _cPacmanSpeed;
	const int _cPacmanFrameTime;

	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);

	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);

	void CheckStart(Input::KeyboardState* state, Input::Keys space);

	void CheckViewportCollision();

	void UpdatePacman(int elapsedTime);

	void CheckArrowCollisions();

	void UpdateFireballs(int elapsedTime);

	void CheckRestart(Input::KeyboardState* state, Input::Keys space);

	void SpawnFireball(Input::KeyboardState* state, Input::Keys spawnKey);

	void DeleteFireball();

	void SpawnArrow();

	void UpdateArrows(int elapsedTime);

	void DeleteArrow();

	void LoadTextureFireball();

	void SpawnEnemy(int elapsedTime);

	void UpdateEnemy(int elpasedTime);

	void DeleteEnemy();

	void CheckEnemyCollision();


	Texture2D* _background;
	Rect* _backgroundRectangle;

	Texture2D* _leftBallista;
	Rect* _leftBallistaRectangle;
	Rect* _leftBallistaSourceRect;

	Texture2D* _midLeftBallista;
	Rect* _midLeftBallistaRect;
	Rect* _midLeftBallistaSourceRect;

	Texture2D* _midRightBallista;
	Rect* _midRightBallistaRect;
	Rect* _midRightBallistaSourceRect;

	Texture2D* _rightBallista;
	Rect* _rightBallistaRect;
	Rect* _rightBallistaSourceRect;


public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

};