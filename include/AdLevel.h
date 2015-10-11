#ifndef __ADLEVEL_H_
#define __ADLEVEL_H_

#include "AdBase.h"
#include "AdPlayer.h"
#include "AdTiledManager.h"

//-----------------------------------------------------------------------------
class AdLevel {
protected:
	AdTiledManager m_objMap;
	SDL_Surface**  m_pLayers;
	AdPlayer*      m_pPlayer;
	char           m_pName[NAME_LENGTH];

public:
	AdMoveable*     GetPlayer(void) {return m_pPlayer;}
	AdTiledManager* GetTiledMap(void) {return &m_objMap;}

public:
	void Update(SDL_Event* sdlEvent);
	void Render(void);

public:
	void Load(const char* pName);
	void Unload(void);

public:
	AdLevel(void);
	~AdLevel(void);
};

#endif
