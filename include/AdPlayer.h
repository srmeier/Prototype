#ifndef __ADPLAYER_H_
#define __ADPLAYER_H_

//-----------------------------------------------------------------------------
class AdPlayer {
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
	AdPlayer(void);
	~AdPlayer(void);
};

#endif
