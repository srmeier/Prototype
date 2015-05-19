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
class LevelOne:public AdOverworld {
public:
	void Init(void);
	void Quit(void);

public:
	void Update(void);
	void Render(void);
};

//-----------------------------------------------------------------------------
class AdWorldNode {
protected:
	int          m_pIndices[23*40];
	SDL_Surface* m_pBackground;
	SDL_Surface* m_pForeground;

public:
	void Init(int pIndices[23*40]);
	void Quit(void);

public:
	void Update(void);
	void Render(SDL_Point pnt);
};

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(320, 240, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.");
		return -1;
	}

	/* === */

	AdBase::SetActiveProc(AdBase::s_pGameProc);

	/* === */

	/* AdWorldNode */

	int pIndices1[23*40];

	int i, j;
	for(j=0; j<23; j++) {
		for(i=0; i<40; i++) {
			pIndices1[40*j+i] = 0x181;
		}
	}

	SDL_Surface* pSprite1 = AdSpriteManager::BuildSprite(
		40, 23, pIndices1
	);

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
		AdScreen::DrawSprite(pntLoc1, pSprite1);

		/* === */

		AdScreen::Render();
	}

	/* === */

	SDL_FreeSurface(pSprite1);
	pSprite1 = NULL;

	/* === */

	AdBase::Quit();

	return 0;
}
