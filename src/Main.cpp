/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- 

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- the game procedure can take care of all user input. This is because all other
	types of procedures which do not have overworlds and node will need to
	manage user input directly.
- the node controls player updating and collision. this also allows a node to
	prevent player movement during a "cutscene"
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdProcedure.h"
#include "AdSpriteManager.h"

#include "Player.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(320, 240, 2) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	/* === */

	AdBase::SetActiveProc(AdBase::s_pGameProc);

	/* === */

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		static bool isDown = false;
		if(sdlEvent.type == SDL_KEYDOWN && !isDown) {
			isDown = true;
			Player::DamageHealth();
			Player::DamageHunger();
			Player::DamageThirst();
		}

		if(sdlEvent.type == SDL_KEYUP && isDown) {
			isDown = false;
		}

		/* === */

		AdScreen::Clear();

		/* === */

		AdBase::Update(&sdlEvent);
		AdBase::Render();

		/* === */

		AdScreen::Present();
	}	

	/* === */

	AdBase::Quit();

	return 0;
}
