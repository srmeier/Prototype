/*
*/

#include "Player.h"
#include "AdScreen.h"
#include "AdWorldNode.h"

//-----------------------------------------------------------------------------
AdWorldNode::AdWorldNode(void) {
	m_pBackground = NULL;
	m_pForeground = NULL;

	memset(m_pIndices, 0x00, 23*40*sizeof(int));
}

//-----------------------------------------------------------------------------
AdWorldNode::~AdWorldNode(void) {
	if(m_pBackground) SDL_FreeSurface(m_pBackground);
	if(m_pForeground) SDL_FreeSurface(m_pForeground);
}

//-----------------------------------------------------------------------------
void AdWorldNode::Init(void) {}

//-----------------------------------------------------------------------------
void AdWorldNode::Quit(void) {
	if(m_pBackground) {
		SDL_FreeSurface(m_pBackground);
		m_pBackground = NULL;
	}

	if(m_pForeground) {
		SDL_FreeSurface(m_pForeground);
		m_pForeground = NULL;
	}

	memset(m_pIndices, 0x00, 23*40*sizeof(int));
}

//-----------------------------------------------------------------------------
void AdWorldNode::Update(class AdInput* pInput) {}

//-----------------------------------------------------------------------------
void AdWorldNode::Render(SDL_Point pnt) {
	AdScreen::DrawSprite(pnt, m_pBackground);
	AdScreen::DrawSprite(pnt, m_pForeground);

	Player::Render(pnt);
}
