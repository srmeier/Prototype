#ifndef __ADWORLDNODE_H_
#define __ADWORLDNODE_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdWorldNode {
protected:
	int          m_pIndices[23*40];
	SDL_Surface* m_pBackground;
	SDL_Surface* m_pForeground;

public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(void);
	virtual void Render(SDL_Point pnt);

public:
	AdWorldNode(void);
	virtual ~AdWorldNode(void);
};

#endif
