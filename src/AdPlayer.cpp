/*
*/

#include "AdBase.h"
#include "AdLevel.h"
#include "AdPlayer.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdPlayer::AdPlayer(void) {
	m_pCurLvl = NULL;

	bUp    = false;
	bDown  = false;
	bLeft  = false;
	bRight = false;

	int ind[] = {
		64*12+37, 64*12+38, 64*12+39, 64*12+40, 64*12+41, 64*12+42,
		64*13+37, 64*13+38, 64*13+39, 64*13+40, 64*13+41, 64*13+42,
		64*14+37, 64*14+38, 64*14+39, 64*14+40, 64*14+41, 64*14+42,
		64*15+37, 64*15+38, 64*15+39, 64*15+40, 64*15+41, 64*15+42,
		64*16+37, 64*16+38, 64*16+39, 64*16+40, 64*16+41, 64*16+42,
		64*17+37, 64*17+38, 64*17+39, 64*17+40, 64*17+41, 64*17+42,
	};

	m_pSurface = AdSpriteManager::BuildSprite(6, 6, ind);
}

//-----------------------------------------------------------------------------
AdPlayer::~AdPlayer(void) {
	SDL_FreeSurface(m_pSurface);
}

//-----------------------------------------------------------------------------
void AdPlayer::Update(SDL_Event* sdlEvent) {
	switch(sdlEvent->type) {
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_UP:    bUp    = true; break;
				case SDLK_DOWN:  bDown  = true; break;
				case SDLK_LEFT:  bLeft  = true; break;
				case SDLK_RIGHT: bRight = true; break;
			}
		} break;

		case SDL_KEYUP: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_UP:    bUp    = false; break;
				case SDLK_DOWN:  bDown  = false; break;
				case SDLK_LEFT:  bLeft  = false; break;
				case SDLK_RIGHT: bRight = false; break;
			}
		} break;
	}

	if(m_pCurLvl == NULL) return;
	if(bUp)         m_pCurLvl->m_pntPos.y+=2;
	else if(bDown)  m_pCurLvl->m_pntPos.y-=2;
	else if(bLeft)  m_pCurLvl->m_pntPos.x+=2;
	else if(bRight) m_pCurLvl->m_pntPos.x-=2;
}

//-----------------------------------------------------------------------------
void AdPlayer::Render(void) {
	SDL_Point pnt = {AdBase::GetWidth()/2-48/2, AdBase::GetHeight()/2-48/2};
	AdScreen::DrawSprite(pnt, m_pSurface);
}
