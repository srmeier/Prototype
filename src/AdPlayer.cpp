/*
*/

#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdPlayer::AdPlayer(void) {
	m_iMouseX     = 0;
	m_iMouseY     = 0;
	m_bMouseLeft  = false;
	m_bMouseRight = false;

	// TEMP
	show_move_cursor = true;
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
	m_recTrigger.x = duk_to_int(pCtx, -1);//-duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "y");
	m_recTrigger.y = duk_to_int(pCtx, -1);//-duk_to_int(pCtx, -1);
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
	AdTiledManager* pMap;
	pMap = pLvl->GetTiledMap();
	
	HandleMovement(pMap);
}

//-----------------------------------------------------------------------------
void AdPlayer::Render(AdLevel* pLvl) {
	SDL_Point pnt = {m_recTrigger.x, m_recTrigger.y}; //{AdBase::GetWidth()/2-48/2, AdBase::GetHeight()/2-48/2};
	AdScreen::DrawSprite(pnt, m_pFrames[m_iFrame]);

	// the x, y offset added to an NPCs x, y to draw to screen
	int offset_x = 0;/*AdBase::GetWidth()/2-48/2+m_recTrigger.x;*/
	int offset_y = 0;/*AdBase::GetHeight()/2-48/2+m_recTrigger.y;*/

	// the mouses x, y - offset to draw to the screen
	int offset_i = (int) floor((m_iMouseX-48/2 + offset_x)/8.0f);
	int offset_j = (int) floor((m_iMouseY-48/2 + offset_y)/8.0f);

	// set to an 8x8 grid and subtract the offset to return to screen from map
	pnt.x = m_iMouseX-48/2;//offset_i*8 - offset_x;
	pnt.y = m_iMouseY-48/2;//offset_j*8 - offset_y;

	int offset_ii = offset_i - 2*(int) floor(offset_x/8.0f);
	int offset_jj = offset_j - 2*(int) floor(offset_y/8.0f);

	// TESTING (move to update)
	static int goal_ii = m_iI;
	static int goal_jj = m_iJ;

	if(DoesCollide(pLvl->GetTiledMap(), -1, offset_ii-m_iI, offset_jj-m_iJ)) {
		if(show_move_cursor) AdScreen::DrawSprite(pnt, m_pFrames[2]);
	} else {
		if(show_move_cursor) AdScreen::DrawSprite(pnt, m_pFrames[1]);

		if(m_bMouseLeft && !m_bMoving) {
			goal_ii = offset_ii;
			goal_jj = offset_jj;
		}
	}

	/*
	pnt.x = 8*offset_ii; pnt.y = 8*offset_jj;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*offset_ii+48-8; pnt.y = 8*offset_jj;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*offset_ii; pnt.y = 8*offset_jj+48-8;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*offset_ii+48-8; pnt.y = 8*offset_jj+48-8;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);

	pnt.x = 8*m_iI; pnt.y = 8*m_iJ;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*m_iI+48-8; pnt.y = 8*m_iJ;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*m_iI; pnt.y = 8*m_iJ+48-8;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	pnt.x = 8*m_iI+48-8; pnt.y = 8*m_iJ+48-8;
	AdScreen::DrawSprite(pnt, m_pFrames[3]);
	*/

	if(goal_ii==m_iI && goal_jj==m_iJ /*&& m_bForceMove*/) {
		//m_bForceMove = false;
		//m_bMoving = false;
	} else if(!m_bForceMove) {
		if(goal_jj<m_iJ) {
			m_bForceMove = true;
			m_iForcedirec = UP_DIREC;
		}
		if(goal_jj>m_iJ) {
			m_bForceMove = true;
			m_iForcedirec = DOWN_DIREC;
		}
		if(goal_ii<m_iI) {
			m_bForceMove = true;
			m_iForcedirec = LEFT_DIREC;
		}
		if(goal_ii>m_iI) {
			m_bForceMove = true;
			m_iForcedirec = RIGHT_DIREC;
		}
	}

	//printf("%d %d %d\n", m_iI, goal_ii, m_bForceMove);
	//
}
