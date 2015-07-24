#ifndef __ADINPUT_H_
#define __ADINPUT_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class AdInput {
public:
	SDL_bool m_bUp;
	SDL_bool m_bDown;
	SDL_bool m_bLeft;
	SDL_bool m_bRight;

public:
	AdInput(void);
	virtual ~AdInput(void);
};

#endif
