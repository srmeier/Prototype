#ifndef __ADMOVEABLE_H_
#define __ADMOVEABLE_H_

#include "AdEntity.h"

//-----------------------------------------------------------------------------
class AdMoveable: public AdEntity {
public:
	int  m_iI;
	int  m_iJ;

	int  m_iMoveframe;
	int  m_iMovedirec;

	bool m_bMoving;
	bool m_bFreeToMove;

	int  m_iForcedirec;
	bool m_bForceMove;

	bool m_bUp;
	bool m_bDown;
	bool m_bLeft;
	bool m_bRight;

	bool m_bUpCheck;
	bool m_bDownCheck;
	bool m_bLeftCheck;
	bool m_bRightCheck;

protected:
	virtual void Load(duk_context* pCtx);

public:
	virtual void Update(class AdLevel* pLvl);
	virtual void Render(class AdLevel* pLvl);

public:
	AdMoveable(void);
	~AdMoveable(void);
};

#endif
