/*
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdGameProc.h"
#include "AdProcedure.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
SDL_Window*        AdBase::s_pWindow;
SDL_Renderer*      AdBase::s_pRenderer;

int                AdBase::s_iWinScale;
int                AdBase::s_iWinWidth;
int                AdBase::s_iWinHeight;
class AdProcedure* AdBase::s_pActiveProc;

class AdProcedure* AdBase::s_pGameProc;

//-----------------------------------------------------------------------------
bool AdBase::Init(int iWidth, int iHeight, int iScale) {
	s_iWinScale  = iScale;
	s_iWinWidth  = iWidth;
	s_iWinHeight = iHeight;

	/* === */

	srand((unsigned int) time(NULL));

	/* === */

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, SDL_GetError());
		return false;
	}

	/* === */

	if(TTF_Init() == -1) {
		fprintf(stderr, TTF_GetError());
		return false;
	}

	/* === */

	int flags = IMG_INIT_JPG|IMG_INIT_PNG;

	if((IMG_Init(flags)&flags) != flags) {
		fprintf(stderr, IMG_GetError());
		return false;
	}

	/* === */

	flags = MIX_INIT_OGG|MIX_INIT_MP3;

	if((Mix_Init(flags)&flags) != flags) {
		fprintf(stderr, Mix_GetError());
		return false;
	}

	/* === */

	if(SDLNet_Init() == -1) {
		fprintf(stderr, SDLNet_GetError());
		return false;
	}

	/* === */

	s_pWindow = SDL_CreateWindow(
		"Prototype",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		s_iWinScale*s_iWinWidth,
		s_iWinScale*s_iWinHeight,
		0
	);

	if(s_pWindow == NULL) {
		fprintf(stderr, SDL_GetError());
		return false;
	}

	/* === */

	s_pRenderer = SDL_CreateRenderer(
		s_pWindow, -1,
		SDL_RENDERER_ACCELERATED|
		SDL_RENDERER_PRESENTVSYNC
	);

	if(s_pRenderer == NULL) {
		fprintf(stderr, SDL_GetError());
		return false;
	}

	/* === */

	if(AdScreen::Init() == false) return false;
	if(AdSpriteManager::Init(8, 8, "data/spritesheet.bmp") == false) return false;

	/* === */

	s_pGameProc = new AdGameProc();

	return true;
}

//-----------------------------------------------------------------------------
void AdBase::Quit(void) {
	if(s_pActiveProc) s_pActiveProc->Quit();

	delete s_pGameProc;

	/* === */

	AdSpriteManager::Quit();
	AdScreen::Quit();

	/* === */

	SDL_DestroyRenderer(s_pRenderer);
	s_pRenderer = NULL;

	/* === */

	SDL_DestroyWindow(s_pWindow);
	s_pWindow = NULL;

	/* === */

	SDLNet_Quit();

	/* === */

	Mix_Quit();

	/* === */

	IMG_Quit();

	/* === */

	TTF_Quit();

	/* === */

	SDL_Quit();
}

//-----------------------------------------------------------------------------
void AdBase::Update(void) {
	if(s_pActiveProc) s_pActiveProc->Update();
}

//-----------------------------------------------------------------------------
void AdBase::Render(void) {
	if(s_pActiveProc) s_pActiveProc->Render();
}

//-----------------------------------------------------------------------------
void AdBase::SetActiveProc(class AdProcedure* pProc) {
	if(pProc == NULL) return;
	else pProc->Init();

	if(s_pActiveProc) s_pActiveProc->Quit();

	s_pActiveProc = pProc;
}