#include "pacman.h"
#include <time.h>
#include <sstream>

void Pacman::CheckArrowCollisions()
{
	for (int i = 0; i < _arrows.size(); i++)
	{
		if (!_arrows[i]->eaten)
		{
			if (_arrows[i]->rect->Intersects(*_rampartPosRect))
			{
				_arrows[i]->eaten = true;
				Audio::Play(_pop);
				gameOver = gameOver + 1;
			}
		}
	}
}
void Pacman::SpawnArrow()
{
	{
		for (int i = 0; i < _enemy.size(); i++)
		{
			if (_enemy[i]->posRect->Intersects(*_leftBallistaRectangle) && !spawn)
			{
				_arrows.push_back(new Enemy());
				_arrows[_arrows.size() - 1]->direction = 0;
				_arrows[_arrows.size() - 1]->speed = 0.2f;
				_arrows[_arrows.size() - 1]->eaten = false;
				_arrows[_arrows.size() - 1]->texture = new Texture2D();
				_arrows[_arrows.size() - 1]->texture->Load("Textures/ArrowSpriteSheet.png", true);
				_arrows[_arrows.size() - 1]->rect = new Rect(_leftBallistaRectangle->X, _leftBallistaRectangle->Y, 16, 32);
				_arrows[_arrows.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
				spawn = true;
				_enemy[i]->direction = 1;
			}
			else if (_enemy[i]->posRect->Intersects(*_midLeftBallistaRect) && !spawn)
			{
				_arrows.push_back(new Enemy());
				_arrows[_arrows.size() - 1]->direction = 0;
				_arrows[_arrows.size() - 1]->speed = 0.2f;
				_arrows[_arrows.size() - 1]->eaten = false;
				_arrows[_arrows.size() - 1]->texture = new Texture2D();
				_arrows[_arrows.size() - 1]->texture->Load("Textures/ArrowSpriteSheet.png", true);
				_arrows[_arrows.size() - 1]->rect = new Rect(_midLeftBallistaRect->X, _midLeftBallistaRect->Y, 16, 32);
				_arrows[_arrows.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
				spawn = true;
				_enemy[i]->direction = 1;
			}
			else if (_enemy[i]->posRect->Intersects(*_midRightBallistaRect) && !spawn)
			{
				_arrows.push_back(new Enemy());
				_arrows[_arrows.size() - 1]->direction = 0;
				_arrows[_arrows.size() - 1]->speed = 0.2f;
				_arrows[_arrows.size() - 1]->eaten = false;
				_arrows[_arrows.size() - 1]->texture = new Texture2D();
				_arrows[_arrows.size() - 1]->texture->Load("Textures/ArrowSpriteSheet.png", true);
				_arrows[_arrows.size() - 1]->rect = new Rect(_midRightBallistaRect->X, _midRightBallistaRect->Y, 16, 32);
				_arrows[_arrows.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
				spawn = true;
				_enemy[i]->direction = 1;
			}
			else if (_enemy[i]->posRect->Intersects(*_rightBallistaRect) && !spawn)
			{
				_arrows.push_back(new Enemy());
				_arrows[_arrows.size() - 1]->direction = 0;
				_arrows[_arrows.size() - 1]->speed = 0.2f;
				_arrows[_arrows.size() - 1]->eaten = false;
				_arrows[_arrows.size() - 1]->texture = new Texture2D();
				_arrows[_arrows.size() - 1]->texture->Load("Textures/ArrowSpriteSheet.png", true);
				_arrows[_arrows.size() - 1]->rect = new Rect(_rightBallistaRect->X, _rightBallistaRect->Y, 16, 32);
				_arrows[_arrows.size() - 1]->sourceRect = new Rect(0.0f, 0.0f, 16, 32);
				spawn = true;
				_enemy[i]->direction = 1;
			}
			spawn = false;
		}
		
	}
}
void Pacman::DeleteArrow()
{
	for (int i = 0; i < _arrows.size(); i++)
	{
		if (!_arrows[i]->eaten && (_arrows[i]->rect->Y > Graphics::GetViewportHeight()))
		{
			delete _arrows[i]->rect;
			delete _arrows[i]->sourceRect;
			delete _arrows[i];
			_arrows.erase(_arrows.begin() + i);
		}
	}
}
void Pacman::UpdateArrows(int elapsedTime)
{
	for (int i = 0; i < _arrows.size(); i++)
	{
		if (_arrows[i]->direction == 0) //Moves Up
		{
			_arrows[i]->rect->Y -= _arrows[i]->speed * elapsedTime;
		}

		_arrows[i]->currentFrameTime += elapsedTime;

		if (_arrows[i]->currentFrameTime > _arrows[i]->frameTime)
		{
			_arrows[i]->frameCount++;
			if (_arrows[i]->frameCount >= 2)
			{
				_arrows[i]->frameCount = 0;
			}
			_arrows[i]->currentFrameTime = 0;
		}
		_arrows[i]->sourceRect->X = _arrows[i]->sourceRect->Width * _arrows[i]->frameCount;
	}
}