#include "Pacman.h"
#include <time.h>
#include <sstream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f), _cPacmanFrameTime(250)
{
	_pacman = new Player();
	_menu = new Menu();

	_menu->paused = false;
	_menu->pKeyDown = false;
	_menu->rKeyDown = false;
	_menu->start = true;
	_menu->spaceKeyDown = false;
	_pacman->direction = 0;
	_pacman->currentFrameTime = 0;
	_pacman->frame = 0;
	_pacman->dead = false;
	_menu->restart = false;
	gameOver = 0;
	score = 0;

	_pop = new SoundEffect();
	_pacman->speedMultiplier = 1.0f;

	//Initialise important Game aspects	
	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();

	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacman->texture;
	delete _pacman->sourceRect;

	for (int i = 0; i < _fireball.size(); i++)
	{
		delete _fireball[i]->posRect;
		delete _fireball[i]->sourceRect;
		delete _fireball[i];
		_fireball.erase(_fireball.begin() + i);
	}

	_fireball.clear();

	for (int i = 0; i < _arrows.size(); i++)
	{
		delete _arrows[i]->rect;
		delete _arrows[i]->sourceRect;
		delete _arrows[i];
		_arrows.erase(_arrows.begin() + i);
	}

	_arrows.clear();

	for (int i = 0; i < _enemy.size(); i++)
	{
		delete _enemy[i]->posRect;
		delete _enemy[i]->sourceRect;
		delete _enemy[i];
		_enemy.erase(_enemy.begin() + i);
	}

	_enemy.clear();
}

void Pacman::LoadContent()
{
	// Load Pacman
	_pacman->texture = new Texture2D();
	_pacman->texture->Load("Textures/Pacman.tga", false);
	_pacman->position = new Rect(512.0f - 16, 120.0f - 16, 32, 32);
	_pacman->sourceRect = new Rect(0.0f, 0.0f, 32, 32);

	 //Load Munchie
	for (int i = 0; i < _arrows.size(); i++)
	{
		_arrows[i]->texture = new Texture2D();
		_arrows[i]->texture->Load("Textures/ArrowSpriteShee.png", true);
		_arrows[i]->rect = new Rect(rand() % Graphics::GetViewportWidth(), rand() % Graphics::GetViewportHeight(), 16, 32);
		_arrows[i]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
	}

_pop->Load("Sounds/pop.wav");

// Set string position
_stringPosition = new Vector2(10.0f, 25.0f);
_background = new Texture2D();
_background->Load("Textures/Background.png", true);
_backgroundRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

// Set Menu Paramters
_menu->background = new Texture2D();
_menu->background->Load("Textures/Transparency.png", true);
_menu->rectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(),
	Graphics::GetViewportHeight());
_menu->stringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f - 82.0f,
	Graphics::GetViewportHeight() / 2.0f + 8.0f);

_leftBallista = new Texture2D();
_leftBallista->Load("Textures/Ballista.png", true);
_leftBallistaRectangle = new Rect(((Graphics::GetViewportWidth() / 8.0f) * 1) - 64.0f,
	Graphics::GetViewportHeight() / 2.0f, 128.0f, 128.0f);
_leftBallistaSourceRect = new Rect(0.0f, 0.0f, 128, 128);

_midLeftBallista = new Texture2D();
_midLeftBallista->Load("Textures/Ballista.png", true);
_midLeftBallistaRect = new Rect(((Graphics::GetViewportWidth() / 8.0f) * 3) - 64.0f,
	Graphics::GetViewportHeight() / 2.0f, 128.0f, 128.0f);
_midLeftBallistaSourceRect = new Rect(0.0f, 0.0f, 128, 128);

_midRightBallista = new Texture2D();
_midRightBallista->Load("Textures/Ballista.png", true);
_midRightBallistaRect = new Rect(((Graphics::GetViewportWidth() / 8.0f) * 5) - 64.0f,
	Graphics::GetViewportHeight() / 2.0f, 128.0f, 128.0f);
_midRightBallistaSourceRect = new Rect(0.0f, 0.0f, 128, 128);

_rightBallista = new Texture2D();
_rightBallista->Load("Textures/Ballista.png", true);
_rightBallistaRect = new Rect(((Graphics::GetViewportWidth() / 8.0f) * 7) - 64.0f,
	Graphics::GetViewportHeight() / 2.0f, 128.0f, 128.0f);
_rightBallistaSourceRect = new Rect(0.0f, 0.0f, 128, 128);

_rampart = new Texture2D();
_rampart->Load("Textures/Rampart.png", true);
_rampartPosRect = new Rect(0.0f, 0.0f, 1024, 236);
}

void Pacman::Update(int elapsedTime)
{
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();

	CheckStart(keyboardState, Input::Keys::SPACE);

	if (_pacman->dead)
	{
		CheckRestart(keyboardState, Input::Keys::SPACE);
	}

	if (!_menu->start)
	{
		CheckPaused(keyboardState, Input::Keys::P);

		if (!_menu->paused && gameOver != 10)
		{

			Input(elapsedTime, keyboardState, mouseState);

			UpdatePacman(elapsedTime);

			CheckViewportCollision();

			CheckArrowCollisions();

			UpdateFireballs(elapsedTime);

			SpawnFireball(keyboardState, Input::Keys::S);

			DeleteFireball();

			SpawnArrow();

			UpdateArrows(elapsedTime);

			SpawnEnemy(elapsedTime);

			UpdateEnemy(elapsedTime);

			DeleteEnemy();

			CheckEnemyCollision();

		}
	}

}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacman->position->X << " Y: " << _pacman->position->Y;

	SpriteBatch::BeginDraw(); //Starts Drawing
	SpriteBatch::Draw(_background, _backgroundRectangle, nullptr);

	SpriteBatch::Draw(_leftBallista, _leftBallistaRectangle);
	SpriteBatch::Draw(_midLeftBallista, _midLeftBallistaRect);
	SpriteBatch::Draw(_midRightBallista, _midRightBallistaRect);
	SpriteBatch::Draw(_rightBallista, _rightBallistaRect);

	SpriteBatch::Draw(_rampart, _rampartPosRect);

	for (int i = 0; i < _fireball.size(); i++)
	{
		if (!_fireball[i]->gone)
		{
			SpriteBatch::Draw(_fireball[i]->texture, _fireball[i]->posRect, _fireball[i]->sourceRect);
		}
	}

	for (int i = 0; i < _arrows.size(); i++)
	{
		if (!_arrows[i]->eaten)
		{
			SpriteBatch::Draw(_arrows[i]->texture, _arrows[i]->rect, _arrows[i]->sourceRect);
		}
	}
	for (int i = 0; i < _enemy.size(); i++)
	{
		if (!_enemy[i]->dead)
		{
			SpriteBatch::Draw(_enemy[i]->texture, _enemy[i]->posRect, _enemy[i]->sourceRect);
		}
	}
	// Draws String
	if (gameOver != 10)
	{
		SpriteBatch::Draw(_pacman->texture, _pacman->position, _pacman->sourceRect); // Draws Pacman
	}
	else
	{
		std::stringstream menuStream;
		menuStream << "Game Over" << endl;
		menuStream << "Score: " << score << endl; //Add Score Here
		SpriteBatch::Draw(_menu->background, _menu->rectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menu->stringPosition,
			Color::Green);
	}
	if (_menu->start)
	{
		std::stringstream menuStream;
		menuStream << "Press SPACE to Start";
		SpriteBatch::Draw(_menu->background, _menu->rectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _menu->stringPosition,
			Color::Green);
	}
	if (!_menu->start)
	{
		if (_menu->paused)
		{
			std::stringstream menuStream;
			menuStream << "PAUSED!";
			SpriteBatch::Draw(_menu->background, _menu->rectangle, nullptr);
			SpriteBatch::DrawString(menuStream.str().c_str(), _menu->stringPosition,
				Color::Red);
		}
	}

	SpriteBatch::EndDraw(); // Ends Drawing
}
void Pacman::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState)
{
	float pacmanSpeed = _cPacmanSpeed * elapsedTime * _pacman->speedMultiplier;

	if (state->IsKeyDown(Input::Keys::LEFTSHIFT))
	{
		_pacman->speedMultiplier = 3.0f;
	}
	else
	{
		_pacman->speedMultiplier = 1.0f;
	}

	// Checks if D key is pressed
	if (state->IsKeyDown(Input::Keys::D))
	{
		_pacman->position->X += pacmanSpeed; //Moves Pacman across X axis
		_pacman->direction = 0;
	}
	// Checks if S key is pressed
	//else if (state->IsKeyDown(Input::Keys::S))
	//{
	//_pacman->position->Y += pacmanSpeed; //Moves Pacman across Y axis
	//_pacman->direction = 1;
	//}

	// Checks if A key is pressed
	else if (state->IsKeyDown(Input::Keys::A))
	{
		_pacman->position->X -= pacmanSpeed; //Moves Pacman across X axis
		_pacman->direction = 2;
	}
	// Checks if W key is pressed
	//else if (state->IsKeyDown(Input::Keys::W))
	//{
	//	_pacman->position->Y -= pacmanSpeed; //Moves Pacman across Y axis
	//	_pacman->direction = 3;
	//}
}

void Pacman::UpdatePacman(int elapsedTime)
{
	_pacman->currentFrameTime += elapsedTime;
	if (_pacman->currentFrameTime > _cPacmanFrameTime)
	{
		_pacman->frame++;

		if (_pacman->frame >= 2)
			_pacman->frame = 0;

		_pacman->currentFrameTime = 0;
	}
	_pacman->sourceRect->X = _pacman->sourceRect->Width * _pacman->frame;

}
void Pacman::CheckViewportCollision()
{
	// Checks if Pacman is trying to disappear +X
	if (_pacman->position->X > Graphics::GetViewportWidth() + _pacman->sourceRect->Width) //1024 is game width
	{
		// Pacman hit right wall - reset his position
		_pacman->position->X = 0 - _pacman->sourceRect->Width;
	}

	// Checks if Pacman is trying to disappear -X
	if (_pacman->position->X < -33) //1024 is game width
	{
		// Pacman hit left wall - reset his position
		_pacman->position->X = Graphics::GetViewportWidth() + _pacman->sourceRect->Width - 1;
	}
	// Checks if Pacman is trying to disappear +Y
	if (_pacman->position->Y > Graphics::GetViewportHeight() + _pacman->sourceRect->Height) //768 is game height
	{
		// Pacman hit Bottom wall - reset his position
		_pacman->position->Y = 0 - _pacman->sourceRect->Height;
	}
	// Checks if Pacman is trying to disappear -Y
	if (_pacman->position->Y < -33) //768 is game height
	{
		// Pacman hit Top wall - reset his position
		_pacman->position->Y = Graphics::GetViewportHeight() + _pacman->sourceRect->Height - 1;
	}
	_pacman->sourceRect->Y = _pacman->sourceRect->Height * _pacman->direction; //Changes Direction of Sprite
}
