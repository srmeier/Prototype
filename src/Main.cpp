/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- different color font?

- the level should control the cursor
	- this is hard to do because the map itself won't hold the dimensions of
		the cursor surface
	- could code the cursors into the level object by hand

- need to consider the statements below and design a simple system for them
- need to have the "EVENT!" show up at the same time when the cursor is over
	the entity. meaning that the entity will likely need a preTrigger? or
	something. clicking on this will most likely require some sort of
	pathfinding to get the player over to the entity and once the player gets
	there it will auto-trigger the main trigger or something
- need to add the "clicked" hand and also the up, down, left, right arrows for
	moving "screens"
- need a typical "arrow" cursor for when messages are being sent to player

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
	delete lvl;
	//

	AdBase::Quit();

	return 0;
}
