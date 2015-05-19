#ifndef __ADOVERWORLD_H_
#define __ADOVERWORLD_H_

//-----------------------------------------------------------------------------
class AdOverworld {
protected:
	int                 m_iNodeX;
	int                 m_iNodeY;
	class AdWorldNode** m_pNodes;

public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	AdOverworld(void);
	virtual ~AdOverworld(void);
};

#endif
