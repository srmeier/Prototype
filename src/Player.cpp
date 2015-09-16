/*
*/

#include "Player.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
int       Player::m_iHealth;
int       Player::m_iHunger;
int       Player::m_iThirst;

int       Player::m_iCogs;
int       Player::m_iLenses;
int       Player::m_iSprings;
int       Player::m_iTorches;
int       Player::m_iWrenches;
int       Player::m_iDrillBits;

int       Player::m_iElementalType;

SDL_Rect  Player::m_pntPosition = {0, 0, 16, 16};

//-----------------------------------------------------------------------------
void Player::Init(void) {}

//-----------------------------------------------------------------------------
void Player::Quit(void) {}

//-----------------------------------------------------------------------------
void Player::Update(void) {}

//-----------------------------------------------------------------------------
void Player::Render(SDL_Point pntOffset) {
	int pInd[] = {
		0x141,0x141,
		0x141,0x141
	};

	SDL_Surface* pSprite = AdSpriteManager::BuildSprite(
		2, 2, pInd
	);

	pntOffset.x += m_pntPosition.x;
	pntOffset.y += m_pntPosition.y;

	AdScreen::DrawSprite(pntOffset, pSprite);
	SDL_FreeSurface(pSprite);
}
