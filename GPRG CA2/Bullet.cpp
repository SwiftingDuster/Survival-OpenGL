#include "stdafx.h"
#include "Bullet.h"

// Creates a bullet. Provide a forward vector to determine the direction the bullet will fly. Enemies creating a bullet should use this constructor with a forward vector pointing to the player from the enemy's location.
Bullet::Bullet(Musket * source, int damage, Vector2f forwardVector, float projectileSpeed)
{
	this->LoadTextureAndSprite(ResourceHolder::TextureHolder::bulletTexture);

	this->sourceWeapon = source;
	this->damage = damage;
	this->forward = forwardVector;
	this->projectileSpeed = projectileSpeed;

	SetPosition(source->GetPosition());
	this->SetRotation(this->sourceWeapon->GetWeaponOwner()->GetRotation());
	SetOrigin(0, 3);
}

// Update the bullet's location
void Bullet::Update(float deltaTime)
{
	if (forward != Vector2f(0, 0)) this->Move(forward * projectileSpeed * deltaTime);
}

// Removes the bullet from game scene and free heap memory allocated to it
void Bullet::Destroy()
{
	if (Game::GetInstance()->activeProjectiles.size() == 0) return;

	if (Game::GetInstance()->activeProjectiles.size() == 1)
	{
		Game::GetInstance()->activeProjectiles.clear();
		delete heapReference;
	}
	else 
	{
		list<Ammo*>::iterator iter = Game::GetInstance()->activeProjectiles.begin();
		while (iter != Game::GetInstance()->activeProjectiles.end())
		{
			if ((*iter)->uniqueAmmoID == this->uniqueAmmoID)
			{
				// Remove itself from active projectiles list and free heap memory
				iter = Game::GetInstance()->activeProjectiles.erase(iter);
				delete heapReference;
				break;
			}
			else
				++iter;
		}
	}
}