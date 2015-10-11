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

	// TEMP
	_x = -48, _y = -48;
	_i = (int) floor(-_x/8.0f);
	_j = (int) floor(-_y/8.0f);
	_moveframe = 0;
	_movedirec = 1;
	_moving = false;
	_tomove = true;
	_fmovedirec = 1;
	_forceMove = false;

	_a      = false;
	_b      = false;
	_up     = false;
	_down   = false;
	_left   = false;
	_right  = false;

	_ac     = false;
	_bc     = false;
	_upc    = false;
	_downc  = false;
	_leftc  = false;
	_rightc = false;
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

	// TEMP: just working out the player movement
	if(!_forceMove) {
		if(!_up) _upc = false;
		if(!_down) _downc = false;
		if(!_left) _leftc = false;
		if(!_right) _rightc = false;
		if(!_a) _ac = false;
		if(!_b) _bc = false;

		switch(sdlEvent->type) {
			case SDL_KEYDOWN: {
				switch(sdlEvent->key.keysym.sym) {
					case SDLK_UP: _up = true; break;
					case SDLK_DOWN: _down = true; break;
					case SDLK_LEFT: _left = true; break;
					case SDLK_RIGHT: _right = true; break;
					case SDLK_LCTRL: _a = true; break;
					case SDLK_LALT: _b = true; break;
				}
			} break;

			case SDL_KEYUP: {
				switch(sdlEvent->key.keysym.sym) {
					case SDLK_UP: _up = false; break;
					case SDLK_DOWN: _down = false; break;
					case SDLK_LEFT: _left = false; break;
					case SDLK_RIGHT: _right = false; break;
					case SDLK_LCTRL: _a = false; break;
					case SDLK_LALT: _b = false; break;
				}
			} break;
		}
	}

	if(!_tomove && !_moving) return;

	_i = (int) floor(-_x/8.0f);
	_j = (int) floor(-_y/8.0f);

	if(_moveframe>0) _moveframe--;
	else if(_moving) {
		_moving = false;
	}

	if(!_moving) {
		if(_forceMove) {
			if(_fmovedirec==0) {
				_moving = true;
				_forceMove = false;
				_moveframe = 8-1;
				_movedirec = 0;
			} else if(_fmovedirec == 1) {
				_moving = true;
				_forceMove = false;
				_moveframe = 8-1;
				_movedirec = 1;
			} else if(_fmovedirec == 2) {
				_moving = true;
				_forceMove = false;
				_moveframe = 8-1;
				_movedirec = 2;
			} else if(_fmovedirec == 3) {
				_moving = true;
				_forceMove = false;
				_moveframe = 8-1;
				_movedirec = 3;
			}
		} else {
			if(_up &&
				m_objMap.GetTile(COLLISION_LAYER, _i+0, _j-1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+1, _j-1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+2, _j-1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+3, _j-1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+4, _j-1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+5, _j-1)==0
			) {
				_moving = true;
				_moveframe = 8-1;
				_movedirec = 1;
			} else if(_down &&
				m_objMap.GetTile(COLLISION_LAYER, _i+0, _j+6)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+1, _j+6)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+2, _j+6)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+3, _j+6)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+4, _j+6)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+5, _j+6)==0
			) {
				_moving = true;
				_moveframe = 8-1;
				_movedirec = 0;
			} else if(_left &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+0)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+2)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+3)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+4)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i-1, _j+5)==0
			) {
				_moving = true;
				_moveframe = 8-1;
				_movedirec = 3;
			} else if(_right &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+0)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+1)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+2)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+3)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+4)==0 &&
				m_objMap.GetTile(COLLISION_LAYER, _i+6, _j+5)==0
			) {
				_moving = true;
				_moveframe = 8-1;
				_movedirec = 2;
			}
		}
	}

	if(_moving) {
		switch(_movedirec) {
			case 0: _y--; break;
			case 1: _y++; break;
			case 2: _x--; break;
			case 3: _x++; break;
		}
	}
}

//-----------------------------------------------------------------------------
void AdLevel::Render(void) {
	for(int j=0; j<m_objMap.N(); ++j) {
		/*
		// TEMP
		if(j==2 || j==3) continue;
		if(j > 1) {
			SDL_Point pnt = {0, 0};
			AdScreen::DrawSprite(pnt, m_pLayers[j]);
			continue;
		}
		//
		*/
		if(j > 2) continue;

		// TEMP: draw a rectangle where _i, _j is
		//SDL_Rect rec = {8*_i, 8*_j, 8*6, 8};
		//SDL_FillRect(m_pLayers[j], &rec, 0xFF000000);

		//SDL_Point pntLvl = {0, 0};
		SDL_Point pntLvl = {AdBase::GetWidth()/2-48/2+_x, AdBase::GetHeight()/2-48/2+_y};
		AdScreen::DrawSprite(pntLvl, m_pLayers[j]);

		if(j == 1) {
			int ind[] = {
				64*12+37, 64*12+38, 64*12+39, 64*12+40, 64*12+41, 64*12+42,
				64*13+37, 64*13+38, 64*13+39, 64*13+40, 64*13+41, 64*13+42,
				64*14+37, 64*14+38, 64*14+39, 64*14+40, 64*14+41, 64*14+42,
				64*15+37, 64*15+38, 64*15+39, 64*15+40, 64*15+41, 64*15+42,
				64*16+37, 64*16+38, 64*16+39, 64*16+40, 64*16+41, 64*16+42,
				64*17+37, 64*17+38, 64*17+39, 64*17+40, 64*17+41, 64*17+42,
			};

			SDL_Surface* pPlayer = AdSpriteManager::BuildSprite(6, 6, ind);

			SDL_Point pnt = {AdBase::GetWidth()/2-48/2, AdBase::GetHeight()/2-48/2};
			AdScreen::DrawSprite(pnt, pPlayer);

			SDL_FreeSurface(pPlayer);
		}
	}

	/*
	if( m_objMap.GetTile(EVENT_LAYER, _i+0, _j+0)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+0)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+0)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+0)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+0)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+0)!=0 ||

		m_objMap.GetTile(EVENT_LAYER, _i+0, _j+1)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+1)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+1)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+1)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+1)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+1)!=0 ||

		m_objMap.GetTile(EVENT_LAYER, _i+0, _j+2)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+2)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+2)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+2)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+2)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+2)!=0 ||

		m_objMap.GetTile(EVENT_LAYER, _i+0, _j+3)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+3)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+3)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+3)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+3)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+3)!=0 ||

		m_objMap.GetTile(EVENT_LAYER, _i+0, _j+4)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+4)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+4)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+4)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+4)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+4)!=0 ||

		m_objMap.GetTile(EVENT_LAYER, _i+0, _j+5)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+1, _j+5)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+2, _j+5)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+3, _j+5)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+4, _j+5)!=0 ||
		m_objMap.GetTile(EVENT_LAYER, _i+5, _j+5)!=0
	) {
		// TESTING
		SDL_Surface* spr  = AdSpriteManager::BuildSprite("EVENT!!");

		SDL_Point pnt = {8*4, 8*32};
		AdScreen::DrawSprite(pnt, spr);

		SDL_FreeSurface(spr);
	}
	*/

	/*
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
	*/
}

//-----------------------------------------------------------------------------
void AdLevel::Load(const char* pName) {
	Unload();

	strcpy(m_pName, pName);

	m_objMap.Load(pName);

	m_pLayers = (SDL_Surface**) malloc(m_objMap.N()*sizeof(SDL_Surface*));

	for(int j=0; j<m_objMap.N(); ++j) {
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
