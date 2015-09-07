/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- need an relatively abstract way of handling collisions at the node level
	- get a basic level with collision up and running and then form the
		abstraction based off that level
- maybe the point for drawing the world node should be set in the world node
	class since it doesn't really need to change ever
	- since the level/world handles the GUI and the offset depends on the GUI
		I'll leave it the way it is for now
- the nodeX and nodeY integers may need to be handled a special way if the
	player will be entering from multiple pathways

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- each level is it's own overworld. if you have a level above ground and
	another below ground each would have its own class inheriting from
	AdOverworld
- the game procedure can take care of all user input. this is because all other
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
	if(AdBase::Init(320, 240, 3) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	AdBase::SetActiveProc(AdBase::s_pGameProc);

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		static bool isDown = false;
		if(sdlEvent.type == SDL_KEYDOWN && !isDown) {
			isDown = true;
			Player::DamageHealth();
			Player::DamageHunger();
			Player::DamageThirst();
		} else if(sdlEvent.type == SDL_KEYUP && isDown) {
			isDown = false;
		}

		AdScreen::Clear();

		AdBase::Update(&sdlEvent);
		AdBase::Render();

		AdScreen::Present();
	}

	AdBase::Quit();

	return 0;
}
