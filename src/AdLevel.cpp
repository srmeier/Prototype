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
	// NOTE: automatically reload the level when 'r' is pressed
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

	// NOTE: update the player's input
	//if(!m_pPlayer->m_bForceMove) {
		if(!m_pPlayer->m_bUp)    m_pPlayer->m_bUpCheck    = false;
		if(!m_pPlayer->m_bDown)  m_pPlayer->m_bDownCheck  = false;
		if(!m_pPlayer->m_bLeft)  m_pPlayer->m_bLeftCheck  = false;
		if(!m_pPlayer->m_bRight) m_pPlayer->m_bRightCheck = false;

		switch(sdlEvent->type) {
			case SDL_MOUSEMOTION: {
				// NOTE: divide by the window scale
				m_pPlayer->m_iMouseX = sdlEvent->motion.x/AdBase::GetScale();
				m_pPlayer->m_iMouseY = sdlEvent->motion.y/AdBase::GetScale();
			} break;

			case SDL_MOUSEBUTTONDOWN: {
				switch(sdlEvent->button.button) {
					case SDL_BUTTON_LEFT:  m_pPlayer->m_bMouseLeft  = true; break;
					case SDL_BUTTON_RIGHT: m_pPlayer->m_bMouseRight = true; break;
				}
			} break;

			case SDL_MOUSEBUTTONUP: {
				switch(sdlEvent->button.button) {
					case SDL_BUTTON_LEFT:  m_pPlayer->m_bMouseLeft  = false; break;
					case SDL_BUTTON_RIGHT: m_pPlayer->m_bMouseRight = false; break;
				}
			} break;

			case SDL_KEYDOWN: {
				switch(sdlEvent->key.keysym.sym) {
					case SDLK_UP:    m_pPlayer->m_bUp    = true; break;
					case SDLK_DOWN:  m_pPlayer->m_bDown  = true; break;
					case SDLK_LEFT:  m_pPlayer->m_bLeft  = true; break;
					case SDLK_RIGHT: m_pPlayer->m_bRight = true; break;
				}
			} break;

			case SDL_KEYUP: {
				switch(sdlEvent->key.keysym.sym) {
					case SDLK_UP:    m_pPlayer->m_bUp    = false; break;
					case SDLK_DOWN:  m_pPlayer->m_bDown  = false; break;
					case SDLK_LEFT:  m_pPlayer->m_bLeft  = false; break;
					case SDLK_RIGHT: m_pPlayer->m_bRight = false; break;
				}
			} break;
		}
	//}

	// NOTE: update entities
	m_pPlayer->show_move_cursor = true; // TEMP
	SDL_ShowCursor(false);

	for(int e=0; e<m_objMap.nEntities(); ++e) {
		AdEntity* pEnt = m_objMap.GetEntity(e);
		pEnt->Update(this);

		// TEMP
		if(
			m_pPlayer->m_iMouseX<(pEnt->m_recTrigger.x+pEnt->m_recTrigger.w) &&
			m_pPlayer->m_iMouseX>pEnt->m_recTrigger.x &&
			m_pPlayer->m_iMouseY<(pEnt->m_recTrigger.y+pEnt->m_recTrigger.h) &&
			m_pPlayer->m_iMouseY>pEnt->m_recTrigger.y
		) {
			m_pPlayer->show_move_cursor = false;
			SDL_ShowCursor(true);
		}
	}
}

//-----------------------------------------------------------------------------
void AdLevel::Render(void) {
	for(int j=0; j<m_objMap.nLayers(); ++j) {
		if(j == COLLISION_LAYER) continue;

		SDL_Point pntLvl = {
			0, //AdBase::GetWidth()/2-48/2+m_pPlayer->m_recTrigger.x,
			0  //AdBase::GetHeight()/2-48/2+m_pPlayer->m_recTrigger.y
		};

		AdScreen::DrawSprite(pntLvl, m_pLayers[j]);

		if(j == PLAYER_DRAW_LAYER) {
			// NOTE: render entities
			for(int e=0; e<m_objMap.nEntities(); ++e) {
				if(m_pPlayer == m_objMap.GetEntity(e)) continue;
				m_objMap.GetEntity(e)->Render(this);
			}

			m_pPlayer->Render(this);
		}
	}
}

//-----------------------------------------------------------------------------
void AdLevel::Load(const char* pName) {
	Unload();

	strcpy(m_pName, pName);

	m_objMap.Load(pName);

	// NOTE: get the moveable entity to follow
	for(int e=0; e<m_objMap.nEntities(); ++e) {
		AdEntity* pEnt = m_objMap.GetEntity(e);

		if(!strcmp(pEnt->GetType(), "NPC-PLAYER")) {
			m_pPlayer = (AdPlayer*) pEnt;
		}
	}

	// NOTE: create an SDL_Surface for each map layer
	m_pLayers = (SDL_Surface**) malloc(m_objMap.nLayers()*sizeof(SDL_Surface*));

	for(int j=0; j<m_objMap.nLayers(); ++j) {
		if(m_objMap.GetLayer(j)) {
			m_pLayers[j] = AdSpriteManager::BuildSprite(
				m_objMap.Width(), m_objMap.Height(), m_objMap.GetLayer(j)
			);
		} else {
			m_pLayers[j] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
void AdLevel::Unload(void) {
	m_pPlayer = NULL;

	for(int j=0; j<m_objMap.nLayers(); ++j) {
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
