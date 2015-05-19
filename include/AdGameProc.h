#ifndef __ADGAMEPROC_H_
#define __ADGAMEPROC_H_

#include "AdBase.h"
#include "AdProcedure.h"

//-----------------------------------------------------------------------------
class AdGameProc: public AdProcedure {
protected:
	SDL_Surface* m_pTopBarGUI;

public:
	void Init(void);
	void Quit(void);

public:
	void Update(void);
	void Render(void);

public:
	AdGameProc(void);
	virtual ~AdGameProc(void);
};

#endif
