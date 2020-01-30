#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include "BaseEntity.h"
#include "Weapon.h"
#include "EntityManager.h"
#include "Projectile.h"
#include "MessageRelay.h"
#include "ItemSpawner.h"

#include <SFML\Window.hpp>

#include <list>

//Control structure
typedef struct Controls
{
	bool Up;
	bool Left;
	bool Down;
	bool Right;

	bool Space;
} Controls;

//Player class
class Player: public BaseEntity
{
public:
	Player(void);
	~Player(void);
	
	//Delete the player
	virtual void Delete()
	{
		this->~Player();
	}

	void initializePlayer()
	{
		userInput.Up = 
		userInput.Left =
		userInput.Down =
		userInput.Right = 
		userInput.Space = false;

		HeldItem.clear();
		

		currentWeapon = 0;
		Position.setPosition(0.0,0.0,0.0);
		EntityManager::GetInstance()->AddEntity(this);
	}

	void LoadWeapons();

	//Update the player
	virtual void Update(float dt);

	void Activate()
	{
		extern bool HaveTripple;
		if (HeldItem.size() <= 0)
			return;

		if (HeldItem.front() < 6)
		{
			HaveTripple = true;
			currentWeapon = HeldItem.front();
			HeldItem.pop_front();
			upgradeTime.restart();
		}
		else
		{
			//Enable all those other skills (speed boost, combo boost, shield boost, multi-shot)
		}
	}

	//Fire the current weapon
	void Fire();

	Controls userInput;

	sf::Time fireDelay;
	sf::Clock shooterTime;

	sf::Time upgradeActive;
	sf::Clock upgradeTime;

	//Keep track of the current weapon and weapon type
	unsigned int currentWeapon;
	unsigned int currentType;


	//All of the weapons the player has access to
	std::vector<Weapon> Arsenal;
	//List of held weapons
	std::list<int> HeldItem;
};

#endif