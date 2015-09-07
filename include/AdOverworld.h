#ifndef __ADOVERWORLD_H_
#define __ADOVERWORLD_H_

//-----------------------------------------------------------------------------
class AdOverworld {
protected:
	int                  m_iNX;
	int                  m_iNY;
	int                  m_iNTotX;
	int                  m_iNTotY;
	class AdWorldNode*** m_pNodes;

public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(class AdInput* pInput);
	virtual void Render(void);

public:
	AdOverworld(void);
	virtual ~AdOverworld(void);
};

#endif
