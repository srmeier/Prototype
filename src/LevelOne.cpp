/*
*/

#include "Player.h"
#include "AdInput.h"

#include "nodes/L1N1.h"
#include "levels/LevelOne.h"

//-----------------------------------------------------------------------------
LevelOne::LevelOne(void) {
	m_iNTotX = 1; m_iNTotY = 1;

	m_pNodes = (AdWorldNode***) calloc(m_iNTotY, sizeof(AdWorldNode**));
	for(int j=0; j<m_iNTotY; ++j)
		m_pNodes[j] = (AdWorldNode**) calloc(m_iNTotX, sizeof(AdWorldNode*));

	m_pNodes[0][0] = new L1N1();
}

//-----------------------------------------------------------------------------
LevelOne::~LevelOne(void) {
	delete m_pNodes[0][0];

	free(m_pNodes);
}

//-----------------------------------------------------------------------------
void LevelOne::Init(void) {
	m_iNX = 0; m_iNY = 0;

	m_pNodes[m_iNY][m_iNX]->Init();
}

//-----------------------------------------------------------------------------
void LevelOne::Quit(void) {
	m_pNodes[m_iNY][m_iNX]->Quit();
}

//-----------------------------------------------------------------------------
void LevelOne::Update(class AdInput* pInput) {
	m_pNodes[m_iNY][m_iNX]->Update(pInput);
}

//-----------------------------------------------------------------------------
void LevelOne::Render(void) {
	SDL_Point pnt = {0, 56};
	m_pNodes[m_iNY][m_iNX]->Render(pnt);
}
