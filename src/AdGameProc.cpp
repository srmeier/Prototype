/*
*/
#include "Player.h"
#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdOverworld.h"
#include "AdSpriteManager.h"

#include "levels/LevelOne.h"

//-----------------------------------------------------------------------------
AdGameProc::AdGameProc(void) {
	m_pOverworld = new LevelOne();
}

//-----------------------------------------------------------------------------
AdGameProc::~AdGameProc(void) {
	delete m_pOverworld;
}

//-----------------------------------------------------------------------------
void AdGameProc::Init(void) {
	Player::m_iCogs          = 3;
	Player::m_iLenses        = 100;
	Player::m_iSprings       = 12;
	Player::m_iTorches       = 24;
	Player::m_iWrenches      = 53;
	Player::m_iDrillBits     = 98;
	Player::m_iElementalType = 0;

	while(Player::Health()!=12) Player::RestoreHealth();
	while(Player::Hunger()!= 7) Player::RestoreHunger();
	while(Player::Thirst()!= 7) Player::RestoreThirst();

	m_pOverworld->Init();
	
	/* TopBarGUI - Background */

	int pTopBarGUIInds[] = {
		0x800,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FF,0x7FE,
		0x7FD,0x000,0x800,0x7FF,0x7FF,0x7FE,0x000,0x800,0x7FF,0x7FF,0x7FE,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x7FC,
		0x7FD,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x7FC,
		0x7FD,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x7FC,
		0x7FD,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x7FD,0x000,0x000,0x7FC,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x7FC,
		0x7FD,0x000,0x7FB,0x000,0x000,0x7F9,0x000,0x7FB,0x000,0x000,0x7F9,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x7FC,
		0x7FB,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7FA,0x7F9
	};

	m_pTopBarGUI = AdSpriteManager::BuildSprite(
		40, 7, pTopBarGUIInds
	);

	/* TopBarGUI - A and B button labels */

	SDL_Rect rect = {0, 0, 8, 8};
	SDL_Surface* pSprABnt = AdSpriteManager::BuildSprite("A");
	SDL_Surface* pSprBBnt = AdSpriteManager::BuildSprite("B");

	rect.x = 32-4, rect.y = 40;
	SDL_BlitSurface(pSprABnt, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprABnt);

	rect.x = 64+4, rect.y = 40;
	SDL_BlitSurface(pSprBBnt, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprBBnt);

	/* TopBarGUI - Hunger meat icon */

	int pIndMeat[] = {0x101};
	SDL_Surface* pSprMeat = AdSpriteManager::BuildSprite(
		1, 1, pIndMeat
	);

	rect.x = 96, rect.y = 28;
	SDL_BlitSurface(pSprMeat, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprMeat);

	/* TopBarGUI - Thirst water icon */

	int pIndWater[] = {0x141};
	SDL_Surface* pSprWater = AdSpriteManager::BuildSprite(
		1, 1, pIndWater
	);

	rect.x = 96, rect.y = 40;
	SDL_BlitSurface(pSprWater, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprWater);

	/* TopBarGUI - Resources: Cog */

	int pIndCog[] = {0x107};
	SDL_Surface* pSprCog = AdSpriteManager::BuildSprite(
		1, 1, pIndCog
	);

	rect.x = 176, rect.y = 12;
	SDL_BlitSurface(pSprCog, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprCog);

	/* TopBarGUI - Resources: Wrench */

	int pIndWrench[] = {0x108};
	SDL_Surface* pSprWrench = AdSpriteManager::BuildSprite(
		1, 1, pIndWrench
	);

	rect.x = 176, rect.y = 24;
	SDL_BlitSurface(pSprWrench, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprWrench);

	/* TopBarGUI - Resources: Spring */

	int pIndSpring[] = {0x109};
	SDL_Surface* pSprSpring = AdSpriteManager::BuildSprite(
		1, 1, pIndSpring
	);

	rect.x = 176, rect.y = 36;
	SDL_BlitSurface(pSprSpring, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprSpring);

	/* TopBarGUI - Resources: DrillBit */

	int pIndDrillBit[] = {0x147};
	SDL_Surface* pSprDrillBit = AdSpriteManager::BuildSprite(
		1, 1, pIndDrillBit
	);

	rect.x = 176+44, rect.y = 12;
	SDL_BlitSurface(pSprDrillBit, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprDrillBit);

	/* TopBarGUI - Resources: Lens */

	int pIndLens[] = {0x148};
	SDL_Surface* pSprLens = AdSpriteManager::BuildSprite(
		1, 1, pIndLens
	);

	rect.x = 176+44, rect.y = 24;
	SDL_BlitSurface(pSprLens, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprLens);

	/* TopBarGUI - Resources: Torch */

	int pIndTorch[] = {0x149};
	SDL_Surface* pSprTorch = AdSpriteManager::BuildSprite(
		1, 1, pIndTorch
	);

	rect.x = 176+44, rect.y = 36;
	SDL_BlitSurface(pSprTorch, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprTorch);

	/* TopBarGUI - Indicator: Elemental Damage */

	int pIndElemDamage[] = {
		0x10A,0x10B,0x10C,0x10D,
		0x14A,0x14B,0x14C,0x14D,
		0x18A,0x18B,0x18C,0x18D,
		0x1CA,0x1CB,0x1CC,0x1CD
	};

	SDL_Surface* pSprElemDamage = AdSpriteManager::BuildSprite(
		4, 4, pIndElemDamage
	);

	rect.x = 270, rect.y = 12;
	SDL_BlitSurface(pSprElemDamage, NULL, m_pTopBarGUI, &rect);
	SDL_FreeSurface(pSprElemDamage);
}

//-----------------------------------------------------------------------------
void AdGameProc::Quit(void) {
	m_pOverworld->Quit();

	SDL_FreeSurface(m_pTopBarGUI);
	m_pTopBarGUI = NULL;
}

//-----------------------------------------------------------------------------
void AdGameProc::Update(SDL_Event* sdlEvent) {
	switch(sdlEvent->type) {
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_ESCAPE: {
					exit(0);
				} break;

				case SDLK_UP: {
					Player::m_pntPosition.y--;
				} break;

				case SDLK_DOWN: {
					Player::m_pntPosition.y++;
				} break;

				case SDLK_LEFT: {
					Player::m_pntPosition.x--;
				} break;

				case SDLK_RIGHT: {
					Player::m_pntPosition.x++;
				} break;
			}
		} break;
		
		case SDL_KEYUP: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_UP: break;
				case SDLK_DOWN: break;
				case SDLK_LEFT: break;
				case SDLK_RIGHT: break;
			}
		} break;
	}

	m_pOverworld->Update();
}

//-----------------------------------------------------------------------------
void AdGameProc::Render(void) {
	m_pOverworld->Render();

	/* TopBarGUI - Background */

	char tempStr[0x5];
	SDL_Point pnt = {0, 0};
	AdScreen::DrawSprite(pnt, m_pTopBarGUI);

	/* TopBarGUI - Health */

	int pIndHeart0[] = {
		0x102,0x103,
		0x142,0x143
	};

	int pIndHeart1[] = {
		0x182,0x183,
		0x1C2,0x1C3
	};

	int pIndHeart2[] = {
		0x202,0x203,
		0x242,0x243
	};

	int pIndHeart3[] = {
		0x282,0x283,
		0x2C2,0x2C3
	};

	SDL_Surface* pSprHeart = AdSpriteManager::BuildSprite(
		2, 2,
		(Player::Health()>=3)?pIndHeart0:
		(Player::Health()==2)?pIndHeart1:
		(Player::Health()==1)?pIndHeart2:
		pIndHeart3
	);

	pnt.x = 104, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprHeart);
	SDL_FreeSurface(pSprHeart);

	pSprHeart = AdSpriteManager::BuildSprite(
		2, 2,
		(Player::Health()>=6)?pIndHeart0:
		(Player::Health()==5)?pIndHeart1:
		(Player::Health()==4)?pIndHeart2:
		pIndHeart3
	);

	pnt.x = 104+16;
	AdScreen::DrawSprite(pnt, pSprHeart);
	SDL_FreeSurface(pSprHeart);

	pSprHeart = AdSpriteManager::BuildSprite(
		2, 2,
		(Player::Health()>=9)?pIndHeart0:
		(Player::Health()==8)?pIndHeart1:
		(Player::Health()==7)?pIndHeart2:
		pIndHeart3
	);

	pnt.x = 104+32;
	AdScreen::DrawSprite(pnt, pSprHeart);
	SDL_FreeSurface(pSprHeart);

	pSprHeart = AdSpriteManager::BuildSprite(
		2, 2,
		(Player::Health()>=12)?pIndHeart0:
		(Player::Health()==11)?pIndHeart1:
		(Player::Health()==10)?pIndHeart2:
		pIndHeart3
	);

	pnt.x = 104+48;
	AdScreen::DrawSprite(pnt, pSprHeart);
	SDL_FreeSurface(pSprHeart);

	/* TopBarGUI - Hunger bar */

	int pIndMeatBar[] = {
		(Player::Hunger()>0)?0x104:0x184,
		(Player::Hunger()>1)?0x105:0x185,
		(Player::Hunger()>2)?0x105:0x185,
		(Player::Hunger()>3)?0x105:0x185,
		(Player::Hunger()>4)?0x105:0x185,
		(Player::Hunger()>5)?0x105:0x185,
		(Player::Hunger()>6)?0x106:0x186
	};

	SDL_Surface* pSprMeatBar = AdSpriteManager::BuildSprite(
		7, 1, pIndMeatBar
	);

	pnt.x = 108, pnt.y = 28;
	AdScreen::DrawSprite(pnt, pSprMeatBar);
	SDL_FreeSurface(pSprMeatBar);

	/* TopBarGUI - Thirst bar */

	int pIndWaterBar[] = {
		(Player::Thirst()>0)?0x144:0x184,
		(Player::Thirst()>1)?0x145:0x185,
		(Player::Thirst()>2)?0x145:0x185,
		(Player::Thirst()>3)?0x145:0x185,
		(Player::Thirst()>4)?0x145:0x185,
		(Player::Thirst()>5)?0x145:0x185,
		(Player::Thirst()>6)?0x146:0x186
	};

	SDL_Surface* pSprWaterBar = AdSpriteManager::BuildSprite(
		7, 1, pIndWaterBar
	);

	pnt.x = 108, pnt.y = 40;
	AdScreen::DrawSprite(pnt, pSprWaterBar);
	SDL_FreeSurface(pSprWaterBar);

	/* TopBarGUI - Number of Cogs */

	sprintf(tempStr, "%03d", Player::m_iCogs);
	SDL_Surface* pSprCogNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprCogNum);
	SDL_FreeSurface(pSprCogNum);

	/* TopBarGUI - Number of Wrenches */

	sprintf(tempStr, "%03d", Player::m_iWrenches);
	SDL_Surface* pSprWrenchNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprWrenchNum);
	SDL_FreeSurface(pSprWrenchNum);

	/* TopBarGUI - Number of Springs */

	sprintf(tempStr, "%03d", Player::m_iSprings);
	SDL_Surface* pSprSpringNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188, pnt.y = 36;
	AdScreen::DrawSprite(pnt, pSprSpringNum);
	SDL_FreeSurface(pSprSpringNum);

	/* TopBarGUI - Number of Drill Bits */

	sprintf(tempStr, "%03d", Player::m_iDrillBits);
	SDL_Surface* pSprDrillBitNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188+44, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprDrillBitNum);
	SDL_FreeSurface(pSprDrillBitNum);

	/* TopBarGUI - Number of Lenes */

	sprintf(tempStr, "%03d", Player::m_iLenses);
	SDL_Surface* pSprLensNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188+44, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprLensNum);
	SDL_FreeSurface(pSprLensNum);

	/* TopBarGUI - Number of Torches */

	sprintf(tempStr, "%03d", Player::m_iTorches);
	SDL_Surface* pSprTorchNum = AdSpriteManager::BuildSprite(tempStr);
	pnt.x = 188+44, pnt.y = 36;
	AdScreen::DrawSprite(pnt, pSprTorchNum);
	SDL_FreeSurface(pSprTorchNum);

	/* TopBarGUI - Indicator: Elemental Damage */

	int pIndArrow[1];
	if(Player::m_iElementalType == 0) {
		pIndArrow[0] = 0x10E;
	} else if(Player::m_iElementalType == 1) {
		pIndArrow[0] = 0x10F;
	} else if(Player::m_iElementalType == 2) {
		pIndArrow[0] = 0x110;
	} else {
		pIndArrow[0] = 0x111;
	}

	SDL_Surface* pSprArrow = AdSpriteManager::BuildSprite(
		1, 1, pIndArrow
	);
	pnt.x = 282, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprArrow);
	SDL_FreeSurface(pSprArrow);
}
