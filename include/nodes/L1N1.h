#ifndef __L1N1_H_
#define __L1N1_H_

#include "AdWorldNode.h"

//-----------------------------------------------------------------------------
class L1N1:public AdWorldNode {
public:
	void Init(void);
	void Quit(void);

public:
	void Update(class AdInput* pInput);
	void Render(SDL_Point pnt);

public:
	L1N1(void);
	virtual ~L1N1(void);
};

#endif
