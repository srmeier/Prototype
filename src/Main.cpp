/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- 

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- 
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(8*40, 8*30, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	// TESTING
	SDL_Surface* spr  = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	SDL_Surface* spr0 = AdSpriteManager::BuildSprite("1234567890!#$%&*()-+=[]\"\'<>.?/");

	int inds[] = {
		 64*6+1,  64*6+2,  64*6+3,  64*6+4,  64*6+5,  64*6+6,
		 64*7+1,  64*7+2,  64*7+3,  64*7+4,  64*7+5,  64*7+6,
		 64*8+1,  64*8+2,  64*8+3,  64*8+4,  64*8+5,  64*8+6,
		 64*9+1,  64*9+2,  64*9+3,  64*9+4,  64*9+5,  64*9+6,
		64*10+1, 64*10+2, 64*10+3, 64*10+4, 64*10+5, 64*10+6,
		64*11+1, 64*11+2, 64*11+3, 64*11+4, 64*11+5, 64*11+6,

		64*12+1, 64*12+2, 64*12+3, 64*12+4, 64*12+5, 64*12+6,
		64*13+1, 64*13+2, 64*13+3, 64*13+4, 64*13+5, 64*13+6,
		64*14+1, 64*14+2, 64*14+3, 64*14+4, 64*14+5, 64*14+6,
		64*15+1, 64*15+2, 64*15+3, 64*15+4, 64*15+5, 64*15+6,
		64*16+1, 64*16+2, 64*16+3, 64*16+4, 64*16+5, 64*16+6,
		64*17+1, 64*17+2, 64*17+3, 64*17+4, 64*17+5, 64*17+6,

		64*18+1, 64*18+2, 64*18+3, 64*18+4, 64*18+5, 64*18+6,
		64*19+1, 64*19+2, 64*19+3, 64*19+4, 64*19+5, 64*19+6,
		64*20+1, 64*20+2, 64*20+3, 64*20+4, 64*20+5, 64*20+6,
		64*21+1, 64*21+2, 64*21+3, 64*21+4, 64*21+5, 64*21+6,
		64*22+1, 64*22+2, 64*22+3, 64*22+4, 64*22+5, 64*22+6,
		64*23+1, 64*23+2, 64*23+3, 64*23+4, 64*23+5, 64*23+6
	};

	SDL_Surface* spr1 = AdSpriteManager::BuildSprite(6, 18, inds);

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		AdScreen::Clear();

		// TESTING
		SDL_Point pnt = {0, 0};
		AdScreen::DrawSprite(pnt, spr);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, spr0);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, spr1);

		AdBase::Update(&sdlEvent);
		AdBase::Render();

		AdScreen::Present();
	}

	// TESTING
	SDL_FreeSurface(spr);
	SDL_FreeSurface(spr0);
	SDL_FreeSurface(spr1);

	AdBase::Quit();

	return 0;
}
