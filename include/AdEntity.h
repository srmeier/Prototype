#ifndef __ADPLAYER_H_
#define __ADPLAYER_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdEntity: public AdBase {
protected:
	bool bUp, bDown;
	bool bLeft, bRight;
	SDL_Surface* m_pSurface;

public:
	class AdLevel* m_pCurLvl;

public:
	void Update(SDL_Event* sdlEvent);
	void Render(void);

public:
	AdEntity(void);
	~AdEntity(void);
};

#endif
