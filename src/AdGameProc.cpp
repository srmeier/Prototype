/*
*/

#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdGameProc::AdGameProc(void) {}

//-----------------------------------------------------------------------------
AdGameProc::~AdGameProc(void) {}

//-----------------------------------------------------------------------------
void AdGameProc::Init(void) {
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
	SDL_FreeSurface(m_pTopBarGUI);
	m_pTopBarGUI = NULL;
}

//-----------------------------------------------------------------------------
void AdGameProc::Update(void) {
}

//-----------------------------------------------------------------------------
void AdGameProc::Render(void) {
	/* TopBarGUI - Background */

	SDL_Point pnt = {0, 0};
	AdScreen::DrawSprite(pnt, m_pTopBarGUI);

	/* TopBarGUI - Health */

	int pIndHeart[] = {
		0x102,0x103,
		0x142,0x143
	};

	SDL_Surface* pSprHeart = AdSpriteManager::BuildSprite(
		2, 2, pIndHeart
	);

	pnt.x = 104, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprHeart);
	pnt.x = 104+16;
	AdScreen::DrawSprite(pnt, pSprHeart);
	pnt.x = 104+32;
	AdScreen::DrawSprite(pnt, pSprHeart);
	pnt.x = 104+48;
	AdScreen::DrawSprite(pnt, pSprHeart);

	SDL_FreeSurface(pSprHeart);

	/* TopBarGUI - Hunger bar */

	int pIndMeatBar[] = {
		0x104,0x105,0x105,0x105,0x105,0x105,0x106
	};

	SDL_Surface* pSprMeatBar = AdSpriteManager::BuildSprite(
		7, 1, pIndMeatBar
	);

	pnt.x = 108, pnt.y = 28;
	AdScreen::DrawSprite(pnt, pSprMeatBar);
	SDL_FreeSurface(pSprMeatBar);

	/* TopBarGUI - Thirst bar */

	int pIndWaterBar[] = {
		0x144,0x145,0x145,0x145,0x145,0x145,0x146
	};

	SDL_Surface* pSprWaterBar = AdSpriteManager::BuildSprite(
		7, 1, pIndWaterBar
	);

	pnt.x = 108, pnt.y = 40;
	AdScreen::DrawSprite(pnt, pSprWaterBar);
	SDL_FreeSurface(pSprWaterBar);

	/* TopBarGUI - Number of Cogs */

	SDL_Surface* pSprCogNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprCogNum);
	SDL_FreeSurface(pSprCogNum);

	/* TopBarGUI - Number of Wrenches */

	SDL_Surface* pSprWrenchNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprWrenchNum);
	SDL_FreeSurface(pSprWrenchNum);

	/* TopBarGUI - Number of Springs */

	SDL_Surface* pSprSpringNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188, pnt.y = 36;
	AdScreen::DrawSprite(pnt, pSprSpringNum);
	SDL_FreeSurface(pSprSpringNum);

	/* TopBarGUI - Number of Drill Bits */

	SDL_Surface* pSprDrillBitNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188+44, pnt.y = 12;
	AdScreen::DrawSprite(pnt, pSprDrillBitNum);
	SDL_FreeSurface(pSprDrillBitNum);

	/* TopBarGUI - Number of Lenes */

	SDL_Surface* pSprLensNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188+44, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprLensNum);
	SDL_FreeSurface(pSprLensNum);

	/* TopBarGUI - Number of Torches */

	SDL_Surface* pSprTorchNum = AdSpriteManager::BuildSprite("100");
	pnt.x = 188+44, pnt.y = 36;
	AdScreen::DrawSprite(pnt, pSprTorchNum);
	SDL_FreeSurface(pSprTorchNum);

	/* TopBarGUI - Indicator: Elemental Damage */

	int pIndUpArrow[]    = {0x10E};
	int pIndDownArrow[]  = {0x10F};
	int pIndLeftArrow[]  = {0x110};
	int pIndRightArrow[] = {0x111};

	SDL_Surface* pSprArrow = AdSpriteManager::BuildSprite(
		1, 1, pIndUpArrow
	);
	pnt.x = 282, pnt.y = 24;
	AdScreen::DrawSprite(pnt, pSprArrow);
	SDL_FreeSurface(pSprArrow);
}
