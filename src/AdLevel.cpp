/*
*/

#include "AdLevel.h"
#include "AdScreen.h"
#include "AdEntity.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdLevel::AdLevel(void) {
	m_pLayers = NULL;
	memset(m_pName, 0x00, NAME_LENGTH);
}

//-----------------------------------------------------------------------------
AdLevel::~AdLevel(void) {
	Unload();
}

//-----------------------------------------------------------------------------
void AdLevel::Update(SDL_Event* sdlEvent) {
	static bool bReload = false;
	static bool bChkReload = false;

	switch(sdlEvent->type) {
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_r: bReload = true; break;
			}
		} break;

		case SDL_KEYUP: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_r: bReload = false; break;
			}
		} break;
	}

	if(bReload && !bChkReload) {
		char pName[NAME_LENGTH];
		strcpy(pName, m_pName);

		Unload(); Load(pName);

	} else if(!bReload) bChkReload = false;
}

//-----------------------------------------------------------------------------
void AdLevel::Render(void) {
	for(int j=0; j<m_objMap.N(); ++j) {
		// TEMP
		if(j==2 || j==3) continue;
		if(j > 1) {
			SDL_Point pnt = {0, 0};
			AdScreen::DrawSprite(pnt, m_pLayers[j]);
			continue;
		}
		//

		SDL_Point pntLvl = {0, 0};
		AdScreen::DrawSprite(pntLvl, m_pLayers[j]);
	}

	// TESTING
	SDL_Surface* spr  = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	SDL_Surface* spr0 = AdSpriteManager::BuildSprite("1234567890!#$%&*()-+=[]\"\'<>.?/");

	SDL_Point pnt = {8*4, 8*32};
	AdScreen::DrawSprite(pnt, spr);
	pnt.y += 8;
	AdScreen::DrawSprite(pnt, spr0);

	SDL_FreeSurface(spr);
	SDL_FreeSurface(spr0);
	//
}

//-----------------------------------------------------------------------------
void AdLevel::Load(const char* pName) {
	Unload();

	strcpy(m_pName, pName);

	m_objMap.Load(pName);

	m_pLayers = (SDL_Surface**) malloc(m_objMap.N()*sizeof(SDL_Surface*));

	for(int j=0; j<m_objMap.N(); ++j) {
		m_pLayers[j] = AdSpriteManager::BuildSprite(
			m_objMap.Width(), m_objMap.Height(), m_objMap.GetLayer(j)
		);
	}
}

//-----------------------------------------------------------------------------
void AdLevel::Unload(void) {
	for(int j=0; j<m_objMap.N(); ++j) {
		if(m_pLayers && m_pLayers[j]) {
			SDL_FreeSurface(m_pLayers[j]);
			m_pLayers[j] = NULL;
		}
	}

	if(m_pLayers) {
		free(m_pLayers);
		m_pLayers = NULL;
	}

	memset(m_pName, 0x00, NAME_LENGTH);
}
