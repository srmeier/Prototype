#ifndef __ADLEVEL_H_
#define __ADLEVEL_H_

#include "AdBase.h"
#include "AdTiledManager.h"

//-----------------------------------------------------------------------------
class AdLevel: public AdBase {
protected:
	SDL_Surface** m_pLayers;
	char          m_pName[NAME_LENGTH];

	// TODO: rename this
	AdTiledManager tiledMng;

public:
	SDL_Point m_pntPos;

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
