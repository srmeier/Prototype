#ifndef __ADPROCEDURE_H_
#define __ADPROCEDURE_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdProcedure: AdBase {
public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(SDL_Event* sdlEvent);
	virtual void Render(void);

public:
	AdProcedure(void);
	virtual ~AdProcedure(void);
};

#endif
