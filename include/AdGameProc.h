#ifndef __ADGAMEPROC_H_
#define __ADGAMEPROC_H_

#include "AdBase.h"
#include "AdProcedure.h"

//-----------------------------------------------------------------------------
class AdGameProc: public AdProcedure {
protected:
	SDL_Surface*       m_pTopBarGUI;
	class AdOverworld* m_pOverworld;

public:
	void Init(void);
	void Quit(void);

public:
	void Update(SDL_Event* sdlEvent);
	void Render(void);

public:
	AdGameProc(void);
	virtual ~AdGameProc(void);
};

#endif
