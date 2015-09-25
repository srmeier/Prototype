/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- need to abstract the duktape/tiled piece so I can use it for simply grabing
	multiple layers and use them for either background/foreground or for
	multiple frames in an animation

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
	AdTiledManager tiledMng;
	tiledMng.Load("testing");

	printf("%d %d %d\n", tiledMng.N(), tiledMng.Width(), tiledMng.Height());

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

	AdBase::Quit();

	return 0;
}
