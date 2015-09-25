/*
*/

#include "AdLevel.h"
#include "AdScreen.h"
#include "AdEntity.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdLevel::AdLevel(void) {
	memset(m_pName, 0x00, 0xFF);
	memset(&m_pntPos, 0x00, sizeof(SDL_Point));

	m_iWidth   = 0;
	m_iHeight  = 0;
	m_nLayers  = 0;
	m_pIndices = NULL;
	m_pLayers  = NULL;
	m_pPlayer  = NULL;
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
		char pName[0xFF];
		strcpy(pName, m_pName);

		Unload(); Load(pName);

	} else if(!bReload) bChkReload = false;

	if(m_pPlayer == NULL) return;
	m_pPlayer->Update(sdlEvent);
}

//-----------------------------------------------------------------------------
void AdLevel::Render(void) {
	for(int j=0; j<m_nLayers; ++j) {
		// TEMP
		if(j==2 || j==3) continue;
		if(j > 1) {
			SDL_Point pnt = {0, 0};
			AdScreen::DrawSprite(pnt, m_pLayers[j]);
			continue;
		}
		//

		AdScreen::DrawSprite(m_pntPos, m_pLayers[j]);
	}

	if(m_pPlayer == NULL) return;
	m_pPlayer->Render();

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

	char pFN[FILENAME_MAX];
	sprintf(pFN, "data/maps/%s.json", m_pName);

	/*
	duk_context* ctx = GetJSCtx();

	duk_push_string_file(ctx, pFN);
	duk_json_decode(ctx, -1);

	if(!duk_is_object(ctx, -1)) {
		fprintf(stderr, "NOTE: Failed parse %s.json!\n", m_pName);
		return;
	}
	
	duk_get_prop_string(ctx, -1, "width");
	m_iWidth = duk_to_int(ctx, -1);
	duk_pop(ctx);

	duk_get_prop_string(ctx, -1, "height");
	m_iHeight = duk_to_int(ctx, -1);
	duk_pop(ctx);

	duk_get_prop_string(ctx, -1, "layers");
	
	if(duk_is_array(ctx, -1)) {
		m_nLayers  = duk_get_length(ctx, -1);
		m_pIndices = (int**) calloc(m_nLayers, sizeof(int*));
		m_pLayers  = (SDL_Surface**) calloc(m_nLayers, sizeof(SDL_Surface*));

		for(int j=0; j<m_nLayers; ++j) {
			duk_get_prop_index(ctx, -1, j);

			duk_get_prop_string(ctx, -1, "data");

			if(duk_is_array(ctx, -1)) {
				int size = duk_get_length(ctx, -1);

				if((m_iWidth*m_iHeight) == size) {
					m_pIndices[j] = (int*) malloc(size*sizeof(int));

					for(int i=0; i<size; ++i) {
						duk_get_prop_index(ctx, -1, i);
						m_pIndices[j][i] = duk_to_int(ctx, -1);
						duk_pop(ctx);
					}

					m_pLayers[j] = AdSpriteManager::BuildSprite(
						m_iWidth, m_iHeight, m_pIndices[j]
					);
				} else {
					fprintf(stderr,
						"NOTE: Failed to match layer size with map size for level %s!\n",
						m_pName
					);
				}
			}

			duk_pop_2(ctx);
		}
	}

	duk_pop_2(ctx);
	*/
}

//-----------------------------------------------------------------------------
void AdLevel::Unload(void) {
	/*
	if(m_pIndices && m_nLayers>0) {
		for(int j=0; j<m_nLayers; ++j) {
			if(m_pIndices[j] == NULL) continue;

			free(m_pIndices[j]);
			m_pIndices[j] = NULL;

			if(m_pLayers && m_pLayers[j]) {
				SDL_FreeSurface(m_pLayers[j]);
				m_pLayers[j] = NULL;
			}
		}

		free(m_pIndices);
		m_pIndices = NULL;

		if(m_pLayers) {
			free(m_pLayers);
			m_pLayers = NULL;
		}
	}

	memset(m_pName, 0x00, 0xFF);
	memset(&m_pntPos, 0x00, sizeof(SDL_Point));

	m_iWidth   = 0;
	m_iHeight  = 0;
	m_nLayers  = 0;
	*/
}

//-----------------------------------------------------------------------------
void AdLevel::SetPlayer(class AdEntity* pPlayer) {
	m_pPlayer = pPlayer;
	if(pPlayer) m_pPlayer->m_pCurLvl = this;
}
