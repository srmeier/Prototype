/*
*/

#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdPlayer::AdPlayer(void) {
	m_iMouseX = 0;
	m_iMouseY = 0;
}

//-----------------------------------------------------------------------------
AdPlayer::~AdPlayer(void) {}

//-----------------------------------------------------------------------------
void AdPlayer::Load(duk_context* pCtx) {
	Unload();

	duk_get_prop_string(pCtx, -1, "type");
	strcpy(m_pType, duk_get_string(pCtx, -1));
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "x");
	m_recTrigger.x = -duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "y");
	m_recTrigger.y = -duk_to_int(pCtx, -1);
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
void AdPlayer::Update(AdLevel* pLvl) {
	AdTiledManager* pMap = pLvl->GetTiledMap();

	if(!m_bFreeToMove && !m_bMoving) return;

	m_iI = (int) floor(-m_recTrigger.x/8.0f);
	m_iJ = (int) floor(-m_recTrigger.y/8.0f);

	if(m_iMoveframe>0) m_iMoveframe--;
	else if(m_bMoving) {
		m_bMoving = false;
	}

	if(!m_bMoving) {
		if(m_bForceMove) {
			if(m_iForcedirec==UP_DIREC &&
				!DoesCollide(pMap, UP_DIREC)
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = UP_DIREC;
			} else if(m_iForcedirec==DOWN_DIREC &&
				!DoesCollide(pMap, DOWN_DIREC)
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = DOWN_DIREC;
			} else if(m_iForcedirec==LEFT_DIREC &&
				!DoesCollide(pMap, LEFT_DIREC)
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = LEFT_DIREC;
			} else if(m_iForcedirec==RIGHT_DIREC &&
				!DoesCollide(pMap, RIGHT_DIREC)
			) {
				m_bMoving    = true;
				m_bForceMove = false;
				m_iMoveframe = 8-1;
				m_iMovedirec = RIGHT_DIREC;
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
			case DOWN_DIREC:  m_recTrigger.y--; break;
			case UP_DIREC:    m_recTrigger.y++; break;
			case RIGHT_DIREC: m_recTrigger.x--; break;
			case LEFT_DIREC:  m_recTrigger.x++; break;
		}
	}
}

//-----------------------------------------------------------------------------
void AdPlayer::Render(AdLevel* pLvl) {
	SDL_Point pnt = {AdBase::GetWidth()/2-48/2, AdBase::GetHeight()/2-48/2};
	AdScreen::DrawSprite(pnt, m_pFrames[m_iFrame]);

	// the x, y offset added to an NPCs x, y to draw to screen
	int offset_x = AdBase::GetWidth()/2-48/2+m_recTrigger.x;
	int offset_y = AdBase::GetHeight()/2-48/2+m_recTrigger.y;

	// the mouses x, y - offset to draw to the screen
	int offset_i = (int) floor((m_iMouseX/2-48/2 + offset_x)/8.0f);
	int offset_j = (int) floor((m_iMouseY/2-48/2 + offset_y)/8.0f);

	// set to an 8x8 grid and subtract the offset to return to screen from map
	pnt.x = m_iMouseX/2-48/2;//offset_i*8 - offset_x;
	pnt.y = m_iMouseY/2-48/2;//offset_j*8 - offset_y;


	int offset_ii = offset_i - 2*(int) floor(offset_x/8.0f);
	int offset_jj = offset_j - 2*(int) floor(offset_y/8.0f);

	if(DoesCollide(pLvl->GetTiledMap(), -1, offset_ii-m_iI, offset_jj-m_iJ))
		AdScreen::DrawSprite(pnt, m_pFrames[2]);
	else
		AdScreen::DrawSprite(pnt, m_pFrames[1]);
}