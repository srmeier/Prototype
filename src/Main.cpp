/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- work on the door entity

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- 
*/

#include "AdBase.h"
#include "AdLevel.h"
#include "AdScreen.h"
#include "AdTiledManager.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(8*68, 8*45, 2) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	// TESTING
	int ind[] = {
		64*1+40, 64*1+41, 64*1+42, 64*1+43,
		64*2+40, 64*2+41, 64*2+42, 64*2+43,
		64*3+40, 64*3+41, 64*3+42, 64*3+43,
		64*4+40, 64*4+41, 64*4+42, 64*4+43,
	};

	SDL_Surface* pCursorSurf = AdSpriteManager::BuildSprite(4, 4, ind);
	SDL_Cursor* pCursor = SDL_CreateColorCursor(pCursorSurf, 0, 0);
	SDL_SetCursor(pCursor);

	AdLevel* lvl = new AdLevel();
	lvl->Load("testing");
	//

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		AdScreen::Clear();

		// TESTING
		lvl->Update(&sdlEvent);
		lvl->Render();
		//

		AdScreen::Present();
	}

	// TESTING
	SDL_FreeCursor(pCursor);
	SDL_FreeSurface(pCursorSurf);
	//

	AdBase::Quit();

	return 0;
}
