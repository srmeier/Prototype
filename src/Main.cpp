/*
- need to move the keyboard events out of into a boolean "input" structure type
	thing and pass this structure around to everyone who needs it withing this
	procedure. Perhaps the node should take case of collision and updating the
	player's position
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdProcedure.h"
#include "AdSpriteManager.h"

#include "Player.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(320, 240, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.");
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
