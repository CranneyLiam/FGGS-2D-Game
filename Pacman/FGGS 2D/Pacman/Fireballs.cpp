#include "pacman.h"
#include <time.h>
#include <sstream>

void Pacman::UpdateFireballs(int elapsedTime)
{
	for (int i = 0; i < _fireball.size(); i++)
	{
		if (_fireball[i]->direction == 1)
		{
			_fireball[i]->posRect->Y += _fireball[i]->speed * elapsedTime;
		}
		if (_fireball[i]->gone)
		{
			delete _fireball[i]->posRect;
			delete _fireball[i]->sourceRect;
			delete _fireball[i];
			_fireball.erase(_fireball.begin() + i);
		}
	}

}
void Pacman::CheckEnemyCollision()
{
	for (int i = 0; i < _fireball.size() && i < _enemy.size(); i++)
	{
		if (!_fireball[i]->gone)
		{
			if (_fireball[i]->posRect->Intersects(*_enemy[i]->posRect))
			{
				_fireball[i]->gone = true;
				_enemy[i]->dead = true;
				score = score + 100;
			}
		}
	}
	
}
void Pacman::SpawnFireball(Input::KeyboardState* state, Input::Keys spawnKey)
{

	if (state->IsKeyDown(Input::Keys::S) && !spawnKeyDown)
	{
		_fireball.push_back(new MovingEnemy());
		_fireball[_fireball.size() - 1]->direction = 1;
		_fireball[_fireball.size() - 1]->speed = 0.2f;
		_fireball[_fireball.size() - 1]->gone = false;
		_fireball[_fireball.size() - 1]->texture = new Texture2D();
		_fireball[_fireball.size() - 1]->texture->Load("Textures/Fireball.png", true);
		_fireball[_fireball.size() - 1]->posRect = new Rect(_pacman->position->X, _pacman->position->Y, 16, 32);
		_fireball[_fireball.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
		spawnKeyDown = true;
	}
	if (state->IsKeyUp(Input::Keys::S))
	{
		spawnKeyDown = false;
	}
}
void Pacman::DeleteFireball()
{
	for (int i = 0; i < _fireball.size(); i++)
	{
		if (!_fireball[i]->gone && (_fireball[i]->posRect->Y > Graphics::GetViewportHeight()))
		{
			delete _fireball[i]->posRect;
			delete _fireball[i]->sourceRect;
			delete _fireball[i];
			_fireball.erase(_fireball.begin() + i);
		}
	}
}