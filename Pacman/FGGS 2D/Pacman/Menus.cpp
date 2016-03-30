#include "pacman.h"
#include <time.h>
#include <sstream>

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys space)
{
	// Checks if Space key is pressed
	if (state->IsKeyDown(Input::Keys::SPACE) && !_menu->spaceKeyDown)
	{
		_menu->spaceKeyDown = true;
		_menu->start = !_menu->start; // Starts Game
	}

}
void Pacman::CheckRestart(Input::KeyboardState* state, Input::Keys space)
{
	if (state->IsKeyDown(Input::Keys::SPACE) && !_menu->spaceKeyDown)
	{
		_menu->spaceKeyDown = true;
		_menu->restart = !_menu->restart;
	}
}
void Pacman::CheckPaused(Input::KeyboardState* keyboardState, Input::Keys pauseKey)
{
	// Checks if P key is pressed
	if (keyboardState->IsKeyDown(Input::Keys::P) && !_menu->pKeyDown)
	{
		_menu->pKeyDown = true;
		_menu->paused = !_menu->paused; // Pauses Game
	}
	if (keyboardState->IsKeyUp(Input::Keys::P))
		_menu->pKeyDown = false;
}