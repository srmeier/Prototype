#ifndef __LEVELONE_H_
#define __LEVELONE_H_

#include "AdOverworld.h"

//-----------------------------------------------------------------------------
class LevelOne:public AdOverworld {
public:
	void Init(void);
	void Quit(void);

public:
	void Update(class AdInput* pInput);
	void Render(void);

public:
	LevelOne(void);
	virtual ~LevelOne(void);
};

#endif
