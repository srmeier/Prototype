/*
*/

#include "Player.h"
#include "AdInput.h"

#include "nodes/L1N1.h"
#include "levels/LevelOne.h"

//-----------------------------------------------------------------------------
LevelOne::LevelOne(void) {
	m_pNodes = (AdWorldNode**) calloc(1, sizeof(AdWorldNode*));

	m_pNodes[0] = new L1N1();
}

//-----------------------------------------------------------------------------
LevelOne::~LevelOne(void) {
	delete m_pNodes[0];

	free(m_pNodes);
}

//-----------------------------------------------------------------------------
void LevelOne::Init(void) {
	m_pNodes[0]->Init();
}

//-----------------------------------------------------------------------------
void LevelOne::Quit(void) {
	m_pNodes[0]->Quit();
}

//-----------------------------------------------------------------------------
void LevelOne::Update(class AdInput* pInput) {
	m_pNodes[0]->Update(pInput);
}

//-----------------------------------------------------------------------------
void LevelOne::Render(void) {
	SDL_Point pnt = {0, 56};
	m_pNodes[0]->Render(pnt);
}
