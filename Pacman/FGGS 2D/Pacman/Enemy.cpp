#include "pacman.h"
#include <time.h>
#include <sstream>

void Pacman::SpawnEnemy(int elapsedTime)
{
	spawnTimer = elapsedTime;
	if (spawnTimer % 3 == 0)
	{
	_enemy.push_back(new Dwarf());
	_enemy[_enemy.size() - 1]->direction = 0;
	_enemy[_enemy.size() - 1]->speed = 0.01f;
	_enemy[_enemy.size() - 1]->dead = false;
	_enemy[_enemy.size() - 1]->texture = new Texture2D();
	_enemy[_enemy.size() - 1]->texture->Load("Textures/BrownDwarf.png", true);
	_enemy[_enemy.size() - 1]->posRect = new Rect(rand() % Graphics::GetViewportWidth(), Graphics::GetViewportHeight(), 32, 32);
	_enemy[_enemy.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 32, 32);
	}
	else
	{
	}
}

void Pacman::UpdateEnemy(int elapsedTime)
{
	for (int i = 0; i < _enemy.size(); i++)
	{
		if (_enemy[i]->direction == 0)
		{
			_enemy[i]->posRect->Y -= _enemy[i]->speed * elapsedTime;
		}
		if (_enemy[i]->direction == 1)
		{
			_enemy[i]->posRect->Y += _enemy[i]->speed * elapsedTime;
		}
		if (!_enemy[i]->dead)
		{
		//	if (_enemy[i]->posRect->Intersects(*_fireball[i]->posRect))
		//	{
		//		_enemy[i]->dead = true;
		//	}
			if (_enemy[i]->posRect->Intersects(*_pacman->position))
			{
				_enemy[i]->direction = 1;
			}
			if (_enemy[i]->dead)
			{
				delete _enemy[i]->posRect;
				delete _enemy[i]->sourceRect;
				delete _enemy[i];
				_enemy.erase(_enemy.begin() + i);
			}
		}
	}

}
void Pacman::DeleteEnemy()
{
	for (int i = 0; i < _enemy.size(); i++)
	{
		if (!_enemy[i]->dead && (_enemy[i]->posRect->Y > Graphics::GetViewportHeight()))
		{
			delete _enemy[i]->posRect;
			delete _enemy[i]->sourceRect;
			delete _enemy[i];
			_enemy.erase(_enemy.begin() + i);
		}
	}
}