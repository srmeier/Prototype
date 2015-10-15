/*
- to force movement just set forced move to true and set the direction
*/

#include "AdLevel.h"
#include "AdScreen.h"
#include "AdMoveable.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdMoveable::AdMoveable(void) {
	m_iFrame      = 0;
	m_pFrames     = NULL;

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
AdMoveable::~AdMoveable(void) {
	Unload();
}

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

	// NOTE: load the animation frames
	duk_get_prop_string(pCtx, -1, "properties");
	duk_get_prop_string(pCtx, -1, "frames");

	m_AniMap.Load(duk_get_string(pCtx, -1));

	// NOTE: create an SDL_Surface for each frame
	m_pFrames = (SDL_Surface**) malloc(m_AniMap.nLayers()*sizeof(SDL_Surface*));

	for(int j=0; j<m_AniMap.nLayers(); ++j) {
		if(m_AniMap.GetLayer(j)) {
			m_pFrames[j] = AdSpriteManager::BuildSprite(
				m_AniMap.Width(), m_AniMap.Height(), m_AniMap.GetLayer(j)
			);
		} else {
			m_pFrames[j] = NULL;
		}
	}

	duk_pop_2(pCtx);
}

//-----------------------------------------------------------------------------
void AdMoveable::Unload(void) {
	AdEntity::Unload();

	for(int j=0; j<m_AniMap.nLayers(); ++j) {
		if(m_pFrames && m_pFrames[j]) {
			SDL_FreeSurface(m_pFrames[j]);
			m_pFrames[j] = NULL;
		}
	}

	if(m_pFrames) {
		free(m_pFrames);
		m_pFrames = NULL;
	}
}

//-----------------------------------------------------------------------------
bool AdMoveable::DoesCollide(
	class AdTiledManager* pMap, int iDirec /*= -1*/,
	int iOffsetI /*= 0*/, int iOffsetJ /*= 0*/
) {
	int iW = (int) floor(m_recTrigger.w/8.0f);
	int iH = (int) floor(m_recTrigger.h/8.0f);

	bool bCollides = false;

	switch(iDirec) {
		case UP_DIREC: {
			bool bTemp = true;
			for(int i=0; i<iW; ++i) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)-1)==0
				);
			} bCollides = !bTemp;
		} break;

		case DOWN_DIREC: {
			bool bTemp = true;
			for(int i=0; i<iW; ++i) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)+iH)==0
				);
			} bCollides = !bTemp;
		} break;

		case LEFT_DIREC: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)-1, (m_iJ+iOffsetJ)+j)==0
				);
			} bCollides = !bTemp;
		} break;

		case RIGHT_DIREC: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				bTemp = (bTemp && pMap->GetTile(
					COLLISION_LAYER, (m_iI+iOffsetI)+iW, (m_iJ+iOffsetJ)+j)==0
				);
			} bCollides = !bTemp;
		} break;

		default: {
			bool bTemp = true;
			for(int j=0; j<iH; ++j) {
				for(int i=0; i<iW; ++i)
					bTemp = (bTemp && pMap->GetTile(
						COLLISION_LAYER, (m_iI+iOffsetI)+i, (m_iJ+iOffsetJ)+j)==0
					);
			} bCollides = !bTemp;
		} break;
	}

	return bCollides;
}

//-----------------------------------------------------------------------------
void AdMoveable::HandleMovement(class AdTiledManager* pMap) {
	m_iI = (int) floor(m_recTrigger.x/8.0f);
	m_iJ = (int) floor(m_recTrigger.y/8.0f);

	if(!m_bFreeToMove && !m_bMoving) return;

	if(m_iMoveframe>0) m_iMoveframe--;
	else if(m_bMoving) {
		m_bMoving = false;
		m_bForceMove = false;
	}

	if(!m_bMoving) {
		if(m_bForceMove) {
			if(m_iForcedirec==UP_DIREC &&
				!DoesCollide(pMap, UP_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = UP_DIREC;
			} else if(m_iForcedirec==DOWN_DIREC &&
				!DoesCollide(pMap, DOWN_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = DOWN_DIREC;
			} else if(m_iForcedirec==LEFT_DIREC &&
				!DoesCollide(pMap, LEFT_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = LEFT_DIREC;
			} else if(m_iForcedirec==RIGHT_DIREC &&
				!DoesCollide(pMap, RIGHT_DIREC)
			) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = RIGHT_DIREC;
			} else {
				// NOTE: if the forced moves results in a collision then toggle
				// off the forced move
				m_bForceMove = false;
			}
		} else {
			if(m_bUp && !DoesCollide(pMap, UP_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = UP_DIREC;
			} else if(m_bDown && !DoesCollide(pMap, DOWN_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = DOWN_DIREC;
			} else if(m_bLeft && !DoesCollide(pMap, LEFT_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = LEFT_DIREC;
			} else if(m_bRight && !DoesCollide(pMap, RIGHT_DIREC)) {
				m_bMoving    = true;
				m_iMoveframe = 8-1;
				m_iMovedirec = RIGHT_DIREC;
			}
		}
	}

	if(m_bMoving) {
		switch(m_iMovedirec) {
			case UP_DIREC:    m_recTrigger.y--; break;
			case DOWN_DIREC:  m_recTrigger.y++; break;
			case LEFT_DIREC:  m_recTrigger.x--; break;
			case RIGHT_DIREC: m_recTrigger.x++; break;
		}
	}
}

//-----------------------------------------------------------------------------
void AdMoveable::Update(AdLevel* pLvl) {
	AdEntity::Update(pLvl);

	// TESTING
	if(m_bTriggered) m_bFreeToMove = false;
	else m_bFreeToMove = true;

	m_bForceMove = true;
	int newDirec = rand()%256;

	if(newDirec<4) {
		m_iForcedirec = newDirec;
	} else if(newDirec<32) {
		m_iForcedirec = -1;
	}
	//
	
	AdTiledManager* pMap;
	pMap = pLvl->GetTiledMap();
	
	HandleMovement(pMap);
}

//-----------------------------------------------------------------------------
void AdMoveable::Render(AdLevel* pLvl) {
	int offset_x = AdBase::GetWidth()/2-48/2+pLvl->GetPlayer()->m_recTrigger.x;
	int offset_y = AdBase::GetHeight()/2-48/2+pLvl->GetPlayer()->m_recTrigger.y;

	SDL_Point pnt = {/*offset_x+*/m_recTrigger.x, /*offset_y+*/m_recTrigger.y};
	AdScreen::DrawSprite(pnt, m_pFrames[m_iFrame]);

	if(m_bTriggered) {
		// TESTING
		SDL_Surface* spr = AdSpriteManager::BuildSprite("TALK!!");

		int offset_x = AdBase::GetWidth()/2-48/2+pLvl->GetPlayer()->m_recTrigger.x;
		int offset_y = AdBase::GetHeight()/2-48/2+pLvl->GetPlayer()->m_recTrigger.y;

		SDL_Point pnt = {m_recTrigger.x/*+offset_x*/, m_recTrigger.y/*+offset_y*/};
		AdScreen::DrawSprite(pnt, spr);

		SDL_FreeSurface(spr);

		//

		int inds0[] = {
			64*18+43, 64*18+44, 64*18+45, 64*18+46, 64*18+47, 64*18+48,
			64*19+43, 64*19+44, 64*19+45, 64*19+46, 64*19+47, 64*19+48,
			64*20+43, 64*20+44, 64*20+45, 64*20+46, 64*20+47, 64*20+48,
			64*21+43, 64*21+44, 64*21+45, 64*21+46, 64*21+47, 64*21+48,
			64*22+43, 64*22+44, 64*22+45, 64*22+46, 64*22+47, 64*22+48,
			64*23+43, 64*23+44, 64*23+45, 64*23+46, 64*23+47, 64*23+48,
		};

		SDL_Surface* face = AdSpriteManager::BuildSprite(6, 6, inds0);

		int inds[] = {
			64*2+10, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+11, 64*2+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*4+10, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+11, 64*3+17,
			64*5+10, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+16, 64*5+17
		};

		SDL_Surface* bkg = AdSpriteManager::BuildSprite(62, 11, inds);

		spr  = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		SDL_Surface* spr0 = AdSpriteManager::BuildSprite("1234567890!#$%&*()-+=[]\"\'<>.?/");

		SDL_Point pnt2 = {8*3, 8*31};
		AdScreen::DrawSprite(pnt2, bkg);
		pnt2.x += 8; pnt2.y += 16;
		AdScreen::DrawSprite(pnt2, face);
		pnt2.x += 48+8; pnt2.y -= 8;
		AdScreen::DrawSprite(pnt2, spr);
		pnt2.y += 8;
		AdScreen::DrawSprite(pnt2, spr0);

		SDL_FreeSurface(face);
		SDL_FreeSurface(bkg);
		SDL_FreeSurface(spr);
		SDL_FreeSurface(spr0);
		//
	}
}
