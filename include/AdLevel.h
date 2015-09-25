#ifndef __ADLEVEL_H_
#define __ADLEVEL_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdLevel: public AdBase {
protected:
	int             m_iWidth;
	int             m_iHeight;
	int             m_nLayers;
	SDL_Surface**   m_pLayers;
	int**           m_pIndices;
	char            m_pName[0xFF];
	class AdEntity* m_pPlayer;

public:
	SDL_Point m_pntPos;

public:
	void Update(SDL_Event* sdlEvent);
	void Render(void);

public:
	void Load(const char* pName);
	void Unload(void);
	void SetPlayer(class AdEntity* pPlayer);

public:
	AdLevel(void);
	~AdLevel(void);
};

#endif
