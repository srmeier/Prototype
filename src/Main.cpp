/*
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdProcedure.h"
#include "AdSpriteManager.h"

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

//-----------------------------------------------------------------------------
class AdWorldNode {
protected:
	int          m_pIndices[23*40];
	SDL_Surface* m_pBackground;
	SDL_Surface* m_pForeground;

public:
	virtual void Init(void);
	virtual void Quit(void);

public:
	virtual void Update(void);
	virtual void Render(SDL_Point pnt);

public:
	AdWorldNode(void);
	virtual ~AdWorldNode(void);
};

//-----------------------------------------------------------------------------
AdWorldNode::AdWorldNode(void) {
	m_pBackground = NULL;
	m_pForeground = NULL;

	memset(m_pIndices, 0x00, 23*40*sizeof(int));
}

//-----------------------------------------------------------------------------
AdWorldNode::~AdWorldNode(void) {
	if(m_pBackground) SDL_FreeSurface(m_pBackground);
	if(m_pForeground) SDL_FreeSurface(m_pForeground);
}

//-----------------------------------------------------------------------------
void AdWorldNode::Init(void) {}

//-----------------------------------------------------------------------------
void AdWorldNode::Quit(void) {
	if(m_pBackground) {
		SDL_FreeSurface(m_pBackground);
		m_pBackground = NULL;
	}

	if(m_pForeground) {
		SDL_FreeSurface(m_pForeground);
		m_pForeground = NULL;
	}

	memset(m_pIndices, 0x00, 23*40*sizeof(int));
}

//-----------------------------------------------------------------------------
void AdWorldNode::Update(void) {}

//-----------------------------------------------------------------------------
void AdWorldNode::Render(SDL_Point pnt) {
	AdScreen::DrawSprite(pnt, m_pBackground);
	AdScreen::DrawSprite(pnt, m_pForeground);
}

//-----------------------------------------------------------------------------
class LevelOne:public AdOverworld {
public:
	void Init(void);
	void Quit(void);

public:
	void Update(void);
	void Render(void);

public:
	LevelOne(void);
	virtual ~LevelOne(void);
};

//-----------------------------------------------------------------------------
class L1N1:public AdWorldNode {
public:
	void Init(void);
	void Quit(void);

public:
	void Update(void);
	void Render(SDL_Point pnt);

public:
	L1N1(void);
	virtual ~L1N1(void);
};

//-----------------------------------------------------------------------------
L1N1::L1N1(void) {}

//-----------------------------------------------------------------------------
L1N1::~L1N1(void) {}

//-----------------------------------------------------------------------------
void L1N1::Init(void) {
	AdWorldNode::Init();

	int i, j;
	for(j=0; j<23; j++) {
		for(i=0; i<40; i++) {
			m_pIndices[40*j+i] = 0x181;
		}
	}

	m_pBackground = AdSpriteManager::BuildSprite(
		40, 23, m_pIndices
	);
}

//-----------------------------------------------------------------------------
void L1N1::Quit(void) {
	AdWorldNode::Quit();
}

//-----------------------------------------------------------------------------
void L1N1::Update(void) {
	AdWorldNode::Update();
}

//-----------------------------------------------------------------------------
void L1N1::Render(SDL_Point pnt) {
	AdWorldNode::Render(pnt);
}

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(320, 240, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.");
		return -1;
	}

	/* === */

	AdBase::SetActiveProc(AdBase::s_pGameProc);

	/* === */

	L1N1* node = new L1N1();
	node->Init();

	/* === */

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		/* === */

		AdScreen::Clear();

		/* === */

		AdBase::Update();
		AdBase::Render();

		SDL_Point pntLoc1 = {0, 56};
		node->Render(pntLoc1);

		/* === */

		AdScreen::Present();
	}

	/* === */

	

	/* === */

	AdBase::Quit();

	return 0;
}
