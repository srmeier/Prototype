#ifndef __ADPLAYER_H_
#define __ADPLAYER_H_

#include "AdMoveable.h"

//-----------------------------------------------------------------------------
class AdPlayer: public AdMoveable {
public:
	int m_iMouseX;
	int m_iMouseY;

protected:
	void Load(duk_context* pCtx);

public:
	void Update(class AdLevel* pLvl);
	void Render(class AdLevel* pLvl);

public:
	AdPlayer(void);
	~AdPlayer(void);
};

#endif