/*
*/

#include "AdInput.h"
#include "AdProcedure.h"

//-----------------------------------------------------------------------------
AdProcedure::AdProcedure(void) {
	m_pInput = new AdInput();
}

//-----------------------------------------------------------------------------
AdProcedure::~AdProcedure(void) {
	delete m_pInput;
}

//-----------------------------------------------------------------------------
void AdProcedure::Init(void) {}

//-----------------------------------------------------------------------------
void AdProcedure::Quit(void) {}

//-----------------------------------------------------------------------------
void AdProcedure::Update(SDL_Event* sdlEvent) {
	switch(sdlEvent->type) {
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_ESCAPE: exit(0);                       break;
				case SDLK_UP:     m_pInput->m_bUp = SDL_TRUE;    break;
				case SDLK_DOWN:   m_pInput->m_bDown = SDL_TRUE;  break;
				case SDLK_LEFT:   m_pInput->m_bLeft = SDL_TRUE;  break;
				case SDLK_RIGHT:  m_pInput->m_bRight = SDL_TRUE; break;
			}
		} break;
		
		case SDL_KEYUP: {
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_UP:    m_pInput->m_bUp = SDL_FALSE;    break;
				case SDLK_DOWN:  m_pInput->m_bDown = SDL_FALSE;  break;
				case SDLK_LEFT:  m_pInput->m_bLeft = SDL_FALSE;  break;
				case SDLK_RIGHT: m_pInput->m_bRight = SDL_FALSE; break;
			}
		} break;
	}
}

//-----------------------------------------------------------------------------
void AdProcedure::Render(void) {}
