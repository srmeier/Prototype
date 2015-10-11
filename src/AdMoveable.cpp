/*
- to force movement just set forced move to true and set the direction
*/

#include "AdLevel.h"
#include "AdScreen.h"
#include "AdMoveable.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdMoveable::AdMoveable(void) {
	m_iI          = 0;
	m_iJ          = 0;

	m_iMoveframe  = 0;
	m_iMovedirec  = 0;

	m_bMoving     = false;
	m_bFreeToMove = true;

	m_iForcedirec = 0;
	m_bForceMove  = false;

	m_bUp         = false;
	m_bDown       = false;
	m_bLeft       = false;
	m_bRight      = false;

	m_bUpCheck    = false;
	m_bDownCheck  = false;
	m_bLeftCheck  = false;
	m_bRightCheck = false;
}

//-----------------------------------------------------------------------------
AdMoveable::~AdMoveable(void) {}

//-----------------------------------------------------------------------------
void AdMoveable::Load(duk_context* pCtx) {
	Unload();

	duk_get_prop_string(pCtx, -1, "type");
	strcpy(m_pType, duk_get_string(pCtx, -1));
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "x");
	m_recTrigger.x = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "y");
	m_recTrigger.y = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "width");
	m_recTrigger.w = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "height");
	m_recTrigger.h = duk_to_int(pCtx, -1);
	duk_pop(pCtx);
}

//-----------------------------------------------------------------------------
void AdMoveable::Update(AdLevel* pLvl) {
	// TESTING
	SDL_Rect res;
	SDL_Rect recPlayer = {8*pLvl->GetPlayer()->m_iI, 8*pLvl->GetPlayer()->m_iJ, 8*6, 8*6};

	if(SDL_IntersectRect(&m_recTrigger, &recPlayer, &res))
		m_bTriggered = true;
	else
		m_bTriggered = false;
	//

	// TESTING
	m_bForceMove = true;
	m_iForcedirec = rand()%32;
	//
	
	AdTiledManager* pMap = pLvl->GetTiledMap();

	if(!m_bFreeToMove && !m_bMoving) return;

	m_iI = (int) floor(m_recTrigger.x/8.0f);
	m_iJ = (int) floor(m_recTrigger.y/8.0f);

	if(m_iMoveframe>0) m_iMoveframe--;
	else if(m_bMoving) {
		m_bMoving = false;
	}

	if(!m_bMoving) {
		if(m_bForceMove) {
			if(m_iForcedirec==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+0, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+1, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+2, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+3, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+4, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+5, m_iJ-1)==0
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = 0;
			} else if(m_iForcedirec==1 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+0, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+1, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+2, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+3, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+4, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+5, m_iJ+6)==0
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = 1;
			} else if(m_iForcedirec==2 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+0)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+2)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+3)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+4)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+5)==0
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = 2;
			} else if(m_iForcedirec==3 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+0)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+2)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+3)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+4)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+5)==0
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = 3;
			}
		} else {
			if(m_bUp &&
				pMap->GetTile(COLLISION_LAYER, m_iI+0, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+1, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+2, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+3, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+4, m_iJ-1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+5, m_iJ-1)==0
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = 0;
			} else if(m_bDown &&
				pMap->GetTile(COLLISION_LAYER, m_iI+0, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+1, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+2, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+3, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+4, m_iJ+6)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+5, m_iJ+6)==0
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = 1;
			} else if(m_bLeft &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+0)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+2)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+3)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+4)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI-1, m_iJ+5)==0
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = 2;
			} else if(m_bRight &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+0)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+1)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+2)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+3)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+4)==0 &&
				pMap->GetTile(COLLISION_LAYER, m_iI+6, m_iJ+5)==0
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = 3;
			}
		}
	}

	if(m_bMoving) {
		switch(m_iMovedirec) {
			case 0: m_recTrigger.y--; break;
			case 1: m_recTrigger.y++; break;
			case 2: m_recTrigger.x--; break;
			case 3: m_recTrigger.x++; break;
		}
	}
}

//-----------------------------------------------------------------------------
void AdMoveable::Render(AdLevel* pLvl) {
	// TEMP: will need to make this dependent on NPC data
	int ind[] = {
		64*12+37, 64*12+38, 64*12+39, 64*12+40, 64*12+41, 64*12+42,
		64*13+37, 64*13+38, 64*13+39, 64*13+40, 64*13+41, 64*13+42,
		64*14+37, 64*14+38, 64*14+39, 64*14+40, 64*14+41, 64*14+42,
		64*15+37, 64*15+38, 64*15+39, 64*15+40, 64*15+41, 64*15+42,
		64*16+37, 64*16+38, 64*16+39, 64*16+40, 64*16+41, 64*16+42,
		64*17+37, 64*17+38, 64*17+39, 64*17+40, 64*17+41, 64*17+42,
	};

	SDL_Surface* pPlayer = AdSpriteManager::BuildSprite(6, 6, ind);

	SDL_Point pnt = {
		AdBase::GetWidth()/2-48/2+pLvl->GetPlayer()->m_recTrigger.x+m_recTrigger.x,
		AdBase::GetHeight()/2-48/2+pLvl->GetPlayer()->m_recTrigger.y+m_recTrigger.y
	};

	AdScreen::DrawSprite(pnt, pPlayer);

	SDL_FreeSurface(pPlayer);

	if(m_bTriggered) {
		// TESTING
		SDL_Surface* spr = AdSpriteManager::BuildSprite("EVENT!!");

		int offset_x = AdBase::GetWidth()/2-48/2+pLvl->GetPlayer()->m_recTrigger.x;
		int offset_y = AdBase::GetHeight()/2-48/2+pLvl->GetPlayer()->m_recTrigger.y;

		SDL_Point pnt = {m_recTrigger.x+offset_x, m_recTrigger.y+offset_y};
		AdScreen::DrawSprite(pnt, spr);

		SDL_FreeSurface(spr);
		//
	}
}
